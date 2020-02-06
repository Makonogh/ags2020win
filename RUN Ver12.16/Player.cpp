#include "Player.h"
#include "Scene\GameScene.h"
#include <common/ImgMng.h>
#include <Input/KeyState.h>
#include <_debug\_DebugConOut.h>
#include "Bg.h"

Player::Player()
{
	Init();
}

Player::Player(Vector2Dbl pos, Vector2Dbl size)
{
	_pos = pos;
	_size = size;
	_objID = OBJ_ID::PLAYER;
	PlayerCount = 0;
	aliveCount = 0;
	Init();
}

void Player::Updata(sharedObj& list)
{
	PlayerCount++;
	aliveCount++;
	double moveLane = (LIMIT_DOWN - LIMIT_UP) / 2.0;

	_input->Updata();

	// プレイヤーの移動処理
	auto move = [&](std::weak_ptr<InputState> keyData, INPUT_ID id, Vector2Dbl moveSpeed)	//(入力されたキー,キーデータ,現在のpos,移動速度)
	{
		// リンクが切れていないかの判定(.expired)
		if (!keyData.expired())
		{
			// shared_ptrのオブジェクトを取得(.lock)
			if ((*keyData.lock()).state(id).first)
			{
				// 上の移動制御
				if (_pos.y + moveSpeed.y < LIMIT_UP - 20.0)
				{
					_pos.y = LIMIT_UP;
				}
				// 下の移動制御
				else if (_pos.y + moveSpeed.y > LIMIT_DOWN)
				{
					_pos.y = LIMIT_DOWN;
				}
				else
				{
					_pos.y += moveSpeed.y;
				}
			}
		}
	};

	// 移動可能な状態かの判定
	if (_state == STATE::NORMAL)
	{
		// 上移動
		if ((*_input).state(INPUT_ID::UP).first && !(*_input).state(INPUT_ID::UP).second)
		{
			if (!(*_input).state(INPUT_ID::DOWN).first)
			{
				plSpeed = { 0.0,-moveLane };
				move(_input, INPUT_ID::UP, plSpeed);
			}
		}

		// 下移動
		if ((*_input).state(INPUT_ID::DOWN).first && !(*_input).state(INPUT_ID::DOWN).second)
		{
			plSpeed = { 0.0,moveLane };
			move(_input, INPUT_ID::DOWN, plSpeed);
		}
	}

	// アクションが可能な状態かどうか
	if (_state == STATE::NORMAL)
	{
		// アクション用キーが押下されているか
		if ((*_input).state(INPUT_ID::ACTION).first && !(*_input).state(INPUT_ID::ACTION).second)
		{
			TRACE("アクション\n");
			_animCount = 0;
			_animFrame = 0;
			PlayerCount = -30;
			state(STATE::JUMP);
		}
	}

	_zOrder = static_cast<int>(_pos.y + 1);

	// 転倒時は背景を停止
	if (_state == STATE::FALL)
	{
		lpSceneMng.bgSpeed = 0.0;
	}
	else
	{
		// 生存時間に応じて背景のスピード上昇
		lpSceneMng.bgSpeed = DFBG_SPEED + (aliveCount / 300);
		// 上限設定
		if (lpSceneMng.bgSpeed >= 20.0)
		{
			lpSceneMng.bgSpeed = 20.0;
		}
	}

	if (PlayerCount >= 0)
	{
		state(STATE::NORMAL);
	}
}


Player::~Player()
{
}

Vector2Dbl Player::GetPos(void)
{
	return _pos;
}

Vector2Dbl Player::GetSize(void)
{
	return _size;
}

// プレイヤーのイニシャライズ
void Player::Init(void)
{
	AnimVector data;

	data.reserve(PL_DIV_CNT);
	for (int i = 0; i < PL_DIV_CNT; i++)
	{
		data.emplace_back(IMAGE_ID("ｷｬﾗ")[i], (i + 1) * 2);
	}
	SetAnim(STATE::NORMAL, data);

	data.reserve(PL_DIV_CNT);
	for (int i = 0; i < PL_DIV_CNT; i++)
	{
		data.emplace_back(IMAGE_ID("ｼﾞｬﾝﾌﾟ")[i], (i + 1) * 2);
	}
	SetAnim(STATE::JUMP, data);

	data.reserve(PL_DIV_CNT);
	for (int i = 0; i < PL_DIV_CNT - 1; i++)
	{
		data.emplace_back(IMAGE_ID("転倒")[i], (i + 1) * 2);
	}
	data.emplace_back(IMAGE_ID("転倒")[PL_DIV_CNT - 1], 70);
	SetAnim(STATE::FALL, data);

	_input = std::make_shared<KeyState>();
}
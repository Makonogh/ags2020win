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
	Init();
}

void Player::Updata()
{
	PlayerCount++;
	double moveLane = (LIMIT_DOWN - LIMIT_UP) / 2.0;

	_lane = ((static_cast<int>(_pos.y - 360.0) % 3) + 1);

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

	if ((*_input).state(INPUT_ID::ACTION).first && !(*_input).state(INPUT_ID::ACTION).second)
	{
		TRACE("アクション\n");
		_animCount = 0;
		_animFrame = 0;
		PlayerCount = -75;
		
		state(STATE::JUMP);
	}

	if ((*_input).state(INPUT_ID::DEBUG).first && !(*_input).state(INPUT_ID::DEBUG).second && PlayerCount >= 0)
	{
		TRACE("デバッグ\n");
		_animCount = 0;
		_animFrame = 0;

		state(STATE::FALL);
		PlayerCount = -70;
	}

	if (PlayerCount >= 0)
	{
		state(STATE::NORMAL);
	}

	_zOrder = static_cast<int>(_pos.y + 1);
	/*TRACE("%d\n",lpSceneMng.bgSpeed);*/
	if (_state == STATE::FALL)
	{
		lpSceneMng.bgSpeed = 0;
	}
	else
	{
		switch (PlayerCount)
		{
		case 0:
			lpSceneMng.bgSpeed = DFBG_SPEED;
			break;
		case 180:
			lpSceneMng.bgSpeed = 8;
			break;
		case 360:
			lpSceneMng.bgSpeed = 10;
			break;
		case 540:
			lpSceneMng.bgSpeed = 16;
			break;
		case 800:
			lpSceneMng.bgSpeed = 20;
			break;
		default:
			break;
		}
	}
}


Player::~Player()
{
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
		data.emplace_back(IMAGE_ID("ｷｬﾗ")[i], (i + 1));
	}
	SetAnim(STATE::RUN, data);

	data.reserve(PL_DIV_CNT);
	for (int i = 0; i < PL_DIV_CNT; i++)
	{
		data.emplace_back(IMAGE_ID("ｼﾞｬﾝﾌﾟ")[i], (i + 1) * 5);
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
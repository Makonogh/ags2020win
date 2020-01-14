#include "Player.h"
#include <common/ImgMng.h>
#include <Input/KeyState.h>
#include <_debug\_DebugConOut.h>

Player::Player()
{
	Init();
}

Player::Player(Vector2Dbl pos, Vector2Dbl size)
{
	_pos = pos;
	_size = size;
	_objID = OBJ_ID::PLAYER;
	Init();
}

void Player::Updata()
{
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

	double moveLane = (LIMIT_DOWN - LIMIT_UP) / 2.0;

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
		data.emplace_back(IMAGE_ID("ｷｬﾗ")[i], (i + 1) * 8);
	}
	SetAnim(STATE::NORMAL, data);

	_input = std::make_shared<KeyState>();
}

// プレイヤーと障害物の当たり判定
void Player::isHit(ObsState& state)
{
	int fallTime = 0;
	AnimVector data;
	OBS_TYPE _obsType;

	Vector2Dbl _obsPos = std::get<static_cast<int>(OBS_STATE::VECTOR)>(state);
	Vector2Dbl _obsSize = std::get<static_cast<int>(OBS_STATE::SIZE)>(state);

	for (auto type : _obsType)
	{
		if (_pos.y == _obsPos.y)
		{
			if (abs(_pos.x - _obsPos.x) < (_size.x + _obsSize.x))
			{
				// プレイヤーの状態 == STATE::FALL;
				SetAnim(STATE::FALL, data);
				while (fallTime < 180)
				{
					fallTime++;
				}
				// プレイヤーの状態 == STATE::NORMAL;
				SetAnim(STATE::NORMAL, data);
			}
		}
	}
}

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

	// �v���C���[�̈ړ�����
	auto move = [&](std::weak_ptr<InputState> keyData, INPUT_ID id, Vector2Dbl moveSpeed)	//(���͂��ꂽ�L�[,�L�[�f�[�^,���݂�pos,�ړ����x)
	{
		// �����N���؂�Ă��Ȃ����̔���(.expired)
		if (!keyData.expired())
		{
			// shared_ptr�̃I�u�W�F�N�g���擾(.lock)
			if ((*keyData.lock()).state(id).first)
			{
				// ��̈ړ�����
				if (_pos.y + moveSpeed.y < LIMIT_UP - 20.0)
				{
					_pos.y = LIMIT_UP ;
				}
				// ���̈ړ�����
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

	// ��ړ�
	if ((*_input).state(INPUT_ID::UP).first && !(*_input).state(INPUT_ID::UP).second)
	{
		if (!(*_input).state(INPUT_ID::DOWN).first)
		{
			plSpeed = { 0.0,-moveLane};
			move(_input, INPUT_ID::UP, plSpeed);
		}
	} 

	// ���ړ�
	if ((*_input).state(INPUT_ID::DOWN).first && !(*_input).state(INPUT_ID::DOWN).second)
	{
		plSpeed = { 0.0,moveLane};
		move(_input, INPUT_ID::DOWN, plSpeed);
	}
}


Player::~Player()
{
}

// �v���C���[�̃C�j�V�����C�Y
void Player::Init(void)
{
	AnimVector data;

	data.reserve(1);
	data.emplace_back( IMAGE_ID("���")[0], 8 );
	data.emplace_back( IMAGE_ID("���")[1], 16 );
	data.emplace_back( IMAGE_ID("���")[2], 24 );
	data.emplace_back( IMAGE_ID("���")[3], 32 );
	data.emplace_back( IMAGE_ID("���")[4], 40 );

	SetAnim(STATE::NORMAL, data);

	_input = std::make_shared<KeyState>();
}
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
					_pos.y = LIMIT_UP;
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

	// �ړ��\�ȏ�Ԃ��̔���
	if (_state == STATE::NORMAL)
	{
		// ��ړ�
		if ((*_input).state(INPUT_ID::UP).first && !(*_input).state(INPUT_ID::UP).second)
		{
			if (!(*_input).state(INPUT_ID::DOWN).first)
			{
				plSpeed = { 0.0,-moveLane };
				move(_input, INPUT_ID::UP, plSpeed);
			}
		}

		// ���ړ�
		if ((*_input).state(INPUT_ID::DOWN).first && !(*_input).state(INPUT_ID::DOWN).second)
		{
			plSpeed = { 0.0,moveLane };
			move(_input, INPUT_ID::DOWN, plSpeed);
		}
	}

	// �A�N�V�������\�ȏ�Ԃ��ǂ���
	if (_state == STATE::NORMAL)
	{
		// �A�N�V�����p�L�[����������Ă��邩
		if ((*_input).state(INPUT_ID::ACTION).first && !(*_input).state(INPUT_ID::ACTION).second)
		{
			TRACE("�A�N�V����\n");
			_animCount = 0;
			_animFrame = 0;
			PlayerCount = -30;
			state(STATE::JUMP);
		}
	}

	_zOrder = static_cast<int>(_pos.y + 1);

	// �]�|���͔w�i���~
	if (_state == STATE::FALL)
	{
		lpSceneMng.bgSpeed = 0.0;
	}
	else
	{
		// �������Ԃɉ����Ĕw�i�̃X�s�[�h�㏸
		lpSceneMng.bgSpeed = DFBG_SPEED + (aliveCount / 300);
		// ����ݒ�
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

// �v���C���[�̃C�j�V�����C�Y
void Player::Init(void)
{
	AnimVector data;

	data.reserve(PL_DIV_CNT);
	for (int i = 0; i < PL_DIV_CNT; i++)
	{
		data.emplace_back(IMAGE_ID("���")[i], (i + 1) * 2);
	}
	SetAnim(STATE::NORMAL, data);

	data.reserve(PL_DIV_CNT);
	for (int i = 0; i < PL_DIV_CNT; i++)
	{
		data.emplace_back(IMAGE_ID("�ެ���")[i], (i + 1) * 2);
	}
	SetAnim(STATE::JUMP, data);

	data.reserve(PL_DIV_CNT);
	for (int i = 0; i < PL_DIV_CNT - 1; i++)
	{
		data.emplace_back(IMAGE_ID("�]�|")[i], (i + 1) * 2);
	}
	data.emplace_back(IMAGE_ID("�]�|")[PL_DIV_CNT - 1], 70);
	SetAnim(STATE::FALL, data);

	_input = std::make_shared<KeyState>();
}
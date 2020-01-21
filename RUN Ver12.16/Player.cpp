#include "Player.h"
#include "Scene\GameScene.h"
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
	double moveLane = (LIMIT_DOWN - LIMIT_UP) / 2.0;

	_lane = ((static_cast<int>(_pos.y - 360.0) % 3) + 1);

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

	if (Player::CheckHit(_lane,_pos, _size))
	{

	}


	if ((*_input).state(INPUT_ID::ACTION).first && !(*_input).state(INPUT_ID::ACTION).second)
	{
		TRACE("�A�N�V����\n");
		state(STATE::FALL);
	}
}


Player::~Player()
{
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
		data.emplace_back(IMAGE_ID("�]�|")[i], (i + 1));
	}
	SetAnim(STATE::FALL, data);


	_input = std::make_shared<KeyState>();
}

// �v���C���[�Ə�Q���̓����蔻��
bool Player::CheckHit(int lane,Vector2Dbl plPos, Vector2Dbl plSize)
{
	return false;
}

#include "KeyState.h"
#include "DxLib.h"
#include <algorithm>
#include "../_Debug/_DebugConOut.h"

KeyState::KeyState()
{
	// �e�ϐ��̏�����
	_keyConDef.reserve(static_cast<size_t>(end(INPUT_ID())));			// �����������炩���ߊm�ۂ��Ă���
	_keyConDef.emplace_back(KEY_INPUT_UP);
	_keyConDef.emplace_back(KEY_INPUT_DOWN);
	_keyConDef.emplace_back(KEY_INPUT_SPACE);

	_keyDef.resize(static_cast<size_t>(end(INPUT_ID())));

	// �L�[�R���t�B�O�̃t�@�C�������邩�̌���
	FILE* fp = NULL;
	if (fopen_s(&fp, "data/key.dat", "rb") != 0)
	{
		// �Ȃ������ꍇ�f�t�H���g��_keyConDef�ɓ����
		_keyCon = _keyConDef;
	}
	else
	{
		_keyCon.resize(static_cast<size_t>(end(INPUT_ID())));	// _keyCon�̗e�ʂ��m��

		fread(_keyCon.data(),									// &_keyCon.front() .data�@�z��̐擪�|�C���^���擾
			sizeof(_keyCon[0]),
			_keyCon.size(),
			fp);
		
		fclose(fp);
	}

	modeKeyOld = 1;

	func = &KeyState::RefKeyData;
}

KeyState::~KeyState()
{
}

void KeyState::Updata(void)
{
	SetOld();							// �L�[���̍X�V
	modeKeyOld = _buf[KEY_INPUT_F1];	// �L�[���̍X�V

	GetHitKeyStateAll(_buf);			// �L�[���̎擾

	/*  �L�[�������ɊY������L�[��T���ď�������
		�ݒ��ς��鏈���@�ʏ�̎擾�����Ƃ͕ʂ̏���
		�N���X�̃����o�[�֐��̃|�C���^�[���g��������
	*/
	(this->*func)();					// �������g�̃|�C���^�[�����ǂ�
}

void KeyState::RefKeyData(void)
{
	for (auto key : INPUT_ID())
	{
		state(key, _buf[_keyCon[static_cast<int>(key)]]);									// _keyCon�ɓ����Ă������state�ɏ�������
	}

	if (_buf[KEY_INPUT_F1] && !modeKeyOld)													// F1�������ꂽ�Ƃ�func���R���t�B�O�ֈڍs
	{
		_configID = INPUT_ID::UP;															// _configID�̏�����
		func = &KeyState::SetKeyConfig;														// F1�������ꂽ�Ƃ�func��SetKeyConfig�ֈڍs
		TRACE("�L�[�R���t�B�O�ֈڍs\n\n");													// �f�o�b�O��ʂւ̕\��
		TRACE("%d/%d�Ԗڂ̃L�[�ݒ�\n", static_cast<int>(_configID) + 1, end(INPUT_ID()));	// �f�o�b�O��ʂւ̕\��
	}
}

void KeyState::SetKeyConfig(void)
{
	for (auto key : INPUT_ID())
	{
		state(key, 0);
	}

	auto checkKey = [&](int id)		// �����_���ł��łɉ�����Ă���L�[������ꍇfor�������߂ɖ߂�(continue) �L���v�`���[��[=]�ŃR�s�[�L���v�`���A[&]�ŎQ�ƃL���v�`��
	{
		for (auto checkID = INPUT_ID::UP; checkID < _configID; ++checkID)
		{
			if (id == _keyCon[static_cast<int>(checkID)])
			{
				return false;
			}
		}
		return true;
	};

	for (int id = 0; id < sizeof(_buf); id++)
	{
		if (!checkKey(id))
		{
			continue;
		}

		if (_buf[id] && !_buf[KEY_INPUT_F1])
		{
			TRACE("%d��ݒ�\n\n", id);																// �f�o�b�O��ʂւ̕\��
			_keyDef[static_cast<int>(_configID)] = _keyCon[static_cast<int>(_configID)];			// ���̒l��ۑ����Ă���
			_keyCon[static_cast<int>(_configID)] = id;												// �l�̑��
			++_configID;																			// enumClass��INPUT_ID�̑���

			if (_configID < end(INPUT_ID()))
			{
				TRACE("%d/%d�Ԗڂ̃L�[�ݒ�\n", static_cast<int>(_configID) + 1, end(INPUT_ID()));	// �f�o�b�O��ʂւ̕\��
			}

			if (_configID >= end(_configID))														// _configID���͈͓����`�F�b�N
			{
				FILE* fp = NULL;																	// ���ׂẴL�[�ύX���Ƀt�@�C���ɏ�������
				if (fopen_s(&fp, "data/key.dat", "wb") == 0)
				{
					fwrite(_keyCon.data(),															// �t�@�C���̏�������(�擪�|�C���^,
						sizeof(_keyCon[0]),															// ��v�f�̃T�C�Y
						_keyCon.size(),																// �v�f��
						fp);																		// �t�@�C���̃|�C���^

					fclose(fp);																		// �J�����t�@�C�������
				}

				func = &KeyState::RefKeyData;														// �͈͊O�̏ꍇfunc��RefKeyData�ֈڍs
				TRACE("�Q�[����ʂֈڍs\n\n\n");													// �f�o�b�O��ʂւ̕\��
				break;
			}
		}
	}

	if (_buf[KEY_INPUT_F1] && !modeKeyOld)
	{
		_keyCon = _keyDef;							// �r����F1�������ꂽ��ۑ����Ă����l��_keyCon�ɖ߂�
		func = &KeyState::RefKeyData;				// F1�������ꂽ�Ƃ�func��RefKeyData�ֈڍs
		TRACE("\n\n�L�[�R���t�B�O�L�����Z��\n");	// �f�o�b�O��ʂւ̕\��
		TRACE("�Q�[����ʂֈڍs\n\n");				// �f�o�b�O��ʂւ̕\��
		return;
	}
}

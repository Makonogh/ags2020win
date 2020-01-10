#pragma once
#include "InputState.h"
#include <vector>

class KeyState :
	public InputState
{
public:
	KeyState();
	~KeyState();
	void Updata(void);
private:
	void RefKeyData(void);
	void SetKeyConfig(void);
	void (KeyState::*func)(void);

	char _buf[256];
	char _oldBuf[256];
	std::vector<int> _keyCon;			// �L�[�R���t�B�O
	std::vector<int> _keyConDef;		// �L�[�R���t�B���O�̃f�t�H���g
	std::vector<int> _keyDef;			// �L�[�R���t�B�O�ύX�O�̃f�[�^
	int modeKeyOld;
	INPUT_ID _configID;
};

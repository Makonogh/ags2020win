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
	std::vector<int> _keyCon;			// キーコンフィグ
	std::vector<int> _keyConDef;		// キーコンフィングのデフォルト
	std::vector<int> _keyDef;			// キーコンフィグ変更前のデータ
	int modeKeyOld;
	INPUT_ID _configID;
};

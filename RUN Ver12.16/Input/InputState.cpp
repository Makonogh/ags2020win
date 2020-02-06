#include "InputState.h"
#include "../_Debug/_DebugConOut.h"

InputState::InputState()
{
	// �L�[���̏�����
	
	for (auto id : INPUT_ID())
	{
		_state.try_emplace(static_cast<INPUT_ID>(id), KeyPair{ 0,1 });
	}
}

InputState::~InputState()
{
}

const KeyMap & InputState::state(void) const
{
	return _state;
}

const KeyPair& InputState::state(INPUT_ID id) const	// �������݋֎~
{
	static KeyPair defData = { 0,0 };
	try												// �ʏ폈��
	{
		return _state.at(id);
	}
	catch (...)										// �G���[���o���ۂ̏��� catch(...)�G���[���o���珈�����s��
	{
		AST();
		// �E�쐬���Ă������_�~�[��Ԃ� �Estatic�ȕϐ�������Ă����Ēl��Ԃ� �E�v���C�x�[�g�ϐ�������Ă��� �E�Q�Ƃ���߂�
		return defData;
	}
}

bool InputState::state(INPUT_ID id, int data)
{
	if (_state.find(id) != _state.end())
	{
		_state[id].first = data;
		return true;
	}
	return false;
}

void InputState::SetOld(void)
{
	for (auto id : INPUT_ID())
	{
		try
		{
			_state[id].second = _state[id].first;
		}
		catch(...)
		{
			_state.emplace(id, KeyPair{ 0,1 });
			AST();
		}
	}
}

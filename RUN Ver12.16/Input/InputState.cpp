#include "InputState.h"
#include "../_Debug/_DebugConOut.h"

InputState::InputState()
{
	// キー情報の初期化
	
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

const KeyPair& InputState::state(INPUT_ID id) const	// 書き込み禁止
{
	static KeyPair defData = { 0,0 };
	try												// 通常処理
	{
		return _state.at(id);
	}
	catch (...)										// エラーが出た際の処理 catch(...)エラーが出たら処理を行う
	{
		AST();
		// ・作成しておいたダミーを返す ・staticな変数を作っておいて値を返す ・プライベート変数を作っておく ・参照をやめる
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

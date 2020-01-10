#include "KeyState.h"
#include "DxLib.h"
#include <algorithm>
#include "../_Debug/_DebugConOut.h"

KeyState::KeyState()
{
	// 各変数の初期化
	_keyConDef.reserve(static_cast<size_t>(end(INPUT_ID())));			// メモリをあらかじめ確保しておく
	_keyConDef.emplace_back(KEY_INPUT_UP);
	_keyConDef.emplace_back(KEY_INPUT_DOWN);
	_keyConDef.emplace_back(KEY_INPUT_SPACE);

	_keyDef.resize(static_cast<size_t>(end(INPUT_ID())));

	// キーコンフィグのファイルがあるかの検索
	FILE* fp = NULL;
	if (fopen_s(&fp, "data/key.dat", "rb") != 0)
	{
		// なかった場合デフォルトを_keyConDefに入れる
		_keyCon = _keyConDef;
	}
	else
	{
		_keyCon.resize(static_cast<size_t>(end(INPUT_ID())));	// _keyConの容量を確保

		fread(_keyCon.data(),									// &_keyCon.front() .data　配列の先頭ポインタを取得
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
	SetOld();							// キー情報の更新
	modeKeyOld = _buf[KEY_INPUT_F1];	// キー情報の更新

	GetHitKeyStateAll(_buf);			// キー情報の取得

	/*  キー情報を左に該当するキーを探して書き込む
		設定を変える処理　通常の取得処理とは別の処理
		クラスのメンバー関数のポインターを使った分岐
	*/
	(this->*func)();					// 自分自身のポインターをたどる
}

void KeyState::RefKeyData(void)
{
	for (auto key : INPUT_ID())
	{
		state(key, _buf[_keyCon[static_cast<int>(key)]]);									// _keyConに入っている情報をstateに書き込む
	}

	if (_buf[KEY_INPUT_F1] && !modeKeyOld)													// F1が押されたときfuncをコンフィグへ移行
	{
		_configID = INPUT_ID::UP;															// _configIDの初期化
		func = &KeyState::SetKeyConfig;														// F1が押されたときfuncをSetKeyConfigへ移行
		TRACE("キーコンフィグへ移行\n\n");													// デバッグ画面への表示
		TRACE("%d/%d番目のキー設定\n", static_cast<int>(_configID) + 1, end(INPUT_ID()));	// デバッグ画面への表示
	}
}

void KeyState::SetKeyConfig(void)
{
	for (auto key : INPUT_ID())
	{
		state(key, 0);
	}

	auto checkKey = [&](int id)		// ラムダ式ですでに押されているキーがある場合for文を初めに戻す(continue) キャプチャー部[=]でコピーキャプチャ、[&]で参照キャプチャ
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
			TRACE("%dを設定\n\n", id);																// デバッグ画面への表示
			_keyDef[static_cast<int>(_configID)] = _keyCon[static_cast<int>(_configID)];			// 元の値を保存しておく
			_keyCon[static_cast<int>(_configID)] = id;												// 値の代入
			++_configID;																			// enumClassのINPUT_IDの増加

			if (_configID < end(INPUT_ID()))
			{
				TRACE("%d/%d番目のキー設定\n", static_cast<int>(_configID) + 1, end(INPUT_ID()));	// デバッグ画面への表示
			}

			if (_configID >= end(_configID))														// _configIDが範囲内かチェック
			{
				FILE* fp = NULL;																	// すべてのキー変更時にファイルに書き込み
				if (fopen_s(&fp, "data/key.dat", "wb") == 0)
				{
					fwrite(_keyCon.data(),															// ファイルの書き込み(先頭ポインタ,
						sizeof(_keyCon[0]),															// 一要素のサイズ
						_keyCon.size(),																// 要素数
						fp);																		// ファイルのポインタ

					fclose(fp);																		// 開いたファイルを閉じる
				}

				func = &KeyState::RefKeyData;														// 範囲外の場合funcをRefKeyDataへ移行
				TRACE("ゲーム画面へ移行\n\n\n");													// デバッグ画面への表示
				break;
			}
		}
	}

	if (_buf[KEY_INPUT_F1] && !modeKeyOld)
	{
		_keyCon = _keyDef;							// 途中でF1を押されたら保存していた値を_keyConに戻す
		func = &KeyState::RefKeyData;				// F1が押されたときfuncをRefKeyDataへ移行
		TRACE("\n\nキーコンフィグキャンセル\n");	// デバッグ画面への表示
		TRACE("ゲーム画面へ移行\n\n");				// デバッグ画面への表示
		return;
	}
}

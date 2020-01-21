#include "DxLib.h"
#include "BaseScene.h"
#include "SceneMng.h"
#include "GameScene.h"
#include "TitleScene.h"
#include <algorithm>
#include <_debug/_DebugConOut.h>
#include <time.h>

SceneMng* SceneMng::sInstance = nullptr;
Bg bg;

SceneMng::SceneMng() :ScreenSize{ 1280,720 }, ScreenCenter{ ScreenSize / 2 }, GameSize{ ScreenSize.x,576 }, UISize{ ScreenSize - GameSize }
{
}

void SceneMng::Draw()
{
	std::sort(_drawList.begin(), _drawList.end(), [](DrawQueT dQueA, DrawQueT dQueB)			// ﾘｽﾄをｿｰﾄする
	{
		return
			std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(dQueA), std::get<static_cast<int>(DRAW_QUE::ZORDER)>(dQueA))
			<
			std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(dQueB), std::get<static_cast<int>(DRAW_QUE::ZORDER)>(dQueB));
	});

	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();
	for (auto layer : LAYER())
	{
		SetDrawScreen(_screenID[layer]);
		ClsDrawScreen();
	}

	for (auto dQue : _drawList)
	{
		double x, y, rad;
		int id;
		LAYER layer;

		std::tie(id, x, y, rad, std::ignore, layer) = dQue;
		if (_screenID[layer] != GetDrawScreen())
		{
			SetDrawScreen(_screenID[layer]);
		}

		DrawRotaGraph(
			static_cast<int>(x),
			static_cast<int>(y),
			1.0,
			rad,
			id,
			true
		);
	}

	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();
	for (auto layer : LAYER())
	{
		DrawRotaGraph(ScreenCenter.x,
			ScreenCenter.y,
			1.0,
			0,
			_screenID[layer],
			true);

	}

	for (int i = 0; i < 4; i++)
	{
		DrawLine(0, 360 + (72 * i), 1280, 360 + (72 * i), 0x00FF00);
	}

	for (int i = 0; i < 10; i++)
	{
		DrawLine(i * 128, 576, 245 + (i * 128), 360, 0x00FF00);
	}

	ScreenFlip();
}

SceneMng::~SceneMng()
{
}


void SceneMng::Run(void)
{
	SysInit();
	_activeScene = std::make_unique<TitleScene>();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		_drawList.clear();				// 要素をｸﾘｱする
		OldReturn = Return;
		Return = CheckHitKey(KEY_INPUT_RETURN);

		_activeScene = (*_activeScene).Update(std::move(_activeScene));
		GameCount++;
		Draw();
	}
}

bool SceneMng::AddDrawQue(DrawQueT dQue)
{
	if (std::get <static_cast<int>(DRAW_QUE::IMAGE)>(dQue) <= 0)
	{
		// 画像IDが不正なので、追加しない
		return false;
	}
	// Queを追加
	_drawList.emplace_back(dQue);

	return true;
}


bool SceneMng::SysInit(void)
{
	// ---------ｼｽﾃﾑ処理
	SetWindowText("RUN");
	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);			// 1280*720ﾄﾞｯﾄ、65536色ﾓｰﾄﾞに設定
	ChangeWindowMode(true);									// true:window false:ﾌﾙｽｸﾘｰﾝ

	if (DxLib_Init() == -1)
	{
		return false;										// DXﾗｲﾌﾞﾗﾘ初期化処理
	}
	SetDrawScreen(DX_SCREEN_BACK);							// ﾊﾞｯｸﾊﾞｯﾌｧに描画

	for (auto layer : LAYER())
	{
		_screenID.try_emplace(layer, MakeScreen(ScreenSize.x, ScreenSize.y, true));
	}

	
	srand(static_cast<unsigned int>(time(NULL)));

	GameCount = 0;
	return false;
}

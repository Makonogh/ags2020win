#include "GameScene.h"
#include "Player.h"
#include <Scene/ResultScene.h>
#include <common/ImgMng.h>
#include "Obstacles.h"
#include "DxLib.h"
#include "Bg.h"
#include "Bg/GameBg.h"

GameScene::GameScene()
{
	lpImgMng.GetID("πﬁ∞—îwåi", "image/BGB.png");
	lpImgMng.GetID("UI", "image/UI2.png");
	lpImgMng.GetID("è·äQï®", "image/Obj1.png", { 160,160 }, { 3,1 });
	lpImgMng.GetID("∑¨◊", "image/pl.png", { 100,150 }, { PL_DIV_CNT,1 });
	lpImgMng.GetID("ÇÊÅ[Ç¢", "image/ready.png", { 210,75 }, { 1,2 });
	lpImgMng.GetID("Ω∫±", "image/number.png", { 60,60 }, { 10,1 });
	lpImgMng.GetID("πﬁ∞—îwåi1", "image/BGB.png");
	lpImgMng.GetID("πﬁ∞—îwåi2", "image/BG1.png");
	lpImgMng.GetID("πﬁ∞—îwåi3", "image/BG2.png");

	_objList.emplace_back(new Player({ 125.0, (LIMIT_UP + LIMIT_DOWN) / 2.0 }, { 70.0,150.0 }));

	for (auto type : OBS_TYPE())
	{
		ObsState state = { static_cast<OBS_TYPE>(type),{ 500.0 + 134 * static_cast<double>(type), LIMIT_UP + ((rand() % 2) * static_cast<int>((LIMIT_DOWN - LIMIT_UP) / 2.0)) },{ 100.0,10.0 } };
		_objList.emplace_back(new Obstacles(state));
	}

	_bgList.emplace_back(new GameBg({ GAME_TYPE::BG1,{ 320.0,288.0 },{ 640,576 } }));
	_bgList.emplace_back(new GameBg({ GAME_TYPE::BG2,{ 960.0,288.0 },{ 640,576 } }));
	_bgList.emplace_back(new GameBg({ GAME_TYPE::BG3,{ 1600.0,288.0 },{ 640,576 } }));
	SceneCount = 0;

	score = 0.0;
}


GameScene::~GameScene()
{
}

unique_Base GameScene::Update(unique_Base own)
{
	Vector2Dbl UICenter = { lpSceneMng.GameSize.x / 2.0 ,(lpSceneMng.ScreenSize.y + lpSceneMng.GameSize.y) / 2.0 };

	if (SceneCount >= 180)
	{
		for (auto data : _objList)
		{
			(*data).Updata();

			if ((*data).pos().x == (*data).size().x)
			{
				ObsState state = { static_cast<OBS_TYPE>(rand() % static_cast<int>(OBS_STATE::MAX)),{ lpSceneMng.ScreenSize.x + static_cast<double>(rand() % 100), LIMIT_UP + static_cast<double>(((rand() % 2) * static_cast<int>((LIMIT_DOWN - LIMIT_UP) / 2.0))) },{ 100.0,10.0 } };
				_objList.emplace_back(new Obstacles(state));
				break;
			}
			score += static_cast<double>(bg.bgSpeed) / 100;
		}

		for (auto data : _bgList)
		{
			(*data).Updata();
			if ((*data)._pos.x == -320)
			{
				_bgList.emplace_back(new GameBg({ static_cast<GAME_TYPE>(rand() % 3),{ 1600.0,288.0 },{ 640,576 } }));
				break;
			}
		}
	}
	else
	{
		lpSceneMng.AddDrawQue({ IMAGE_ID("ÇÊÅ[Ç¢")[0],lpSceneMng.GameSize.x / 2.0,lpSceneMng.GameSize.y / 2.0,0.0,INT_MAX, LAYER::UI });
	}

	for (auto data : _objList)
	{
		(*data).Draw();
	}

	for (auto data : _bgList)
	{
		(*data).Draw();
	}

	lpSceneMng.AddDrawQue({ IMAGE_ID("UI")[0],UICenter.x,UICenter.y,0.0,INT_MAX, LAYER::UI });

	if (lpSceneMng.Return && !lpSceneMng.OldReturn)
	{
		return std::make_unique<ResultScene>();
	}

	SceneCount++;

	tmpScore = score;

	// ÉXÉRÉAÇÃï\é¶
	lpSceneMng.AddDrawQue({ IMAGE_ID("Ω∫±")[tmpScore % 10],270.05,UICenter.y + 30.0,0.0,INT_MAX, LAYER::UI });
	tmpScore /= 10;

	for (int i = 0; i < 3; i++)
	{
		lpSceneMng.AddDrawQue({ IMAGE_ID("Ω∫±")[tmpScore % 10],150.0 - (i * 60),UICenter.y + 30.0,0.0,INT_MAX, LAYER::UI });
		tmpScore /= 10;
	}

	return own;
}


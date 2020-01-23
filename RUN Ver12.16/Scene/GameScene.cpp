#include "GameScene.h"
#include "Player.h"
#include <Scene/ResultScene.h>
#include <common/ImgMng.h>
#include "Obstacles.h"
#include "DxLib.h"
#include "Bg.h"

#include "Bg/GameBg.h"
#include <_debug/_DebugConOut.h>

GameScene::GameScene()
{
	lpImgMng.GetID("πﬁ∞—îwåi", "image/BGB.png");
	lpImgMng.GetID("UI", "image/UI2.png");
	lpImgMng.GetID("è·äQï®", "image/Obj1.png", { 200,200 }, { static_cast<int>(OBS_TYPE::MAX),1 });
	lpImgMng.GetID("∑¨◊", "image/pl.png", { 100,150 }, { PL_DIV_CNT,1 });
	lpImgMng.GetID("ºﬁ¨›Ãﬂ", "image/Jump.png", { 160,160 }, { PL_DIV_CNT,1 });
	lpImgMng.GetID("ì]ì|", "image/FALL.png", { 160,144 }, { PL_DIV_CNT,1 });
	lpImgMng.GetID("ÇÊÅ[Ç¢", "image/ready.png", { 210,75 }, { 1,2 });
	lpImgMng.GetID("Ω∫±", "image/num.png", { 60,60 }, { 10,1 });
	lpImgMng.GetID("πﬁ∞—îwåi0", "image/BGB.png");
	lpImgMng.GetID("πﬁ∞—îwåi1", "image/BG1.png");
	lpImgMng.GetID("πﬁ∞—îwåi2", "image/BG2.png");
	lpImgMng.GetID("πﬁ∞—îwåi3", "image/BG3.png");
	lpImgMng.GetID("πﬁ∞—îwåi4", "image/BG4.png");
	lpImgMng.GetID("πﬁ∞—îwåi5", "image/BG5.png");
	lpImgMng.GetID("πﬁ∞—îwåi6", "image/BG6.png");
	lpImgMng.GetID("πﬁ∞—îwåi7", "image/BG7.png");
	lpImgMng.GetID("πﬁ∞—îwåi8", "image/BG8.png");
	lpImgMng.GetID("πﬁ∞—îwåi9", "image/BG9.png");
	lpImgMng.GetID("πﬁ∞—îwåi10", "image/BG10.png");
	lpImgMng.GetID("πﬁ∞—îwåi11", "image/BG11.png");
	lpImgMng.GetID("πﬁ∞—îwåi12", "image/BG12.png");
	lpImgMng.GetID("πﬁ∞—îwåi13", "image/BG13.png");
	lpImgMng.GetID("πﬁ∞—îwåi14", "image/BG14.png");
	lpImgMng.GetID("πﬁ∞—îwåi15", "image/BG15.png");

	_objList.emplace_back(new Player({ 125.0, (LIMIT_UP + LIMIT_DOWN) / 2.0 }, { 70.0,150.0 }));

	lpSceneMng.bgSpeed = DFBG_SPEED;

	for (auto type : OBS_TYPE())
	{
		ObsState state = { static_cast<OBS_TYPE>(type),{ 500.0 + 134 * static_cast<double>(type), LIMIT_UP + ((rand() % 2) * static_cast<int>((LIMIT_DOWN - LIMIT_UP) / 2.0)) },{ 100.0,10.0 } };
		_objList.emplace_back(new Obstacles(state));
	}

	_bgList.emplace_back(new GameBg({ GAME_TYPE::BG0,{ 320.0,288.0 },{ 640,576 } }));
	_bgList.emplace_back(new GameBg({ GAME_TYPE::BG1,{ 960.0,288.0 },{ 640,576 } }));
	_bgList.emplace_back(new GameBg({ GAME_TYPE::BG2,{ 1600.0,288.0 },{ 640,576 } }));
	SceneCount = 0;

	lpSceneMng.score = 0.0;
}


GameScene::~GameScene()
{
}

unique_Base GameScene::Update(unique_Base own)
{
	
	Vector2Dbl UICenter = { lpSceneMng.GameSize.x / 2.0 ,(lpSceneMng.ScreenSize.y + lpSceneMng.GameSize.y) / 2.0 };

	

	if (SceneCount >= 60)
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
		}
		lpSceneMng.score += static_cast<double>(lpSceneMng.bgSpeed) / 150;
		TRACE("%d\n", lpSceneMng.bgSpeed);
		for (auto data : _bgList)
		{
			(*data).Updata();
	
		}
		for (auto data : _bgList)
		{
			if ((*data)._pos.x <= -320)
			{
				_bgList.erase(_bgList.begin());
				_bgList.emplace_back(new GameBg({ static_cast<GAME_TYPE>(rand() % 16),{ 1600.0,288.0 },{ 640,576 } }));
				
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

	SceneCount++;

	lpSceneMng.tmpScore = static_cast<int> (lpSceneMng.score);
	tmpTime = abs(SceneCount - 10800 - 120) / 60;
	if (tmpTime > 180)
	{
		tmpTime = 180;
	}

	if (tmpTime <= 0 || (lpSceneMng.Return && !lpSceneMng.OldReturn))
	{
		return std::make_unique<ResultScene>();
	}

	// ÉXÉRÉAÇÃï\é¶
	lpSceneMng.AddDrawQue({ IMAGE_ID("Ω∫±")[lpSceneMng.tmpScore % 10],270.05,UICenter.y + 30.0,0.0,INT_MAX, LAYER::UI });
	lpSceneMng.tmpScore /= 10;

	for (int i = 0; i < 3; i++)
	{
		lpSceneMng.AddDrawQue({ IMAGE_ID("Ω∫±")[lpSceneMng.tmpScore % 10],150.0 - (i * 60),UICenter.y + 30.0,0.0,INT_MAX, LAYER::UI });
		lpSceneMng.tmpScore /= 10;
	}

	// écÇËéûä‘ÇÃï\é¶
	for (int i = 0; i < 3; i++)
	{
		lpSceneMng.AddDrawQue({ IMAGE_ID("Ω∫±")[tmpTime % 10],1170.0 - (i * 60),UICenter.y + 30.0,0.0,INT_MAX, LAYER::UI });
		tmpTime /= 10;
	}

	if (rand() % 100 == 0)
	{
		ObsState state = { static_cast<OBS_TYPE>(rand() % static_cast<int>(OBS_TYPE::MAX)),{ lpSceneMng.ScreenSize.x + static_cast<double>(rand() % 100), LIMIT_UP + static_cast<double>(((rand() % 3) * static_cast<int>((LIMIT_DOWN - LIMIT_UP) / 2.0))) },{ 100.0,10.0 } };
		_objList.emplace_back(new Obstacles(state));
	}
	return own;

}



#include "GameScene.h"
#include "Player.h"
#include <Scene/ResultScene.h>
#include <common/ImgMng.h>
#include "Obstacles.h"
#include "DxLib.h"
#include "Bg.h"

GameScene::GameScene()
{
	lpImgMng.GetID("πﬁ∞—îwåi", "image/BGB.png");
	lpImgMng.GetID("UI", "image/UI.png");
	lpImgMng.GetID("è·äQï®", "image/Obj.png", { 80,80 }, { 3,1 });
	lpImgMng.GetID("∑¨◊", "image/pl2.png", { 80,160 }, { 5,1 });
	lpImgMng.GetID("ÇÊÅ[Ç¢", "image/ready.png", { 210,75 }, { 1,2 });

	_objList.emplace_back(new Player({ 125.0, (LIMIT_UP + LIMIT_DOWN) / 2.0 - 20.0}, { 0,0 }));
	
	for (auto type: OBS_TYPE())
	{
		ObsState state = { static_cast<OBS_TYPE>(type),{ 1200, LIMIT_UP + 50 + 70 * static_cast<int>(type) }, {0,0} };
		_objList.emplace_back(new Obstacles(state));
	}
	
	SceneCount = 0;
}


GameScene::~GameScene()
{
}

unique_Base GameScene::Update(unique_Base own)
{
	if (SceneCount >= 180)
	{
		for (auto data : _objList)
		{
			(*data).Updata();
		}
		bg._pos.x -= bg.bgSpeed;
	}
	else
	{
		lpSceneMng.AddDrawQue({ IMAGE_ID("ÇÊÅ[Ç¢")[0],lpSceneMng.GameSize.x / 2.0,lpSceneMng.GameSize.y / 2.0,0.0,INT_MAX, LAYER::UI });
	}

	for (auto data : _objList)
	{
		(*data).Draw();
	}

	
	bg.Draw(BG_TYPE::GAME);

	Vector2Dbl UICenter = { lpSceneMng.GameSize.x / 2.0 ,(lpSceneMng.ScreenSize.y + lpSceneMng.GameSize.y) / 2.0};

	lpSceneMng.AddDrawQue({ IMAGE_ID("UI")[0],UICenter.x,UICenter.y,0.0,INT_MAX, LAYER::UI });

	if (lpSceneMng.Return && !lpSceneMng.OldReturn)
	{
		return std::make_unique<ResultScene>();
	}

	SceneCount++;
	return own;
}


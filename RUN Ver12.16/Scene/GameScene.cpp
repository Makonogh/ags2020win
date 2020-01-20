#include <functional>
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
	lpImgMng.GetID("�ްєw�i", "image/BGB.png");
	lpImgMng.GetID("UI", "image/UI.png");
	lpImgMng.GetID("��Q��", "image/Obj1.png", { 160,160 }, { 3,1 });
	lpImgMng.GetID("���", "image/plEx.png", { 100,150 }, { PL_DIV_CNT,1 });
	lpImgMng.GetID("��[��", "image/ready.png", { 210,75 }, { 1,2 });
	lpImgMng.GetID("�ްєw�i1","image/BGB.png");
	lpImgMng.GetID("�ްєw�i2","image/BG1.png");
	lpImgMng.GetID("�ްєw�i3", "image/BG2.png");

	_objList.emplace_back(new Player({ 125.0, (LIMIT_UP + LIMIT_DOWN) / 2.0 }, { 70.0,150.0 }));

	for (auto type : OBS_TYPE())
	{
		ObsState state = { static_cast<OBS_TYPE>(type),{ 500.0 + ((rand() % 3) * 100), LIMIT_UP + ((rand() % 2) * static_cast<int>((LIMIT_DOWN - LIMIT_UP) / 2.0)) },{ 100.0,10.0 } };
		_objList.emplace_back(new Obstacles(state));
	}

	_bgList.emplace_back(new GameBg({ GAME_TYPE::BG1, { 320.0,288.0 }, {640,576} }));
	_bgList.emplace_back(new GameBg({ GAME_TYPE::BG2, { 960.0,288.0 }, { 640,576 }}));
	_bgList.emplace_back(new GameBg({GAME_TYPE::BG3, { 1600.0,288.0 }, { 640,576 }}));
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
		lpSceneMng.AddDrawQue({ IMAGE_ID("��[��")[0],lpSceneMng.GameSize.x / 2.0,lpSceneMng.GameSize.y / 2.0,0.0,INT_MAX, LAYER::UI });
	}

	

	for (auto data : _objList)
	{
		(*data).Draw();
	}

	for (auto data : _bgList)
	{
		(*data).Draw();
	}

	Vector2Dbl UICenter = { lpSceneMng.GameSize.x / 2.0 ,(lpSceneMng.ScreenSize.y + lpSceneMng.GameSize.y) / 2.0 };

	lpSceneMng.AddDrawQue({ IMAGE_ID("UI")[0],UICenter.x,UICenter.y,0.0,INT_MAX, LAYER::UI });

	if (lpSceneMng.Return && !lpSceneMng.OldReturn)
	{
		return std::make_unique<ResultScene>();
	}

	SceneCount++;
	return own;
}


#include "GameScene.h"
#include "Player.h"
#include <Scene/ResultScene.h>
#include <common/ImgMng.h>
#include "Obstacles.h"
#include "DxLib.h"
#include "Bg.h"
#include "Bg/GameBg.h"
#include <_debug/_DebugConOut.h>
#include <algorithm>

GameScene::GameScene()
{

	_objList.emplace_back(new Player({ 125.0, (LIMIT_UP + LIMIT_DOWN) / 2.0 }, { 70.0,150.0 }));

	lpSceneMng.bgSpeed = DFBG_SPEED;

	for (auto type : OBS_TYPE())
	{
		ObsState state = { static_cast<OBS_TYPE>(type),{ 500.0 + 134 * static_cast<double>(type), LIMIT_UP + ((rand() % 3) * static_cast<int>((LIMIT_DOWN - LIMIT_UP) / 2.0)) }};
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
			(*data).Updata(_objList.front());
		}

		for (auto data : _objList)
		{
			auto itr = std::remove_if(_objList.begin(), _objList.end(), [](sharedObj& obj) {return obj->isJudge(); });
			_objList.erase(itr, _objList.end());
		}

		if (_objList.size() <= 5 && ObsCount >= 60)
		{
			ObsCount = 0;
			ObsState state = { static_cast<OBS_TYPE>(rand() % static_cast<int>(OBS_TYPE::MAX)),{ lpSceneMng.ScreenSize.x + static_cast<double>(rand() % 100), LIMIT_UP + static_cast<double>(((rand() % 3) * static_cast<int>((LIMIT_DOWN - LIMIT_UP) / 2.0))) } };
			_objList.emplace_back(new Obstacles(state));
		}

		lpSceneMng.score += (static_cast<double>(lpSceneMng.bgSpeed) / 150) * 11.01514734;
		//TRACE("%d\n", lpSceneMng.bgSpeed);

		for (auto data : _bgList)
		{
			(*data).Updata();
		}

		for (auto data : _bgList)
		{
			if ((*data)._pos.x <= -320)
			{
				_bgList.erase(_bgList.begin());
				_bgList.emplace_back(new GameBg({ static_cast<GAME_TYPE>(rand() % 16),{(*_bgList.back())._pos.x + 640,288.0 },{ 640,576 } }));
				
				break;
			}
		}	
	}
	else
	{
		lpSceneMng.AddDrawQue({ IMAGE_ID("よーい")[0],lpSceneMng.GameSize.x / 2.0,lpSceneMng.GameSize.y / 2.0,0.0,INT_MAX, LAYER::UI });
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

	lpSceneMng.tmpScore = static_cast<int> (lpSceneMng.score);
	tmpTime = abs(SceneCount - 7200 - 120) / 60;
	if (tmpTime > 120)
	{
		tmpTime = 120;
	}

	if (tmpTime <= 0 || (lpSceneMng.Return && !lpSceneMng.OldReturn))
	{
		return std::make_unique<ResultScene>();
	}

	// スコアの表示
	lpSceneMng.AddDrawQue({ IMAGE_ID("ｽｺｱ")[lpSceneMng.tmpScore % 10],270.05,UICenter.y + 30.0,0.0,INT_MAX, LAYER::UI });
	lpSceneMng.tmpScore /= 10;

	for (int i = 0; i < 3; i++)
	{
		lpSceneMng.AddDrawQue({ IMAGE_ID("ｽｺｱ")[lpSceneMng.tmpScore % 10],150.0 - (i * 60),UICenter.y + 30.0,0.0,INT_MAX, LAYER::UI });
		lpSceneMng.tmpScore /= 10;
	}

	// 残り時間の表示
	for (int i = 0; i < 3; i++)
	{
		lpSceneMng.AddDrawQue({ IMAGE_ID("ｽｺｱ")[tmpTime % 10],1170.0 - (i * 60),UICenter.y + 30.0,0.0,INT_MAX, LAYER::UI });
		tmpTime /= 10;
	}

	//if (rand() % 100 == 0)
	//{
	//	ObsState state = { static_cast<OBS_TYPE>(rand() % static_cast<int>(OBS_TYPE::MAX)),{ lpSceneMng.ScreenSize.x + static_cast<double>(rand() % 100), LIMIT_UP + static_cast<double>(((rand() % 3) * static_cast<int>((LIMIT_DOWN - LIMIT_UP) / 2.0))) }};
	//	_objList.emplace_back(new Obstacles(state));
	//}

	SceneCount++;
	ObsCount += lpSceneMng.bgSpeed / 4;
	return own;
}

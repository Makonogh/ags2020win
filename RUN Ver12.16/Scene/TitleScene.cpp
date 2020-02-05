#include "TitleScene.h"
#include "DxLib.h"
#include "GameScene.h"
#include "common/ImgMng.h"
#include "Bg/TitleBg.h"
#include "Obstacles.h"
#include <algorithm>


TitleScene::TitleScene()
{
	// ¿≤ƒŸ
	lpImgMng.GetID("¿≤ƒŸ√∑Ωƒ", "image/TitleText.png");
	lpImgMng.GetID("¿≤ƒŸ", "image/GameName.png");

	// πﬁ∞—
	lpImgMng.GetID("πﬁ∞—îwåi", "image/BGB.png");
<<<<<<< HEAD
	lpImgMng.GetID("UI", "image/UI3.png");
=======
	lpImgMng.GetID("UI", "image/UI2.png");
	lpImgMng.GetID("πﬁ∞—¥Ã™∏ƒ", "image/SpeedAnim.png", { 1280,576 }, { 4,1 });
>>>>>>> bae936ce12129882c0a001887cae008138ff04fc
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
	lpImgMng.GetID("¥Ã™∏ƒ", "image/SpeedEffect.png");

	// ÿªﬁŸƒ
	lpImgMng.GetID("ÿªﬁŸƒîwåi", "image/Result.png");
	lpImgMng.GetID("ÿªﬁŸƒ√∑Ωƒ", "image/ResultText.png");
	lpImgMng.GetID("ÿªﬁŸƒΩ∫±", "image/number.png", { 60, 60 }, { 10,1 });

	SceneCount = 0;
	lpSceneMng.bgSpeed = DFBG_SPEED;

	_bgList.emplace_back(new TitleBg({ TITLE_TYPE::BG0,{ 320.0,288.0 },{ 640,576 } }));
	_bgList.emplace_back(new TitleBg({ TITLE_TYPE::BG1,{ 960.0,288.0 },{ 640,576 } }));
	_bgList.emplace_back(new TitleBg({ TITLE_TYPE::BG2,{ 1600.0,288.0 },{ 640,576 } }));
	for (auto type : OBS_TYPE())
	{
		ObsState state = { static_cast<OBS_TYPE>(type),{ 500.0 + 134 * static_cast<double>(type), LIMIT_UP + ((rand() % 3) * static_cast<int>((LIMIT_DOWN - LIMIT_UP) / 2.0)) } };
		_objList.emplace_back(new Obstacles(state));
	}
	Init();
}


TitleScene::~TitleScene()
{
}

unique_Base TitleScene::Update(unique_Base own)
{
	if (lpSceneMng.Return && !lpSceneMng.OldReturn)
	{
		return std::make_unique<GameScene>();
	}

	for (auto data : _bgList)
	{
		(*data).Updata();
	}

	for (auto data : _bgList)
	{
		if ((*data)._pos.x <= -320)
		{
			_bgList.erase(_bgList.begin());
			_bgList.emplace_back(new TitleBg({ static_cast<TITLE_TYPE>(rand() % 16),{(*_bgList.back())._pos.x + 640,288.0 },{ 640,576 } }));

			break;
		}
	}

	for (auto data : _objList)
	{
		(*data).Updata();
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
	
	for (auto data : _objList)
	{
		(*data).Draw();
	}

	for (auto data : _bgList)
	{
		(*data).Draw();
	}

	lpSceneMng.AddDrawQue({ IMAGE_ID("¿≤ƒŸ√∑Ωƒ")[0],640.0,static_cast<double>(lpSceneMng.ScreenSize.y - (lpSceneMng.UISize.y / 2)),0.0,INT_MAX,LAYER::UI });
	lpSceneMng.AddDrawQue({ IMAGE_ID("¿≤ƒŸ")[0], 320.0,172.5,0.0,INT_MAX,LAYER::UI });

	SceneCount++;
	ObsCount++;
	
	return std::move(own);
}

void TitleScene::Init(void)
{
	// ç≈è¨éËêîèâä˙âª
	FILE* fp = NULL;
	if (fopen_s(&fp, "scr.dat", "rb") != 0)
	{
		for (int i = 0; i < SCR_MAX; i++)
		{
			highScore = { 0.0, 0.0, 0.0, 0.0, 0.0 };
		}
	}
	else
	{
		highScore.resize(SCR_MAX);
		fread(&highScore[0],
			sizeof(highScore[0]),
			SCR_MAX,
			fp);
		fclose(fp);
	}
}

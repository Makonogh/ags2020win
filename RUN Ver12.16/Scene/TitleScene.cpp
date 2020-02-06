#include "TitleScene.h"
#include "DxLib.h"
#include "GameScene.h"
#include "common/ImgMng.h"
#include "Bg/TitleBg.h"
#include "Obstacles.h"
#include <algorithm>


TitleScene::TitleScene()
{
	// À²ÄÙ
	lpImgMng.GetID("À²ÄÙÃ·½Ä", "image/TitleText.png");
	lpImgMng.GetID("À²ÄÙ", "image/GameName.png");

	// ¹Ş°Ñ
	lpImgMng.GetID("¹Ş°Ñ”wŒi", "image/BGB.png");
	lpImgMng.GetID("UI", "image/UI2.png");
	lpImgMng.GetID("¹Ş°Ñ´Ìª¸Ä", "image/SpeedAnim.png", { 1280,576 }, { 4,1 });
	lpImgMng.GetID("áŠQ•¨", "image/Obj1.png", { 200,200 }, { static_cast<int>(OBS_TYPE::MAX),1 });
	lpImgMng.GetID("·¬×", "image/pl.png", { 100,150 }, { PL_DIV_CNT,1 });
	lpImgMng.GetID("¼Ş¬İÌß", "image/Jump.png", { 160,160 }, { PL_DIV_CNT,1 });
	lpImgMng.GetID("“]“|", "image/FALL.png", { 160,144 }, { PL_DIV_CNT,1 });
	lpImgMng.GetID("‚æ[‚¢", "image/ready.png", { 210,75 }, { 1,2 });
	lpImgMng.GetID("½º±", "image/num.png", { 60,60 }, { 10,1 });
	lpImgMng.GetID("¹Ş°Ñ”wŒi0", "image/BGB.png");
	lpImgMng.GetID("¹Ş°Ñ”wŒi1", "image/BG1.png");
	lpImgMng.GetID("¹Ş°Ñ”wŒi2", "image/BG2.png");
	lpImgMng.GetID("¹Ş°Ñ”wŒi3", "image/BG3.png");
	lpImgMng.GetID("¹Ş°Ñ”wŒi4", "image/BG4.png");
	lpImgMng.GetID("¹Ş°Ñ”wŒi5", "image/BG5.png");
	lpImgMng.GetID("¹Ş°Ñ”wŒi6", "image/BG6.png");
	lpImgMng.GetID("¹Ş°Ñ”wŒi7", "image/BG7.png");
	lpImgMng.GetID("¹Ş°Ñ”wŒi8", "image/BG8.png");
	lpImgMng.GetID("¹Ş°Ñ”wŒi9", "image/BG9.png");
	lpImgMng.GetID("¹Ş°Ñ”wŒi10", "image/BG10.png");
	lpImgMng.GetID("¹Ş°Ñ”wŒi11", "image/BG11.png");
	lpImgMng.GetID("¹Ş°Ñ”wŒi12", "image/BG12.png");
	lpImgMng.GetID("¹Ş°Ñ”wŒi13", "image/BG13.png");
	lpImgMng.GetID("¹Ş°Ñ”wŒi14", "image/BG14.png");
	lpImgMng.GetID("¹Ş°Ñ”wŒi15", "image/BG15.png");
	lpImgMng.GetID("´Ìª¸Ä", "image/SpeedEffect.png");

	// Ø»ŞÙÄ
	lpImgMng.GetID("Ø»ŞÙÄ”wŒi", "image/Result.png");
	lpImgMng.GetID("Ø»ŞÙÄÃ·½Ä", "image/ResultText.png");
	lpImgMng.GetID("Ø»ŞÙÄ½º±", "image/number.png", { 60, 60 }, { 10,1 });

	// ƒIƒuƒWƒFƒNƒg‚Ì¶¬
	_bgList.emplace_back(new TitleBg({ TITLE_TYPE::BG0,{ 320.0,288.0 },{ 640,576 } }));
	_bgList.emplace_back(new TitleBg({ TITLE_TYPE::BG1,{ 960.0,288.0 },{ 640,576 } }));
	_bgList.emplace_back(new TitleBg({ TITLE_TYPE::BG2,{ 1600.0,288.0 },{ 640,576 } }));

	for (auto type : OBS_TYPE())
	{
		ObsState state = { static_cast<OBS_TYPE>(type),{ 500.0 + 134 * static_cast<double>(type), LIMIT_UP + ((rand() % 3) * static_cast<int>((LIMIT_DOWN - LIMIT_UP) / 2.0)) } };
		_objList.emplace_back(new Obstacles(state));
	}

	// •Ï”‚Ì‰Šú‰»
	SceneCount = 0;
	lpSceneMng.bgSpeed = DFBG_SPEED;

	Init();
}


TitleScene::~TitleScene()
{
}

unique_Base TitleScene::Update(unique_Base own)
{
	// ƒGƒ“ƒ^[ƒL[‰Ÿ‰º‚ÅƒV[ƒ“•ÏX
	if (lpSceneMng.Return && !lpSceneMng.OldReturn)
	{
		return std::make_unique<GameScene>();
	}

	for (auto data : _bgList)
	{
		(*data).Updata();
	}

	// ƒIƒuƒWƒFƒNƒg‚ª‰æ–ÊŠO‚Åíœ‹y‚Ñ¶¬
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
		// •s—v‚È—v‘f‚Ìíœ
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

	// ƒQ[ƒ€ƒ^ƒCƒgƒ‹‚Æƒ^ƒCƒgƒ‹‰æ–Ê‚Å‚ÌƒeƒLƒXƒg•`‰æ
	lpSceneMng.AddDrawQue({ IMAGE_ID("À²ÄÙÃ·½Ä")[0],640.0,static_cast<double>(lpSceneMng.ScreenSize.y - (lpSceneMng.UISize.y / 2)),0.0,INT_MAX,LAYER::UI });
	lpSceneMng.AddDrawQue({ IMAGE_ID("À²ÄÙ")[0], 320.0,172.5,0.0,INT_MAX,LAYER::UI });

	SceneCount++;
	ObsCount++;
	
	return std::move(own);
}

void TitleScene::Init(void)
{
	// Å¬è”‰Šú‰»
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

#include "TitleScene.h"
#include "DxLib.h"
#include "GameScene.h"
#include "common/ImgMng.h"
#include "Bg/TitleBg.h"


TitleScene::TitleScene()
{
	lpImgMng.GetID("¿≤ƒŸîwåi", "image/title.png");
	lpImgMng.GetID("¿≤ƒŸ√∑Ωƒ", "image/TitleText.png");
	lpImgMng.GetID("¿≤ƒŸ", "image/GameName.png");
	SceneCount = 0;

	_bgList.emplace_back(new TitleBg({ TITLE_TYPE::BG ,{ 640.0,288.0 },lpSceneMng.ScreenSize }));
	_bgList.emplace_back(new TitleBg({ TITLE_TYPE::TEXT,{ 640.0,static_cast<double>(lpSceneMng.ScreenSize.y - (lpSceneMng.UISize.y / 2 ))},{600,150} }));
	_bgList.emplace_back(new TitleBg({ TITLE_TYPE::TITLE ,{ 320.0,172.5 },lpSceneMng.ScreenSize }));
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
		(*data).Draw();
	}

	SceneCount++;
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
			score[i] = 0.0;
		}
	}
	else
	{
		fread(&score[0],
			sizeof(score[0]),
			SCR_MAX,
			fp);
		fclose(fp);
	}
}

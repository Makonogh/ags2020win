#include "TitleScene.h"
#include "DxLib.h"
#include "GameScene.h"
#include "common/ImgMng.h"
#include "Bg/TitleBg.h"


TitleScene::TitleScene()
{
	lpImgMng.GetID("À²ÄÙ”wŒi", "image/title.png");
	lpImgMng.GetID("À²ÄÙÃ·½Ä", "image/TitleText.png");
	SceneCount = 0;

	_bgList.emplace_back(new TitleBg({ TITLE_TYPE::BG ,{640.0,360.0},lpSceneMng.ScreenSize }));
	_bgList.emplace_back(new TitleBg({ TITLE_TYPE::TEXT,{ 640.0,500.0 },{600,150} }));
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

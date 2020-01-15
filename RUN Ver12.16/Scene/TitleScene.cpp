#include "TitleScene.h"
#include "DxLib.h"
#include "GameScene.h"
#include "common/ImgMng.h"

TitleScene::TitleScene()
{
	lpImgMng.GetID("À²ÄÙ”wŒi", "image/pl1.png");
	lpImgMng.GetID("À²ÄÙÃ·½Ä", "image/TitleText.png");
	SceneCount = 0;
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
	//bg.Draw(BG_TYPE::TITLE);
	SceneCount++;
	return std::move(own);
}

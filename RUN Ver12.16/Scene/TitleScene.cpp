#include "TitleScene.h"
#include "DxLib.h"
#include "GameScene.h"
#include "common/ImgMng.h"

TitleScene::TitleScene()
{
	lpImgMng.GetID("���ٔw�i", "image/pl1.png");
	lpImgMng.GetID("����÷��", "image/TitleText.png");
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

#include "ResultScene.h"
#include "Scene\TitleScene.h"
#include "DxLib.h"
#include "SceneMng.h"
#include "common/ImgMng.h"

ResultScene::ResultScene()
{
	lpImgMng.GetID("ػ��Ĕw�i", "image/Obj.png");
}


ResultScene::~ResultScene()
{
}

unique_Base ResultScene::Update(unique_Base own)
{

	if (lpSceneMng.Return && !lpSceneMng.OldReturn)
	{
		return std::make_unique<TitleScene>();
	}
	
	SceneCount++;
	return std::move(own);

}
#include "ResultScene.h"
#include "Scene\TitleScene.h"
#include "DxLib.h"
#include "SceneMng.h"
#include "common/ImgMng.h"
#include "bg/ResultBg.h"

ResultScene::ResultScene()
{
	lpImgMng.GetID("Ø»ÞÙÄ”wŒi", "image/Result_Test.png");
	SceneCount = 0;
	_bgList.emplace_back(new ResultBg({ RESULT_TYPE::BG ,{ 640.0,288.0 },lpSceneMng.ScreenSize }));
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
	
	for (auto data : _bgList)
	{
		(*data).Draw();
	}

	SceneCount++;
	return std::move(own);

}
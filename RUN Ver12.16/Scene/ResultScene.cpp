#include "ResultScene.h"
#include "Scene\TitleScene.h"
#include "DxLib.h"
#include "SceneMng.h"
#include <vector>
#include "common/ImgMng.h"
#include "bg/ResultBg.h"
#include <_debug/_DebugConOut.h>

ResultScene::ResultScene()
{
	lpImgMng.GetID("ﾘｻﾞﾙﾄ背景", "image/Result.png");
	lpImgMng.GetID("ﾘｻﾞﾙﾄﾃｷｽﾄ", "image/ResultText.png");
	lpImgMng.GetID("ﾘｻﾞﾙﾄｽｺｱ", "image/number.png",{ 60, 60 }, { 10,1 });
	SceneCount = 0;
	_bgList.emplace_back(new ResultBg({ RESULT_TYPE::BG ,{ 640.0,360.0 },lpSceneMng.ScreenSize }));
	_bgList.emplace_back(new ResultBg({ RESULT_TYPE::TEXT,{ 640.0,static_cast<double>(lpSceneMng.ScreenCenter.y) },{ 600,150 } }));
	Init();
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

	 //スコアの表示
	_score = static_cast<int>(lpSceneMng.score);
	lpSceneMng.AddDrawQue({ IMAGE_ID("ﾘｻﾞﾙﾄｽｺｱ")[_score % 10],450.0,210.0,0.0,INT_MAX, LAYER::SYSTEM });
	_score /= 10;

	for (int i = 0; i < 3; i++)
	{
		lpSceneMng.AddDrawQue({ IMAGE_ID("ﾘｻﾞﾙﾄｽｺｱ")[_score % 10],330.0 - (60.0 * i),210.0,0.0,INT_MAX, LAYER::SYSTEM });
		_score /= 10;
	}


	for (int k = 0; k < SCR_MAX; k++)
	{
		tmpScore[k] = static_cast<int> (highScore[k]);

		lpSceneMng.AddDrawQue({ IMAGE_ID("ﾘｻﾞﾙﾄｽｺｱ")[tmpScore[k] % 10],990.0,150.0 + (60.0 * k),0.0,INT_MAX, LAYER::SYSTEM });
		tmpScore[k] /= 10;

		for (int i = 0; i < 3; i++)
		{
			lpSceneMng.AddDrawQue({ IMAGE_ID("ﾘｻﾞﾙﾄｽｺｱ")[tmpScore[k] % 10],870.0 - (60.0 * i),150.0 + (60.0 * k),0.0,INT_MAX, LAYER::SYSTEM });
			tmpScore[k] /= 10;
		}
	}
	return std::move(own);
}

void ResultScene::Init(void)
{
	TRACE("%d\n", static_cast<int>(lpSceneMng.score));
	for (int i = 0; i < SCR_MAX; i++)
	{
		if (highScore[i] < lpSceneMng.score)
		{
			for (int j = SCR_MAX - 2; j >= i; j--)
			{
				highScore[j + 1] = highScore[j];
			}
			highScore[i] = lpSceneMng.score;
			break;
		}
	}

	FILE* fp = NULL;
	if (fopen_s(&fp, "scr.dat", "wb") == 0)
	{
		fwrite(&highScore[0],
			sizeof(highScore[0]),
			SCR_MAX,
			fp);
		fclose(fp);
	}
}

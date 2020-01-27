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
	lpImgMng.GetID("ﾘｻﾞﾙﾄ背景", "image/Result_Test.png");
	lpImgMng.GetID("ﾘｻﾞﾙﾄｽｺｱ", "image/Result_Score.png");
	SceneCount = 0;
	_bgList.emplace_back(new ResultBg({ RESULT_TYPE::BG ,{ 640.0,288.0 },lpSceneMng.ScreenSize }));
	_bgList.emplace_back(new ResultBg({ RESULT_TYPE::SCORE,{640.0,360.0}, lpSceneMng.ScreenSize}));
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

	// スコアの表示
	for (int k = 0; k < SCR_MAX; k++)
	{
		tmpScore[k] = static_cast<int> (highScore[k]);

		lpSceneMng.AddDrawQue({ IMAGE_ID("ｽｺｱ")[tmpScore[k] % 10],730.0,270.0 + (60.0 * k),0.0,INT_MAX, LAYER::UI });
		tmpScore[k] /= 10;

		for (int i = 0; i < 3; i++)
		{
			lpSceneMng.AddDrawQue({ IMAGE_ID("ｽｺｱ")[tmpScore[k] % 10],610.0 - (60.0 * i),270.0 + (60.0 * k),0.0,INT_MAX, LAYER::UI });
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

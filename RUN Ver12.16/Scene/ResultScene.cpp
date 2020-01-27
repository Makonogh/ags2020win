#include "ResultScene.h"
#include "Scene\TitleScene.h"
#include "DxLib.h"
#include "SceneMng.h"
#include "common/ImgMng.h"
#include "bg/ResultBg.h"

ResultScene::ResultScene()
{
	lpImgMng.GetID("Ø»ÞÙÄ”wŒi", "image/Result_Test.png");
	lpImgMng.GetID("Ø»ÞÙÄ½º±", "image/Result_Score.png");
	SceneCount = 0;
	_bgList.emplace_back(new ResultBg({ RESULT_TYPE::BG ,{ 640.0,288.0 },lpSceneMng.ScreenSize }));
	_bgList.emplace_back(new ResultBg({ RESULT_TYPE::SCORE,{640.0,360.0}, lpSceneMng.ScreenSize
}));
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

	for (int i = 0; i < SCR_MAX; i++)
	{
		DrawFormatString(320, 16 + i * 16, 0xffffff, "%d:%d", i + 1, score[i]);
	}

	// ƒXƒRƒA‚Ì•\Ž¦
	for (int k = 0; k < SCR_MAX; k++)
	{
		tmpScore[k] = static_cast<int> (score[k]);

		lpSceneMng.AddDrawQue({ IMAGE_ID("½º±")[tmpScore[k] % 10],730.0,270.0 + (60.0 * k),0.0,INT_MAX, LAYER::UI });
		tmpScore[k] /= 10;

		for (int i = 0; i < 3; i++)
		{
			lpSceneMng.AddDrawQue({ IMAGE_ID("½º±")[tmpScore[k] % 10],610.0 - (60.0 * i),270.0 + (60.0 * k),0.0,INT_MAX, LAYER::UI });
			tmpScore[k] /= 10;
		}
	}

	return std::move(own);
}

void ResultScene::Init(void)
{
	for (int i = 0; i < SCR_MAX; i++)
	{
		if (score[i] < lpSceneMng.score)
		{
			for (int j = SCR_MAX - 2; j >= i; j--)
			{
				score[j + 1] = score[j];
			}
			score[i] = lpSceneMng.score;
			break;
		}
	}

	FILE* fp = NULL;
	if (fopen_s(&fp, "scr.dat", "wb") == 0)
	{
		fwrite(&score[0],
			sizeof(score[0]),
			SCR_MAX,
			fp);
		fclose(fp);
	}
}

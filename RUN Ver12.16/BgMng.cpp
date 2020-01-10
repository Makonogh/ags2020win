#include "DxLib.h"
#include "BgMng.h"
#include "Scene\SceneMng.h"
#include "common\ImgMng.h"


BgMng::BgMng()
{
}

BgMng::~BgMng()
{
}

void BgMng::BgSet(void)
{
	Bg[0] = LoadGraph("image/BGB.png");
	Bg[1] = LoadGraph("image/BG1.png");
	Bg[2] = LoadGraph("image/BG2.png");


	_Bglist.emplace_back(1);
	_Bglist.emplace_back(2);
	_Bglist.emplace_back(1);
	_Bglist.emplace_back(0);
}

void BgMng::Draw(void)
{
	for (const auto i : _Bglist)
	{
		lpSceneMng.AddDrawQue({ Bg[_Bglist[i]],0.0,INT_MAX, LAYER::BG });
	}
}

bool BgMng::Init(void)
{

	return false;
}

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


	_Bglist.emplace_back(1);
	_Bglist.emplace_back(2);
	_Bglist.emplace_back(1);
	_Bglist.emplace_back(0);
}

void BgMng::Draw(void)
{
	for (const auto i : _Bglist)
	{
		lpSceneMng.AddDrawQue({IMAGE_ID("πﬁ∞—îwåi")[_Bglist[i]],320 + i * 640.0,288.0,0.0,INT_MAX, LAYER::BG });
	}
}

bool BgMng::Init(void)
{

	return false;
}

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
	_Bglist.emplace_back();
}

void BgMng::Draw(void)
{
	for (const auto i : _Bglist)
	{
		lpSceneMng.AddDrawQue({std::get<0>,0.0,INT_MAX, LAYER::BG });
	}
}

bool BgMng::Init(void)
{

	return false;
}

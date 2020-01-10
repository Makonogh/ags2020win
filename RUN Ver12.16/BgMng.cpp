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

<<<<<<< HEAD
//void BgMng::Draw(void)
//{
//	for (const auto i : _Bglist)
//	{
//		lpSceneMng.AddDrawQue({ Bg[_Bglist[i]],0.0,INT_MAX, LAYER::BG });
//	}
//}
=======
void BgMng::Draw(void)
{
	for (const auto i : _Bglist)
	{
		lpSceneMng.AddDrawQue({IMAGE_ID("¹Þ°Ñ”wŒi")[_Bglist[i]],320 + i * 640.0,288.0,0.0,INT_MAX, LAYER::BG });
	}
}
>>>>>>> 293efa733dddd3fefc3118460008b64e49b26fc8

bool BgMng::Init(void)
{

	return false;
}

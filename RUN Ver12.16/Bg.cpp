#include <DxLib.h>
#include "Bg.h"
#include "common\ImgMng.h"
#include "Scene\SceneMng.h"


Bg::Bg()
{
}

void Bg::Updata()
{
}

void Bg::Draw(void)
{
	//if (_animMap.find(_state) == _animMap.end())
	//{
	//	return;
	//}

	//if (_animMap[_state].size() <= _animFrame || _animFrame < 0)
	//{
	//	return;
	//}

	//// ｱﾆﾑﾌﾚｰﾑが規定値まで行ったらｱﾆﾑｶｳﾝﾄが変わるようにする
	//if (_animMap[_state][_animFrame].second <= _animCount)
	//{
	//	if (_animMap[_state][_animFrame].first >= 0)
	//	{
	//		_animFrame++;
	//	}
	//}

	//_animCount++;

	//double OffSet;		// 基準座標(ｹﾞｰﾑ画面の下)とのyの差分
	//OffSet = lpSceneMng.GameSize.y - _pos.y;

	//if (_animMap[_state].size() <= _animFrame)
	//{
	//	_animFrame = 0;
	//	_animCount = 0;
	//}
	//lpSceneMng.AddDrawQue({ _animMap[_state][_animFrame].first ,_pos.x + OffSet, _pos.y ,0,_zOrder,LAYER::CHAR });
}

void Bg::Draw(int id)
{
}

Bg::~Bg()
{
}




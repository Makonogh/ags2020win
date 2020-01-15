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

	//// ±ÆÑÌÚ°Ñ‚ª‹K’è’l‚Ü‚Ås‚Á‚½‚ç±ÆÑ¶³İÄ‚ª•Ï‚í‚é‚æ‚¤‚É‚·‚é
	//if (_animMap[_state][_animFrame].second <= _animCount)
	//{
	//	if (_animMap[_state][_animFrame].first >= 0)
	//	{
	//		_animFrame++;
	//	}
	//}

	//_animCount++;

	//double OffSet;		// Šî€À•W(¹Ş°Ñ‰æ–Ê‚Ì‰º)‚Æ‚Ìy‚Ì·•ª
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




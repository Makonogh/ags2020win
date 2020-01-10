#include <DxLib.h>
#include "Bg.h"
#include "common\ImgMng.h"
#include "Scene\SceneMng.h"


Bg::Bg()
{
	bgSpeed = 4;
	_pos.x = 0.0;
	_pos.y = lpSceneMng.GameSize.y / 2;
}

Bg::~Bg()
{
}

void Bg::Draw(BG_TYPE type)
{
	switch (type)
	{
	case BG_TYPE::TITLE:
		lpSceneMng.AddDrawQue({ IMAGE_ID("À²ÄÙ”wŒi")[0],lpSceneMng.GameSize.x / 2,472,0.0,INT_MAX, LAYER::BG });
		lpSceneMng.AddDrawQue({ IMAGE_ID("À²ÄÙÃ·½Ä")[0],lpSceneMng.GameSize.x / 2,580,0.0,INT_MAX, LAYER::BG });
		break;
	case BG_TYPE::GAME:
		lpSceneMng.AddDrawQue({ IMAGE_ID("¹Þ°Ñ”wŒi")[0],_pos.x + STAGE_SIZE_X / 2,_pos.y,0.0,INT_MAX, LAYER::BG });
		break;
	case BG_TYPE::RESULT:
		lpSceneMng.AddDrawQue({ IMAGE_ID("Ø»ÞÙÄ”wŒi")[0],lpSceneMng.GameSize.x / 2,472,0.0,INT_MAX, LAYER::BG });
		break;
	default:
		break;
	}
}


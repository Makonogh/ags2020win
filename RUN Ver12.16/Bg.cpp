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
	lpSceneMng.AddDrawQue({ IMAGE_ID(image)[0],_pos.x,_pos.y ,0.0,INT_MAX, LAYER::BG });
}

void Bg::Draw(int id)
{
}

Bg::~Bg()
{
}




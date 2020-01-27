#include "Obstacles.h"
#include <common/ImgMng.h>

Obstacles::Obstacles()
{
	Init();
}

Obstacles::Obstacles(ObsState & state)
{
	_obsType = std::move(std::get <static_cast<int>(OBS_STATE::TYPE)>(state));
	_pos = std::move(std::get <static_cast<int>(OBS_STATE::VECTOR)>(state));
	_objID = OBJ_ID::OBSTACLES;

	Init();
}

void Obstacles::Updata()
{
	_pos.x -= obsSpeed;
	_lane = ((static_cast<int>(_pos.y - 360.0) % 3) + 1);
	switch (_obsType)
	{
	case OBS_TYPE::CAR:
		if (lpSceneMng.bgSpeed >= 1)
		{
			obsSpeed = lpSceneMng.bgSpeed + 3.0;
		}
		else
		{
			obsSpeed = 3.0;
		}
		break;
	case OBS_TYPE::BICYCLE:
		if (lpSceneMng.bgSpeed >= 1)
		{
			obsSpeed = lpSceneMng.bgSpeed + 1.0;
		}
		else
		{
			obsSpeed = 1.0;
		}
		break;
	case OBS_TYPE::BANANA:
		obsSpeed = lpSceneMng.bgSpeed;
		break;
	case OBS_TYPE::CONE:
		obsSpeed = lpSceneMng.bgSpeed;
		break;
	case OBS_TYPE::CAN:
		obsSpeed = lpSceneMng.bgSpeed;
		break;
	case OBS_TYPE::PUDDLE:
		_size = { 200,0.0 };
		obsSpeed = lpSceneMng.bgSpeed;
		break;

	default:
		break;
	}

	_zOrder = static_cast<int>(_pos.y);

	if (_pos.x <= -300)
	{
		_judge = true;
	}
}

Obstacles::~Obstacles()
{

}

void Obstacles::Init(void)
{
	AnimVector data;

	data.reserve(1);
	data.emplace_back(IMAGE_ID("áŠQ•¨")[static_cast<int>(_obsType)], 30);

	SizeMap[OBS_TYPE::CAR] = { 200.0,50.0 };
	SizeMap[OBS_TYPE::BICYCLE] = { 200.0,50.0 };
	SizeMap[OBS_TYPE::BANANA] = { 200.0,50.0 };
	SizeMap[OBS_TYPE::CONE] = { 200.0,50.0 };
	SizeMap[OBS_TYPE::CAN] = { 200.0,50.0 };
	SizeMap[OBS_TYPE::PUDDLE] = { 200.0,50.0 };


	SetAnim(STATE::NORMAL, data);
}

// “–‚½‚è”»’è
//void Obstacles::CheckHit(void)
//{
//	TRACE("%d\n", pl._pos.y);
//
//	if (_pos.y == pl._pos.y)
//	{
//		if (abs(_pos.x - pl._pos.x) <= (_size.x + pl._size.x) / 2)
//		{
//			pl.state(STATE::FALL);
//			pl.PlayerCount = -70;
//		}
//	}
//}

Vector2Dbl Obstacles::GetSize(OBS_TYPE key)
{
	Vector2Dbl size;
	size = SizeMap.at(key);
	return size;
}

OBS_TYPE begin(OBS_TYPE)
{
	return OBS_TYPE::CAR;
}

OBS_TYPE end(OBS_TYPE)
{
	return OBS_TYPE::MAX;
}

OBS_TYPE operator*(OBS_TYPE key)
{
	return key;
}

OBS_TYPE operator++(OBS_TYPE& key)
{
	return key = static_cast<OBS_TYPE>(std::underlying_type<OBS_TYPE>::type(key) + 1);
}

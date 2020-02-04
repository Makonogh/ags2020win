#include "Obstacles.h"
#include <common/ImgMng.h>
#include <_debug/_DebugConOut.h>

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

void Obstacles::Updata(sharedObj& list)
{
	
	_pos.x -= obsSpeed;
	_lane = ((static_cast<int>(_pos.y - 360.0) % 3) + 1);
	switch (_obsType)
	{
	case OBS_TYPE::CAR:
		if (lpSceneMng.bgSpeed >= 1.0)
		{
			obsSpeed = lpSceneMng.bgSpeed + 3.0;
		}
		else
		{
			obsSpeed = 3.0;
		}
		break;
	case OBS_TYPE::BICYCLE:
		if (lpSceneMng.bgSpeed >= 1.0)
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
		obsSpeed = lpSceneMng.bgSpeed;
		break;
	default:
		break;
	}

	CheckHit(list);

	_zOrder = static_cast<int>(_pos.y);

	if (_pos.x <= -300)
	{
		_judge = true;
	}
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

	SizeMap[OBS_TYPE::CAR] = { 100.0,50.0 };
	SizeMap[OBS_TYPE::BICYCLE] = { 40.0,50.0 };
	SizeMap[OBS_TYPE::BANANA] = { 0.0,50.0 };
	SizeMap[OBS_TYPE::CONE] = { 5.0,50.0 };
	SizeMap[OBS_TYPE::CAN] = { 0.0,50.0 };
	SizeMap[OBS_TYPE::PUDDLE] = { 75.0,50.0 };


	SetAnim(STATE::NORMAL, data);
}


void Obstacles::CheckHit(sharedObj& pl)
{
	Vector2Dbl plPos = (*pl)._pos;
	Vector2Dbl plSize = (*pl)._size;
	
	//TRACE("%d\n", pl->PlayerCount);

	double ObsSize = SizeMap[_obsType].x;

	if (_pos.y == plPos.y)
	{
		if (abs(_pos.x - plPos.x) <= (ObsSize + plSize.x) / 2)
		{
			(*pl).PlayerCount = -70;
			(*pl)._animFrame = 0;
			(*pl)._animCount = 0;
			(*pl).state(STATE::FALL);
			_judge = true;
			//TRACE("%d\n", static_cast<int>(plPos.y));
		}
	}
}

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

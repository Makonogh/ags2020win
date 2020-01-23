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
	//_size = std::move(std::get <static_cast<int>(OBS_STATE::SIZE)>(state));
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
		_size = { 200.0,0.0 };
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
		_size = { 100.0,0.0 };
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
		_size = { 60.0,0.0 };
		obsSpeed = lpSceneMng.bgSpeed;
		break;
	}
}

Obstacles::~Obstacles()
{

}

void Obstacles::Init(void)
{
	AnimVector data;

	data.reserve(1);
	data.emplace_back(IMAGE_ID("è·äQï®")[static_cast<int>(_obsType)], 30);
	SetAnim(STATE::NORMAL, data);
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
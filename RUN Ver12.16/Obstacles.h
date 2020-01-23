#pragma once
#include "Obj.h"
#include <map>

enum class OBS_TYPE
{
	CAR,		// 車
	BICYCLE,	// 自転車
	BANANA,		// バナナの皮
	CONE,
	MAX
};

enum class OBS_STATE
{
	TYPE,		// 障害物の種類
	VECTOR,		// 座標
	SIZE,		// サイズ
	MAX
};

// 障害物の状態<種類,座標,サイズ>
using ObsState = std::tuple<OBS_TYPE, Vector2Dbl, Vector2Dbl>;

class Obstacles :
	public Obj
{
public:
	Obstacles();
	Obstacles(ObsState& state);
	const OBS_TYPE& type() { return _obsType; }
	void Updata() override;
	~Obstacles();
	double obsSpeed;
private:
	OBS_TYPE _obsType;
	void Init(void);
	std::map<OBS_TYPE, Vector2Dbl> _obsMap;
	Vector2Dbl GetSize(OBS_TYPE);
};

OBS_TYPE begin(OBS_TYPE);
OBS_TYPE end(OBS_TYPE);
OBS_TYPE operator*(OBS_TYPE key);
OBS_TYPE operator++(OBS_TYPE& key);

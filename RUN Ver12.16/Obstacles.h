#pragma once
#include "Obj.h"
#include "Player.h"
#include <_debug/_DebugConOut.h>
#include <map>

enum class OBS_TYPE
{
	CAR,		// 車
	BICYCLE,	// 自転車
	BANANA,		// バナナの皮
	CONE,		// さんかくコーン
	CAN,		// 空き缶
	PUDDLE,		// 水たまり
	MAX
};

enum class OBS_STATE
{
	TYPE,		// 障害物の種類
	VECTOR,		// 座標
	SIZE,		// サイズ
	MAX
};

// 障害物の状態<種類,座標>
using ObsState = std::tuple<OBS_TYPE, Vector2Dbl>;
using ObjSize = std::pair<double,double>;



class Obstacles :
	public Obj
{
public:
	Obstacles();
	Obstacles(ObsState& state);
	const OBS_TYPE& type() { return _obsType; }
	void Updata(sharedObj& list) override;
	~Obstacles();
	double obsSpeed;
	Vector2Dbl GetSize(OBS_TYPE key);

private:
	OBS_TYPE _obsType;
	void Init(void);
	void CheckHit(sharedObj& pl);
	std::map<OBS_TYPE,Vector2Dbl> SizeMap;
	
};

OBS_TYPE begin(OBS_TYPE);
OBS_TYPE end(OBS_TYPE);
OBS_TYPE operator*(OBS_TYPE key);
OBS_TYPE operator++(OBS_TYPE& key);

#pragma once
#include "Obj.h"
#include "Player.h"
#include <_debug/_DebugConOut.h>
#include <map>

enum class OBS_TYPE
{
	CAR,		// ��
	BICYCLE,	// ���]��
	BANANA,		// �o�i�i�̔�
	CONE,		// ���񂩂��R�[��
	CAN,		// �󂫊�
	PUDDLE,		// �����܂�
	MAX
};

enum class OBS_STATE
{
	TYPE,		// ��Q���̎��
	VECTOR,		// ���W
	SIZE,		// �T�C�Y
	MAX
};

// ��Q���̏��<���,���W>
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

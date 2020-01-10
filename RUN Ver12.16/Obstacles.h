#pragma once
#include "Obj.h"

enum class OBS_TYPE
{
	CAR,		// ��
	BICYCLE,	// ���]��
	BANANA,		// �o�i�i�̔�
	MAX
};

enum class OBS_STATE
{
	TYPE,		// ��Q���̎��
	VECTOR,		// ���W
	SIZE,		// �T�C�Y
	MAX
};

// ��Q���̏��<���,���W,�T�C�Y>
using ObsState = std::tuple<OBS_TYPE, Vector2Dbl, Vector2Dbl>;

class Obstacles :
	public Obj
{
public:
	Obstacles();
	Obstacles(ObsState& state);
	const OBS_TYPE& type() { return _type; }
	void Updata() override;
	~Obstacles();
	double obsSpeed;
private:
	OBS_TYPE _type;
	void Init(void);
};

OBS_TYPE begin(OBS_TYPE);
OBS_TYPE end(OBS_TYPE);
OBS_TYPE operator*(OBS_TYPE key);
OBS_TYPE operator++(OBS_TYPE& key);

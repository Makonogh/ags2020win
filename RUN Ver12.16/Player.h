#pragma once
#include <DxLib.h>
#include "Obj.h"
#include "Obstacles.h"
#include "Input/KeyState.h"

enum class PL_STATE
{
	LANE,
	SIZE,
	MAX
};

class Player :
	public Obj
{
public:
	Player();
	Player(Vector2Dbl pos, Vector2Dbl size);
	void Updata() override;
	~Player();
private:
	Vector2Dbl plSpeed;		// プレイヤーのスピード

	void Init(void);
	bool CheckHit(int lane,Vector2Dbl plPos, Vector2Dbl plSize);
	std::shared_ptr<InputState>_input;
};

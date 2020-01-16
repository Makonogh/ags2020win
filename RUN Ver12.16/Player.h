#pragma once
#include <DxLib.h>
#include "Obj.h"
#include "Obstacles.h"
#include "Input/KeyState.h"

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
	void isHit(ObsState& state);
	void Jump(bool flag);
	std::shared_ptr<InputState>_input;
};

#pragma once
#include "Obj.h"
#include "Input/KeyState.h"

#define SPEED_X 5.0
#define SPEED_Y 5.0
#define LIMIT_UP 350.0
#define LIMIT_DOWN 504.0
#define PL_DIV_CNT 5

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
	void isHit(void);
	std::shared_ptr<InputState>_input;
};

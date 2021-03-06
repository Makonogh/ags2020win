#pragma once
#include <DxLib.h>
#include "Obj.h"
#include "Obstacles.h"
#include "Input/KeyState.h"

enum class PL_STATE
{
	SIZE,
	MAX
};

class Player :
	public Obj
{
public:
	Player();
	Player(Vector2Dbl pos, Vector2Dbl size);
	void Updata(sharedObj& list) override;
	~Player();
	Vector2Dbl GetPos(void);
	Vector2Dbl GetSize(void);
private:
	Vector2Dbl plSpeed;		// プレイヤーのスピード
	Bg bg;
	void Init(void);
	
	std::shared_ptr<InputState>_input;
};

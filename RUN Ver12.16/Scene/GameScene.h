#pragma once
#include <Scene/BaseScene.h>
#include "Obj.h"
#include <vector>

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base Update(unique_Base);
private:
	std::vector<sharedObj> _objList;
	std::vector<sharedBG> _bgList;
};


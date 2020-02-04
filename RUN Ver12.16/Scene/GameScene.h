#pragma once
#include <Scene/BaseScene.h>
#include "Obj.h"
#include <vector>

#define DFBG_SPEED 4.0

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base Update(unique_Base);
private:
	int tmpTime;
	int ObsCount;
	std::vector<sharedObj> _objList;
	std::vector<sharedBG> _bgList;
};


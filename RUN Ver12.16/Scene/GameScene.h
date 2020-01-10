#pragma once
#include <Scene/BaseScene.h>
#include "Obj.h"

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base Update(unique_Base);
	
private:
	std::vector<sharedObj> _objList;
};


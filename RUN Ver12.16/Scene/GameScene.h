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
	double score;
	int tmpScore;
private:
	int tmpTime;
	std::vector<sharedObj> _objList;
	std::vector<sharedBG> _bgList;

};


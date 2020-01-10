#pragma once
#include <Scene/BaseScene.h>
class ResultScene :
	public BaseScene
{
public:
	ResultScene();
	~ResultScene();
	unique_Base Update(unique_Base);
};


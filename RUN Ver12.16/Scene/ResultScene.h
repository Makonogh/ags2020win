#pragma once
#include <Scene/BaseScene.h>
#include <vector>

class ResultScene :
	public BaseScene
{
public:
	ResultScene();
	~ResultScene();
	unique_Base Update(unique_Base);
private:
	std::vector<sharedBG> _bgList;
};


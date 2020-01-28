#pragma once
#include <memory>
#include <vector>
#include "Bg.h"

#define SCR_MAX 3

class BaseScene;

using unique_Base = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual unique_Base Update(unique_Base) = 0;
	int SceneCount;
	static std::vector<double> highScore;

protected:
	Bg bg;
};

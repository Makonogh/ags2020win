#pragma once
#include <memory>
#include "Bg.h"

#define SCR_MAX 5

class BaseScene;

using unique_Base = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual unique_Base Update(unique_Base) = 0;
	int SceneCount;
protected:
	double score[SCR_MAX];
	Bg bg;
};

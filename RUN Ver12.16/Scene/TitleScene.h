#pragma once
#include <Scene/BaseScene.h>
#include <vector>
#include <Bg.h>


class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	unique_Base Update(unique_Base);
private:
	void Init(void);
	std::vector<sharedBG> _bgList;
};


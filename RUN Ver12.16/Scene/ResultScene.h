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
	void Init(void);
	int _score;
	int tmpScore[SCR_MAX];
	std::vector<sharedBG> _bgList;
};


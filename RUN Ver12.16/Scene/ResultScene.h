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
	int _score;						// ����̃X�R�A
	int tmpScore[SCR_MAX];			// �����L���O
	std::vector<sharedBG> _bgList;
};


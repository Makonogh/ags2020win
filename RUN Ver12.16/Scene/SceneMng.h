#pragma once

#include <common/Vector2.h>
#include "BaseScene.h"
#include "LAYER.h"
#include "../Bg.h"
#include <tuple>
#include <vector>
#include <map>

#define lpSceneMng SceneMng::GetInstance()

#define SPEED_X 5.0
#define SPEED_Y 5.0

enum class DRAW_QUE
{
	IMAGE,
	X,
	Y,
	RAD,
	ZORDER,
	LAYER
};

using DrawQueT = std::tuple<int, double, double, double, int, LAYER>;

class SceneMng
{
public:
	static SceneMng &GetInstance(void)
	{
		Create();
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new SceneMng();
		}
	}

	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	};

	
	void Run(void);
	bool AddDrawQue(DrawQueT dQue);			// �󂯎����������۳ؽĂɓ����

	const Vector2 ScreenSize;
	const Vector2 ScreenCenter;
	const Vector2 GameSize;
	const Vector2 UISize;
	int GameCount;					// �ްт̶���
	bool OldReturn;
	bool Return;
	int bgSpeed;
private:
	static SceneMng* sInstance;

	unique_Base _activeScene;				// �ư��߲���ż�݂��Ǘ�

	void Draw();

	std::map<LAYER, int> _screenID;
	std::vector<DrawQueT> _drawList;

	SceneMng();
	~SceneMng();
	bool SysInit(void);
};


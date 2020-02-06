#pragma once

#include <common/Vector2.h>
#include "BaseScene.h"
#include "LAYER.h"
#include "../Bg.h"
#include <tuple>
#include <vector>
#include <map>

#define lpSceneMng SceneMng::GetInstance()

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
	bool AddDrawQue(DrawQueT dQue);			// 受け取った情報をﾄﾞﾛｳﾘｽﾄに入れる

	const Vector2 ScreenSize;
	const Vector2 ScreenCenter;
	const Vector2 GameSize;
	const Vector2 UISize;
	int GameCount;							// ｹﾞｰﾑのｶｳﾝﾄ
	bool OldReturn;							// 1フレーム前のエンターキーの押下フラグ
	bool Return;							// 現在のエンターキーの押下フラグ
	double bgSpeed;							// 背景のスピード
	double score;							// スコア
	int tmpScore;							// スコア退避用変数
private:
	static SceneMng* sInstance;

	unique_Base _activeScene;				// ﾕﾆｰｸﾎﾟｲﾝﾀでｼｰﾝを管理

	void Draw();

	std::map<LAYER, int> _screenID;
	std::vector<DrawQueT> _drawList;

	SceneMng();
	~SceneMng();
	bool SysInit(void);
};


#pragma once
#include <vector>
#include <memory>
#include <map>
#include "common/Vector2.h"
#include "Scene\SceneMng.h"
#include "Bg.h"

#define LIMIT_UP 360.0
#define LIMIT_DOWN 504.0
#define PL_DIV_CNT 15

enum class STATE
{
	NORMAL,		// 通常状態
	RUN,
	DASH,
	JUMP,		// ジャンプ
	FALL,		// 転倒
	MAX
};

enum class OBJ_ID
{
	NON,		// 何もない状態
	PLAYER,		// プレイヤー
	OBSTACLES,  // 障害物
	MAX
};

class Obj;

using AnimVector = std::vector<std::pair<int, unsigned int>>;					// ｺﾏとﾌﾚｰﾑ
using sharedObj = std::shared_ptr<Obj>;

class Obj
{
public:
	Obj();
	virtual void Updata();
	void Draw(void);
	void Draw(int id);
	virtual ~Obj();

	bool state(const STATE state);
	const STATE state(void) const;

	const Vector2Dbl &pos(void) const;
	const Vector2Dbl &size(void) const;
	const OBJ_ID &objID(void) const;
	bool SetAnim(const STATE state, AnimVector& data);	// アニメーションのセット
	//bool isAnimEnd(void);								// アニメーションが終了しているかの情報取得
	Vector2Dbl _pos;									// 座標
	bool isJudge(void) { return _judge; }					// 死亡しているかの情報取得
private:
	std::map<STATE, AnimVector>_animMap;
	STATE _state;
protected:
	bool _judge;
	Vector2Dbl _size;									// サイズ
	int _lane;
	int _zOrder;										// 描画優先度
	OBJ_ID _objID;
	Bg bg;
	unsigned int _animCount;							// 見出しから何回ﾙｰﾌﾟしてるか
	unsigned int _animFrame;							// なんﾌﾚｰﾑか
};

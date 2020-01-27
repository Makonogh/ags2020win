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
	NORMAL,		// �ʏ���
	RUN,
	DASH,
	JUMP,		// �W�����v
	FALL,		// �]�|
	MAX
};

enum class OBJ_ID
{
	NON,		// �����Ȃ����
	PLAYER,		// �v���C���[
	OBSTACLES,  // ��Q��
	MAX
};

class Obj;

using AnimVector = std::vector<std::pair<int, unsigned int>>;					// �ς��ڰ�
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
	bool SetAnim(const STATE state, AnimVector& data);	// �A�j���[�V�����̃Z�b�g
	//bool isAnimEnd(void);								// �A�j���[�V�������I�����Ă��邩�̏��擾
	Vector2Dbl _pos;									// ���W
	bool isJudge(void) { return _judge; }					// ���S���Ă��邩�̏��擾
private:
	std::map<STATE, AnimVector>_animMap;
	STATE _state;
protected:
	bool _judge;
	Vector2Dbl _size;									// �T�C�Y
	int _lane;
	int _zOrder;										// �`��D��x
	OBJ_ID _objID;
	Bg bg;
	unsigned int _animCount;							// ���o�����牽��ٰ�߂��Ă邩
	unsigned int _animFrame;							// �Ȃ��ڰт�
};

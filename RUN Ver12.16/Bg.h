#pragma once
#include "common/Vector2.h"
#include <memory>
#include <string>

#define STAGE_SIZE_X 640
#define STAGE_SIZE_Y 216


class Bg;
using sharedBG = std::shared_ptr<Bg>;


enum class BG_STATE
{
	IMAGE,
	POS,
	SIZE,
};

class Bg
{
public:
	Bg();
	virtual void Updata();
	void Draw(void);
	virtual ~Bg();
	Vector2Dbl _pos;
private:
	
	unsigned int _animFrame;							// �Ȃ��ڰт�
	unsigned int _animCount;							// ���o�����牽��ٰ�߂��Ă邩
protected:
	std::string image;									// �e�׽�ł̲Ұ�ނ̖��O
	Vector2Dbl _size;
	int _zOrder;										// �`��D��x
};

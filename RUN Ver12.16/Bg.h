#pragma once
#include "common/Vector2.h"
#include <memory>

#define STAGE_SIZE_X 640
#define STAGE_SIZE_Y 216

class Bg;
using unique_BG = std::unique_ptr<Bg>;

enum class BG_TYPE
{
	TITLE,				// ����
	GAME,				// �ް�
	RESULT				// ػ���
};

class Bg
{
public:
	Bg();
	~Bg();
	void Draw(BG_TYPE);
	Vector2Dbl _pos;
	const Vector2Dbl _size;
	int bgSpeed;
private:
	unsigned int _animFrame;							// �Ȃ��ڰт�
	unsigned int _animCount;							// ���o�����牽��ٰ�߂��Ă邩
};


#include <DxLib.h>
#include <common/ImgMng.h>
#include "Obj.h"

Obj::Obj()
{
	_animFrame = 0;
	_animCount = 0;

	_judge = false;
}

void Obj::Draw(int id)
{
	double OffSet;		// ����W(�ްщ�ʂ̉�)�Ƃ�y�̍���
	OffSet = lpSceneMng.GameSize.y - _pos.y;
	lpSceneMng.AddDrawQue({ id,_pos.x + OffSet,_pos.y,0,_zOrder,LAYER::CHAR });
}

void Obj::Draw(void)
{
	if (_animMap.find(_state) == _animMap.end())
	{
		return;
	}

	if (_animMap[_state].size() <= _animFrame || _animFrame < 0)
	{
		return;
	}

	// ����ڰт��K��l�܂ōs�������Ѷ��Ă��ς��悤�ɂ���
	if (_animMap[_state][_animFrame].second <= _animCount)
	{
		if (_animMap[_state][_animFrame].first >= 0)
		{
			_animFrame++;
		}
	}

	

	double OffSet;		// ����W(�ްщ�ʂ̉�)�Ƃ�y�̍���
	OffSet = lpSceneMng.GameSize.y - _pos.y;

	if (_animMap[_state].size() <= _animFrame)
	{
		_animFrame = 0;
		_animCount = 0;
	}
	else
	{
		_animCount++;
	}
	lpSceneMng.AddDrawQue({ _animMap[_state][_animFrame].first ,_pos.x + OffSet, _pos.y - (LIMIT_DOWN - LIMIT_UP) / 4.0,0,_zOrder,LAYER::CHAR });
}

void Obj::Updata(std::vector<sharedObj>)
{
}

Obj::~Obj()
{
}

bool Obj::state(const STATE state)
{
	_state = state;
	return false;
}

const STATE Obj::state(void) const
{
	return _state;
}

const Vector2Dbl & Obj::pos(void) const
{
	return _pos;
}

const Vector2Dbl & Obj::size(void) const
{
	return _size;
}

const OBJ_ID & Obj::objID(void) const
{
	return _objID;
}

bool Obj::SetAnim(const STATE state, AnimVector & data)
{
	return (_animMap.try_emplace(state, std::move(data))).second;
}

#pragma once
#include <vector>
#include <map>
#include <tuple>

using BgSt = std::tuple<int, double, double>;				// �摜ID�A�����W�A�����W

class BgMng
{
public:
	BgMng();
	~BgMng();
private:
	void BgSet(void);
	void Draw(void);
	bool Init(void);
	std::vector<BgSt> _Bglist;				// ���ŗ����w�i�̃��X�g
	std::map<int, int> _BgID;				// int�𷰂ɉ摜ID��o�^
};


#pragma once
#include <vector>
#include <map>
#include <tuple>


class BgMng
{
public:
	BgMng();
	~BgMng();
private:
	int Bg[3];
	void BgSet(void);
	void Draw(void);
	bool Init(void);
	std::vector<int> _Bglist;				// Œã‚ë‚Å—¬‚·”wŒi‚ÌƒŠƒXƒg
};


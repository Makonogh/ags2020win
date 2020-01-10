#pragma once
#include <vector>
#include <map>
#include <tuple>

using BgSt = std::tuple<int, double, double>;				// ζIDAΐWAΐW

class BgMng
{
public:
	BgMng();
	~BgMng();
private:
	void BgSet(void);
	void Draw(void);
	bool Init(void);
	std::vector<BgSt> _Bglist;				// γλΕ¬·wiΜXg
	std::map<int, int> _BgID;				// intπ·°ΙζIDπo^
};


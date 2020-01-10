#pragma once
#include <vector>
#include <map>
#include <tuple>

using BgSt = std::tuple<int, double, double>;				// 画像ID、ｘ座標、ｙ座標

class BgMng
{
public:
	BgMng();
	~BgMng();
private:
	void BgSet(void);
	void Draw(void);
	bool Init(void);
	std::vector<BgSt> _Bglist;				// 後ろで流す背景のリスト
	std::map<int, int> _BgID;				// intをｷｰに画像IDを登録
};


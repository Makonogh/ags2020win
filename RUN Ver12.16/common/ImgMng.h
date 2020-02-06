#pragma once
#include <memory>
#include <map>
#include <vector>
#include "Vector2.h"

using VecInt = std::vector<int>;

#define lpImgMng ImgMng::GetInstance()
#define IMAGE_ID(KEY)(ImgMng::GetInstance().GetID(KEY))

class ImgMng
{
public:
	static ImgMng &GetInstance(void)
	{
		return *sInstance;
	}

	const VecInt& GetID(const std::string& key);
	const VecInt& GetID(const std::string& key,const std::string& fileName);
	const VecInt& GetID(const std::string& key, const std::string& fileName,
						const Vector2& divSize, const Vector2& divCnt);


private:
	struct ImgMngDeleter
	{
		void operator()(ImgMng* imageMng) const
		{
			delete imageMng;
		}
	};

	ImgMng();
	~ImgMng();

	static std::unique_ptr<ImgMng, ImgMngDeleter>sInstance;

	std::map<std::string, VecInt> imgMap;

};


#include "ImgMng.h"
#include "DxLib.h"
#include <_debug/_DebugConOut.h>

std::unique_ptr<ImgMng, ImgMng::ImgMngDeleter> ImgMng::sInstance(new ImgMng());

ImgMng::ImgMng()
{
}


ImgMng::~ImgMng()
{

}

const VecInt & ImgMng::GetID(const std::string & key) 
{
	return GetID(key,key);
}

const VecInt & ImgMng::GetID(const std::string & key, const std::string & fileName)
{
	if (imgMap.find(key) == imgMap.end())
	{
		imgMap[key].resize(1);
		imgMap[key][0] = LoadGraph(fileName.c_str());
	}
	return imgMap[key];
}

const VecInt & ImgMng::GetID(const std::string & key, const std::string & fileName, const Vector2 & divSize, const Vector2 & divCnt)
{
	if (imgMap.find(key) == imgMap.end())
	{
		VecInt tmpData;
		tmpData.resize(divCnt.x * divCnt.y);

		if (LoadDivGraph(fileName.c_str(), divCnt.x * divCnt.y, divCnt.x, divCnt.y, divSize.x, divSize.y, &tmpData[0])
			== 0)
		{
			imgMap[key] = std::move(tmpData);
		}
		else
		{
			return std::move(tmpData);
		}
	}
	return imgMap[key];
}

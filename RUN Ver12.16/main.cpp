#include <DxLib.h>		// DxLib×²ÌÞ×Ø‚ðŽg—p‚·‚é
#include "Scene\SceneMng.h"
#include <time.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	unsigned int randSeed = (unsigned int)time(NULL);
	srand(randSeed);

	SceneMng::GetInstance().Run();
	SceneMng::Destroy();
	return 0;
}

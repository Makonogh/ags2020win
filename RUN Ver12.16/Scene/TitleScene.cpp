#include "TitleScene.h"
#include "DxLib.h"
#include "GameScene.h"
#include "common/ImgMng.h"
#include "Bg/TitleBg.h"
#include "Obstacles.h"
#include <algorithm>


TitleScene::TitleScene()
{
	// ����
	lpImgMng.GetID("����÷��", "image/TitleText.png");
	lpImgMng.GetID("����", "image/GameName.png");

	// �ް�
	lpImgMng.GetID("�ްєw�i", "image/BGB.png");
	lpImgMng.GetID("UI", "image/UI2.png");
	lpImgMng.GetID("�ްѴ̪��", "image/SpeedAnim.png", { 1280,576 }, { 4,1 });
	lpImgMng.GetID("��Q��", "image/Obj1.png", { 200,200 }, { static_cast<int>(OBS_TYPE::MAX),1 });
	lpImgMng.GetID("���", "image/pl.png", { 100,150 }, { PL_DIV_CNT,1 });
	lpImgMng.GetID("�ެ���", "image/Jump.png", { 160,160 }, { PL_DIV_CNT,1 });
	lpImgMng.GetID("�]�|", "image/FALL.png", { 160,144 }, { PL_DIV_CNT,1 });
	lpImgMng.GetID("��[��", "image/ready.png", { 210,75 }, { 1,2 });
	lpImgMng.GetID("���", "image/num.png", { 60,60 }, { 10,1 });
	lpImgMng.GetID("�ްєw�i0", "image/BGB.png");
	lpImgMng.GetID("�ްєw�i1", "image/BG1.png");
	lpImgMng.GetID("�ްєw�i2", "image/BG2.png");
	lpImgMng.GetID("�ްєw�i3", "image/BG3.png");
	lpImgMng.GetID("�ްєw�i4", "image/BG4.png");
	lpImgMng.GetID("�ްєw�i5", "image/BG5.png");
	lpImgMng.GetID("�ްєw�i6", "image/BG6.png");
	lpImgMng.GetID("�ްєw�i7", "image/BG7.png");
	lpImgMng.GetID("�ްєw�i8", "image/BG8.png");
	lpImgMng.GetID("�ްєw�i9", "image/BG9.png");
	lpImgMng.GetID("�ްєw�i10", "image/BG10.png");
	lpImgMng.GetID("�ްєw�i11", "image/BG11.png");
	lpImgMng.GetID("�ްєw�i12", "image/BG12.png");
	lpImgMng.GetID("�ްєw�i13", "image/BG13.png");
	lpImgMng.GetID("�ްєw�i14", "image/BG14.png");
	lpImgMng.GetID("�ްєw�i15", "image/BG15.png");
	lpImgMng.GetID("�̪��", "image/SpeedEffect.png");

	// ػ���
	lpImgMng.GetID("ػ��Ĕw�i", "image/Result.png");
	lpImgMng.GetID("ػ���÷��", "image/ResultText.png");
	lpImgMng.GetID("ػ��Ľ��", "image/number.png", { 60, 60 }, { 10,1 });

	// �I�u�W�F�N�g�̐���
	_bgList.emplace_back(new TitleBg({ TITLE_TYPE::BG0,{ 320.0,288.0 },{ 640,576 } }));
	_bgList.emplace_back(new TitleBg({ TITLE_TYPE::BG1,{ 960.0,288.0 },{ 640,576 } }));
	_bgList.emplace_back(new TitleBg({ TITLE_TYPE::BG2,{ 1600.0,288.0 },{ 640,576 } }));

	for (auto type : OBS_TYPE())
	{
		ObsState state = { static_cast<OBS_TYPE>(type),{ 500.0 + 134 * static_cast<double>(type), LIMIT_UP + ((rand() % 3) * static_cast<int>((LIMIT_DOWN - LIMIT_UP) / 2.0)) } };
		_objList.emplace_back(new Obstacles(state));
	}

	// �ϐ��̏�����
	SceneCount = 0;
	lpSceneMng.bgSpeed = DFBG_SPEED;

	Init();
}


TitleScene::~TitleScene()
{
}

unique_Base TitleScene::Update(unique_Base own)
{
	// �G���^�[�L�[�����ŃV�[���ύX
	if (lpSceneMng.Return && !lpSceneMng.OldReturn)
	{
		return std::make_unique<GameScene>();
	}

	for (auto data : _bgList)
	{
		(*data).Updata();
	}

	// �I�u�W�F�N�g����ʊO�ō폜�y�ѐ���
	for (auto data : _bgList)
	{
		if ((*data)._pos.x <= -320)
		{
			_bgList.erase(_bgList.begin());
			_bgList.emplace_back(new TitleBg({ static_cast<TITLE_TYPE>(rand() % 16),{(*_bgList.back())._pos.x + 640,288.0 },{ 640,576 } }));

			break;
		}
	}

	for (auto data : _objList)
	{
		(*data).Updata();
	}

	for (auto data : _objList)
	{
		// �s�v�ȗv�f�̍폜
		auto itr = std::remove_if(_objList.begin(), _objList.end(), [](sharedObj& obj) {return obj->isJudge(); });
		_objList.erase(itr, _objList.end());
	}


	if (_objList.size() <= 5 && ObsCount >= 60)
	{
		ObsCount = 0;
		ObsState state = { static_cast<OBS_TYPE>(rand() % static_cast<int>(OBS_TYPE::MAX)),{ lpSceneMng.ScreenSize.x + static_cast<double>(rand() % 100), LIMIT_UP + static_cast<double>(((rand() % 3) * static_cast<int>((LIMIT_DOWN - LIMIT_UP) / 2.0))) } };
		_objList.emplace_back(new Obstacles(state));
	}
	
	for (auto data : _objList)
	{
		(*data).Draw();
	}

	for (auto data : _bgList)
	{
		(*data).Draw();
	}

	// �Q�[���^�C�g���ƃ^�C�g����ʂł̃e�L�X�g�`��
	lpSceneMng.AddDrawQue({ IMAGE_ID("����÷��")[0],640.0,static_cast<double>(lpSceneMng.ScreenSize.y - (lpSceneMng.UISize.y / 2)),0.0,INT_MAX,LAYER::UI });
	lpSceneMng.AddDrawQue({ IMAGE_ID("����")[0], 320.0,172.5,0.0,INT_MAX,LAYER::UI });

	SceneCount++;
	ObsCount++;
	
	return std::move(own);
}

void TitleScene::Init(void)
{
	// �ŏ��萔������
	FILE* fp = NULL;
	if (fopen_s(&fp, "scr.dat", "rb") != 0)
	{
		for (int i = 0; i < SCR_MAX; i++)
		{
			highScore = { 0.0, 0.0, 0.0, 0.0, 0.0 };
		}
	}
	else
	{
		highScore.resize(SCR_MAX);
		fread(&highScore[0],
			sizeof(highScore[0]),
			SCR_MAX,
			fp);
		fclose(fp);
	}
}


#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "StageSelect.h"
#include "GameData.h"
#include "EffectManager.h"
#include "UICamera.h"
#include "SaveData.h"
#include "TransitionMaker.h"
#include "OP.h"



class FadeOut : public IGameObject {
public :
	prefab::CSpriteRender* m_sptite;
	void Update() 
	{
		CVector4 mulColor = m_sptite->GetMulColor();

		mulColor.w -= 0.05f;
		if (mulColor.w < 0.0f) {
			mulColor.w = 0.0f;
			m_sptite->SetMulColor(mulColor);
			DeleteGO(this);
			return;
		}
		else {
			m_sptite->SetMulColor(mulColor);
		}
	}
};

class FadeIn : public IGameObject {
public:
	prefab::CSpriteRender* m_sptite;
	void Update()
	{
		CVector4 mulColor = m_sptite->GetMulColor();

		mulColor.w += 0.05f;
		if (mulColor.w > 1.0f) {
			mulColor.w = 1.0f;
			m_sptite->SetMulColor(mulColor);
			DeleteGO(this);
			return;
		}
		else {
			m_sptite->SetMulColor(mulColor);
		}
	}
};

Title* Title::m_instance = nullptr;

Title::Title()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;


}


Title::~Title()
{
	DeleteGOs("�t�F�[�h�A�E�g");
	DeleteGOs("�t�F�[�h�C��");
	for (int i = 0; i < m_spriteRender.size(); i++) {
		DeleteGO(m_spriteRender[i]);
	}
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
}

bool Title::Start() {

	ss = NewGO<prefab::CSoundSource>(0);
	ss->Init(L"sound/Title.wav");
	ss->SetVolume(BGM_V);
	ss->Play(true);

	//NewGame�p�^�C�g��
	//0�ԁ�NewGame�w�i
	r = NewGO<prefab::CSpriteRender>(2);
	r->Init(L"sprite/Title/Title1BG_Full.dds", 1280, 720);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//1�ԁ�Title1_h 
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/Title/Title1_h.dds", 1880.0f, 980.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	r->SetScale(misi1setscale);
	r->SetPosition({ hoge1posX, hoge1posY, 0.0f });
	m_spriteRender.push_back(r);
	//2�ԁ�Title1�w�i�@����
	r = NewGO<prefab::CSpriteRender>(4);
	r->Init(L"sprite/Title/Title1BG_Touka.dds", 1280, 720);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//3�ԁ�Title1
	r = NewGO<prefab::CSpriteRender>(4);
	r->Init(L"sprite/Title/Title1.dds", 1880.0f, 980.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//4�ԁ�Titleloop1�p
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/Title/TitlrLoop1.dds", 1000.0f, 720.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	r->SetPosition({ setloop1_1x, loop_11y, 0.0f });
	m_spriteRender.push_back(r);

	//LoadGame�p�^�C�g��
	//5�ԁ�LoadGame�w�i
	r = NewGO<prefab::CSpriteRender>(2);
	r->Init(L"sprite/Title/Title2BG_Full.dds", 1280.0f, 720.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//6�ԁ�Title2_h
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/Title/Tiele2_h.dds", 1580.0f, 720.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	r->SetScale(misi2setscale);
	r->SetPosition({ hoge2posX,hoge2posY,0.0f });
	m_spriteRender.push_back(r);
	//7�ԁ�Title2�w�i�@����
	r = NewGO<prefab::CSpriteRender>(4);
	r->Init(L"sprite/Title/Title2BG_Touka.dds", 1280.0f, 720.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//8�ԁ�Title2
	r = NewGO<prefab::CSpriteRender>(4);
	r->Init(L"sprite/Title/Tiele2.dds", 1580.0f, 720.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//9�ԁ�Titleloop2�p
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/Title/TitlrLoop2.dds", 1000.0f, 720.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	r->SetPosition({ setloop2_1x, loop_1y, 0.0f });
	m_spriteRender.push_back(r);

	//Exit�p�^�C�g��
	//10�ԁ�Exit�w�i
	r = NewGO<prefab::CSpriteRender>(2);
	r->Init(L"sprite/Title/Title3BG_Full.dds", 1280, 720);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//11�ԁ�Title3_h
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/Title/Title3_h.dds", 1380.0f, 720.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetPosition({ 0.0f,hogeposY,0.0f });
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//12�ԁ�Title3�w�i�@����
	r = NewGO<prefab::CSpriteRender>(4);
	r->Init(L"sprite/Title/Title3BG_Touka.dds", 1280.0f, 720.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//13�ԁ�Title3
	r = NewGO<prefab::CSpriteRender>(4);
	r->Init(L"sprite/Title/Title3.dds", 1380.0f, 720.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//14�ԁ�Titleloop3�p 
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/Title/TitlrLoop3.dds", 1000.0f, 720.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	r->SetPosition({ setloop3_1x, loop_1y, 0.0f });
	m_spriteRender.push_back(r);

	//15�ԁ�Titleloop1�p 2����
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/Title/TitlrLoop1.dds", 1000.0f, 720.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	r->SetPosition({ setloop1_2x, loop_12y, 0.0f });
	m_spriteRender.push_back(r);
	//16�ԁ�Titleloop2�p 2����
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/Title/TitlrLoop2.dds", 1000.0f, 720.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	r->SetPosition({ setloop2_2x, loop_2y, 0.0f });
	m_spriteRender.push_back(r);
	//17�ԁ�Titleloop3�p 2����
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/Title/TitlrLoop3.dds", 1000.0f, 720.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	r->SetPosition({ setloop3_2x, loop_2y, 0.0f });
	m_spriteRender.push_back(r);

	//18�ԁ��^�C�g��
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/rogo.dds", 440.0f, 245.0f);
	MulColor = { 1.0f,1.0f,1.0f,1.0f };
	r->SetPosition({ -330.0f ,190.0f,0.0f });
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//19�ԁ�NewGame
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/Title/NewGame.dds", 344.0f, 136.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	r->SetPosition({ -330.0f ,-70.0f,0.0f });
	m_spriteRender.push_back(r);
	//20�ԁ�LoadGame
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/Title/LoadGame.dds", 380.0f, 122.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	r->SetPosition({ -330.0f ,-180.0f,0.0f });
	m_spriteRender.push_back(r);
	//21�ԁ�Exit
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/Title/Exit.dds", 185.0f, 126.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	r->SetPosition({ -330.0f ,-300.0f,0.0f });
	m_spriteRender.push_back(r);

	//22�ԁ��~�j��
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/Title/TitleIC.dds", 80.0f, 80.0f);
	MulColor = { 1.0f,1.0f,1.0f,1.0f };
	r->SetMulColor(MulColor);
	r->SetPosition({ -550.0f ,minipos.y,0.0f });
	m_spriteRender.push_back(r);


	m_spriteRender[0]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_spriteRender[5]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
	m_spriteRender[6]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });


	return true;
}
void Title::minimusi() {

	timer++;
	if (timer <= 30) {
		minipos.y += 1.0f;
	}
	else if (timer <= 60) {
		minipos.y -= 1.0f;
	}
	else {
		timer = 0;
	}
	m_spriteRender[22]->SetPosition({ -550.0f,minipos.y,0.0f });
	
}
void Title::minimove() {
	CVector3 getpos = m_spriteRender[22]->GetPosition();
	movetimer++;

	BGM_V -= 0.1f;
	if (BGM_V < 0.0f) {
		BGM_V = 0.0f;
	}
	ss->SetVolume(BGM_V);

	if (movetimer < 10.0f) {
		getpos.x -= 10.0f;
		m_spriteRender[22]->SetPosition({ getpos.x,	minipos.y,0.0f });
	}
	else if (movetimer < 40.0f) {
		getpos.x += 50.0f;
		m_spriteRender[22]->SetPosition({ getpos.x,	minipos.y,0.0f });
	}
	else if (movetimer < 60.0f) {
		getpos.x = getpos.x;
		m_spriteRender[22]->SetPosition({ getpos.x,	minipos.y,0.0f });

	}
	else {
		minimoveflag = true;
	}
}
void Title::NewMove() {
	switch (m_new) {
	case Title::NewUp:
	{
		CVector3 pos1_1 = m_spriteRender[1]->GetPosition();
		CVector3 scale1_1 = m_spriteRender[1]->GetScale();
		diff = musi - pos1_1;
		scalediff = misi1scale - scale1_1;
		diff.y /= (float)movecount;
		scalediff /= (float)movecount;
		pos1_1.x += diff.x;
		pos1_1.y += diff.y;
		scale1_1 += scalediff;
		m_spriteRender[1]->SetPosition({ pos1_1.x,pos1_1.y,0.0f });
		m_spriteRender[1]->SetScale({ scale1_1 });
		down1timer++;
		if (down1timer > 80.0f) {
			m_new = Newloop;
		}
		break;
	}
	case Title::Newloop:
	{
		m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		m_spriteRender[3]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		m_spriteRender[4]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		m_spriteRender[15]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		//���̉H���
		if (Featherflag == false) {
			Feathertoumaina -= 0.1f;
			if (Feathertoumaina < 0.0f) {
				Feathertoumaina = 0.0f;
			}
			if (Feathertoumaina == 0.0f) {
				Featherflag = true;
			}
		}
		else if (Featherflag == true) {
			setloop1_1x += 1.0f;
			setloop1_2x += 1.0f;
			if (setloop1_1x >= 1200.0f) {
				setloop1_1x = -800.0f;
			}
			if (setloop1_2x >= 1200.0f) {
				setloop1_2x = -800.0f;
			}
			m_spriteRender[4]->SetPosition({ setloop1_1x, loop_11y, 0.0f });
			m_spriteRender[15]->SetPosition({ setloop1_2x, loop_12y, 0.0f });
		}
		m_spriteRender[0]->SetMulColor({ 1.0f,1.0f,1.0f,Feathertoumaina });
		m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,Feathertoumaina });

		if (Pad(0).IsTrigger(enButtonDown) && miniflag == false) {
			prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
			//SE�Đ�
			ss->Init(L"sound/TitleSelect.wav");
			ss->SetVolume(1.0f);
			ss->Play(false);

			m_new = NewDisappear;
		}

		break;

	}
	case Title::NewDisappear:
	{
		m_spriteRender[0]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
		m_spriteRender[3]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
		m_spriteRender[4]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
		m_spriteRender[15]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });

		CVector3 pos1_2 = m_spriteRender[1]->GetPosition();
		CVector3 scale1_2 = m_spriteRender[1]->GetScale();
		diff = musi1up - pos1_2;
		scalediff = misi1upscale - scale1_2;
		diff.y /= (float)movecount;
		scalediff /= (float)movecount;
		pos1_2.x += diff.x;
		pos1_2.y += diff.y;
		scale1_2 += scalediff;
		m_spriteRender[1]->SetPosition({ pos1_2.x,pos1_2.y,0.0f });
		m_spriteRender[1]->SetScale({ scale1_2 });
		down2timer++;
		if (down2timer > 50.0f) {
			Featherflag = false;
			Feathertoumaina = 1.0f;
			down1timer = 0;
			down2timer = 0;
			m_spriteRender[1]->SetPosition({ hoge1posX, hoge1posY, 0.0f });
			m_spriteRender[4]->SetPosition({ setloop1_1x,loop_11y,0.0f });
			m_spriteRender[15]->SetPosition({ setloop1_2x,loop_12y,0.0f });
			m_spriteRender[1]->SetScale({ misi1setscale });

			m_new = NewUp;
			FadeOut* fadeOut = NewGO<FadeOut>(0, "�t�F�[�h�A�E�g");
			fadeOut->m_sptite = m_spriteRender[0];
			fadeOut = NewGO<FadeOut>(0, "�t�F�[�h�A�E�g");
			fadeOut->m_sptite = m_spriteRender[1];
			fadeOut = NewGO<FadeOut>(0, "�t�F�[�h�A�E�g");
			fadeOut->m_sptite = m_spriteRender[10];
			fadeOut = NewGO<FadeOut>(0, "�t�F�[�h�A�E�g");
			fadeOut->m_sptite = m_spriteRender[11];

			FadeIn* fadeIn = NewGO<FadeIn>(0, "�t�F�[�h�C��");
			fadeIn->m_sptite= m_spriteRender[5];
			fadeIn = NewGO<FadeIn>(0, "�t�F�[�h�C��");
			fadeIn->m_sptite = m_spriteRender[6];

			minipos.y = -180.0f;
			m_stete = LoadGame;
		}
		break;
	}
	}
	}
void Title::LoadMove() {
	switch (m_load) {
	case Title::LoadDown:{
		CVector3 pos2_1 = m_spriteRender[6]->GetPosition();
		CVector3 scale2_1 = m_spriteRender[6]->GetScale();
		diff = musi - pos2_1;
		scalediff = misi2scale - scale2_1;
		diff /= (float)movecount;
		scalediff /= (float)movecount;
		pos2_1.x += diff.x;
		pos2_1.y += diff.y;
		scale2_1 += scalediff;
		m_spriteRender[6]->SetPosition({ pos2_1.x,pos2_1.y,0.0f });
		m_spriteRender[6]->SetScale({ scale2_1 });
		down1timer++;
		if (down1timer > 80.0f) {
			m_load = Loadloop;
		}
		break;
	}
	case Title::Loadloop:{
		m_spriteRender[7]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		m_spriteRender[8]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		m_spriteRender[9]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		m_spriteRender[16]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		if (Featherflag == false) {
			Feathertoumaina -= 0.1f;
			if (Feathertoumaina < 0.0f) {
				Feathertoumaina = 0.0f;
			}
			if (Feathertoumaina == 0.0f) {
				Featherflag = true;
			}
		}
		else {
			setloop2_1x += 1.0f;
			setloop2_2x += 1.0f;
			if (setloop2_1x >= 1200.0f) {
				setloop2_1x = -800.0f;
			}
			if (setloop2_2x >= 1200.0f) {
				setloop2_2x = -800.0f;
			}
			m_spriteRender[9]->SetPosition({ setloop2_1x, loop_1y, 0.0f });
			m_spriteRender[16]->SetPosition({ setloop2_2x, loop_2y, 0.0f });
		}
		m_spriteRender[5]->SetMulColor({ 1.0f,1.0f,1.0f,Feathertoumaina });
		m_spriteRender[6]->SetMulColor({ 1.0f,1.0f,1.0f,Feathertoumaina });

		if (Pad(0).IsTrigger(enButtonUp) && miniflag == false) {
			prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
			//SE�Đ�
			ss->Init(L"sound/TitleSelect.wav");
			ss->SetVolume(1.0f);
			ss->Play(false);

			m_load = LoadUp;
			selectflag = false;
		}
		else if (Pad(0).IsTrigger(enButtonDown) && miniflag == false) {
			prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
			//SE�Đ�
			ss->Init(L"sound/TitleSelect.wav");
			ss->SetVolume(1.0f);
			ss->Play(false);

			m_load = LoadUp;
			selectflag = true;
		}
		break;
}
	case Title::LoadUp: {
		m_spriteRender[5]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		m_spriteRender[6]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		m_spriteRender[7]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
		m_spriteRender[8]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
		m_spriteRender[9]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
		m_spriteRender[16]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });

		CVector3 pos2_2 = m_spriteRender[6]->GetPosition();
		CVector3 scale2_2 = m_spriteRender[6]->GetScale();
		diff = musi2up - pos2_2;
		scalediff = misi2bigscale - scale2_2;
		diff /= (float)movecount;
		scalediff /= (float)movecount;
		pos2_2.x += diff.x;
		pos2_2.y += diff.y;
		scale2_2 += scalediff;
		m_spriteRender[6]->SetPosition({ pos2_2.x,pos2_2.y,0.0f });
		m_spriteRender[6]->SetScale({ scale2_2 });
		down2timer++;
		if (down2timer > 50.0f) {
			Featherflag = false;
			Feathertoumaina = 1.0f;
			down1timer = 0;
			down2timer = 0;
			m_spriteRender[9]->SetPosition({ setloop2_1x,loop_1y,0.0f });
			m_spriteRender[16]->SetPosition({ setloop2_2x,loop_2y,0.0f });
			m_spriteRender[6]->SetPosition({ hoge2posX,	hoge2posY,0.0f });
			m_spriteRender[6]->SetScale({ misi2setscale });
			m_load = LoadDown;
			if (selectflag == false) {
				FadeOut* fadeOut = NewGO<FadeOut>(0, "�t�F�[�h�A�E�g");
				fadeOut->m_sptite = m_spriteRender[5];
				fadeOut = NewGO<FadeOut>(0, "�t�F�[�h�A�E�g");
				fadeOut->m_sptite = m_spriteRender[6];

				FadeIn* fadeIn = NewGO<FadeIn>(0, "�t�F�[�h�C��");
				fadeIn->m_sptite = m_spriteRender[0];
				fadeIn = NewGO<FadeIn>(0, "�t�F�[�h�C��");
				fadeIn->m_sptite = m_spriteRender[1];
				minipos.y = -70.0f;
					m_stete = NewGame;
			}
			else {
				if (selectflag == true) {
					FadeOut* fadeOut = NewGO<FadeOut>(0, "�t�F�[�h�A�E�g");
					fadeOut->m_sptite = m_spriteRender[5];
					fadeOut = NewGO<FadeOut>(0, "�t�F�[�h�A�E�g");
					fadeOut->m_sptite = m_spriteRender[6];
					FadeIn* fadeIn = NewGO<FadeIn>(0, "�t�F�[�h�C��");
					fadeIn->m_sptite = m_spriteRender[10];
					fadeIn = NewGO<FadeIn>(0, "�t�F�[�h�C��");
					fadeIn->m_sptite = m_spriteRender[11];
					minipos.y = -300.0f;
					m_stete = Exit;
				}
			}
		}
		
		Featherflag = false;
		break;
	}
	}

}

void Title::ExitMove() {
	switch (m_exit) {
	case Title::Exitdown1:
	{
		CVector3 pos3_1 = m_spriteRender[11]->GetPosition();
		diff = musi - pos3_1;
		diff.y /= (float)movecount;
		pos3_1.y += diff.y;
		m_spriteRender[11]->SetPosition({ 0.0f,pos3_1.y,0.0f });
		down1timer++;
		if (down1timer > 80.0f) {
			m_exit = Exitloop;
		}
		break;
	}
	case Title::Exitloop:
	{
		m_spriteRender[12]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		m_spriteRender[13]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		m_spriteRender[14]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		m_spriteRender[17]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		//���̉H���
		if (Featherflag == false) {
			Feathertoumaina -= 0.1f;
			if (Feathertoumaina < 0.0f) {
				Feathertoumaina = 0.0f;
			}
			if (Feathertoumaina == 0.0f ) {
				Featherflag = true;
			}		
		}
		else if(Featherflag == true){
			setloop3_1x += 1.0f;
			setloop3_2x += 1.0f;
			if (setloop3_1x >= 1000.0f) {
				setloop3_1x = -1000.0f;
			}
			if (setloop3_2x >= 1000.0f) {
				setloop3_2x = -1000.0f;
			}
			m_spriteRender[14]->SetPosition({ setloop3_1x, loop_1y, 0.0f });
			m_spriteRender[17]->SetPosition({ setloop3_2x, loop_2y, 0.0f });
		}
		m_spriteRender[10]->SetMulColor({ 1.0f,1.0f,1.0f,Feathertoumaina });
		m_spriteRender[11]->SetMulColor({ 1.0f,1.0f,1.0f,Feathertoumaina });

			if (Pad(0).IsTrigger(enButtonUp) && miniflag == false) {
				prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
				//SE�Đ�
				ss->Init(L"sound/TitleSelect.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				m_exit = Exitdown2;
			}

			break;
		
	}
	case Title::Exitdown2: 
	{
		m_spriteRender[10]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		m_spriteRender[11]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		m_spriteRender[12]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
		m_spriteRender[13]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
		m_spriteRender[14]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
		m_spriteRender[17]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });

		CVector3 pos3_2 = m_spriteRender[11]->GetPosition();
		diff = musidown - pos3_2;
		diff.y /= (float)movecount;
		pos3_2.y += diff.y;
		m_spriteRender[11]->SetPosition({ 0.0f,pos3_2.y,0.0f });
		down2timer++;
		if (down2timer > 50.0f) {
			Featherflag = false;
			Feathertoumaina = 1.0f;
			down1timer = 0;
			down2timer = 0;
			m_spriteRender[11]->SetPosition({ 0.0f,	hogeposY,0.0f });
			m_spriteRender[14]->SetPosition({ setloop3_1x,loop_1y,0.0f });
			m_spriteRender[17]->SetPosition({ setloop3_2x,loop_2y,0.0f });
			m_exit = Exitdown1;

			FadeOut* fadeOut = NewGO<FadeOut>(0, "�t�F�[�h�A�E�g");
			fadeOut->m_sptite = m_spriteRender[0];
			fadeOut = NewGO<FadeOut>(0, "�t�F�[�h�A�E�g");
			fadeOut->m_sptite = m_spriteRender[1];
			fadeOut = NewGO<FadeOut>(0, "�t�F�[�h�A�E�g");
			fadeOut->m_sptite = m_spriteRender[10];
			fadeOut = NewGO<FadeOut>(0, "�t�F�[�h�A�E�g");
			fadeOut->m_sptite = m_spriteRender[11];

			FadeIn* fadeIn = NewGO<FadeIn>(0, "�t�F�[�h�C��");
			fadeIn->m_sptite = m_spriteRender[5];
			fadeIn = NewGO<FadeIn>(0, "�t�F�[�h�C��");
			fadeIn->m_sptite = m_spriteRender[6];
			minipos.y = -180.0f;
			m_stete = LoadGame;
		}
		break;


	}
	}
}

void Title::GameStart(){

	NewMove();
	if (Pad(0).IsTrigger(enButtonA) && miniflag == false && Timer > 60) {
		prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
		//SE�Đ�
		ss->Init(L"sound/TitleOK.wav");
		ss->SetVolume(1.0f);
		ss->Play(false);

		miniflag = true;
		TransitionMaker * tm = TransitionMaker::GetInstance();
		tm->TransitionSetting(TransitionMaker::Fade, 12, 12, false);
	}
	if (minimoveflag == false && miniflag == true) {
		minimove();
	}
	else if (minimoveflag == true) {
		TransitionMaker * tm = TransitionMaker::GetInstance();
		tm->TransitionSetting(TransitionMaker::Fade, 12, 30, true);
		//NewGO<OP>(0, "OP");
		NewGO<StageSelect>(0);

		DeleteGO(this);
	}
}
void Title::GameMore() {
	
	LoadMove();
	if (Pad(0).IsTrigger(enButtonA) && miniflag==false &&  Timer > 60) {
		prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
		//SE�Đ�
		ss->Init(L"sound/TitleOK.wav");
		ss->SetVolume(1.0f);
		ss->Play(false);

		miniflag = true;
	}
	if (minimoveflag == false && miniflag == true) {
		minimove();
	}
	else if (minimoveflag == true) {
		{
			FILE* fp = fopen("save.bin", "r");
			if (fp != NULL) {
				fread(SaveData::GetInstance(), sizeof(SaveData), 1, fp);
				fread(GameData::GetInstance(), sizeof(GameData), 1, fp);
				fclose(fp);
			}
		}
		NewGO<StageSelect>(0);

		DeleteGO(this);
	}

}
void Title::GameEnd() {
	ExitMove();
	if (Pad(0).IsTrigger(enButtonA) && miniflag == false && Timer > 60) {
		prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
		//SE�Đ�
		ss->Init(L"sound/TitleOK.wav");
		ss->SetVolume(1.0f);
		ss->Play(false);

		miniflag = true;
	}
	if (minimoveflag == false && miniflag == true) {
		minimove();
	}
	else if(minimoveflag == true){
		DestroyWindow(Engine().GetHwnd());
	}

}
void Title::Update() {
	switch (m_stete) {
	case Title::NewGame:
		GameStart();	//���߂���
		m_spriteRender[19]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		m_spriteRender[20]->SetMulColor({ 1.0f,1.0f,1.0f,0.5f });
		m_spriteRender[21]->SetMulColor({ 1.0f,1.0f,1.0f,0.5f });
		break;
	case Title::LoadGame:
		GameMore();		//��������
		m_spriteRender[19]->SetMulColor({ 1.0f,1.0f,1.0f,0.5f });
		m_spriteRender[20]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		m_spriteRender[21]->SetMulColor({ 1.0f,1.0f,1.0f,0.5f });
		break;
	case Title::Exit:
		GameEnd();		//�o�C�o�C
		m_spriteRender[19]->SetMulColor({ 1.0f,1.0f,1.0f,0.5f });
		m_spriteRender[20]->SetMulColor({ 1.0f,1.0f,1.0f,0.5f });
		m_spriteRender[21]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		break;

	}

	Timer++;

	if (miniflag == false) {
		minimusi();
	}
}
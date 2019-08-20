#include "stdafx.h"
#include "Tutorial.h"

#include "GameData.h"
#include "Player.h"
#include "Bunbogu.h"
#include "BackGround.h"
#include "Player_Status.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "GameCamera.h"
#include "UICamera.h"
#include "StageSelect.h"
#include "StarItem.h"
#include "TransitionMaker.h"
#include "EffectManager.h"

Tutorial* Tutorial::m_instance = nullptr;

Tutorial::Tutorial()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;
}

Tutorial::~Tutorial()
{
	for (int i = 0; i < m_spriteRender.size(); i++) {
		DeleteGO(m_spriteRender[i]);
	}
	for (int i = 0; i < m_fontRender.size(); i++) {
		DeleteGO(m_fontRender[i]);
	}

	QueryGOs<Bunbogu>("bun", [&](Bunbogu* bunbogu) {
		bunbogu->SetDeath2();
		return true;
		});
	QueryGOs<StarItem>("Item", [&](StarItem* staritem) {
		staritem->DeleteItem2();
		return true;
		});

	DeleteGOs("Gamecamera");
	DeleteGOs("Status");
	DeleteGOs("WaveManager");
	DeleteGOs("BackGround");
	DeleteGOs("Player_Status");
	DeleteGOs("LevelSet");
	DeleteGOs("Sky");
	DeleteGOs("L_Light");

	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;

	DeleteGOs("Bug");

	NewGO<UICamera>(0, "UICamera");
	NewGO<StageSelect>(0);
	//�P�x��߂��B
	postEffect::Tonemap().SetLuminance(0.4);

}
bool Tutorial::Start() {

	//����
	EnableSpecialLigRange();

	GameData * gamedata = GameData::GetInstance();
	gamedata->SetGameMode(GameData::Tutorial);
	gamedata->GameDataReset();
	DeleteGOs("UICamera");

	NewGO<Player>(0, "Bug");
	NewGO<Player_Status>(0, "Status");
	NewGO<BackGround>(0, "BackGround");
	NewGO<GameCamera>(0, "Gamecamera");

	//�w�i��\��
	BackGround * background = BackGround::GetInstance();
	background->StageMaker(-100);

	prefab::CSky* sky = NewGO<prefab::CSky>(0, "Sky");
	sky->SetScale({ 20000.0f, 20000.0f, 20000.0f });
	sky->SetEmissionColor({ 6.1f, 6.1f, 8.1f });
	LightManager().SetAmbientLight({ 100.1f,100.1f, 100.1f });

	m_directionLig = NewGO<prefab::CDirectionLight>(0, "L_Light");
	m_directionLig->SetColor({ 900.0f, 900.0f, 1000.0f, 1.0f });
	CVector3 ligDir = { 1, -1, 1 };
	ligDir.Normalize();
	m_directionLig->SetDirection(ligDir);
	GraphicsEngine().GetShadowMap().SetLightDirection(ligDir);



	//0�ԁ��g
	r = NewGO<prefab::CSpriteRender>(5);
	r->Init(L"sprite/MemoWaku.dds", 750.0f, 366.0f*1.5f);
	r->SetPosition({ 0.0f ,M_PosY - M_YHosei,0.0f });
	MulColor = { 1.0f,1.0f,1.0f,1.0f };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//1�ԁ�A�{�^��
	r = NewGO<prefab::CSpriteRender>(7);
	r->Init(L"sprite/A_Button.dds", 50.0f, 50.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetPosition({ 250.0f,-150.0f,0.0f });
	r->SetMulColor(MulColor);
	r->SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRender.push_back(r);
	//2�ԁ����
	r = NewGO<prefab::CSpriteRender>(7);
	r->Init(L"sprite/yazirusi.dds", 100.0f, 100.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetPosition({ -500.0f,-180.0f,0.0f });
	r->SetMulColor(MulColor);
	r->SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRender.push_back(r);

	//���b�Z�[�W 0��
	f = NewGO<prefab::CFontRender>(5);
	//�\��
	text[256];
	//����
	swprintf(text, L"�V�R�E�`���E�̂������ւ悤�����I");
	//�͂��B
	f->SetText(text);
	f->SetPosition({ -300.0f,M_PosY2 - M_YHosei });
	f->SetScale(1.0f);
	f->SetColor({ 0.2f,1.0f,0.2f,1.0f });
	f->SetPivot({ 0.0f,1.0f });
	m_fontRender.push_back(f);
	//���b�Z�[�W 1��
	f = NewGO<prefab::CFontRender>(5);
	//�\��
	text[256];
	//����
	swprintf(text, L"���イ���L�[ �� �X���C�h�p�b�h �ł��ǂ�");
	//�͂��B
	f->SetText(text);
	f->SetPosition({ 0.0f,-250.0f });
	f->SetScale(1.0f);
	f->SetColor({ 1.0f,1.0f,1.0f,0.0f });
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);
	return true;
}

void Tutorial::Update() {

	m_tonemapDisableTimer -= GameTime().GetFrameDeltaTime();
	if (m_tonemapDisableTimer <= 0.0f) {
		m_tonemapDisableTimer = 0.0f;
	}
	if (m_tonemapDisableTimer > 0.0f) {
		GraphicsEngine().GetTonemap().Reset();
	}

	switch (Tutorialscene) {

	case scene1://�ŏ�
	{
		if (PushCount == 0) {//����

			if (Timer > 20) {

				CVector3 pos = m_spriteRender[0]->GetPosition();
				pos.y -= M_PosY / 20.0f;
				m_spriteRender[0]->SetPosition(pos);
				CVector2 pos2 = m_fontRender[0]->GetPosition();
				pos2.y -= M_PosY / 20.0f;
				m_fontRender[0]->SetPosition(pos2);

			}

			Timer++;

			if (Timer == 40) {
				PushCount++;
				Timer = 0;
				m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
			}
		}
		else if (PushCount == 1) {
			if (Pad(0).IsTrigger(enButtonA)) {
				ss = NewGO<prefab::CSoundSource>(0);
				//SE�Đ�
				ss->Init(L"sound/TitleOK.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				text[256];
				//����
				swprintf(text, L"���イ���L�[ �� �X���C�h�p�b�h ��\n���ǂ� �ł��܂�");
				//�͂��B
				m_fontRender[0]->SetText(text);

				PushCount++;
			}

		}
		else if (PushCount == 2) {
			if (Pad(0).IsTrigger(enButtonA)) {
				ss = NewGO<prefab::CSoundSource>(0);
				//SE�Đ�
				ss->Init(L"sound/TitleOK.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });

				PushCount++;
			}

		}
		else if (PushCount == 3) {
			if (Timer > 20) {

				CVector3 pos = m_spriteRender[0]->GetPosition();
				pos.y -= M_PosY / 20.0f;
				m_spriteRender[0]->SetPosition(pos);
				CVector2 pos2 = m_fontRender[0]->GetPosition();
				pos2.y -= M_PosY / 20.0f;
				m_fontRender[0]->SetPosition(pos2);

			}

			Timer++;

			if (Timer == 40) {
				PushCount++;
				Timer = 0;
			}
		}
		else if (PushCount == 4) {//�I������
			m_spriteRender[0]->SetPosition({ 0.0f ,M_PosY - M_YHosei,0.0f });
			m_fontRender[0]->SetPosition({ -300.0f,M_PosY2 - M_YHosei });
			m_fontRender[1]->SetColor({ 1.0f,1.0f,1.0f,1.0f });
			GameData * gamedata = GameData::GetInstance();
			gamedata->SetGameMode(GameData::Battle2D_Mode);
			Tutorialscene = scene1_Play;
			text[256];
			//����
			swprintf(text, L"�Ƃ��񂵂�ł��܂���\n���ǂ낫�܂������H");
			//�͂��B
			m_fontRender[0]->SetText(text);
			PushCount = 0;
		}

		break;
	}
	case scene1_Play://�ړ�
	{
		GameData * gamedata = GameData::GetInstance();
		int zanki = gamedata->GetZanki();
		if (zanki == 29) {
			gamedata->SetGameMode(GameData::Tutorial);
			Tutorialscene = scene2;
			m_fontRender[1]->SetColor({ 1.0f,1.0f,1.0f,0.0f });
		}

		break;
	}

	case scene2://�G��
	{
		if (PushCount == 0) {//����

			if (Timer > 20) {

				CVector3 pos = m_spriteRender[0]->GetPosition();
				pos.y -= M_PosY / 20.0f;
				m_spriteRender[0]->SetPosition(pos);
				CVector2 pos2 = m_fontRender[0]->GetPosition();
				pos2.y -= M_PosY / 20.0f;
				m_fontRender[0]->SetPosition(pos2);

			}

			Timer++;

			if (Timer == 40) {
				m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
				PushCount++;
				Timer = 0;
			}
		}
		else if (PushCount == 1) {
			if (Pad(0).IsTrigger(enButtonA)) {
				ss = NewGO<prefab::CSoundSource>(0);
				//SE�Đ�
				ss->Init(L"sound/TitleOK.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

				text[256];
				//����
				swprintf(text, L"�Ђ���ɂ���̂�����݂傤�ł�");
				//�͂��B
				m_fontRender[0]->SetText(text);

				PushCount++;
			}
		}
		else if (PushCount == 2) {
			if (Pad(0).IsTrigger(enButtonA)) {
				ss = NewGO<prefab::CSoundSource>(0);
				//SE�Đ�
				ss->Init(L"sound/TitleOK.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				text[256];
				//����
				swprintf(text, L"�����񂪂��ƁA�ǂ�ǂ�\n�ւ��Ă���...");
				//�͂��B
				m_fontRender[0]->SetText(text);

				PushCount++;
			}
		}
		else if (PushCount == 3) {
			if (Pad(0).IsTrigger(enButtonA)) {
				ss = NewGO<prefab::CSoundSource>(0);
				//SE�Đ�
				ss->Init(L"sound/TitleOK.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
				PushCount++;
			}
		}
		else if (PushCount == 4) {

			Player * player = Player::GetInstance();
			player->SetLife(1);

			if (Timer == 60) {
				text[256];
				//����
				swprintf(text, L"�Ȃ��Ȃ�Ƃ���ł��܂��܂�");
				//�͂��B
				m_fontRender[0]->SetText(text);
				m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

				Timer = -1;
				PushCount++;
			}

			Timer++;
		}
		else if (PushCount == 5) {
			if (Pad(0).IsTrigger(enButtonA)) {
				ss = NewGO<prefab::CSoundSource>(0);
				//SE�Đ�
				ss->Init(L"sound/TitleOK.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
				PushCount++;
			}
		}
		else if (PushCount == 6) {

			Player * player = Player::GetInstance();
			player->SetLife(1);

			if (Timer == 40) {
				m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });

				text[256];
				//����
				swprintf(text, L"�ł��������傤�ԁI\n�V�R�E�`���E �ɂ͂��������\n�Ȃ��܂����܂�");
				//�͂��B
				m_fontRender[0]->SetText(text);
				m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

				Timer = -1;
				PushCount++;
			}

			Timer++;
		}
		else if (PushCount == 7) {
			if (Pad(0).IsTrigger(enButtonA)) {
				ss = NewGO<prefab::CSoundSource>(0);
				//SE�Đ�
				ss->Init(L"sound/TitleOK.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				//�Z�b�g
				Player * player = Player::GetInstance();
				player->SetLife(-100);
				GameData * gamedata = GameData::GetInstance();
				gamedata->SetZanki(-1);//�c�@����

				m_spriteRender[2]->SetPosition({ -350.0f,250.0f,0.0f });
				m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

				text[256];
				//����
				swprintf(text, L"�Ђ��肤���́u���񂫁v�����邩����A\n�Ȃ�ǂł� �����炵���V�R�E�`���E��\n���������Ă���܂�");
				//�͂��B
				m_fontRender[0]->SetText(text);

				PushCount++;
			}
		}
		else if (PushCount == 8) {
			if (Pad(0).IsTrigger(enButtonA)) {
				ss = NewGO<prefab::CSoundSource>(0);
				//SE�Đ�
				ss->Init(L"sound/TitleOK.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				//�u�����[�O����
				Bunbogu* bun = NewGO<Bunbogu>(0, "bun");
				bun->SetPosition({ 500.0f,0.0f,500.0f });
				m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
				GameData * gamedata = GameData::GetInstance();
				gamedata->EnemyCounterSet(1);

				m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,0.0f });
				m_spriteRender[0]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
				m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
				PushCount++;
			}
		}
		else if (PushCount == 9) {

			if (Timer == 60) {
				text[256];
				//����
				swprintf(text, L"�Ă���������܂����I�I");
				//�͂��B
				m_fontRender[0]->SetText(text);
				m_fontRender[0]->SetColor({ 0.2f,1.0f,0.2f,1.0f });
				m_spriteRender[0]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
				m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

				Timer = -1;
				PushCount++;
			}

			Timer++;
		}
		else if (PushCount == 10) {
			if (Pad(0).IsTrigger(enButtonA)) {
				ss = NewGO<prefab::CSoundSource>(0);
				//SE�Đ�
				ss->Init(L"sound/TitleOK.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				text[256];
				//����
				swprintf(text, L"�V�R�E�`���E�� A�{�^�� ��\n�u�_�b�V���v���ł��܂�");
				//�͂��B
				m_fontRender[0]->SetText(text);

				PushCount++;
			}
		}
		else if (PushCount == 11) {
			if (Pad(0).IsTrigger(enButtonA)) {
				ss = NewGO<prefab::CSoundSource>(0);
				//SE�Đ�
				ss->Init(L"sound/TitleOK.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				text[256];
				//����
				swprintf(text, L"�_�b�V�����Ȃ���\n�Ă��ɂ��������肷�邱�Ƃ�\n���������Ƃ��ł��܂�");
				//�͂��B
				m_fontRender[0]->SetText(text);

				PushCount++;
			}
		}
		else if (PushCount == 12) {
			if (Pad(0).IsTrigger(enButtonA)) {
				ss = NewGO<prefab::CSoundSource>(0);
				//SE�Đ�
				ss->Init(L"sound/TitleOK.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				text[256];
				//����
				swprintf(text, L"������ �Ă��������������Ă���Ƃ���\n���������肵�Ă��������Ȃ��̂�\n���イ�����Ă���������");
				//�͂��B
				m_fontRender[0]->SetText(text);

				PushCount++;
			}
		}
		else if (PushCount == 13) {
			if (Pad(0).IsTrigger(enButtonA)) {
				ss = NewGO<prefab::CSoundSource>(0);
				//SE�Đ�
				ss->Init(L"sound/TitleOK.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				text[256];
				//����
				swprintf(text, L"�V�R�E�`���E�̂܂��ɂ���\n�₶�邵 �͂Ă��̂ق�������\n���߂��Ă��܂�");
				//�͂��B
				m_fontRender[0]->SetText(text);

				PushCount++;
			}
		}
		else if (PushCount == 14) {
			if (Pad(0).IsTrigger(enButtonA)) {
				ss = NewGO<prefab::CSoundSource>(0);
				//SE�Đ�
				ss->Init(L"sound/TitleOK.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				text[256];
				//����
				swprintf(text, L"����ł́A�Ă����������Ă݂܂��傤�I");
				//�͂��B
				m_fontRender[0]->SetText(text);

				PushCount++;
			}
		}
		else if (PushCount == 15) {
			if (Pad(0).IsTrigger(enButtonA)) {
				ss = NewGO<prefab::CSoundSource>(0);
				//SE�Đ�
				ss->Init(L"sound/TitleOK.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);
				m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });

				PushCount++;
				text[256];
				//����
				swprintf(text, L"A�{�^���Ń_�b�V�� ���Ȃ��� �Ă��ɂƂ���");
				//�͂��B
				m_fontRender[1]->SetText(text);
			}

		}
		else if (PushCount == 16) {
			if (Timer > 20) {

				CVector3 pos = m_spriteRender[0]->GetPosition();
				pos.y -= M_PosY / 20.0f;
				m_spriteRender[0]->SetPosition(pos);
				CVector2 pos2 = m_fontRender[0]->GetPosition();
				pos2.y -= M_PosY / 20.0f;
				m_fontRender[0]->SetPosition(pos2);

			}

			Timer++;

			if (Timer == 40) {
				PushCount++;
				Timer = 0;
			}
		}
		else if (PushCount == 17) {//�I������
			m_spriteRender[0]->SetPosition({ 0.0f ,M_PosY - M_YHosei,0.0f });
			m_fontRender[0]->SetPosition({ -300.0f,M_PosY2 - M_YHosei });
			m_fontRender[1]->SetColor({ 1.0f,1.0f,1.0f,1.0f });
			GameData * gamedata = GameData::GetInstance();
			gamedata->SetGameMode(GameData::Battle2D_Mode);
			Tutorialscene = scene2_Play;
			text[256];
			//����
			swprintf(text, L"���݂��Ƃł��I�I");
			//�͂��B
			m_fontRender[0]->SetText(text);
			PushCount = 0;
		}


		break;
	}
	case scene2_Play://�o�g���I
	{
			GameData * gamedata = GameData::GetInstance();
			int enemy = gamedata->GetEnemyCounter();
			if (enemy == 0) {
				if (Timer == 60) {
					Timer = -1;
					gamedata->SetGameMode(GameData::Tutorial);
					Tutorialscene = scene3;
					m_fontRender[1]->SetColor({ 1.0f,1.0f,1.0f,0.0f });
				}

				Timer++;
			}

			break;
		}

	case scene3://�����_�b�V��
	{
			if (PushCount == 0) {//����

				if (Timer > 40) {

					CVector3 pos = m_spriteRender[0]->GetPosition();
					pos.y -= M_PosY / 20.0f;
					m_spriteRender[0]->SetPosition(pos);
					CVector2 pos2 = m_fontRender[0]->GetPosition();
					pos2.y -= M_PosY / 20.0f;
					m_fontRender[0]->SetPosition(pos2);

				}

				Timer++;

				if (Timer == 60) {
					PushCount++;
					Timer = 0;
					m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
				}
			}
			else if (PushCount == 1) {
				if (Pad(0).IsTrigger(enButtonA)) {
					ss = NewGO<prefab::CSoundSource>(0);
					//SE�Đ�
					ss->Init(L"sound/TitleOK.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);

					text[256];
					//����
					swprintf(text, L"���������A\n���łɂ����񂶂�������܂���...");
					//�͂��B
					m_fontRender[0]->SetText(text);

					PushCount++;
				}
			}
			else if (PushCount == 2) {
				if (Pad(0).IsTrigger(enButtonA)) {
					ss = NewGO<prefab::CSoundSource>(0);
					//SE�Đ�
					ss->Init(L"sound/TitleOK.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);

					text[256];
					//����
					swprintf(text, L"�V�R�E�`���E �͂��ʂ�\n�ق� �ɂȂ�܂�");
					//�͂��B
					m_fontRender[0]->SetText(text);

					PushCount++;
				}
			}
			else if (PushCount == 3) {
				if (Pad(0).IsTrigger(enButtonA)) {
					ss = NewGO<prefab::CSoundSource>(0);
					//SE�Đ�
					ss->Init(L"sound/TitleOK.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);

					text[256];
					//����
					swprintf(text, L"���̂ق��͂����݂��Ă炵�A\n���Ȃ����������Ă����ł��傤");
					//�͂��B
					m_fontRender[0]->SetText(text);

					PushCount++;
				}
			}
			else if (PushCount == 4) {
				if (Pad(0).IsTrigger(enButtonA)) {
					ss = NewGO<prefab::CSoundSource>(0);
					//SE�Đ�
					ss->Init(L"sound/TitleOK.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);

					text[256];
					//����
					swprintf(text, L"����ł��܂�������Ƃ�����\n�ނ��ɂȂ邱�Ƃ͂���܂���");
					//�͂��B
					m_fontRender[0]->SetText(text);

					PushCount++;
				}
			}
			else if (PushCount == 5) {
				if (Pad(0).IsTrigger(enButtonA)) {
					ss = NewGO<prefab::CSoundSource>(0);
					//SE�Đ�
					ss->Init(L"sound/TitleOK.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);

					//�A�C�e���o��
					EffectManager * effectmanager = EffectManager::GetInstance();

					StarItem* ITEM = NewGO<StarItem>(0, "Item");
					ITEM->SetPosition({ 0.0f,0.0f,80.0f });
					//Effect�Đ�
					effectmanager->EffectPlayer_Post(EffectManager::ItemSpawn, { 0.0f,0.0f,80.0f }, EffectScale);
					ITEM = NewGO<StarItem>(0, "Item");
					ITEM->SetPosition({ 120.0f,0.0f,120.0f });
					effectmanager->EffectPlayer(EffectManager::ItemSpawn, { 120.0f,0.0f,120.0f }, EffectScale);
					ITEM = NewGO<StarItem>(0, "Item");
					ITEM->SetPosition({ -120.0f,0.0f,120.0f });
					effectmanager->EffectPlayer(EffectManager::ItemSpawn, { -120.0f,0.0f,120.0f }, EffectScale);
					ITEM = NewGO<StarItem>(0, "Item");
					ITEM->SetPosition({ 120.0f,0.0f,-120.0f });
					effectmanager->EffectPlayer(EffectManager::ItemSpawn, { 120.0f,0.0f,-120.0f }, EffectScale);
					ITEM = NewGO<StarItem>(0, "Item");
					ITEM->SetPosition({ -120.0f,0.0f,-120.0f });
					effectmanager->EffectPlayer(EffectManager::ItemSpawn, { -120.0f,0.0f,-120.0f }, EffectScale);

					m_spriteRender[2]->SetPosition({ 100.0f,150.0f,0.0f });
					m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

					m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,0.0f });
					m_spriteRender[0]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
					m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
					PushCount++;
				}
			}
			else if (PushCount == 6) {

				if (Timer == 120) {
					text[256];
					//����
					swprintf(text, L"�X�e�[�W�ɂ́u�X�^�[�{�b�N�X�v�Ƃ���\n�A�C�e���������Ă��܂�");
					//�͂��B
					m_fontRender[0]->SetText(text);
					m_fontRender[0]->SetColor({ 0.2f,1.0f,0.2f,1.0f });
					m_spriteRender[0]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
					m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
					m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });

					Timer = -1;
					PushCount++;
				}

				Timer++;
			}
			else if (PushCount == 7) {
				if (Pad(0).IsTrigger(enButtonA)) {
					ss = NewGO<prefab::CSoundSource>(0);
					//SE�Đ�
					ss->Init(L"sound/TitleOK.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);

					m_spriteRender[2]->SetPosition({ -450.0f,-120.0f,0.0f });
					m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

					text[256];
					//����
					swprintf(text, L"�X�^�[�{�b�N�X���Ђ낤��\n�u��イ�����Q�[�W�v��\n���傤���傤���܂�");
					//�͂��B
					m_fontRender[0]->SetText(text);

					PushCount++;
				}
			}
			else if (PushCount == 8) {
				if (Pad(0).IsTrigger(enButtonA)) {
					ss = NewGO<prefab::CSoundSource>(0);
					//SE�Đ�
					ss->Init(L"sound/TitleOK.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);

					text[256];
					//����
					swprintf(text, L"�����񂯂����ł��A\n��イ�����Q�[�W�͂��傤���傤���܂�");
					//�͂��B
					m_fontRender[0]->SetText(text);

					PushCount++;
				}
			}
			else if (PushCount == 9) {
				if (Pad(0).IsTrigger(enButtonA)) {
					ss = NewGO<prefab::CSoundSource>(0);
					//SE�Đ�
					ss->Init(L"sound/TitleOK.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);

					m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });

					text[256];
					//����
					swprintf(text, L"�V�R�E�`���E�̂܂���\n�X�^�[�{�b�N�X��5�����܂���");
					//�͂��B
					m_fontRender[0]->SetText(text);

					PushCount++;
				}
			}
			else if (PushCount == 10) {
				if (Pad(0).IsTrigger(enButtonA)) {
					ss = NewGO<prefab::CSoundSource>(0);
					//SE�Đ�
					ss->Init(L"sound/TitleOK.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);

					text[256];
					//����
					swprintf(text, L"���������Ђ���Ă݂܂��傤�I");
					//�͂��B
					m_fontRender[0]->SetText(text);

					PushCount++;
				}
			}
			else if (PushCount == 11) {
				if (Pad(0).IsTrigger(enButtonA)) {
					ss = NewGO<prefab::CSoundSource>(0);
					//SE�Đ�
					ss->Init(L"sound/TitleOK.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);

					m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });

					PushCount++;
					text[256];
					//����
					swprintf(text, L"�X�^�[�{�b�N�X���Ђ���Ă݂悤");
					//�͂��B
					m_fontRender[1]->SetText(text);
				}

			}
			else if (PushCount == 12) {
				if (Timer > 20) {

					CVector3 pos = m_spriteRender[0]->GetPosition();
					pos.y -= M_PosY / 20.0f;
					m_spriteRender[0]->SetPosition(pos);
					CVector2 pos2 = m_fontRender[0]->GetPosition();
					pos2.y -= M_PosY / 20.0f;
					m_fontRender[0]->SetPosition(pos2);

				}

				Timer++;

				if (Timer == 40) {
					PushCount++;
					Timer = 0;
				}
			}
			else if (PushCount == 13) {//�I������
				m_spriteRender[0]->SetPosition({ 0.0f ,M_PosY - M_YHosei,0.0f });
				m_fontRender[0]->SetPosition({ -300.0f,M_PosY2 - M_YHosei });
				m_fontRender[1]->SetColor({ 1.0f,1.0f,1.0f,1.0f });
				GameData * gamedata = GameData::GetInstance();
				gamedata->SetGameMode(GameData::Battle2D_Mode);
				Tutorialscene = scene3_Play;
				text[256];
				//����
				swprintf(text, L"��イ�����_�b�V�����イ��\n�ނĂ��ɂȂ� �Ă����������Ă�\n���Ԃ�͂�����܂���");
				//�͂��B
				m_fontRender[0]->SetText(text);
				PushCount = 0;
			}

			break;
		}

	case scene3_Play://�����_�b�V��
	{
			GameData * gamedata = GameData::GetInstance();
			int star = gamedata->GetStar_Power();

			if (StarFlag == false) {
				if (star == gamedata->GetMAXStar_Power()) {
					text[256];
					//����
					swprintf(text, L"Y�{�^���� ��イ�����_�b�V���I");
					//�͂��B
					m_fontRender[1]->SetText(text);

					StarFlag = true;
				}
			}
			else if (StarFlag == true) {
				if (star != gamedata->GetMAXStar_Power()) {
					if (Timer == 120) {
						Timer = -1;
						gamedata->SetGameMode(GameData::Tutorial);
						Tutorialscene = scene4;
						m_fontRender[1]->SetColor({ 1.0f,1.0f,1.0f,0.0f });
					}
					Timer++;
				}

			}

			break;
				}

	case scene4://�����
	{
		if (PushCount == 0) {//����

			if (Timer > 20) {

				CVector3 pos = m_spriteRender[0]->GetPosition();
				pos.y -= M_PosY / 20.0f;
				m_spriteRender[0]->SetPosition(pos);
				CVector2 pos2 = m_fontRender[0]->GetPosition();
				pos2.y -= M_PosY / 20.0f;
				m_fontRender[0]->SetPosition(pos2);

			}

			Timer++;

			if (Timer == 40) {
				PushCount++;
				Timer = 0;
				m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
			}
		}
		else if (PushCount == 1) {
			if (Pad(0).IsTrigger(enButtonA)) {
				ss = NewGO<prefab::CSoundSource>(0);
				//SE�Đ�
				ss->Init(L"sound/TitleOK.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				text[256];
				//����
				swprintf(text, L"��������̂Ă��� �����܂��Ă���\n�΂���ɂ����ƁA\n�܂Ƃ߂Ă������܂���I");
				//�͂��B
				m_fontRender[0]->SetText(text);

				Tutorialscene = END;
				PushCount = 0;
			}
		}

		break;
	}

	case END://��������
	{
		if (PushCount == 0) {//����

			if (GameOverFlag == false) {
				PushCount++;
				Timer = -1;
				m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
			}

			if (Timer > 20) {

				CVector3 pos = m_spriteRender[0]->GetPosition();
				pos.y -= M_PosY / 20.0f;
				m_spriteRender[0]->SetPosition(pos);
				CVector2 pos2 = m_fontRender[0]->GetPosition();
				pos2.y -= M_PosY / 20.0f;
				m_fontRender[0]->SetPosition(pos2);

			}

			Timer++;

			if (Timer == 40) {
				PushCount++;
				Timer = 0;
				m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
			}
		}
		else if (PushCount == 1) {
			if (Pad(0).IsTrigger(enButtonA)) {
				ss = NewGO<prefab::CSoundSource>(0);
				//SE�Đ�
				ss->Init(L"sound/TitleOK.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				text[256];
				//����
				swprintf(text, L"��������̂��߂�������܂�����\n�u�Ȃ炤���Ȃ��v�ł�");
				//�͂��B
				m_fontRender[0]->SetText(text);

				PushCount++;
			}

		}
		else if (PushCount == 2) {
			if (Pad(0).IsTrigger(enButtonA)) {
				ss = NewGO<prefab::CSoundSource>(0);
				//SE�Đ�
				ss->Init(L"sound/TitleOK.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				text[256];
				//����
				swprintf(text, L"���� ���Ȃ��̂������\n�V�R�E�`���E�������炵����������\n��Ă����Ă����Ă���������");
				//�͂��B
				m_fontRender[0]->SetText(text);

				PushCount++;
			}

		}
		else if (PushCount == 3) {
			if (Pad(0).IsTrigger(enButtonA)) {
				ss = NewGO<prefab::CSoundSource>(0);
				//SE�Đ�
				ss->Init(L"sound/TitleOK.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				text[256];
				//����
				swprintf(text, L"�����ꂳ�܂ł����I");
				//�͂��B
				m_fontRender[0]->SetText(text);

				PushCount++;
			}

		}
		else if (PushCount == 4) {
			if (Pad(0).IsTrigger(enButtonA)) {
				ss = NewGO<prefab::CSoundSource>(0);
				//SE�Đ�
				ss->Init(L"sound/TitleOK.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				PushCount++;
			}

		}
		else if (PushCount == 5) {

			//�I��
			if (Timer == 0) {
				TransitionMaker * tm = TransitionMaker::GetInstance();
				tm->TransitionSetting(TransitionMaker::Fade, 12, 0, false);
			}

			if (Timer == 60) {
				TransitionMaker * tm = TransitionMaker::GetInstance();
				tm->TransitionSetting(TransitionMaker::Fade, 12, 12, true);
				DeleteGO(this);
			}

			Timer++;
		}

		break;
	}

	}

	//�Q�[���I�[�o�[�Ȃ�I��
	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();
	if (mode == GameData::GameOver) {
		gamedata->SetGameMode(GameData::Tutorial);
		Tutorialscene = END;
		Timer = 0;
		GameOverFlag = true;
		text[256];
		//����
		swprintf(text, L"���񂫂��Ȃ��Ȃ����̂�\n�`���[�g���A���͂����܂��ł�");
		//�͂��B
		m_fontRender[0]->SetText(text);
		m_fontRender[1]->SetColor({ 1.0f,1.0f,1.0f,0.0f });

	}

	//�{�^���v�b�V��
	if (A_Timer == 24) {
		m_spriteRender[1]->Init(L"sprite/A_Button2.dds", 50.0f, 50.0f);
	}
	else if (A_Timer == 48) {
		A_Timer = -1;
		m_spriteRender[1]->Init(L"sprite/A_Button.dds", 50.0f, 50.0f);
	}
	A_Timer++;

	//��󃀁[�u
	if (YazirusiTimer == 12) {
		YazirusiFlag = true;
	}
	else if (YazirusiTimer == 24) {
		YazirusiFlag = false;
		YazirusiTimer = -1;
	}
	if (YazirusiFlag == false) {
		CVector3 pos = m_spriteRender[2]->GetPosition();
		pos.x += 1.0f;
		m_spriteRender[2]->SetPosition(pos);
	}
	else if (YazirusiFlag == true) {
		CVector3 pos = m_spriteRender[2]->GetPosition();
		pos.x -= 1.0f;
		m_spriteRender[2]->SetPosition(pos);
	}
	
	YazirusiTimer++;
}

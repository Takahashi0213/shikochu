#include "stdafx.h"
#include "Zukan.h"
#include "ZukanData.h"
#include "SaveData.h"
#include "UICamera.h"
#include "TransitionMaker.h"
#include "StageSelect.h"

Zukan* Zukan::m_instance = nullptr;

Zukan::Zukan()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;


}


Zukan::~Zukan()
{
	for (int i = 0; i < m_spriteRender.size(); i++) {
		DeleteGO(m_spriteRender[i]);
	}
	for (int i = 0; i < m_fontRender.size(); i++) {
		DeleteGO(m_fontRender[i]);
	}
	for (int i = 0; i < m_skinModelRender.size(); i++) {
		DeleteGO(m_skinModelRender[i]);
	}

	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;

}

bool Zukan::Start() {

	ss = NewGO<prefab::CSoundSource>(0);
	//SE�Đ�
	ss->Init(L"sound/zukan.wav");
	ss->SetVolume(1.0f);
	ss->Play(true);

	//�A�j���[�V�����Z�b�g
	int hoge = 0;
	m_mo0anim[0].Load(MonsterAnime[hoge]);
	m_mo0anim[0].SetLoopFlag(true);
	if (MonsterATK_Flag[hoge] == true) {
		m_mo0anim[1].Load(MonsterAnime_ATK[hoge]);
		m_mo0anim[1].SetLoopFlag(false);
	}
	hoge++;
	m_mo1anim[0].Load(MonsterAnime[hoge]);
	m_mo1anim[0].SetLoopFlag(true);
	if (MonsterATK_Flag[hoge] == true) {
		m_mo1anim[1].Load(MonsterAnime_ATK[hoge]);
		m_mo1anim[1].SetLoopFlag(false);
	}
	hoge++;
	m_mo2anim[0].Load(MonsterAnime[hoge]);
	m_mo2anim[0].SetLoopFlag(true);
	if (MonsterATK_Flag[hoge] == true) {
		m_mo2anim[1].Load(MonsterAnime_ATK[hoge]);
		m_mo2anim[1].SetLoopFlag(false);
	}
	hoge++;
	m_mo3anim[0].Load(MonsterAnime[hoge]);
	m_mo3anim[0].SetLoopFlag(true);
	if (MonsterATK_Flag[hoge] == true) {
		m_mo3anim[1].Load(MonsterAnime_ATK[hoge]);
		m_mo3anim[1].SetLoopFlag(false);
	}
	hoge++;
	m_mo4anim[0].Load(MonsterAnime[hoge]);
	m_mo4anim[0].SetLoopFlag(true);
	if (MonsterATK_Flag[hoge] == true) {
		m_mo4anim[1].Load(MonsterAnime_ATK[hoge]);
		m_mo4anim[1].SetLoopFlag(false);
	}
	hoge++;
	m_mo5anim[0].Load(MonsterAnime[hoge]);
	m_mo5anim[0].SetLoopFlag(true);
	if (MonsterATK_Flag[hoge] == true) {
		m_mo5anim[1].Load(MonsterAnime_ATK[hoge]);
		m_mo5anim[1].SetLoopFlag(false);
	}
	hoge++;
	m_mo6anim[0].Load(MonsterAnime[hoge]);
	m_mo6anim[0].SetLoopFlag(true);
	if (MonsterATK_Flag[hoge] == true) {
		m_mo6anim[1].Load(MonsterAnime_ATK[hoge]);
		m_mo6anim[1].SetLoopFlag(false);
	}
	hoge++;
	m_mo7anim[0].Load(MonsterAnime[hoge]);
	m_mo7anim[0].SetLoopFlag(true);
	if (MonsterATK_Flag[hoge] == true) {
		m_mo7anim[1].Load(MonsterAnime_ATK[hoge]);
		m_mo7anim[1].SetLoopFlag(false);
	}
	hoge++;
	m_mo8anim[0].Load(MonsterAnime[hoge]);
	m_mo8anim[0].SetLoopFlag(true);
	if (MonsterATK_Flag[hoge] == true) {
		m_mo8anim[1].Load(MonsterAnime_ATK[hoge]);
		m_mo8anim[1].SetLoopFlag(false);
	}
	hoge++;
	m_mo9anim[0].Load(MonsterAnime[hoge]);
	m_mo9anim[0].SetLoopFlag(true);
	if (MonsterATK_Flag[hoge] == true) {
		m_mo9anim[1].Load(MonsterAnime_ATK[hoge]);
		m_mo9anim[1].SetLoopFlag(false);
	}
	hoge++;
	m_mo10anim[0].Load(MonsterAnime[hoge]);
	m_mo10anim[0].SetLoopFlag(true);
	if (MonsterATK_Flag[hoge] == true) {
		m_mo10anim[1].Load(MonsterAnime_ATK[hoge]);
		m_mo10anim[1].SetLoopFlag(false);
	}
	hoge++;
	m_mo11anim[0].Load(MonsterAnime[hoge]);
	m_mo11anim[0].SetLoopFlag(true);
	if (MonsterATK_Flag[hoge] == true) {
		m_mo11anim[1].Load(MonsterAnime_ATK[hoge]);
		m_mo11anim[1].SetLoopFlag(false);
	}
	hoge++;
	m_mo12anim[0].Load(MonsterAnime[hoge]);
	m_mo12anim[0].SetLoopFlag(true);
	if (MonsterATK_Flag[hoge] == true) {
		m_mo12anim[1].Load(MonsterAnime_ATK[hoge]);
		m_mo12anim[1].SetLoopFlag(false);
	}
	hoge++;
	m_mo13anim[0].Load(MonsterAnime[hoge]);
	m_mo13anim[0].SetLoopFlag(true);
	if (MonsterATK_Flag[hoge] == true) {
		m_mo13anim[1].Load(MonsterAnime_ATK[hoge]);
		m_mo13anim[1].SetLoopFlag(false);
	}

	//0�� �w�i�p
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/Zukan_Haikei.dds", 1280.0f, 720.0f);
	r->SetPosition({ 0.0f ,0.0f,0.0f });
	m_spriteRender.push_back(r);
	//1�� �G�O�W�b�g���V�`
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/ExitMusi.dds", 400.0f, 400.0f);
	r->SetPosition({ 400.0f ,200.0f,0.0f });
	m_spriteRender.push_back(r);
	//2�ԁ�RB
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/RB.dds", 100.0f, 100.0f);
	r->SetPosition({ 400.0f,300.0f,0.0f });
	r->SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRender.push_back(r);
	//3�� �X
	r = NewGO<prefab::CSpriteRender>(2);
	r->Init(L"sprite/heiten.dds", 1280.0f, 720.0f);
	r->SetPosition({ -50.0f ,20.0f + 420.0f,0.0f });
	m_spriteRender.push_back(r);
	//4�� ���炢
	r = NewGO<prefab::CSpriteRender>(15);
	r->Init(L"sprite/Black.dds", 1280.0f, 720.0f);
	r->SetPosition({ 0.0f ,0.0f,0.0f });
	MulAlpha2 = 0.0f;
	MulColor = { 1.0f,1.0f,1.0f,MulAlpha2 };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);

	//�w�i 0��
	e = NewGO<prefab::CSkinModelRender>(0);
	e->Init(L"modelData/Zukan_Back.cmo", nullptr, 0);
	e->SetPosition({ 500.0f,-50.0f,-1500.0f });
	e->SetScale({ 10.0f,10.0f,10.0f });
	m_rotation.SetRotation(CVector3::AxisX, -0.6f);
	e->SetRotation(m_rotation);
	m_skinModelRender.push_back(e);
	//�����X�^�[ 1��
	e = NewGO<prefab::CSkinModelRender>(0);
	e->Init(L"modelData/hatena.cmo", nullptr, 0);
	e->SetPosition({ 90.0f,10.0f, 0.0f });
	e->SetScale({ 1.0f,1.0f,1.0f });
	m_rotation2.SetRotation(CVector3::AxisY, 3.3f);
	m_rotation *= m_rotation2;
	e->SetRotation(m_rotation);
	m_skinModelRender.push_back(e);

	//�����X�^�[�ԍ� 0��
	f = NewGO<prefab::CFontRender>(10);
	//�\��
	wchar_t text[256];
	//����
	swprintf(text, L"No.%d", SelectNow+1);
	//�͂��B
	f->SetText(text);
	f->SetPosition({ -600.0f,-200.0f });
	f->SetScale(0.8f);
	f->SetColor({ 0.2f,0.2f,0.8f,1.0f });
	f->SetPivot({ 0.0f,0.5f });
	m_fontRender.push_back(f);
	//�����X�^�[�� 1��
	f = NewGO<prefab::CFontRender>(10);
	//�\��
	text[256];
	//����
	swprintf(text, L"������������");
	//�͂��B
	f->SetText(text);
	f->SetPosition({ -600.0f,-250.0f });
	f->SetScale(1.5f);
	f->SetColor({ 0.2f,0.2f,0.2f,1.0f });
	f->SetPivot({ 0.0f,0.5f });
	m_fontRender.push_back(f);
	//������ 2��
	f = NewGO<prefab::CFontRender>(10);
	//�\��
	text[256];
	//����
	swprintf(text, L"������������������������\n������������������������\n������������������������");
	//�͂��B
	f->SetText(text);
	f->SetPosition({ -180.0f,-200.0f });
	f->SetScale(0.8f);
	f->SetColor({ 0.2f,0.2f,0.2f,1.0f });
	f->SetPivot({ 0.0f,1.0f });
	m_fontRender.push_back(f);
	//�U�����[�V�������� 3��
	f = NewGO<prefab::CFontRender>(10);
	//�\��
	text[256];
	//����
	swprintf(text, L"A�{�^��:�����������[�V����");
	//�͂��B
	f->SetText(text);
	f->SetPosition({ 460.0f,-320.0f });
	f->SetScale(0.8f);
	f->SetColor({ 0.2f,1.0f,0.2f,1.0f });
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);

	KoumokuUpdate();

	return true;
}

void Zukan::Update() {


	if (DeleteFlag == false) {

		if (Pad(0).IsTrigger(enButtonUp)) {
			SelectNow--;
			if (SelectNow == -1) {
				SelectNow = 0;
			}
			else {
				prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
				ss->Init(L"sound/SE_Page.wav");
				ss->SetVolume(0.5f);
				ss->Play(false);
				AttackAnimeFlag = false;
				KoumokuUpdate();
			}
		}
		else if (Pad(0).IsTrigger(enButtonDown)) {
			SelectNow++;
			if (SelectNow >= Monster) {
				SelectNow = Monster - 1;
			}
			else {
				prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
				ss->Init(L"sound/SE_Page.wav");
				ss->SetVolume(0.5f);
				ss->Play(false);
				AttackAnimeFlag = false;
				KoumokuUpdate();
			}
		}
		else if (Pad(0).IsPress(enButtonLeft)) {
			//�����X�^�[�̉�]
			CQuaternion qAddRot;
			qAddRot.SetRotationDeg(CVector3::AxisY, 10.0f);
			m_rotation *= qAddRot;
			m_skinModelRender[1]->SetRotation(m_rotation);

		}
		else if (Pad(0).IsPress(enButtonRight)) {
			//�����X�^�[�̉�]
			CQuaternion qAddRot;
			qAddRot.SetRotationDeg(CVector3::AxisY, -10.0f);
			m_rotation *= qAddRot;
			m_skinModelRender[1]->SetRotation(m_rotation);

		}

		else if (Pad(0).IsTrigger(enButtonA)) {
			//�����X�^�[�A�j���[�V����
			SaveData * savedata = SaveData::GetInstance();
			bool flag = savedata->GetMonFlag(SelectNow);
			if (MonsterATK_Flag[SelectNow] == true && AttackAnimeFlag ==false && flag == true) {//�󔒂łȂ��Ȃ���s
				prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
				ss->Init(L"sound/kettei.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				m_fontRender[3]->SetColor({ 1.0f,0.2f,0.2f,1.0f });

				AttackAnime(1);
				AttackAnimeFlag = true;
			}
		}

		else if (Pad(0).IsTrigger(enButtonRB1)) {
			prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/heiten2.wav");
			ss->SetVolume(1.0f);
			ss->Play(false);

			DeleteFlag = true;
		}

	}

	//�I������
	if (DeleteFlag == true) {

		BMG_V -= 0.1f;
		if (BMG_V < 0.0f) {
			BMG_V = 0.0f;
		}
		ss->SetVolume(BMG_V);

		if (Timer == 12) {
			TransitionMaker * tm = TransitionMaker::GetInstance();
			tm->TransitionSetting(TransitionMaker::Toziru, 12, 10, false);
			prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/heiten1.wav");
			ss->SetVolume(3.0f);
			ss->Play(false);
		}
		if (Timer < 50) {//��ʉ��o
			CVector3 scl = m_spriteRender[1]->GetScale();
			MulAlpha -= 0.05f;
			if (MulAlpha < 0.0f) {
				MulAlpha = 0.0f;
			}
			scl.x -= 0.1f;
			if (scl.x < 0.0f) {
				scl.x = 0.0f;
			}
			scl.y -= 0.1f;
			if (scl.y < 0.0f) {
				scl.y = 0.0f;
			}
			CVector3 pos = m_spriteRender[3]->GetPosition();
			pos.y -= 60.f;
			if (pos.y < 20.0f) {
				pos.y = 20.0f;
			}
			if (Timer > 5) {
				MulAlpha2 += 0.05f;
				if (MulAlpha2 > 0.6f) {
					MulAlpha2 = 0.6f;
				}
			}
			m_spriteRender[1]->SetMulColor({ 1.0f, 1.0f, 1.0f, MulAlpha });
			m_spriteRender[2]->SetMulColor({ 1.0f, 1.0f, 1.0f, MulAlpha });
			m_spriteRender[4]->SetMulColor({ 1.0f, 1.0f, 1.0f, MulAlpha2 });
			m_spriteRender[1]->SetScale(scl);
			m_spriteRender[3]->SetPosition(pos);

		}
		if (Timer == 50) {
			TransitionMaker * tm = TransitionMaker::GetInstance();
			tm->TransitionSetting(TransitionMaker::Toziru, 12, 10, true);
			UICamera * UIcamera = UICamera::GetInstance();
			UIcamera->CameraFlag(false);
			NewGO<StageSelect>(0);
			DeleteGO(this);
		}


		Timer++;
	}

	if (DeleteFlag == false) {
		CVector3 E_pos = m_spriteRender[1]->GetPosition();
		CVector3 E_pos2 = m_spriteRender[2]->GetPosition();
		if (E_MoveFlag == false) {
			E_pos.y += 0.2f;
			E_pos2.y += 0.2f;
		}
		else {
			E_pos.y -= 0.2f;
			E_pos2.y -= 0.2f;
		}
		m_spriteRender[1]->SetPosition(E_pos);
		m_spriteRender[2]->SetPosition(E_pos2);

		if (E_MoveTimer == 24) {
			E_MoveFlag = true;
		}
		else if (E_MoveTimer == 48) {
			E_MoveTimer = -1;
			E_MoveFlag = false;
		}
		E_MoveTimer++;
	}

	//�U���A�j���^�C�}�[
	if (AttackAnimeFlag ==true) {
		bool flag = m_skinModelRender[1]->IsPlayingAnimation(); //�Đ����łȂ��Ȃ�I������
		if (flag == false) {
			m_fontRender[3]->SetColor({ 0.2f,1.0f,0.2f,1.0f });
			AttackAnimeFlag = false;
			AttackAnime(0);
		}
	}

	//�����X�^�[�̉�]
	CQuaternion qAddRot;
	qAddRot.SetRotationDeg(CVector3::AxisY, 1.0f);
	m_rotation *= qAddRot;
	m_skinModelRender[1]->SetRotation(m_rotation);

}

//���s����ƌ��ݑI���ʒu�̓��e�ɉ�ʂ��X�V����邼
void Zukan::KoumokuUpdate() {

	//�\��
	wchar_t text[256];
	//����
	swprintf(text, L"No.%d", SelectNow + 1);
	m_fontRender[0]->SetText(text);

	SaveData * savedata = SaveData::GetInstance();
	bool flag = savedata->GetMonFlag(SelectNow);
	flag = true;
	if (flag == true) { //�����X�^�[�o�^�ς�

		for (int i = 0; i < 255; i++) {
			ModelName[i] = Reset[0];
		}
		int len = (int)wcslen(MonsterModel[SelectNow]);
		for (int z = 0; z < len + 1; z++) {
			ModelName[z] = MonsterModel[SelectNow][z];
		}

		if (SelectNow == 0) {
			DeleteGO(m_skinModelRender[1]);
			m_skinModelRender[1] = NewGO<prefab::CSkinModelRender>(0);
			m_skinModelRender[1]->Init(ModelName, m_mo0anim, 2);
			m_skinModelRender[1]->PlayAnimation(enAnimationClip_Num);
		}
		if (SelectNow == 1) {
			DeleteGO(m_skinModelRender[1]);
			m_skinModelRender[1] = NewGO<prefab::CSkinModelRender>(0);
			m_skinModelRender[1]->Init(ModelName, m_mo1anim, 2);
			m_skinModelRender[1]->PlayAnimation(enAnimationClip_Num);
		}
		if (SelectNow == 2) {
			DeleteGO(m_skinModelRender[1]);
			m_skinModelRender[1] = NewGO<prefab::CSkinModelRender>(0);
			m_skinModelRender[1]->Init(ModelName, m_mo2anim, 2);
			m_skinModelRender[1]->PlayAnimation(enAnimationClip_Num);
		}
		if (SelectNow == 3) {
			DeleteGO(m_skinModelRender[1]);
			m_skinModelRender[1] = NewGO<prefab::CSkinModelRender>(0);
			m_skinModelRender[1]->Init(ModelName, m_mo3anim, 2);
			m_skinModelRender[1]->PlayAnimation(enAnimationClip_Num);
		}
		if (SelectNow == 4) {
			DeleteGO(m_skinModelRender[1]);
			m_skinModelRender[1] = NewGO<prefab::CSkinModelRender>(0);
			m_skinModelRender[1]->Init(ModelName, m_mo4anim, 2);
			m_skinModelRender[1]->PlayAnimation(enAnimationClip_Num);
		}
		if (SelectNow == 5) {
			DeleteGO(m_skinModelRender[1]);
			m_skinModelRender[1] = NewGO<prefab::CSkinModelRender>(0);
			m_skinModelRender[1]->Init(ModelName, m_mo5anim, 2);
			m_skinModelRender[1]->PlayAnimation(enAnimationClip_Num);
		}
		if (SelectNow == 6) {
			DeleteGO(m_skinModelRender[1]);
			m_skinModelRender[1] = NewGO<prefab::CSkinModelRender>(0);
			m_skinModelRender[1]->Init(ModelName, m_mo6anim, 2);
			m_skinModelRender[1]->PlayAnimation(enAnimationClip_Num);
		}
		if (SelectNow == 7) {
			DeleteGO(m_skinModelRender[1]);
			m_skinModelRender[1] = NewGO<prefab::CSkinModelRender>(0);
			m_skinModelRender[1]->Init(ModelName, m_mo7anim, 2);
			m_skinModelRender[1]->PlayAnimation(enAnimationClip_Num);
		}
		if (SelectNow == 8) {
			DeleteGO(m_skinModelRender[1]);
			m_skinModelRender[1] = NewGO<prefab::CSkinModelRender>(0);
			m_skinModelRender[1]->Init(ModelName, m_mo8anim, 2);
			m_skinModelRender[1]->PlayAnimation(enAnimationClip_Num);
		}
		if (SelectNow == 9) {
			DeleteGO(m_skinModelRender[1]);
			m_skinModelRender[1] = NewGO<prefab::CSkinModelRender>(0);
			m_skinModelRender[1]->Init(ModelName, m_mo9anim, 2);
			m_skinModelRender[1]->PlayAnimation(enAnimationClip_Num);
		}
		if (SelectNow == 10) {
			DeleteGO(m_skinModelRender[1]);
			m_skinModelRender[1] = NewGO<prefab::CSkinModelRender>(0);
			m_skinModelRender[1]->Init(ModelName, m_mo10anim, 2);
			m_skinModelRender[1]->PlayAnimation(enAnimationClip_Num);
		}
		if (SelectNow == 11) {
			DeleteGO(m_skinModelRender[1]);
			m_skinModelRender[1] = NewGO<prefab::CSkinModelRender>(0);
			m_skinModelRender[1]->Init(ModelName, m_mo11anim, 2);
			m_skinModelRender[1]->PlayAnimation(enAnimationClip_Num);
		}
		if (SelectNow == 12) {
			DeleteGO(m_skinModelRender[1]);
			m_skinModelRender[1] = NewGO<prefab::CSkinModelRender>(0);
			m_skinModelRender[1]->Init(ModelName, m_mo12anim, 2);
			m_skinModelRender[1]->PlayAnimation(enAnimationClip_Num);
		}
		if (SelectNow == 13) {
			DeleteGO(m_skinModelRender[1]);
			m_skinModelRender[1] = NewGO<prefab::CSkinModelRender>(0);
			m_skinModelRender[1]->Init(ModelName, m_mo13anim, 2);
			m_skinModelRender[1]->PlayAnimation(enAnimationClip_Num);
		}

		m_skinModelRender[1]->SetScale(M_Scale[SelectNow]);
		m_skinModelRender[1]->SetPosition({ 90.0f + X_Hosei[SelectNow],60.0f + Y_Hosei[SelectNow], 0.0f + Z_Hosei[SelectNow] });

		//�����X�^�[��
		for (int i = 0; i < 255; i++) {
			ModelName[i] = Reset[0];
		}
		len = (int)wcslen(MonsterName[SelectNow]);
		for (int z = 0; z < len + 1; z++) {
			ModelName[z] = MonsterName[SelectNow][z];
		}
		//����
		swprintf(ModelName, ModelName);
		//�͂��B
		m_fontRender[1]->SetText(ModelName);

		//�}�Ӑ���
		for (int i = 0; i < 255; i++) {
			ModelName[i] = Reset[0];
		}
		len = (int)wcslen(Setumei[SelectNow]);
		for (int z = 0; z < len + 1; z++) {
			ModelName[z] = Setumei[SelectNow][z];
		}
		//����
		swprintf(ModelName, ModelName);
		//�͂��B
		m_fontRender[2]->SetText(ModelName);

		//�U�����[�V�����̗L��
		if (MonsterATK_Flag[SelectNow] == true) {
			m_fontRender[3]->SetColor({ 0.2f,1.0f,0.2f,1.0f });
		}
		else {
			m_fontRender[3]->SetColor({ 0.2f,1.0f,0.2f,0.0f });
		}

	}
	else if (flag == false) { //���o�^

		DeleteGO(m_skinModelRender[1]);
		m_skinModelRender[1] = NewGO<prefab::CSkinModelRender>(0);
		m_skinModelRender[1]->Init(L"modelData/hatena.cmo", nullptr, 0);
		m_skinModelRender[1]->SetScale({ 1.0f,1.0f,1.0f });
		m_skinModelRender[1]->SetPosition({ 120.0f,10.0f, 0.0f });
		text[256];
		swprintf(text, L"�H�H�H�H");
		m_fontRender[1]->SetText(text);
		text[256];
		swprintf(text, L"");
		m_fontRender[2]->SetText(text);
		m_fontRender[3]->SetColor({ 0.2f,1.0f,0.2f,0.0f });

	}

}

void Zukan::AttackAnime(int i) {

	m_skinModelRender[1]->PlayAnimation(i, 0.5f);

}
#include "stdafx.h"
#include "StageSelect.h"
#include "Game.h"
#include "GameData.h"
#include "LevelData.h"
#include "UICamera.h"
#include "SaveData.h"
#include "TransitionMaker.h"
#include "StageWait.h"
#include "PlayerUpgrade.h"
#include "Zukan.h"

StageSelect* StageSelect::m_instance = nullptr;

StageSelect::StageSelect()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;

}

StageSelect::~StageSelect()
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

bool StageSelect::Start() {

	ss = NewGO<prefab::CSoundSource>(0);
	//SE�Đ�
	ss->Init(L"sound/stageselect.wav");
	ss->SetVolume(2.0f);
	ss->Play(true);

	//����
	DisableSpecialLigRange();
	NewGO<StageWait>(0,"stagewait");
	GameData * gamedata = GameData::GetInstance();
	SelectStageNow = gamedata->GetStageNo(); //�X�e�[�WNo���擾���邺
	SelectStageNow -= 1;
	SaveData * savedata = SaveData::GetInstance();
	MAX_Stage = savedata->GetClearedStage();
	MAX_Stage++;

	//�A�j���[�V�����N���b�v�����[�h�ƃ��[�v�t���O�B
	m_animClips[enAnimationClip_motion1].Load(L"animData/StageMini1.tka");
	m_animClips[enAnimationClip_motion1].SetLoopFlag(true);
	m_animClips[enAnimationClip_motion2].Load(L"animData/StageMini2.tka");
	m_animClips[enAnimationClip_motion2].SetLoopFlag(true);
	m_animClips[enAnimationClip_motion3].Load(L"animData/StageMini3.tka");
	m_animClips[enAnimationClip_motion3].SetLoopFlag(true);

	//�K�v�ȗL�ۖ��ۂ�ݒ肷�邺
	//0�� ��̏���
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/SelectDodai.dds", 1280.0f, 220.0f);
	r->SetPosition({ 0.0f ,250.0f,0.0f });
	m_spriteRender.push_back(r);
	//1�� �^�C���J�[�h
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/Time.dds", 400.0f*1.3, 430.0f*1.3);
	r->SetPosition({ -380.0f , -80.0f,0.0f });
	m_spriteRender.push_back(r);
	//2�� �N���A�ρH
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/Clear.dds", 640.0f/2, 200.0f/2);
	r->SetPosition({ 250.0f , -200.0f ,0.0f });
	m_spriteRender.push_back(r);
	//3�� START
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/start.dds", 146.0f, 72.0f);
	r->SetPosition({ 250.0f , -300.0f ,0.0f });
	r->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_spriteRender.push_back(r);
	//4�� �����{�^��
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/Kyoka.dds", 403.0f, 288.0f);
	r->SetPosition({ 550.0f , 300.0f ,0.0f });
	r->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_spriteRender.push_back(r);
	//5�� �}�Ӄ{�^��
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/Zukan.dds", 403.0f, 288.0f);
	r->SetPosition({ -550.0f , 300.0f ,0.0f });
	r->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_spriteRender.push_back(r);

	//�����o��c���V���f���c 0��
	e = NewGO<prefab::CSkinModelRender>(10);
	e->Init(L"modelData/bug.cmo", nullptr, 0);
	e->SetPosition({ -100.0f,BugPosY,20.0f });
	e->SetScale(CVector3::One);	
	m_rotation.SetRotation(CVector3::AxisY, 3.1f);
	e->SetRotation(m_rotation);
	//e->SetEmissionColor({ 1.0f,0.5f,0.5f });
	m_skinModelRender.push_back(e);
	//�w�i 1��
	e = NewGO<prefab::CSkinModelRender>(0);
	e->Init(L"modelData/StageSelect_Back.cmo", nullptr, 0);
	e->SetPosition({ 0.0f,-50.0f,-1000.0f });
	e->SetScale({ 15.0f,15.0f,15.0f });
	e->SetRotation(CQuaternion::Identity);
	m_skinModelRender.push_back(e);

	/////////////////////////
	/////////������//////////
	/////////////////////////

	float HogePosZ = BoxPosDEF.z;

	int SettingCount = 0;
	//�n�_�ƂȂ锠���W�����߂�
	while (SettingCount < SelectStageNow)
	{
		HogePosZ += BoXMoveZ;
		SettingCount++;
	}

	for (int i = 0; i < MAX_Stage; i++) {
		e = NewGO<prefab::CSkinModelRender>(0);
		int len = (int)wcslen(StageMiniName[i]);
		for (int z = 0; z < len + 1; z++) {
			BOX_Name[z] = StageMiniName[i][z];
		}
		e->Init(BOX_Name, m_animClips, enAnimationClip_Num);
		e->SetPosition({ BoxPosDEF.x,BoxPosDEF.y,HogePosZ });
		e->SetScale({ 4.0f,4.0f,3.0f });
		m_rotation.SetRotation(CVector3::AxisY, RotBox);
		e->SetRotation(m_rotation);
		e->PlayAnimation(i);
		m_skinModelRender.push_back(e);
		HogePosZ -= BoXMoveZ;
	}

	//�n�C�X�R�A 0��
	f = NewGO<prefab::CFontRender>(11);
	//�\��
	wchar_t text[256];
	//����
	swprintf(text, L"11037");
	//�͂��B
	f->SetText(text);
	f->SetPosition({ -470.0f,-120.0f });
	f->SetScale(HighScoreFontSize);
	f->SetColor({ 0.2f,1.0f,0.2f,1.0f });
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);
	//�X�e�[�W�ԍ� 1��
	f = NewGO<prefab::CFontRender>(11);
	//�\��
	text[256];
	//����
	swprintf(text, L"STAGE 1");
	//�͂��B
	f->SetText(text);
	f->SetPosition({ 250.0f,150.0f });
	f->SetScale(StageFontSize);
	f->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);
	//�X�e�[�W�� 2��
	f = NewGO<prefab::CFontRender>(11);
	//�\��
	text[256];
	//����
	swprintf(text, L"�u����̓e�X�g���b�Z�[�W�v");
	//�͂��B
	f->SetText(text);
	f->SetPosition({ 250.0f,70.0f });
	f->SetScale(StageNameFontSize);
	f->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);

	return true;
}

void StageSelect::Update(){

	if (SelectedFlag == true && KyokaFlag == false && ZukanFlag == false) {

		BMG_V -= 0.1f;
		if (BMG_V < 0.0f) {
			BMG_V = 0.0f;
		}
		ss->SetVolume(BMG_V);

		if (Selected_Counter < 14) {//�������
			int x = 2 + SelectStageNow;
			RotBox += 0.4f;
			m_rotation.SetRotation(CVector3::AxisY, RotBox);
			m_skinModelRender[x]->SetRotation(m_rotation);
			m_skinModelRender[x]->SetPosition({ -100.0f,-100.0f,0.0f });
		}
		else if (Selected_Counter == 14) {
			int x = 2 + SelectStageNow;
			RotBox += 0.2f;
			m_rotation.SetRotation(CVector3::AxisY, RotBox);
			m_skinModelRender[x]->SetRotation(m_rotation);
			m_skinModelRender[x]->SetPosition({ -100.0f,-100.0f,0.0f });
		}
		else {
			int x = 2 + SelectStageNow;
			RotBox += 0.01f;
			m_rotation.SetRotation(CVector3::AxisY, RotBox);
			m_skinModelRender[x]->SetRotation(m_rotation);
			m_skinModelRender[x]->SetPosition({ -100.0f,-100.0f,0.0f });
		}
		//�X�e�[�W���o�E���h
		if (Selected_Counter < 7) {//���
			CVector2 pos = m_fontRender[1]->GetPosition();
			pos.y += 2.0f;
			m_fontRender[1]->SetPosition(pos);
			pos = m_fontRender[2]->GetPosition();
			pos.y += 2.0f;
			m_fontRender[2]->SetPosition(pos);
		}else if (Selected_Counter < 15) {//����
			CVector2 pos = m_fontRender[1]->GetPosition();
			pos.y -= 2.0f;
			m_fontRender[1]->SetPosition(pos);
			pos = m_fontRender[2]->GetPosition();
			pos.y -= 2.0f;
			m_fontRender[2]->SetPosition(pos);
		}

		//�J��
		if (Selected_Counter == 60) {
			TransitionMaker * tm = TransitionMaker::GetInstance();
			tm->TransitionSetting(TransitionMaker::Toziru, 12, 0, false);
		}
		//�A��
		if (Selected_Counter == 80) {
			StageWait * sw = StageWait::GetInstance();
			sw->WaitSet(SelectStageNow);
		}
		//�{�^���X�^���o�[�C
		if (Selected_Counter > 120) {
			if (StartFlag == false) {
				if (Pad(0).IsPress(enButtonA)) {
					StageWait * sw = StageWait::GetInstance();
					sw->WaitDelete();
					TransitionMaker * tm = TransitionMaker::GetInstance();
					tm->TransitionSetting(TransitionMaker::Toziru, 12, 30, true);
					StartFlag = true;
				}
			}
		}

		if (StartFlag == true) {
			if (StartCount == 30) {
				//�����
				NewGO<Game>(0, "Game");
				DeleteGOs("UICamera");
				DeleteGOs("stagewait");
				DeleteGO(this);
			}
			StartCount++;
		}

		Selected_Counter++;
	}
	else if (SelectedFlag == true && KyokaFlag == true) {//������ʂ�

		BMG_V -= 0.1f;
		if (BMG_V < 0.0f) {
			BMG_V = 0.0f;
		}
		ss->SetVolume(BMG_V);

		if (Selected_Counter < 25) {//�I���A�j���[�V����
			if (Selected_Counter < 7) {
				CVector3 scl = m_spriteRender[4]->GetScale();
				scl.x += 0.01f;
				scl.y += 0.01f;
				m_spriteRender[4]->SetScale(scl);
			}
			else if (Selected_Counter < 13) {
				CVector3 scl = m_spriteRender[4]->GetScale();
				scl.x -= 0.01f;
				scl.y -= 0.01f;
				m_spriteRender[4]->SetScale(scl);

			}
		}
		else if (Selected_Counter == 25) {
			TransitionMaker * tm = TransitionMaker::GetInstance();
			tm->TransitionSetting(TransitionMaker::Toziru, 12, 0, false);
		}
		else if (Selected_Counter == 40) {
			TransitionMaker * tm = TransitionMaker::GetInstance();
			tm->TransitionSetting(TransitionMaker::Toziru, 12, 10, true);
			NewGO<PlayerUpgrade>(0);
			DeleteGOs("stagewait");
			DeleteGO(this);
		}

		Selected_Counter++;
	}
	else if (SelectedFlag == true && ZukanFlag == true) {//�}�Ӊ�ʂ�

		BMG_V -= 0.1f;
		if (BMG_V < 0.0f) {
			BMG_V = 0.0f;
		}
		ss->SetVolume(BMG_V);

		if (Selected_Counter < 25) {//�I���A�j���[�V����
			if (Selected_Counter < 7) {
				CVector3 scl = m_spriteRender[5]->GetScale();
				scl.x += 0.01f;
				scl.y += 0.01f;
				m_spriteRender[5]->SetScale(scl);
			}
			else if (Selected_Counter < 13) {
				CVector3 scl = m_spriteRender[5]->GetScale();
				scl.x -= 0.01f;
				scl.y -= 0.01f;
				m_spriteRender[5]->SetScale(scl);

			}
		}
		else if (Selected_Counter == 25) {
			TransitionMaker * tm = TransitionMaker::GetInstance();
			tm->TransitionSetting(TransitionMaker::Toziru, 12, 0, false);
		}
		else if (Selected_Counter == 40) {
			TransitionMaker * tm = TransitionMaker::GetInstance();
			tm->TransitionSetting(TransitionMaker::Toziru, 12, 10, true);
			UICamera * UIcamera = UICamera::GetInstance();
			UIcamera->CameraFlag(true);
			NewGO<Zukan>(0);
			DeleteGOs("stagewait");
			DeleteGO(this);
		}

		Selected_Counter++;
	}
	else if (SelectedFlag == false) { //���쒆�̂ݎ��s����

		//�㉺�ړ�
		if (IdouFlag == false) {
			if (Pad(0).IsTrigger(enButtonUp)) {
				if (SelectStageNow < MAX_Stage - 1) {
					prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
					ss->Init(L"sound/SS.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);

					SelectStageNow++;
					IdouFlag = true;
				}
			}
			if (Pad(0).IsTrigger(enButtonDown)) {
				if (SelectStageNow != 0) {
					prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
					ss->Init(L"sound/SS.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);

					SelectStageNow--;
					IdouFlag = true;
				}
			}

			//����ł���
			if (Pad(0).IsTrigger(enButtonStart)) {
				prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
				ss->Init(L"sound/stageStart.wav");
				ss->SetVolume(0.5f);
				ss->Play(false);

				SelectedFlag = true;
				GameData * gamedata = GameData::GetInstance();
				gamedata->SetStageNo(SelectStageNow+1); //�X�e�[�WNo�����߂��
			}

			//������ʂցc
			if (Pad(0).IsTrigger(enButtonRB1)) {
				prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
				//SE�Đ�
				ss->Init(L"sound/kettei.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				SelectedFlag = true;
				KyokaFlag = true;
			}
			//�}�Ӊ�ʂցc
			if (Pad(0).IsTrigger(enButtonLB1)) {
				prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
				//SE�Đ�
				ss->Init(L"sound/kettei.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				SelectedFlag = true;
				ZukanFlag = true;
			}

		}

		//���͕\��
		TextUpdate();

	}

	//�㉺���钎����
	if (BugPosSet == false) {
		BugPosY -= 0.1f;
		if (BugPosY < -12.0f) {
			BugPosSet = true;
		}
	}
	else {
		BugPosY += 0.1f;
		if (BugPosY > -7.0f) {
			BugPosSet = false;
		}
	}
	m_skinModelRender[0]->SetPosition({ -100.0f,BugPosY,20.0f });

	//���z�u
	BoxUpdate();
	//�X�^�[�g�_��
	STARTUpdate();

}

void StageSelect::TextUpdate() {

	SaveData * savedata = SaveData::GetInstance();

	int highscore = savedata->GetHighScore(SelectStageNow);
	//�n�C�X�R�A�X�V
	wchar_t text[256];
	//����
	swprintf(text, L"%d", highscore);
	//�͂��B
	m_fontRender[0]->SetText(text);
	text[256];
	//����
	swprintf(text, L"STAGE %d", SelectStageNow+1);
	//�͂��B
	m_fontRender[1]->SetText(text);
	text[256];
	//����
	int len = (int)wcslen(StageName[SelectStageNow]);
	for (int z = 0; z < len + 1; z++) {
		text[z] = StageName[SelectStageNow][z];
	}
	swprintf(text, text);
	//�͂��B
	m_fontRender[2]->SetText(text);
	//�N���A����
	if (highscore > 0) {
		m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	}
	else {
		m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
	}

}

void StageSelect::BoxUpdate() {
	//���݂̈ʒu�Ɩ{������ׂ��ʒu������Ă����炻���֌������Ĉړ�����񂾁I�I�I�I�I
	int Sansyo = 2; //�Q�Ƃ���n�_
	int SettingCount = 0;
	BoxPosZ = BoxPosDEF.z;
	CVector3 Hoge_Pos;

	//�n�_�ƂȂ锠���W�����߂�
	while (SettingCount < SelectStageNow)
	{
		BoxPosZ += BoXMoveZ;
		SettingCount++;
	}

	for (int i = 0; i < MAX_Stage; i++) {

		//���ݍ��W�Ɩ{������ׂ����W���ׂ�݃_�u�X�e�b�v
		Hoge_Pos = m_skinModelRender[Sansyo]->GetPosition();

		if (Hoge_Pos.z < BoxPosZ) { //Z��������
			Hoge_Pos.z += 10.0f;
			Hoge_Pos.y -= 10.0f;
			if (Hoge_Pos.y < BoXDownY) {
				Hoge_Pos.y = BoXDownY;
			}
			if (Hoge_Pos.z >= BoxPosZ) {
				Hoge_Pos.z = BoxPosZ;
			}
			m_skinModelRender[Sansyo]->SetPosition(Hoge_Pos);
		}
		else if (Hoge_Pos.z > BoxPosZ) { //Z���傫��
			Hoge_Pos.z -= 10.0f;
			Hoge_Pos.y -= 10.0f;
			if (Hoge_Pos.y < BoXDownY) {
				Hoge_Pos.y = BoXDownY;
			}
			if (Hoge_Pos.z <= BoxPosZ) {
				Hoge_Pos.z = BoxPosZ;
			}
			m_skinModelRender[Sansyo]->SetPosition(Hoge_Pos);
		}
		else if(Hoge_Pos.z == BoxPosZ&& Hoge_Pos.y < BoxPosDEF.y){
			Hoge_Pos.y += 10.0f;
			if (Hoge_Pos.y > BoxPosDEF.y) {
				Hoge_Pos.y = BoxPosDEF.y;
			}
			m_skinModelRender[Sansyo]->SetPosition(Hoge_Pos);
		}
		else {
			if (IdouFlag == true) {
				IdouFlag = false;
			}
		}

		//�͂���
		BoxPosZ -= BoXMoveZ;
		Sansyo++;
	}

}

void StageSelect::STARTUpdate() {

	if (TenmetuTimer == 30) {
		m_spriteRender[3]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
	}else if(TenmetuTimer==60){
		m_spriteRender[3]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		TenmetuTimer = -1;
	}

	TenmetuTimer++;
}
#include "stdafx.h"
#include "GameResult.h"
#include "GameData.h"
#include "DataBase.h"
#include "SaveData.h"
#include "TransitionMaker.h"
#include "SkillData.h"

GameResult* GameResult::m_instance = nullptr;

GameResult::GameResult()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;

}

GameResult::~GameResult()
{
	DeleteAllSpriteRender();
	DeleteAllFontRender();
	for (int i = 0; i < m_spriteRender_skill.size(); i++) {
		DeleteGO(m_spriteRender_skill[i]);
	}
	for (int i = 0; i < m_fontRender_skill.size(); i++) {
		DeleteGO(m_fontRender_skill[i]);
	}

	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;

}

bool GameResult::Start() {

	ss = NewGO<prefab::CSoundSource>(0);
	//SE�Đ�
	ss->Init(L"sound/result.wav");
	ss->SetVolume(BMG_V);
	ss->Play(false);

	//�ϐ��̏���
	GameData * gamedata = GameData::GetInstance();
	SaveData * savedata = SaveData::GetInstance();
	ZankiBonus = gamedata->ZankiBonusKeisan();
	GiriBonus = gamedata->GetGiriCountKeisan();
	ItemBonus = gamedata->GetItemCountKeisan();
	FinalScore = ZankiBonus + GiriBonus + ItemBonus;
	NowStage = gamedata->GetStageNo();
	Point_Count = gamedata->GetPoint();
	Point = Point_Count + FinalScore;
	HardFlag = gamedata->GetHardModeFlag();
	HardHosei = gamedata->GetHardScoreHosei();
	KikoFlag = gamedata->GetKikoFlag();
	KikoBonus= gamedata->GetKikoBonus();
	if (savedata->GetSkill(false) == 19 || savedata->GetSkill(true) == 19 || savedata->GetSkill(false) == 20 || savedata->GetSkill(true) == 20 || savedata->GetSkill(false) == 21 || savedata->GetSkill(true) == 21) {
		SkillFlag = true;
	}
	SkillGetSetup(); //�X�L���̔���

	//0�ԁ��w�i
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/ResultBG.dds", 1920.0f, 1080.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//1�ԁ��g�i���j
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/Result_Back.dds", 400.0f, 1080.0f);
	HogePosition1 = -1200.0f;
	r->SetPosition({ HogePosition1 ,0.0f,0.0f });
	m_spriteRender.push_back(r);
	//2�ԁ��g�i�E�j
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/Result_Back.dds", 400.0f, 1080.0f);
	HogePosition2 = 1200.0f;
	r->SetPosition({ HogePosition2 ,0.0f,0.0f });
	m_spriteRender.push_back(r);
	//3�ԁ�����1
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/ResultAccessory.dds", 300.0f, 720.0f);
	r->SetPosition({ ACCPositionX ,0.0f,0.0f });
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//4�ԁ�����2
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/ResultAccessory.dds", 300.0f, 720.0f);
	r->SetPosition({ ACCPositionX ,-720.0f,0.0f });
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//5�ԁ�����1
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/ResultAccessoryM.dds", 300.0f, 720.0f);
	r->SetPosition({ -ACCPositionX ,360.0f,0.0f });
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//6�ԁ�����2
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/ResultAccessoryM.dds", 300.0f, 720.0f);
	r->SetPosition({ -ACCPositionX ,-360.0f,0.0f });
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);

	return true;
}

void GameResult::Update() {

	switch (ResultTurn) {

	case scene1_Background://�w�i���������\��
	{
		//�w�i���t�F�[�h
		MulColor.a=MulAlpha;
		m_spriteRender[0]->SetMulColor(MulColor);
		m_spriteRender[3]->SetMulColor(MulColor);
		m_spriteRender[4]->SetMulColor(MulColor);
		m_spriteRender[5]->SetMulColor(MulColor);
		m_spriteRender[6]->SetMulColor(MulColor);

		//���E�g���ړ�
		HogePosition1 += WakuMoveSpeed;
		if (HogePosition1 > -WakuSpeedDown) {
			HogePosition1 -= WakuMoveSpeed * WakuSpeedDownHosei;
		}
		if (HogePosition1 > -WakuPositon) {
			HogePosition1 = -WakuPositon;
		}
		//
		HogePosition2 -= WakuMoveSpeed;
		if (HogePosition2 < WakuSpeedDown) {
			HogePosition2 += WakuMoveSpeed * WakuSpeedDownHosei;
		}
		if (HogePosition2 < WakuPositon) {
			HogePosition2 = WakuPositon;
		}
		m_spriteRender[1]->SetPosition({ HogePosition1 ,0.0f,0.0f });
		m_spriteRender[2]->SetPosition({ HogePosition2 ,0.0f,0.0f });

		MulPuls();

		//�����v���I���Ƌ��������A����̑J�ڂ��K���i�^�C�}�[���I�����Ԃƈ�v�������Ƀt�F�C�Y�����ɐi�߂܂��I�j
		if (Hoge_Couneter >= PhaseTimer1) {
			CountReset();
			ResultTurn = scene1_ResultMozi;
		}
		break;
	}

	case scene1_ResultMozi://���U���g�̕�����\������
	{
		if (Hoge_Couneter == 1) {//�ŏ���
			//7�ԁ����U���g
			r = NewGO<prefab::CSpriteRender>(1);
			r->Init(L"sprite/Result_Bar.dds", 691.0f, 218.0f);
			HogePosition1 = -850.0f;
			r->SetPosition({ HogePosition1 ,ResultMoziHigh,0.0f });
			m_spriteRender.push_back(r);
			//8�ԁ����U���g�A�C�R��
			r = NewGO<prefab::CSpriteRender>(2);
			r->Init(L"sprite/Icon2.dds", 200.0f, 200.0f);
			r->SetPosition({ 100.0f ,ResultIconMoveY,0.0f });
			MulColor = { 1.0f,1.0f,1.0f,0.0f };
			r->SetMulColor(MulColor);
			m_spriteRender.push_back(r);
			ResultIconMoveFlag = true; //�t���O�I��
		}

		//���U���g���ړ�
		if (Hoge_Couneter < 40.0f) {
			HogePosition1 += ResultMoziMoveSpeed;
		}
		else if(Hoge_Couneter < 60.0f) {
			HogePosition1 -= ResultMoziMoveX;
		}
		m_spriteRender[7]->SetPosition({ HogePosition1 ,ResultMoziHigh,0.0f });

		if (Hoge_Couneter >= PhaseTimer2 / 3) {
			MulColor.a = MulAlpha;
			m_spriteRender[8]->SetMulColor(MulColor);
			MulPuls();
		}

		//�����v���I���Ƌ��������A����̑J�ڂ��K���i�^�C�}�[���I�����Ԃƈ�v�������Ƀt�F�C�Y�����ɐi�߂܂��I�j
		if (Hoge_Couneter >= PhaseTimer2) {
			CountReset();
			ResultTurn = scene1_ZankiBonus;
		}
		break;
	}

	case scene1_ZankiBonus://�c�@�{�[�i�X��\������
	{
		if (Hoge_Couneter == BonusAverage) {//������x�o������

			prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/kettei.wav");
			ss->SetVolume(0.5f);
			ss->Play(false);

			f = NewGO<prefab::CFontRender>(1);
			//�\��
			wchar_t text[256];
			//����
			swprintf(text, L"���񂫃{�[�i�X:%d", ZankiBonus);
			//�͂��B
			f->SetText(text);
			f->SetPosition({ 280.0f,0.0f });
			f->SetScale(BonusFontSize);
			f->SetPivot({ 1.0f,0.0f });
			m_fontRender.push_back(f);
		}

		//�����v���I���Ƌ��������A����̑J�ڂ��K���i�^�C�}�[���I�����Ԃƈ�v�������Ƀt�F�C�Y�����ɐi�߂܂��I�j
		if (Hoge_Couneter >= PhaseTimer3) {
			CountReset();
			ResultTurn = scene1_GiriBonus;
		}
		break;
	}

	case scene1_GiriBonus://�M���M���{�[�i�X��\������
	{
		if (Hoge_Couneter == BonusAverage) {//������x�o������

			prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/kettei.wav");
			ss->SetVolume(0.5f);
			ss->Play(false);

			f = NewGO<prefab::CFontRender>(1);
			//�\��
			wchar_t text[256];
			//����
			swprintf(text, L"�M���M���{�[�i�X:%d", GiriBonus);
			//�͂��B
			f->SetText(text);
			f->SetPosition({ 280.0f,-BonusMoziIdou });
			f->SetScale(BonusFontSize);
			f->SetPivot({ 1.0f,0.0f });
			m_fontRender.push_back(f);
		}

		//�����v���I���Ƌ��������A����̑J�ڂ��K���i�^�C�}�[���I�����Ԃƈ�v�������Ƀt�F�C�Y�����ɐi�߂܂��I�j
		if (Hoge_Couneter >= PhaseTimer4) {
			CountReset();
			ResultTurn = scene1_ItemBonus;
		}
		break;
	}

	case scene1_ItemBonus://�A�C�e���{�[�i�X��\������
	{
		if (Hoge_Couneter == BonusAverage) {//������x�o������

			prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/kettei.wav");
			ss->SetVolume(0.5f);
			ss->Play(false);

			f = NewGO<prefab::CFontRender>(1);
			//�\��
			wchar_t text[256];
			//����
			swprintf(text, L"�A�C�e���{�[�i�X:%d", ItemBonus);
			//�͂��B
			f->SetText(text);
			f->SetPosition({ 280.0f,-BonusMoziIdou *2 });
			f->SetScale(BonusFontSize);
			f->SetPivot({ 1.0f,0.0f });
			m_fontRender.push_back(f);
			f = NewGO<prefab::CFontRender>(1);
			//�\��
			text[256];
			//����
			swprintf(text, L"----------------------");
			//�͂��B
			f->SetText(text);
			f->SetPosition({ 280.0f,-BonusMoziIdou * 2 });
			f->SetScale(BonusFontSize);
			f->SetPivot({ 1.0f,0.0f });
			m_fontRender.push_back(f);
		}

		//�����v���I���Ƌ��������A����̑J�ڂ��K���i�^�C�}�[���I�����Ԃƈ�v�������Ƀt�F�C�Y�����ɐi�߂܂��I�j
		if (Hoge_Couneter >= PhaseTimer5) {
			CountReset();
			ResultTurn = scene1_MatometeScore;
		}
		break;
	}

	case scene1_MatometeScore://�X�R�A��\������
	{
		if (Hoge_Couneter == ScoreAverage) {//������x�o������

			prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/kettei.wav");
			ss->SetVolume(0.5f);
			ss->Play(false);

			f = NewGO<prefab::CFontRender>(1);
			//�\��
			wchar_t text[256];
			//����
			swprintf(text, L"%d", FinalScore);
			//�͂��B
			f->SetText(text);
			f->SetPosition({ 280.0f,-BonusMoziIdou * 3 + ScoreYHosei });
			f->SetScale(ScoreFontSize);
			f->SetPivot({ 1.0f,1.0f });
			m_fontRender.push_back(f);

			//�{�[�i�X����
			f = NewGO<prefab::CFontRender>(1);
			//�\��
			text[256];
			//����
			swprintf(text, L"X");
			//�͂��B
			f->SetText(text);
			f->SetPosition({ 280.0f,-BonusMoziIdou * 3 - ScoreYHosei - 20.0f });
			f->SetPivot({ 1.0f,1.0f });
			f->SetColor({ 1.0f,1.0f,1.0f,0.0f });//�����ɕ\�������
			m_fontRender.push_back(f);

			//�L�R�E�`���E�m�F
			if (KikoFlag == true) {
				hoge += HardTimerHosei;
				hoge2 += HardTimerHosei;
				hoge3 += HardTimerHosei;
			}
			//�n�[�h�m�F
			if (HardFlag == true) {
				hoge += HardTimerHosei;
				hoge3 += HardTimerHosei;
			}
			//�X�L���m�F
			if (SkillFlag == true) {
				hoge += HardTimerHosei;
			}

		}

		//�L�R�E�`���E�{�[�i�X
		if (KikoFlag == true && Hoge_Couneter == PhaseTimer6_Hard) {
			prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/kettei.wav");
			ss->SetVolume(0.5f);
			ss->Play(false);

			wchar_t text[256];
			swprintf(text, L"�L�R�E�`���E�{�[�i�X�I");
			m_fontRender[5]->SetText(text);
			m_fontRender[5]->SetColor({ 1.0f,0.0f,0.0f,1.0f });
			float score = (float)FinalScore;
			score += KikoBonus;
			FinalScore = (int)score;
			Point = Point_Count + FinalScore;
			text[256];
			//����
			swprintf(text, L"%d", FinalScore);
			//�͂��B
			m_fontRender[4]->SetText(text);
			m_fontRender[4]->SetColor({ 1.0f,0.8f,0.1f,1.0f });
		}

		//�L�R�E�`���E�ړ�
		if (KikoFlag == true && Hoge_Couneter < PhaseTimer6_Hard + 5 && Hoge_Couneter>PhaseTimer6_Hard) {
			CVector2 pos = m_fontRender[4]->GetPosition();
			pos.y += 5.0f;
			m_fontRender[4]->SetPosition(pos);
		}
		else if (KikoFlag == true && Hoge_Couneter < PhaseTimer6_Hard + 10 && Hoge_Couneter>PhaseTimer6_Hard) {
			CVector2 pos = m_fontRender[4]->GetPosition();
			pos.y -= 5.0f;
			m_fontRender[4]->SetPosition(pos);
		}

		//�n�[�h�{�[�i�X
		if (HardFlag == true && Hoge_Couneter == PhaseTimer6_Hard + hoge2) {
			prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/kettei.wav");
			ss->SetVolume(0.5f);
			ss->Play(false);

			wchar_t text[256];
			swprintf(text, L"�n�[�h�{�[�i�X�I");
			m_fontRender[5]->SetText(text);
			m_fontRender[5]->SetColor({ 1.0f,0.0f,0.0f,1.0f });
			float score = (float)FinalScore;
			score *= HardHosei;
			FinalScore = (int)score;
			Point = Point_Count + FinalScore;
			text[256];
			//����
			swprintf(text, L"%d", FinalScore);
			//�͂��B
			m_fontRender[4]->SetText(text);
			m_fontRender[4]->SetColor({ 1.0f,0.8f,0.1f,1.0f });
		}

		//�n�[�h�ړ�
		if (HardFlag == true && Hoge_Couneter < PhaseTimer6_Hard + hoge2 + 5 && Hoge_Couneter>PhaseTimer6_Hard + hoge2) {
			CVector2 pos = m_fontRender[4]->GetPosition();
			pos.y += 5.0f;
			m_fontRender[4]->SetPosition(pos);
		}else if (HardFlag == true && Hoge_Couneter < PhaseTimer6_Hard + hoge2 + 10 && Hoge_Couneter>PhaseTimer6_Hard + hoge2) {
			CVector2 pos = m_fontRender[4]->GetPosition();
			pos.y -= 5.0f;
			m_fontRender[4]->SetPosition(pos);
		}

		//�X�L���{�[�i�X
		if (SkillFlag == true && Hoge_Couneter == PhaseTimer6_Hard + hoge3) {
			prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/kettei.wav");
			ss->SetVolume(0.5f);
			ss->Play(false);

			wchar_t text[256];
			swprintf(text, L"�X�L���{�[�i�X�I");
			m_fontRender[5]->SetText(text);
			m_fontRender[5]->SetColor({ 1.0f,0.0f,0.0f,1.0f });
			float score = (float)FinalScore;
			//�v�Z
			SaveData * savedata = SaveData::GetInstance();
			if (savedata->GetSkill(false) == 19 || savedata->GetSkill(true) == 19) {
				score *= 1.5f;
			}			
			if (savedata->GetSkill(false) == 20 || savedata->GetSkill(true) == 20) {
				score *= 1.5f;
			}
			if (savedata->GetSkill(false) == 21 || savedata->GetSkill(true) == 21) {
				score *= 2.0f;
			}
			FinalScore = (int)score;
			Point = Point_Count + FinalScore;
			text[256];
			//����
			swprintf(text, L"%d", FinalScore);
			//�͂��B
			m_fontRender[4]->SetText(text);
			m_fontRender[4]->SetColor({ 1.0f,0.8f,0.1f,1.0f });
		}

		//�X�L���ړ�
		if (SkillFlag == true && Hoge_Couneter < PhaseTimer6_Hard + hoge3 + 5 && Hoge_Couneter>PhaseTimer6_Hard + hoge3) {
			CVector2 pos = m_fontRender[4]->GetPosition();
			pos.y += 5.0f;
			m_fontRender[4]->SetPosition(pos);
		}
		else if (SkillFlag == true && Hoge_Couneter < PhaseTimer6_Hard + hoge3 + 10 && Hoge_Couneter>PhaseTimer6_Hard + hoge3) {
			CVector2 pos = m_fontRender[4]->GetPosition();
			pos.y -= 5.0f;
			m_fontRender[4]->SetPosition(pos);
		}

		//�����v���I���Ƌ��������A����̑J�ڂ��K���i�^�C�}�[���I�����Ԃƈ�v�������Ƀt�F�C�Y�����ɐi�߂܂��I�j
		if (Hoge_Couneter >= PhaseTimer6 + hoge ) {
			CountReset();
			ResultTurn = scene1_Runk;
		}
		break;
	}

	case scene1_Runk://�]����\������
	{
		if (Hoge_Couneter == RunkAverage) {//������x�o������

			//9�ԁ������N
			r = NewGO<prefab::CSpriteRender>(1);

			if (HardFlag == false) {
				if (FinalScore >= ScoreData[NowStage][3]) {
					//S�����N
					r->Init(L"sprite/S_Runk.dds", 256.0f, 256.0f);
				}
				else if (FinalScore >= ScoreData[NowStage][2]) {
					//A�����N
					r->Init(L"sprite/A_Runk.dds", 256.0f, 256.0f);
				}
				else if (FinalScore >= ScoreData[NowStage][1]) {
					//B�����N
					r->Init(L"sprite/B_Runk.dds", 256.0f, 256.0f);
				}
				else if (FinalScore >= ScoreData[NowStage][0]) {
					//C�����N
					r->Init(L"sprite/C_Runk.dds", 256.0f, 256.0f);
				}
				else {
					//D�����N
					r->Init(L"sprite/D_Runk.dds", 256.0f, 256.0f);
				}
			}
			else {
				if (FinalScore >= (ScoreData[NowStage][3]*2)) {
					//S�����N
					r->Init(L"sprite/S_Runk.dds", 256.0f, 256.0f);
				}
				else if (FinalScore >= (ScoreData[NowStage][2]*2)) {
					//A�����N
					r->Init(L"sprite/A_Runk.dds", 256.0f, 256.0f);
				}
				else if (FinalScore >= (ScoreData[NowStage][1]*2)) {
					//B�����N
					r->Init(L"sprite/B_Runk.dds", 256.0f, 256.0f);
				}
				else if (FinalScore >= (ScoreData[NowStage][0]*2)) {
					//C�����N
					r->Init(L"sprite/C_Runk.dds", 256.0f, 256.0f);
				}
				else {
					//D�����N
					r->Init(L"sprite/D_Runk.dds", 256.0f, 256.0f);
				}
			}

			//�R�R�J���t�@�C��
			r->SetPosition(RunkPos);
			HogePosition2 = 0.0f;
			MulColor = { 1.0f,1.0f,1.0f,HogePosition2 };
			r->SetMulColor(MulColor); 
			HogePosition1 = 10.0f;
			r->SetScale({ HogePosition1,HogePosition1,HogePosition1 });
			m_spriteRender.push_back(r);
			HogeFlag = true;
		}

		if (HogeFlag == true && OK_Flag == false ) {
			HogePosition2 += 0.03f;
			if (RunkFlag == false) {
				HogePosition1 -= RunkScaleSpeed;
			}
			else {
				HogePosition1 += RunkScaleSpeed / 2;
			}
			if (RunkKakudaiMin > HogePosition1) {//�����ɂȂ����I
				HogePosition1 = RunkKakudaiMin;

				prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
				ss->Init(L"sound/Result_dodon.wav");
				ss->SetVolume(0.5f);
				ss->Play(false);

				RunkFlag = true;
			}
			if (RunkFlag == true && HogePosition1 > 1.0f) {//����ɂȂ����I
				HogePosition1 = 1.0f;
			}
			if (HogePosition2 > 1.0f) {//�����x��1.0f���傫���Ȃ�Ȃ��悤�ɂ���
				HogePosition2 = 1.0f;
			}
			MulColor = { 1.0f,1.0f,1.0f,HogePosition2 };
			m_spriteRender[9]->SetMulColor(MulColor);
			m_spriteRender[9]->SetScale({ HogePosition1,HogePosition1,HogePosition1 });
		}

		//�����v���I���Ƌ��������A����̑J�ڂ��K���i�^�C�}�[���I�����Ԃƈ�v�������Ƀt�F�C�Y�����ɐi�߂܂��I�j
		if (Hoge_Couneter >= PhaseTimer7) {
			CountReset();
			OK_Flag = true;
		}
		break;
	}

///////////////////////////////////////////////('��')////////////////////////////////////////////////

	case scene2_Seni://1����2�ցc
	{
		//�ړ�����
		for (int i = 0; i < m_fontRender.size(); i++) {
			CVector2 pos = m_fontRender[i]->GetPosition();
			pos.x -= SeniMove;
			m_fontRender[i]->SetPosition(pos);
		}

		//�����v���I���Ƌ��������A����̑J�ڂ��K���i�^�C�}�[���I�����Ԃƈ�v�������Ƀt�F�C�Y�����ɐi�߂܂��I�j
		if (Hoge_Couneter >= PhaseTimer8) {
			CountReset();
			ResultTurn = scene2_ScoreUp;
		}
		break;
	}

	case scene2_ScoreUp://�V�[��2�̏���������
	{
		if (Hoge_Couneter == 1) {//����
			f = NewGO<prefab::CFontRender>(1);
			//�\��
			wchar_t text[256];
			//����
			swprintf(text, L"Score:%d", FinalScore);
			//�͂��B
			f->SetText(text);
			f->SetPosition({ 600.0f,0.0f });
			f->SetScale(KeisanFontSize);
			f->SetPivot({ 0.5f,0.5f });
			m_fontRender.push_back(f);
			f = NewGO<prefab::CFontRender>(1);
			//�\��
			text[256];
			//����
			swprintf(text, L"Point:%d", Point_Count);
			//�͂��B
			f->SetText(text);
			f->SetPosition({ 600.0f,-200.0f });
			f->SetScale(ScoreFontSize);
			f->SetPivot({ 0.5f,0.5f });
			m_fontRender.push_back(f);
		}

		//�ړ�����
			CVector2 pos = m_fontRender[6]->GetPosition();
			pos.x -= (SeniMove - SeniMoveHosei);
			if (pos.x < 0.0f) {
				pos.x = 0.0f;
			}
			m_fontRender[6]->SetPosition(pos);
			pos = m_fontRender[7]->GetPosition();
			pos.x -= (SeniMove - SeniMoveHosei);
			if (pos.x < 0.0f) {
				pos.x = 0.0f;
			}
			m_fontRender[7]->SetPosition(pos);

		//�����v���I���Ƌ��������A����̑J�ڂ��K���i�^�C�}�[���I�����Ԃƈ�v�������Ƀt�F�C�Y�����ɐi�߂܂��I�j
		if (Hoge_Couneter >= PhaseTimer9) {
			CountReset();
			ResultTurn = scene2_ScoreIdou;
		}
		break;
	}

	case scene2_ScoreIdou://�X�R�A�̉��o
	{
		if (Hoge_Couneter <= 6) {//��Ɉړ�
			CVector2 pos = m_fontRender[6]->GetPosition();
			pos.y += 5.0f;
			m_fontRender[6]->SetPosition(pos);
			HogePosition1 = 1.0f; //��ŕs�����x��ύX���鏀��
		}
		else {//���Ɉړ����t�F�[�h�A�E�g�I
			CVector2 pos = m_fontRender[6]->GetPosition();
			pos.y -= 40.0f;
			m_fontRender[6]->SetPosition(pos);
			//�����ŕs�����x��ύX
			HogePosition1 -= 0.15f;
			m_fontRender[6]->SetColor({ 1.0f, 1.0f, 1.0f, HogePosition1 });
		}

		//�����v���I���Ƌ��������A����̑J�ڂ��K���i�^�C�}�[���I�����Ԃƈ�v�������Ƀt�F�C�Y�����ɐi�߂܂��I�j
		if (Hoge_Couneter >= PhaseTimer10) {
			CountReset();
			ResultTurn = scene2_ScoreKasan;
		}
		break;
	}

	case scene2_ScoreKasan://�X�R�A�����|�C���g�ɂȂ邼
	{
		if (HogeFlag == false) {//���Z
			prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/Result_Ka.wav");
			ss->SetVolume(0.5f);
			ss->Play(false);

			Point_Count += ScoreKasan; 
			if (Point_Count > Point) {
				prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
				ss->Init(L"sound/Result_gageEND.wav");
				ss->SetVolume(0.5f);
				ss->Play(false);

				Point_Count = Point;
				HogeFlag = true;
			}
			wchar_t text[256];
			//����
			swprintf(text, L"Point:%d", Point_Count);
			//�͂��B
			m_fontRender[7]->SetText(text);
		}
		else {//�I�����o

			if (HogePosition1 < 5.0f) {
				CVector2 pos = m_fontRender[7]->GetPosition();
				pos.y += 5.0f;
				m_fontRender[7]->SetPosition(pos);
			}	
			else if (HogePosition1 < 10.0f) {
				CVector2 pos = m_fontRender[7]->GetPosition();
				pos.y -= 5.0f;
				m_fontRender[7]->SetPosition(pos);
				m_fontRender[7]->SetColor({ 1.0f,0.8f,0.1f,1.0f });
			}
			else if (HogePosition1 >= 60.0f && HogePosition1 < 90.0f) {
				CVector2 pos = m_fontRender[7]->GetPosition();
				pos.y += 6.0f;
				m_fontRender[7]->SetPosition(pos);
			}
			else if (HogePosition1 == 90.0f) { //�����ň�x�X�g�b�v�I
				//�X�L���擾����

				if (SkillGetFlag[CheckSkillNow] == true) { //�擾�t���O���I���ł�
					if (Skill_EffectNow == false) { //�G�t�F�N�g���s���łȂ�
						Skill_EffectNow = true;
					}
					else {
						if (Skill_EffectEnd == false) {
							SkillGet(CheckSkillNow); //�G�t�F�N�g���s��
						}
						else { //�G�t�F�N�g���I������
							Skill_EffectNow = false;
							Skill_EffectEnd = false;
							CheckSkillNow++;
						}
					}
				}
				else { //�m�F�ʒu�����Z
					CheckSkillNow++;
				}


				if (CheckSkillNow == 24) { //�m�F�I��
					//10�ԁ��T���i���x�C�x�[
					r = NewGO<prefab::CSpriteRender>(2);
					r->Init(L"sprite/GoodBye.dds", 325.0f, 114.0f);
					MulColor = { 1.0f,1.0f,1.0f,0.0f };
					r->SetMulColor(MulColor);
					r->SetPosition({ 0.0f ,-200.0f,0.0f });
					r->SetScale(CVector3::One);
					m_spriteRender.push_back(r);

					HogePosition1 += 1.0f;//����Œ�~�^�C���I��
				}
				}
			else if (HogePosition1 >= 91.0f && HogePosition1 < 120.0f) {
				//�t�F�[�h
				MulAlpha += 0.05f;
				MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
				m_spriteRender[10]->SetMulColor(MulColor);
				m_spriteRender[10]->SetScale(CVector3::One);

				CVector4 Hoge_Pos;
				for (int pos = 2; pos < 9; pos++) {
					Hoge_Pos = m_fontRender_skill[pos]->GetColor();
					Hoge_Pos.a -= 0.1f;
					if (Hoge_Pos.a < 0.0f) {
						Hoge_Pos.a = 0.0f;
					}
					m_fontRender_skill[pos]->SetColor(Hoge_Pos);
				}
			}
			else if (HogePosition1 >= 120.0f) {//�S�ďI������̂���A�S��
				OK_Flag = true;
			}

			if (HogePosition1 != 90.0f) {
				HogePosition1 += 1.0f;//�����ł̓J�E���^����
			}

		}

		break;
	}

	}//switch�I��

	//���̃y�[�W�ցc
	if (OK_Flag == true) {
		if (Pad(0).IsTrigger(enButtonA) || Pad(0).IsTrigger(enButtonB) || Pad(0).IsTrigger(enButtonY) || Pad(0).IsTrigger(enButtonX)) {
			//�؂�ւ��܂�
			if (ResultScene == scene1) {
				//�V�[��2�ցc
				CountReset();
				ResultTurn = scene2_Seni;
				OK_Flag = false;
				ResultScene = scene2;
			}else if (ResultScene == scene2) {
				//�I���I
				if (FinalFlag == false) {
					TransitionMaker * tm = TransitionMaker::GetInstance();
					tm->TransitionSetting(TransitionMaker::Fade, 60, 0, false);

					FinalFlag = true;//�I�����o�t���O�𗧂Ă�			
				}
			}
		}
	}

	//�ŏI����
	if (FinalFlag == true) {

		if (FinalCount >= DeleteTime) {

			TransitionMaker * tm = TransitionMaker::GetInstance();
			tm->TransitionSetting(TransitionMaker::Fade, 60, 30, true);

			//�Z�[�u�f�[�^��ݒ肷��
			SaveData * savedata = SaveData::GetInstance();
			GameData * gamedata = GameData::GetInstance();
			int stage = gamedata->GetStageNo();
			stage -= 1;
			//�����n�C�X�R�A��0�Ȃ���N���A�������Z
			if (savedata->GetHighScore(stage) == 0) {
				if (stage < 4) {
					savedata->PlusClearedStage();
				}
			}
			//�n�C�X�R�A�Ȃ�n�C�X�R�A�ɑ��
			if (HardFlag == false) {//�m�[�}�����[�h
				if (savedata->GetHighScore(stage) < FinalScore) {
					savedata->SetHighScore(stage, FinalScore);
				}
			}
			else if (HardFlag == true) {//�n�[�h���[�h
				if (savedata->GetHighScore_Hard(stage) < FinalScore) {
					savedata->SetHighScore_Hard(stage, FinalScore);
				}
			}

			//�L�R�E�`���E�o�^����
			if (KikoFlag == true) {
				savedata->SetMonFlag(5);
				if (HardFlag == false) {
					savedata->SetKikoFlag(stage);
				}
				else if (HardFlag == true) {
					savedata->SetKikoFlag_Hard(stage);
				}
			}

			//�����X�^�[�o�^����
			if (stage == 0) {
				savedata->SetMonFlag(0);
				savedata->SetMonFlag(1);
				savedata->SetMonFlag(2);
				savedata->SetMonFlag(3);
				savedata->SetMonFlag(4);
				if (HardFlag == true) {
					savedata->SetMonFlag(6);
					savedata->SetMonFlag(7);
				}
			}
			if (stage == 1) {
				savedata->SetMonFlag(8);
				savedata->SetMonFlag(9);
				savedata->SetMonFlag(10);
				savedata->SetMonFlag(11);
				if (HardFlag == true) {
					savedata->SetMonFlag(12);
					savedata->SetMonFlag(13);
				}
			}
			if (stage == 2) {
				savedata->SetMonFlag(14);
				savedata->SetMonFlag(15);
				savedata->SetMonFlag(16);
				savedata->SetMonFlag(17);
				if (HardFlag == true) {
					savedata->SetMonFlag(18);
					savedata->SetMonFlag(19);
				}
			}
			if (stage == 3) {
				savedata->SetMonFlag(20);
				savedata->SetMonFlag(21);
				savedata->SetMonFlag(22);
				savedata->SetMonFlag(23);
				if (HardFlag == true) {
					savedata->SetMonFlag(24);
					savedata->SetMonFlag(25);
					savedata->SetMonFlag(26);
				}

			}
			if (stage == 4) {
				savedata->SetMonFlag(27);
				savedata->SetMonFlag(28);
				savedata->SetMonFlag(29);
				savedata->SetMonFlag(30);
				if (HardFlag == true) {
					savedata->SetMonFlag(31);
					savedata->SetMonFlag(32);
				}
			}

			gamedata->SetGameMode(GameData::GameEnd);
			gamedata->PlusPoint(FinalScore);
			DeleteGO(this);//�����܂�
		}
		FinalCount++;
	}

	//�A�C�R���ړ��t���O��true�Ȃ�㉺�ړ��I
	if (ResultIconMoveFlag == true) {
		if (ResultIconUpDownFlag == false) {
			ResultIconMoveY += ResultIconMove;
		}
		else {
			ResultIconMoveY -= ResultIconMove;
		}
		m_spriteRender[8]->SetPosition({ 100.0f ,ResultIconMoveY,0.0f });

		ResultIconTimer++;
		if (ResultIconTimer == ResultIconMoveTime/2) {
			ResultIconUpDownFlag = true;
		}
		else if (ResultIconTimer == ResultIconMoveTime) {
			ResultIconUpDownFlag = false;
			ResultIconTimer = 0;
		}
	}

	//�A�N�Z�T���[���[�v�I
	m_spriteRender[3]->SetPosition({ ACCPositionX ,AccPosY1,0.0f });
	m_spriteRender[4]->SetPosition({ ACCPositionX ,AccPosY2,0.0f });
	m_spriteRender[5]->SetPosition({ -ACCPositionX ,AccPosY1m,0.0f });
	m_spriteRender[6]->SetPosition({ -ACCPositionX ,AccPosY2m,0.0f });
	AccPosY1 += 1.0f;
	AccPosY2 += 1.0f;
	AccPosY1m += 1.0f;
	AccPosY2m += 1.0f;
	if (AccPosY1 >= 720.0f) {
		AccPosY1 = -720.0f;
	}
	if (AccPosY2 >= 720.0f) {
		AccPosY2 = -720.0f;
	}
	if (AccPosY1m >= 720.0f) {
		AccPosY1m = -720.0f;
	}
	if (AccPosY2m >= 720.0f) {
		AccPosY2m = -720.0f;
	}

	//�J�E���^�[�����Z����c
	Hoge_Couneter++;

}

void GameResult::SkillGetSetup() {

	//������΁[��
	GameData * gamedata = GameData::GetInstance();
	SaveData * savedata = SaveData::GetInstance();
	short SetSkillPosition = 1; //�X�L���t���O��ݒ肷��ꏊ
	int stage = gamedata->GetStageNo();
	stage -= 1;
	//�ŏI�X�R�A�͌��ǑO�����Čv�Z�ł�����
	int Setup_FinalScore = FinalScore;
	//�v�Z
	if (KikoFlag == true) { //�L�R�E�`���E
		float score = (float)Setup_FinalScore;
		score += KikoBonus;
		Setup_FinalScore = (int)score;
	}
	if (HardFlag == true) { //�n�[�h
		float score = (float)Setup_FinalScore;
		score *= HardHosei;
		Setup_FinalScore = (int)score;
		gamedata->HardClearPlus(); //�n�[�h���[�h�N���A�񐔂����Z
	}
	//�X�L��
	float score = (float)Setup_FinalScore;
	if (savedata->GetSkill(false) == 19 || savedata->GetSkill(true) == 19) {
		score *= 1.5f;
	}
	if (savedata->GetSkill(false) == 20 || savedata->GetSkill(true) == 20) {
		score *= 1.5f;
	}
	if (savedata->GetSkill(false) == 21 || savedata->GetSkill(true) == 21) {
		score *= 2.0f;
	}
	Setup_FinalScore = (int)score;

	//�L�R�E�`���E���j��
	if (KikoFlag == true) {
		//�܂��|���ĂȂ��ꏊ�Ȃ�|�������𑝂₷
		if (HardFlag == false && savedata->GetKikoFlag(stage) == false) { //�m�[�}��
			gamedata->KikoGekihaPlus();
		}
		else if (HardFlag == true && savedata->GetKikoFlag_Hard(stage) == false) { //�n�[�h
			gamedata->KikoGekihaPlus();
		}
	}

	////////////////////////////////////////////////////////////

	//����؂��Ƃ��_�b�V���擾�t���O
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false ) {
		if (stage == 0) { //�V�[�\�[�N�X��|����
			SkillGetFlag[SetSkillPosition] = true; //�t���O�I��
		}
	}
	SetSkillPosition++;
	//���������_�b�V���擾�t���O
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (stage == 0 && HardFlag==true && Setup_FinalScore >= (ScoreData[NowStage][3]*2)) { //�C�n�[�h��S�����N
			SkillGetFlag[SetSkillPosition] = true; //�t���O�I��
		}
	}
	SetSkillPosition++;
	//�X�^�[�h���b�v�擾�t���O
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (gamedata->GetKikoGekiha()==1) { //�L�R�E�`���E���j��1
			SkillGetFlag[SetSkillPosition] = true; //�t���O�I��
		}
	}
	SetSkillPosition++;
	//�J�K���L�m�E�~�擾�t���O
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (gamedata->GetKikoGekiha() == 3) { //�L�R�E�`���E���j��3
			SkillGetFlag[SetSkillPosition] = true; //�t���O�I��
		}
	}
	SetSkillPosition++;
	//�X�^�[�t�B�[�o�[�擾�t���O
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (gamedata->GetKikoGekiha() == 5) { //�L�R�E�`���E���j��5
			SkillGetFlag[SetSkillPosition] = true; //�t���O�I��
		}
	}
	SetSkillPosition++;
	//�~���L�[�E�F�C�擾�t���O
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (gamedata->GetKikoGekiha() == 10) { //�L�R�E�`���E���j��10
			SkillGetFlag[SetSkillPosition] = true; //�t���O�I��
		}
	}
	SetSkillPosition++;
	//�]���r�^�C���擾�t���O
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (stage == 3 && gamedata->GetItemCount() >= 15 ) { //��ՂŃA�C�e��15�ȏ�
			SkillGetFlag[SetSkillPosition] = true; //�t���O�I��
		}
	}
	SetSkillPosition++;
	//�i�K���{�V�擾�t���O
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (stage == 1 && Setup_FinalScore >= ScoreData[NowStage][3]) { //�X��S�����N
			SkillGetFlag[SetSkillPosition] = true; //�t���O�I��
		}
	}
	SetSkillPosition++;
	//�\�E���t���A�擾�t���O
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (stage == 1 && gamedata->GetBombFlag() == false) { //���e�ɓ����炸�N���A
			SkillGetFlag[SetSkillPosition] = true; //�t���O�I��
		}
	}
	SetSkillPosition++;
	//�R���b�g�L���m���擾�t���O
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (stage == 2 && gamedata->GetDensyaFlag() == false) { //�d�Ԃɓ����炸�N���A
			SkillGetFlag[SetSkillPosition] = true; //�t���O�I��
		}
	}
	SetSkillPosition++;
	//�����߂���傭�擾�t���O
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (stage == 2 && HardFlag == true && Setup_FinalScore >= (ScoreData[NowStage][3]*2)) { //�w�n�[�h��S�����N
			SkillGetFlag[SetSkillPosition] = true; //�t���O�I��
		}
	}
	SetSkillPosition++;
	//�A�^�b�N�A�b�v�擾�t���O
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (gamedata->GetRuikeiGekihaEnemy() >= 10) { //�݌v�G���j10
			SkillGetFlag[SetSkillPosition] = true; //�t���O�I��
		}
	}
	SetSkillPosition++;
	//���e�L�m�o�V�擾�t���O
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (gamedata->GetRuikeiGekihaEnemy() >= 30) { //�݌v�G���j30
			SkillGetFlag[SetSkillPosition] = true; //�t���O�I��
		}
	}
	SetSkillPosition++;
	//�A�C�e���u�[�X�g�擾�t���O
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (gamedata->GetRuikeiGekihaEnemy() >= 50) { //�݌v�G���j50
			SkillGetFlag[SetSkillPosition] = true; //�t���O�I��
		}
	}
	SetSkillPosition++;
	//�Z�c���N�擾�t���O
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (gamedata->GetRuikeiGekihaEnemy() >= 70) { //�݌v�G���j70
			SkillGetFlag[SetSkillPosition] = true; //�t���O�I��
		}
	}
	SetSkillPosition++;
	//�C�m�`�J���Q���擾�t���O
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (gamedata->GetRuikeiGekihaEnemy() >= 100) { //�݌v�G���j100
			SkillGetFlag[SetSkillPosition] = true; //�t���O�I��
		}
	}
	SetSkillPosition++;
	//�n�K�l�m�J���_�擾�t���O
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (gamedata->GetRuikeiGekihaEnemy() >= 150) { //�݌v�G���j150
			SkillGetFlag[SetSkillPosition] = true; //�t���O�I��
		}
	}
	SetSkillPosition++;
	//�J�~�J�[�o�g���擾�t���O
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (gamedata->GetLastStarDash() >= 5) { //�����_�b�V���Ńg�h�����h������5��
			SkillGetFlag[SetSkillPosition] = true; //�t���O�I��
		}
	}
	SetSkillPosition++;
	//�A�N���擾�t���O
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (gamedata->GetHardClear() >= 1) { //�n�[�h���[�h�N���A��1
			SkillGetFlag[SetSkillPosition] = true; //�t���O�I��
		}
	}
	SetSkillPosition++;
	//�L���E�t�擾�t���O
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (gamedata->GetHardClear() >= 3) { //�n�[�h���[�h�N���A��3
			SkillGetFlag[SetSkillPosition] = true; //�t���O�I��
		}
	}
	SetSkillPosition++;
	//�i�~�_�擾�t���O
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (gamedata->GetHardClear() >= 5) { //�n�[�h���[�h�N���A��5
			SkillGetFlag[SetSkillPosition] = true; //�t���O�I��
		}
	}
	SetSkillPosition++;
	//�L�R�T�[�`�擾�t���O
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (stage == 4 && HardFlag == true && Setup_FinalScore >= (ScoreData[NowStage][3]*2)) { //�ً�ԃn�[�hS�����N
			SkillGetFlag[SetSkillPosition] = true; //�t���O�I��
		}
	}
	SetSkillPosition++;

	//�擾�摜�������I

	//0�ԁ��w�i
	r_skill = NewGO<prefab::CSpriteRender>(8);
	r_skill->Init(L"sprite/Skill.dds", 660.0f, 200.0f);
	r_skill->SetPosition({ 0.0f + SkillX_Hosei,-220.0f,0.0f });
	r_skill->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_spriteRender_skill.push_back(r_skill);

	//1�ԁ��A�C�R��
	r_skill = NewGO<prefab::CSpriteRender>(8);
	r_skill->Init(L"sprite/skillicon_0.dds", 150.0f, 100.0f);
	r_skill->SetPosition({ -200.0f + SkillX_Hosei,-220.0f,0.0f });
	r_skill->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_spriteRender_skill.push_back(r_skill);

	//2�ԁ��A�C�R���g
	r_skill = NewGO<prefab::CSpriteRender>(9);
	r_skill->Init(L"sprite/skilliconWaku.dds", 150.0f, 100.0f);
	r_skill->SetPosition({ -200.0f + SkillX_Hosei,-220.0f,0.0f });
	r_skill->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_spriteRender_skill.push_back(r_skill);

	//0�ԁ��X�L����
	f_skill = NewGO<prefab::CFontRender>(9);
	//�\��
	wchar_t text[256];
	//����
	swprintf(text, L"�e�X�g���b�Z�[�W");
	//�͂��B
	f_skill->SetText(text);
	f_skill->SetPosition({ -100.0f + SkillX_Hosei,-172.0f });
	f_skill->SetScale(0.8f);
	f_skill->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	f_skill->SetPivot({ 0.0f,1.0f });
	m_fontRender_skill.push_back(f_skill);

	//1�ԁ�������
	f_skill = NewGO<prefab::CFontRender>(9);
	//�\��
	text[256];
	//����
	swprintf(text, L"�ق��ق��ق��ق�\n���������������ڂ�");
	//�͂��B
	f_skill->SetText(text);
	f_skill->SetPosition({ -100.0f + SkillX_Hosei,-215.0f });
	f_skill->SetScale(0.5f);
	f_skill->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	f_skill->SetPivot({ 0.0f,1.0f });
	m_fontRender_skill.push_back(f_skill);

	//2�ԁ��X
	f_skill = NewGO<prefab::CFontRender>(9);
	//�\��
	text[256];
	//����
	swprintf(text, L"�X");
	//�͂��B
	f_skill->SetText(text);
	f_skill->SetPosition({ -180.0f,-90.0f });
	f_skill->SetScale(1.2f);
	f_skill->SetColor({ 1.0f,1.0f,0.2f,0.0f });
	f_skill->SetPivot({ 0.0f,1.0f });
	m_fontRender_skill.push_back(f_skill);

	//3�ԁ��L
	f_skill = NewGO<prefab::CFontRender>(9);
	//�\��
	text[256];
	//����
	swprintf(text, L"�@�L");
	//�͂��B
	f_skill->SetText(text);
	f_skill->SetPosition({ -180.0f,-90.0f });
	f_skill->SetScale(1.2f);
	f_skill->SetColor({ 1.0f,1.0f,0.2f,0.0f });
	f_skill->SetPivot({ 0.0f,1.0f });
	m_fontRender_skill.push_back(f_skill);

	//4�ԁ���
	f_skill = NewGO<prefab::CFontRender>(9);
	//�\��
	text[256];
	//����
	swprintf(text, L"�@�@��");
	//�͂��B
	f_skill->SetText(text);
	f_skill->SetPosition({ -180.0f,-90.0f });
	f_skill->SetScale(1.2f);
	f_skill->SetColor({ 1.0f,1.0f,0.2f,0.0f });
	f_skill->SetPivot({ 0.0f,1.0f });
	m_fontRender_skill.push_back(f_skill);

	//5�ԁ��Q
	f_skill = NewGO<prefab::CFontRender>(9);
	//�\��
	text[256];
	//����
	swprintf(text, L"�@�@�@�Q");
	//�͂��B
	f_skill->SetText(text);
	f_skill->SetPosition({ -180.0f,-90.0f });
	f_skill->SetScale(1.2f);
	f_skill->SetColor({ 1.0f,1.0f,0.2f,0.0f });
	f_skill->SetPivot({ 0.0f,1.0f });
	m_fontRender_skill.push_back(f_skill);

	//6�ԁ��b
	f_skill = NewGO<prefab::CFontRender>(9);
	//�\��
	text[256];
	//����
	swprintf(text, L"�@�@�@�@�b");
	//�͂��B
	f_skill->SetText(text);
	f_skill->SetPosition({ -180.0f,-90.0f });
	f_skill->SetScale(1.2f);
	f_skill->SetColor({ 1.0f,1.0f,0.2f,0.0f });
	f_skill->SetPivot({ 0.0f,1.0f });
	m_fontRender_skill.push_back(f_skill);

	//7�ԁ��g
	f_skill = NewGO<prefab::CFontRender>(9);
	//�\��
	text[256];
	//����
	swprintf(text, L"�@�@�@�@�@�g");
	//�͂��B
	f_skill->SetText(text);
	f_skill->SetPosition({ -180.0f,-90.0f });
	f_skill->SetScale(1.2f);
	f_skill->SetColor({ 1.0f,1.0f,0.2f,0.0f });
	f_skill->SetPivot({ 0.0f,1.0f });
	m_fontRender_skill.push_back(f_skill);

	//8�ԁ��I
	f_skill = NewGO<prefab::CFontRender>(9);
	//�\��
	text[256];
	//����
	swprintf(text, L"�@�@�@�@�@�@�I");
	//�͂��B
	f_skill->SetText(text);
	f_skill->SetPosition({ -180.0f,-90.0f });
	f_skill->SetScale(1.2f);
	f_skill->SetColor({ 1.0f,1.0f,0.2f,0.0f });
	f_skill->SetPivot({ 0.0f,1.0f });
	m_fontRender_skill.push_back(f_skill);

}

void GameResult::SkillGet(short SetPos) {

	if (SkillTimer == 0) {
		//�擾�摜�������̃X�L���d�l�ɕύX�I
		wchar_t text[256];

		//�A�C�R��
		for (int i = 0; i < 256; i++) { //���Z�b�g
			text[i] = Reset[0];
		}
		int len = (int)wcslen(Skill_Data[SetPos].SkillIcon);
		for (int z = 0; z < len + 1; z++) { //���O�̎擾
			text[z] = Skill_Data[SetPos].SkillIcon[z];
		}
		m_spriteRender_skill[1]->Init(text, 150.0f, 100.0f);

		//���O�̎擾
		for (int i = 0; i < 256; i++) { //���Z�b�g
			text[i] = Reset[0];
		}
		len = (int)wcslen(Skill_Data[SetPos].SkillName);
		for (int z = 0; z < len + 1; z++) { //���O�̎擾
			text[z] = Skill_Data[SetPos].SkillName[z];
		}
		swprintf(text, text);
		//�͂��B
		m_fontRender_skill[0]->SetText(text);

		//�������̎擾
		for (int i = 0; i < 256; i++) { //���Z�b�g
			text[i] = Reset[0];
		}
		len = (int)wcslen(Skill_Data[SetPos].SkillSetumei);
		for (int z = 0; z < len + 1; z++) { //���O�̎擾
			text[z] = Skill_Data[SetPos].SkillSetumei[z];
		}
		swprintf(text, text);
		//�͂��B
		m_fontRender_skill[1]->SetText(text);

	}

	//�o��ړ�
	if (SkillTimer < SkillMoveSpeed + SkillMoveWait) { //�ړ�

		CVector3 Hoge_Pos;
		CVector2 Hoge_Pos2;
		CVector4 Hoge_Pos3;

		if (SkillTimer < SkillMoveSpeed) {

			float MoveSpeed = SkillX_Hosei / (float)SkillMoveSpeed; //�ړ��������v�Z

			Hoge_Pos = m_spriteRender_skill[0]->GetPosition();
			Hoge_Pos.x -= MoveSpeed;
			m_spriteRender_skill[0]->SetPosition(Hoge_Pos);
			Hoge_Pos = m_spriteRender_skill[1]->GetPosition();
			Hoge_Pos.x -= MoveSpeed;
			m_spriteRender_skill[1]->SetPosition(Hoge_Pos);
			Hoge_Pos = m_spriteRender_skill[2]->GetPosition();
			Hoge_Pos.x -= MoveSpeed;
			m_spriteRender_skill[2]->SetPosition(Hoge_Pos);
			Hoge_Pos2 = m_fontRender_skill[0]->GetPosition();
			Hoge_Pos2.x -= MoveSpeed;
			m_fontRender_skill[0]->SetPosition(Hoge_Pos2);
			Hoge_Pos2 = m_fontRender_skill[1]->GetPosition();
			Hoge_Pos2.x -= MoveSpeed;
			m_fontRender_skill[1]->SetPosition(Hoge_Pos2);

			//�X�L���Q�b�g�̕����c�i����������Ɠ��������@�Ȃ�������ł����H�j
			Hoge_Pos3 = m_fontRender_skill[2]->GetColor();
			Hoge_Pos3.a += 0.1f;
			if (Hoge_Pos3.a > 1.0f) {
				Hoge_Pos3.a = 1.0f;
			}
			m_fontRender_skill[2]->SetColor(Hoge_Pos3);

			Hoge_Pos3 = m_fontRender_skill[3]->GetColor();
			Hoge_Pos3.a += 0.1f;
			if (Hoge_Pos3.a > 1.0f) {
				Hoge_Pos3.a = 1.0f;
			}
			m_fontRender_skill[3]->SetColor(Hoge_Pos3);

			Hoge_Pos3 = m_fontRender_skill[4]->GetColor();
			Hoge_Pos3.a += 0.1f;
			if (Hoge_Pos3.a > 1.0f) {
				Hoge_Pos3.a = 1.0f;
			}
			m_fontRender_skill[4]->SetColor(Hoge_Pos3);

			Hoge_Pos3 = m_fontRender_skill[5]->GetColor();
			Hoge_Pos3.a += 0.1f;
			if (Hoge_Pos3.a > 1.0f) {
				Hoge_Pos3.a = 1.0f;
			}
			m_fontRender_skill[5]->SetColor(Hoge_Pos3);

			Hoge_Pos3 = m_fontRender_skill[6]->GetColor();
			Hoge_Pos3.a += 0.1f;
			if (Hoge_Pos3.a > 1.0f) {
				Hoge_Pos3.a = 1.0f;
			}
			m_fontRender_skill[6]->SetColor(Hoge_Pos3);

			Hoge_Pos3 = m_fontRender_skill[7]->GetColor();
			Hoge_Pos3.a += 0.1f;
			if (Hoge_Pos3.a > 1.0f) {
				Hoge_Pos3.a = 1.0f;
			}
			m_fontRender_skill[7]->SetColor(Hoge_Pos3);

			Hoge_Pos3 = m_fontRender_skill[8]->GetColor();
			Hoge_Pos3.a += 0.1f;
			if (Hoge_Pos3.a > 1.0f) {
				Hoge_Pos3.a = 1.0f;
			}
			m_fontRender_skill[8]->SetColor(Hoge_Pos3);

		}

		//�ړ�
		if (SkillMove == false) {
			if (SkillTimer == 3 + SkillMoveWait) {
				Hoge_Pos2 = m_fontRender_skill[2]->GetPosition();
				Hoge_Pos2.y -= 7.5f;
				m_fontRender_skill[2]->SetPosition(Hoge_Pos2);
			}
			if (SkillTimer == 4 + SkillMoveWait) {
				Hoge_Pos2 = m_fontRender_skill[2]->GetPosition();
				Hoge_Pos2.y -= 7.5f;
				m_fontRender_skill[2]->SetPosition(Hoge_Pos2);
			}
			if (SkillTimer == 5 + SkillMoveWait) {
				Hoge_Pos2 = m_fontRender_skill[2]->GetPosition();
				Hoge_Pos2.y += 7.5f;
				m_fontRender_skill[2]->SetPosition(Hoge_Pos2);

				Hoge_Pos2 = m_fontRender_skill[3]->GetPosition();
				Hoge_Pos2.y -= 7.5f;
				m_fontRender_skill[3]->SetPosition(Hoge_Pos2);
			}
			if (SkillTimer == 6 + SkillMoveWait) {
				Hoge_Pos2 = m_fontRender_skill[2]->GetPosition();
				Hoge_Pos2.y += 7.5f;
				m_fontRender_skill[2]->SetPosition(Hoge_Pos2);

				Hoge_Pos2 = m_fontRender_skill[3]->GetPosition();
				Hoge_Pos2.y -= 7.5f;
				m_fontRender_skill[3]->SetPosition(Hoge_Pos2);
			}
			if (SkillTimer == 7 + SkillMoveWait) {
				Hoge_Pos2 = m_fontRender_skill[3]->GetPosition();
				Hoge_Pos2.y += 7.5f;
				m_fontRender_skill[3]->SetPosition(Hoge_Pos2);

				Hoge_Pos2 = m_fontRender_skill[4]->GetPosition();
				Hoge_Pos2.y -= 7.5f;
				m_fontRender_skill[4]->SetPosition(Hoge_Pos2);

			}
			if (SkillTimer == 8 + SkillMoveWait) {
				Hoge_Pos2 = m_fontRender_skill[3]->GetPosition();
				Hoge_Pos2.y += 7.5f;
				m_fontRender_skill[3]->SetPosition(Hoge_Pos2);

				Hoge_Pos2 = m_fontRender_skill[4]->GetPosition();
				Hoge_Pos2.y -= 7.5f;
				m_fontRender_skill[4]->SetPosition(Hoge_Pos2);
			}
			if (SkillTimer == 9 + SkillMoveWait) {
				Hoge_Pos2 = m_fontRender_skill[4]->GetPosition();
				Hoge_Pos2.y += 7.5f;
				m_fontRender_skill[4]->SetPosition(Hoge_Pos2);

				Hoge_Pos2 = m_fontRender_skill[5]->GetPosition();
				Hoge_Pos2.y -= 7.5f;
				m_fontRender_skill[5]->SetPosition(Hoge_Pos2);
			}
			if (SkillTimer == 10 + SkillMoveWait) {
				Hoge_Pos2 = m_fontRender_skill[4]->GetPosition();
				Hoge_Pos2.y += 7.5f;
				m_fontRender_skill[4]->SetPosition(Hoge_Pos2);

				Hoge_Pos2 = m_fontRender_skill[5]->GetPosition();
				Hoge_Pos2.y -= 7.5f;
				m_fontRender_skill[5]->SetPosition(Hoge_Pos2);
			}
			if (SkillTimer == 11 + SkillMoveWait) {
				Hoge_Pos2 = m_fontRender_skill[5]->GetPosition();
				Hoge_Pos2.y += 7.5f;
				m_fontRender_skill[5]->SetPosition(Hoge_Pos2);

				Hoge_Pos2 = m_fontRender_skill[6]->GetPosition();
				Hoge_Pos2.y -= 7.5f;
				m_fontRender_skill[6]->SetPosition(Hoge_Pos2);

			}
			if (SkillTimer == 12 + SkillMoveWait) {
				Hoge_Pos2 = m_fontRender_skill[5]->GetPosition();
				Hoge_Pos2.y += 7.5f;
				m_fontRender_skill[5]->SetPosition(Hoge_Pos2);

				Hoge_Pos2 = m_fontRender_skill[6]->GetPosition();
				Hoge_Pos2.y -= 7.5f;
				m_fontRender_skill[6]->SetPosition(Hoge_Pos2);

			}
			if (SkillTimer == 13 + SkillMoveWait) {
				Hoge_Pos2 = m_fontRender_skill[6]->GetPosition();
				Hoge_Pos2.y += 7.5f;
				m_fontRender_skill[6]->SetPosition(Hoge_Pos2);

				Hoge_Pos2 = m_fontRender_skill[7]->GetPosition();
				Hoge_Pos2.y -= 7.5f;
				m_fontRender_skill[7]->SetPosition(Hoge_Pos2);

			}
			if (SkillTimer == 14 + SkillMoveWait) {
				Hoge_Pos2 = m_fontRender_skill[6]->GetPosition();
				Hoge_Pos2.y += 7.5f;
				m_fontRender_skill[6]->SetPosition(Hoge_Pos2);

				Hoge_Pos2 = m_fontRender_skill[7]->GetPosition();
				Hoge_Pos2.y -= 7.5f;
				m_fontRender_skill[7]->SetPosition(Hoge_Pos2);

			}
			if (SkillTimer == 15 + SkillMoveWait) {
				Hoge_Pos2 = m_fontRender_skill[7]->GetPosition();
				Hoge_Pos2.y += 7.5f;
				m_fontRender_skill[7]->SetPosition(Hoge_Pos2);

				Hoge_Pos2 = m_fontRender_skill[8]->GetPosition();
				Hoge_Pos2.y -= 7.5f;
				m_fontRender_skill[8]->SetPosition(Hoge_Pos2);

			}
			if (SkillTimer == 16 + SkillMoveWait) {
				Hoge_Pos2 = m_fontRender_skill[7]->GetPosition();
				Hoge_Pos2.y += 7.5f;
				m_fontRender_skill[7]->SetPosition(Hoge_Pos2);

				Hoge_Pos2 = m_fontRender_skill[8]->GetPosition();
				Hoge_Pos2.y -= 7.5f;
				m_fontRender_skill[8]->SetPosition(Hoge_Pos2);

			}
			if (SkillTimer == 17 + SkillMoveWait) {
				Hoge_Pos2 = m_fontRender_skill[8]->GetPosition();
				Hoge_Pos2.y += 7.5f;
				m_fontRender_skill[8]->SetPosition(Hoge_Pos2);
			}
			if (SkillTimer == 18 + SkillMoveWait) {
				Hoge_Pos2 = m_fontRender_skill[8]->GetPosition();
				Hoge_Pos2.y += 7.5f;
				m_fontRender_skill[8]->SetPosition(Hoge_Pos2);

				prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
				ss->Init(L"sound/skillget.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

			}
		}

		SkillTimer++;
	}
	else { //����҂�
		if (SkillMove == false) {
			if (Pad(0).IsTrigger(enButtonA)) {
				SkillMove = true;
				SkillTimer = 0;
				SaveData * savedata = SaveData::GetInstance();
				savedata->SkillGetFlag_Set(SetPos);
			}
		}
		else { //�I��
			SkillMove = false;
			SkillTimer = 0;
			Skill_EffectEnd = true;
			//�|�W�V������߂�
			m_spriteRender_skill[0]->SetPosition({ 0.0f + SkillX_Hosei,-220.0f,0.0f });
			m_spriteRender_skill[1]->SetPosition({ -200.0f + SkillX_Hosei,-220.0f,0.0f });
			m_spriteRender_skill[2]->SetPosition({ -200.0f + SkillX_Hosei,-220.0f,0.0f });
			m_fontRender_skill[0]->SetPosition({ -100.0f + SkillX_Hosei,-172.0f });
			m_fontRender_skill[1]->SetPosition({ -100.0f + SkillX_Hosei,-215.0f });
		}
	}


}
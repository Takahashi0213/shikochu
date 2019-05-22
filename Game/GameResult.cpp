#include "stdafx.h"
#include "GameResult.h"
#include "GameData.h"
#include "DataBase.h"

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

	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;

}

bool GameResult::Start() {

	//�ϐ��̏���
	GameData * gamedata = GameData::GetInstance();
	ZankiBonus = gamedata->ZankiBonusKeisan();
	GiriBonus = gamedata->GetGiriCountKeisan();
	ItemBonus = gamedata->GetItemCountKeisan();
	FinalScore = ZankiBonus + GiriBonus + ItemBonus;
	NowStage = gamedata->GetStageNo();
	Point_Count = gamedata->GetPoint();
	Point = Point_Count + FinalScore;

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
		}

		//�����v���I���Ƌ��������A����̑J�ڂ��K���i�^�C�}�[���I�����Ԃƈ�v�������Ƀt�F�C�Y�����ɐi�߂܂��I�j
		if (Hoge_Couneter >= PhaseTimer6) {
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
			CVector2 pos = m_fontRender[5]->GetPosition();
			pos.x -= (SeniMove - SeniMoveHosei);
			if (pos.x < 0.0f) {
				pos.x = 0.0f;
			}
			m_fontRender[5]->SetPosition(pos);
			pos = m_fontRender[6]->GetPosition();
			pos.x -= (SeniMove - SeniMoveHosei);
			if (pos.x < 0.0f) {
				pos.x = 0.0f;
			}
			m_fontRender[6]->SetPosition(pos);

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
			CVector2 pos = m_fontRender[5]->GetPosition();
			pos.y += 5.0f;
			m_fontRender[5]->SetPosition(pos);
			HogePosition1 = 1.0f; //��ŕs�����x��ύX���鏀��
		}
		else {//���Ɉړ����t�F�[�h�A�E�g�I
			CVector2 pos = m_fontRender[5]->GetPosition();
			pos.y -= 40.0f;
			m_fontRender[5]->SetPosition(pos);
			//�����ŕs�����x��ύX
			HogePosition1 -= 0.15f;
			m_fontRender[5]->SetColor({ 1.0f, 1.0f, 1.0f, HogePosition1 });
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
			Point_Count += ScoreKasan; 
			if (Point_Count > Point) {
				Point_Count = Point;
				HogeFlag = true;
			}
			wchar_t text[256];
			//����
			swprintf(text, L"Point:%d", Point_Count);
			//�͂��B
			m_fontRender[6]->SetText(text);
		}
		else {//�I�����o

			if (HogePosition1 < 5.0f) {
				CVector2 pos = m_fontRender[6]->GetPosition();
				pos.y += 5.0f;
				m_fontRender[6]->SetPosition(pos);
			}	
			else if (HogePosition1 < 10.0f) {
				CVector2 pos = m_fontRender[6]->GetPosition();
				pos.y -= 5.0f;
				m_fontRender[6]->SetPosition(pos);
				m_fontRender[6]->SetColor({ 1.0f,0.8f,0.1f,1.0f });
			}
			else if (HogePosition1 >= 60.0f && HogePosition1 < 90.0f) {
				CVector2 pos = m_fontRender[6]->GetPosition();
				pos.y += 6.0f;
				m_fontRender[6]->SetPosition(pos);
			}
			else if (HogePosition1 == 90.0f) {
				//10�ԁ��T���i���x�C�x�[
				r = NewGO<prefab::CSpriteRender>(2);
				r->Init(L"sprite/GoodBye.dds", 325.0f, 114.0f);
				MulColor = { 1.0f,1.0f,1.0f,0.0f };
				r->SetMulColor(MulColor);
				r->SetPosition({ 0.0f ,-200.0f,0.0f });
				r->SetScale(CVector3::One);
				m_spriteRender.push_back(r);
			}
			else if (HogePosition1 >= 91.0f && HogePosition1 < 120.0f) {
				//�t�F�[�h
				MulAlpha += 0.05f;
				MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
				m_spriteRender[10]->SetMulColor(MulColor);
				m_spriteRender[10]->SetScale(CVector3::One);
			}
			else if (HogePosition1 >= 120.0f) {//�S�ďI������̂���A�S��
				OK_Flag = true;
			}

			HogePosition1 += 1.0f;//�����ł̓J�E���^����

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
					//11�ԁ��u���b�N�A�E�g
					r = NewGO<prefab::CSpriteRender>(11);
					r->Init(L"sprite/Black.dds", 1280.0f, 720.0f);
					MulAlpha = 0.0f;
					MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
					r->SetMulColor(MulColor);
					r->SetScale(CVector3::One);
					m_spriteRender.push_back(r);
					FinalFlag = true;//�I�����o�t���O�𗧂Ă�			
				}
			}
		}
	}

	//�ŏI����
	if (FinalFlag == true) {
		//�t�F�[�h
		MulAlpha += 0.02f;
		if (MulAlpha > 1.0f) {
			MulAlpha = 1.0f;
		}
		MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
		m_spriteRender[11]->SetMulColor(MulColor);
		if (FinalCount > DeleteTime) {
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



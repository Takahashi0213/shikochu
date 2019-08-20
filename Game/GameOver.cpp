#include "stdafx.h"
#include "GameOver.h"
#include "GameData.h"
#include "TransitionMaker.h"

GameOver* GameOver::m_instance = nullptr;

GameOver::GameOver()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;

}


GameOver::~GameOver()
{
	for (int i = 0; i < m_spriteRender.size(); i++) {
		DeleteGO(m_spriteRender[i]);
	}
	for (int i = 0; i < m_fontRender.size(); i++) {
		DeleteGO(m_fontRender[i]);
	}

	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;

}

bool GameOver::Start() {

	GameData * gamedata = GameData::GetInstance();
	FinalScore = gamedata->GetGameOverKeisan();
	if (FinalScore == 0) {
		FinalScore = 10;
	}
	Point_Count = gamedata->GetPoint();
	Point = Point_Count + FinalScore;

	//0�ԁ��w�i
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/gameover.dds", 880.0f, 320.0f);
	r->SetPosition({ 0.0f,100.0f,0.0f });
	m_spriteRender.push_back(r);

	//0�ԁ��A�h�o�C�X
	f = NewGO<prefab::CFontRender>(10);
	//�\��
	bool mode = gamedata->GetFinalMode();
	int stage = gamedata->GetStageNo();

	if (mode == false) {
		int random = rand() % 4;
		int len = (int)wcslen(Setumei_2D[random]);
		for (int z = 0; z < len + 1; z++) {
			HogeText[z] = Setumei_2D[random][z];
		}
	}else if (mode == true) {
		stage--;
		int len = (int)wcslen(Setumei_3D[stage]);
		for (int z = 0; z < len + 1; z++) {
			HogeText[z] = Setumei_3D[stage][z];
		}
	}
	swprintf(HogeText, HogeText);
	//�͂��B
	f->SetText(HogeText);
	f->SetPivot({ 0.0f,1.0f });
	f->SetPosition({ -400.0f,-100.0f });
	f->SetScale(1.0f);
	f->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	m_fontRender.push_back(f);
	/////////
	f = NewGO<prefab::CFontRender>(1);
	//�\��
	wchar_t text[256];
	//����
	swprintf(text, L"Score:%d", FinalScore);
	//�͂��B
	f->SetText(text);
	f->SetPosition({ 0.0f,-40.0f });
	f->SetScale(KeisanFontSize);
	f->SetPivot({ 0.5f,0.5f });
	f->SetColor({ 1.0f,1.0f,1.0f,A_2 });
	m_fontRender.push_back(f);
	f = NewGO<prefab::CFontRender>(1);
	//�\��
	text[256];
	//����
	swprintf(text, L"Point:%d", Point_Count);
	//�͂��B
	f->SetText(text);
	f->SetPosition({ 0.0f,-200.0f });
	f->SetScale(ScoreFontSize);
	f->SetPivot({ 0.5f,0.5f });
	f->SetColor({ 1.0f,1.0f,1.0f,A_2 });
	m_fontRender.push_back(f);

	return true;
}

void GameOver::Update() {

	if (Pad(0).IsTrigger(enButtonA) || Pad(0).IsTrigger(enButtonB) || Pad(0).IsTrigger(enButtonY) || Pad(0).IsTrigger(enButtonX)) {

		if (PageFlag == false) {
			PageFlag = true;
		}
		else {
			if (DeleteFlag == false && ScoreFlag == true) {
				//�X�R�A���Z
				GameData * gamedata = GameData::GetInstance();
				gamedata->PlusPoint(FinalScore);
				//���͂�
				TransitionMaker * tm = TransitionMaker::GetInstance();
				tm->TransitionSetting(TransitionMaker::Fade, 12, 0, false);
				DeleteFlag = true;
			}

		}
	}

	if (PageFlag == true && ScoreFlag == false) {//��ʑJ�ڂƃX�R�A���Z

		if (Timer < 60) {//�t�F�[�h

			A_1 -= 0.1f;
			if (A_1 < 0.0f) {
				A_1 = 0.0f;
			}
			m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,A_1 });
			A_2 += 0.1f;
			if (A_2 > 1.0f) {
				A_2 = 1.0f;
			}
			m_fontRender[1]->SetColor({ 1.0f,1.0f,1.0f,A_2 });
			m_fontRender[2]->SetColor({ 1.0f,1.0f,1.0f,A_2 });

		}
		else if (Timer <= 66) {//��Ɉړ�
			CVector2 pos = m_fontRender[1]->GetPosition();
			pos.y += 5.0f;
			m_fontRender[1]->SetPosition(pos);
			A_1 = 1.0f; //��ŕs�����x��ύX���鏀��
		}
		else {//���Ɉړ����t�F�[�h�A�E�g�I
			CVector2 pos = m_fontRender[1]->GetPosition();
			pos.y -= 40.0f;
			m_fontRender[1]->SetPosition(pos);
			//�����ŕs�����x��ύX
			A_1 -= 0.15f;
			m_fontRender[1]->SetColor({ 1.0f, 1.0f, 1.0f, A_1 });
		}

		if (Timer > 76) {
			if (KasanLoop == false) {//���Z
				ss = NewGO<prefab::CSoundSource>(0);
				ss->Init(L"sound/Result_Ka.wav");
				ss->SetVolume(0.5f);
				ss->Play(false);

				Point_Count += ScoreKasan;
				if (Point_Count > Point) {
					ss = NewGO<prefab::CSoundSource>(0);
					ss->Init(L"sound/Result_gageEND.wav");
					ss->SetVolume(0.5f);
					ss->Play(false);

					Point_Count = Point;
					KasanLoop = true;
				}
				wchar_t text[256];
				//����
				swprintf(text, L"Point:%d", Point_Count);
				//�͂��B
				m_fontRender[2]->SetText(text);
			}
			else {
				if (Timer2 < 5) {
					CVector2 pos = m_fontRender[2]->GetPosition();
					pos.y += 5.0f;
					m_fontRender[2]->SetPosition(pos);
				}
				else if (Timer2 < 10) {
					CVector2 pos = m_fontRender[2]->GetPosition();
					pos.y -= 5.0f;
					m_fontRender[2]->SetPosition(pos);
					m_fontRender[2]->SetColor({ 1.0f,0.8f,0.1f,1.0f });
				}
				else if (Timer2 >= 60 && Timer2 < 90) {
					CVector2 pos = m_fontRender[2]->GetPosition();
					pos.y += 4.0f;
					m_fontRender[2]->SetPosition(pos);
				}
				else if (Timer2 == 90) {
					//�T���i���x�C�x�[
					ScoreFlag = true;
				}
				Timer2++;
			}
		}

		Timer++;
	}

	if (DeleteFlag == true) {

		if (DeleteTimer == 60) {
			TransitionMaker * tm = TransitionMaker::GetInstance();
			tm->TransitionSetting(TransitionMaker::Fade, 12, 20, true);
			
			GameData * gamedata = GameData::GetInstance();
			gamedata->SetGameMode(GameData::GameEnd);
			DeleteGO(this);

		}

		DeleteTimer++;
	}

}
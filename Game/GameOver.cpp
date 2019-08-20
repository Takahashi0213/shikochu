#include "stdafx.h"
#include "GameOver.h"
#include "GameData.h"
#include "TransitionMaker.h"

GameOver* GameOver::m_instance = nullptr;

GameOver::GameOver()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
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

	//インスタンスが破棄されたので、nullptrを代入
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

	//0番→背景
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/gameover.dds", 880.0f, 320.0f);
	r->SetPosition({ 0.0f,100.0f,0.0f });
	m_spriteRender.push_back(r);

	//0番→アドバイス
	f = NewGO<prefab::CFontRender>(10);
	//表示
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
	//はい。
	f->SetText(HogeText);
	f->SetPivot({ 0.0f,1.0f });
	f->SetPosition({ -400.0f,-100.0f });
	f->SetScale(1.0f);
	f->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	m_fontRender.push_back(f);
	/////////
	f = NewGO<prefab::CFontRender>(1);
	//表示
	wchar_t text[256];
	//おわ
	swprintf(text, L"Score:%d", FinalScore);
	//はい。
	f->SetText(text);
	f->SetPosition({ 0.0f,-40.0f });
	f->SetScale(KeisanFontSize);
	f->SetPivot({ 0.5f,0.5f });
	f->SetColor({ 1.0f,1.0f,1.0f,A_2 });
	m_fontRender.push_back(f);
	f = NewGO<prefab::CFontRender>(1);
	//表示
	text[256];
	//おわ
	swprintf(text, L"Point:%d", Point_Count);
	//はい。
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
				//スコア加算
				GameData * gamedata = GameData::GetInstance();
				gamedata->PlusPoint(FinalScore);
				//おはり
				TransitionMaker * tm = TransitionMaker::GetInstance();
				tm->TransitionSetting(TransitionMaker::Fade, 12, 0, false);
				DeleteFlag = true;
			}

		}
	}

	if (PageFlag == true && ScoreFlag == false) {//画面遷移とスコア加算

		if (Timer < 60) {//フェード

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
		else if (Timer <= 66) {//上に移動
			CVector2 pos = m_fontRender[1]->GetPosition();
			pos.y += 5.0f;
			m_fontRender[1]->SetPosition(pos);
			A_1 = 1.0f; //後で不透明度を変更する準備
		}
		else {//下に移動＆フェードアウト！
			CVector2 pos = m_fontRender[1]->GetPosition();
			pos.y -= 40.0f;
			m_fontRender[1]->SetPosition(pos);
			//ここで不透明度を変更
			A_1 -= 0.15f;
			m_fontRender[1]->SetColor({ 1.0f, 1.0f, 1.0f, A_1 });
		}

		if (Timer > 76) {
			if (KasanLoop == false) {//加算
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
				//おわ
				swprintf(text, L"Point:%d", Point_Count);
				//はい。
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
					//サヨナラベイベー
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
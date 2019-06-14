#include "stdafx.h"
#include "GamePause.h"
#include "GameData.h"
#include "LevelData.h"
#include "TransitionMaker.h"

GamePause* GamePause::m_instance = nullptr;

GamePause::GamePause()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

}


GamePause::~GamePause()
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

bool GamePause::Start() {

	GameData * gamedata = GameData::GetInstance();
	gamedata->SetGameMode(GameData::Pause);
	bool mode= gamedata->GetFinalMode();
	int stage = gamedata->GetStageNo();

	int len = (int)wcslen(StageName[stage - 1]);
	for (int z = 0; z < len + 1; z++) {
		StageName_hoge[z] = StageName[stage - 1][z];
	}

	//0番→背景
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/PauseBack.dds", 1280.0f, 720.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//1番→上飾り
	r = NewGO<prefab::CSpriteRender>(13);
	r->Init(L"sprite/PauseUe.dds", 1280.0f, 520.0f);
	MulColor = { 1.0f,1.0f,1.0f,1.0f };
	r->SetMulColor(MulColor);
	r->SetPosition({ 0.0f,320.0f+ AccPos_Hosei,0.0f });
	m_spriteRender.push_back(r);
	//2番→下飾り
	r = NewGO<prefab::CSpriteRender>(13);
	r->Init(L"sprite/PauseSita.dds", 1280.0f, 520.0f);
	MulColor = { 1.0f,1.0f,1.0f,1.0f };
	r->SetMulColor(MulColor);
	r->SetPosition({ 0.0f,-320.0f- AccPos_Hosei,0.0f });
	m_spriteRender.push_back(r);
	//3番→ルール
	r = NewGO<prefab::CSpriteRender>(12);
	if (mode == false) {
		r->Init(L"sprite/Pause2D.dds", 445.0f, 438.0f);
	}
	else if (mode == true) {
		r->Init(L"sprite/Pause3D.dds", 445.0f, 438.0f);
	}
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	r->SetScale(scale);
	r->SetPosition({ -250.0f,0.0f,0.0f });
	m_spriteRender.push_back(r);
	//4番→ステージ枠
	r = NewGO<prefab::CSpriteRender>(11);
	r->Init(L"sprite/PauseStage.dds", 596.0f, 194.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	r->SetPosition({ 210.0f+ StagePos_Hosei, 100.0f,0.0f });
	m_spriteRender.push_back(r);
	//5番→バック文字
	r = NewGO<prefab::CSpriteRender>(12);
	r->Init(L"sprite/PauseGameBack.dds", 481.0f, 104.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	r->SetPosition({ 210.0f + StagePos_Hosei, -50.0f,0.0f });
	m_spriteRender.push_back(r);
	//6番→リタイア文字
	r = NewGO<prefab::CSpriteRender>(12);
	r->Init(L"sprite/PauseRetire.dds", 481.0f, 104.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	r->SetPosition({ 210.0f + StagePos_Hosei, -150.0f,0.0f });
	m_spriteRender.push_back(r);
	//7番→選択カーソル
	r = NewGO<prefab::CSpriteRender>(12);
	r->Init(L"sprite/Title/TitleIC.dds", 80.0f, 80.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	r->SetPosition({ 0.0f, -50.0f,0.0f });
	m_spriteRender.push_back(r);
	//8番 フェード用
	r = NewGO<prefab::CSpriteRender>(12);
	r->Init(L"sprite/White.dds", 1280.0f, 720.0f);
	r->SetPosition({ 0.0f ,0.0f,0.0f });
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);

	//ステージ番号 0番
	f = NewGO<prefab::CFontRender>(11);
	//表示
	wchar_t text[256];
	//おわ
	swprintf(text, L"STAGE %d", stage);
	//はい。
	f->SetText(text);
	f->SetPosition({ -50.0f+StagePos_Hosei, 130.0f });
	f->SetScale(0.6f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	f->SetColor(MulColor);
	f->SetPivot({ 0.0f,0.5f });
	m_fontRender.push_back(f);
	//ステージ名前 1番
	f = NewGO<prefab::CFontRender>(11);
	//おわ
	swprintf(StageName_hoge, StageName_hoge);
	//はい。
	f->SetText(StageName_hoge);
	f->SetPosition({ 200.0f+ StagePos_Hosei, 80.0f });
	f->SetScale(1.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	f->SetColor(MulColor);
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);

	return true;
}

void GamePause::Update() {

	if (Timer < 13) {//閉じる
		position = m_spriteRender[1]->GetPosition();
		position.y -= 30.0f;
		m_spriteRender[1]->SetPosition(position);
		position = m_spriteRender[2]->GetPosition();
		position.y += 30.0f;
		m_spriteRender[2]->SetPosition(position);

	}
	else if (Timer < 25) {//バウンド
		position = m_spriteRender[1]->GetPosition();
		position.y += 5.0f;
		m_spriteRender[1]->SetPosition(position);
		position = m_spriteRender[2]->GetPosition();
		position.y -= 5.0f;
		m_spriteRender[2]->SetPosition(position);

		//光る
		MulAlpha += 0.1f;
		if (MulAlpha > 1.0f) {
			MulAlpha = 1.0f;
		}
		MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
		m_spriteRender[8]->SetMulColor(MulColor);

	}
	else if (Timer == 25) {//出現！
		MulColor = { 1.0f,1.0f,1.0f,1.0f };
		m_spriteRender[0]->SetMulColor(MulColor);
		m_spriteRender[3]->SetMulColor(MulColor);
		m_spriteRender[4]->SetMulColor(MulColor);
		m_spriteRender[5]->SetMulColor(MulColor);
		m_spriteRender[6]->SetMulColor({ 0.5f,0.5f,0.5f,0.5f });
		m_fontRender[0]->SetColor(MulColor);
		m_fontRender[1]->SetColor(MulColor);

	}
	else if (Timer > 26 && Timer < 37) {
		//サラダバー
		MulAlpha -= 0.1f;
		if (MulAlpha < 0.0f) {
			MulAlpha = 0.0f;
		}
		MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
		m_spriteRender[8]->SetMulColor(MulColor);

		//ステージ移動
		position = m_spriteRender[4]->GetPosition();
		position.x -= 51.0f;
		m_spriteRender[4]->SetPosition(position);
		CV2_position = m_fontRender[0]->GetPosition();
		CV2_position.x -= 51.0f;
		m_fontRender[0]->SetPosition(CV2_position);
		CV2_position = m_fontRender[1]->GetPosition();
		CV2_position.x -= 51.0f;
		m_fontRender[1]->SetPosition(CV2_position);

		//ルール出現
		scale = m_spriteRender[3]->GetScale();
		scale.y += 0.1f;
		if (scale.y > 1.0f) {
			scale.y = 1.0f;
		}
		m_spriteRender[3]->SetScale(scale);
	}
	else if (Timer > 36 && Timer < 47) {
		//ステージ移動
		position = m_spriteRender[4]->GetPosition();
		position.x += 1.0f;
		m_spriteRender[4]->SetPosition(position);
		CV2_position = m_fontRender[0]->GetPosition();
		CV2_position.x += 1.0f;
		m_fontRender[0]->SetPosition(CV2_position);
		CV2_position = m_fontRender[1]->GetPosition();
		CV2_position.x += 1.0f;
		m_fontRender[1]->SetPosition(CV2_position);
	}
	//移動2
	if (Timer > 31 && Timer < 42) {
		//移動
		position = m_spriteRender[5]->GetPosition();
		position.x -= 51.0f;
		m_spriteRender[5]->SetPosition(position);
	}
	else if (Timer > 41 && Timer < 52) {
		//移動
		position = m_spriteRender[5]->GetPosition();
		position.x += 1.0f;
		m_spriteRender[5]->SetPosition(position);
	}
	//移動3
	if (Timer > 36 && Timer < 47) {
		//移動
		position = m_spriteRender[6]->GetPosition();
		position.x -= 51.0f;
		m_spriteRender[6]->SetPosition(position);
	}
	else if (Timer > 46 && Timer < 57) {
		//移動
		position = m_spriteRender[6]->GetPosition();
		position.x += 1.0f;
		m_spriteRender[6]->SetPosition(position);

		//カーソル出現
		MulAlpha += 0.1f;
		if (MulAlpha > 1.0f) {
			MulAlpha = 1.0f;
		}
		MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
		m_spriteRender[7]->SetMulColor(MulColor);
	}

	//処理
	if (Timer > SetWaitLimit && DeleteFlag == false ) {//セット完了してから受け付ける
		if (Pad(0).IsTrigger(enButtonA)) {//決定
			ss = NewGO<prefab::CSoundSource>(0);
			//SE再生
			ss->Init(L"sound/kettei.wav");
			ss->SetVolume(1.0f);
			ss->Play(false);

			DeleteFlag = true;
		}
		if (Pad(0).IsTrigger(enButtonUp) || Pad(0).IsTrigger(enButtonDown)) {//コマンド移動
			ss = NewGO<prefab::CSoundSource>(0);
			//SE再生
			ss->Init(L"sound/select.wav");
			ss->SetVolume(1.0f);
			ss->Play(false);

			if (CommandNow == false) {
				CommandNow = true;
			}
			else if (CommandNow == true) {
				CommandNow = false;
			}
			CursorUpdate();
		}
	}

	//消去演出
	if (DeleteFlag == true) {

		if (CommandNow == false) {//バック
			if (DeleteTimer < 12) {
				MulColor = m_spriteRender[0]->GetMulColor();
				MulColor.a -= 0.1f;
				if (MulColor.a < 0.0f) {
					MulColor.a = 0.0f;
				}
				m_spriteRender[0]->SetMulColor(MulColor);
				MulColor = m_spriteRender[3]->GetMulColor();
				MulColor.a -= 0.1f;
				if (MulColor.a < 0.0f) {
					MulColor.a = 0.0f;
				}
				m_spriteRender[3]->SetMulColor(MulColor);
				MulColor = m_spriteRender[4]->GetMulColor();
				MulColor.a -= 0.1f;
				if (MulColor.a < 0.0f) {
					MulColor.a = 0.0f;
				}
				m_spriteRender[4]->SetMulColor(MulColor);
				MulColor = m_spriteRender[5]->GetMulColor();
				MulColor.a -= 0.1f;
				if (MulColor.a < 0.0f) {
					MulColor.a = 0.0f;
				}
				m_spriteRender[5]->SetMulColor(MulColor);
				MulColor = m_spriteRender[6]->GetMulColor();
				MulColor.a -= 0.1f;
				if (MulColor.a < 0.0f) {
					MulColor.a = 0.0f;
				}
				m_spriteRender[6]->SetMulColor(MulColor);
				MulColor = m_spriteRender[7]->GetMulColor();
				MulColor.a -= 0.1f;
				if (MulColor.a < 0.0f) {
					MulColor.a = 0.0f;
				}
				m_spriteRender[7]->SetMulColor(MulColor);
				MulAlpha -= 0.1f;
				if (MulAlpha < 0.0f) {
					MulAlpha = 0.0f;
				}
				MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
				m_fontRender[0]->SetColor(MulColor);
				m_fontRender[1]->SetColor(MulColor);
			}
			if (DeleteTimer < 13) {
				position = m_spriteRender[1]->GetPosition();
				position.y -= 5.0f;
				m_spriteRender[1]->SetPosition(position);
				position = m_spriteRender[2]->GetPosition();
				position.y += 5.0f;
				m_spriteRender[2]->SetPosition(position);

			}
			else if (DeleteTimer < 25) {
				position = m_spriteRender[1]->GetPosition();
				position.y += 30.0f;
				m_spriteRender[1]->SetPosition(position);
				position = m_spriteRender[2]->GetPosition();
				position.y -= 30.0f;
				m_spriteRender[2]->SetPosition(position);
			}

			if (DeleteTimer == DeleteLimit) {
				GameData * gamedata = GameData::GetInstance();
				bool mode = gamedata->GetFinalMode();
				if (mode == false) {
					gamedata->SetGameMode(GameData::Battle2D_Mode);
				}
				else if (mode == true) {
					gamedata->SetGameMode(GameData::Battle3D_Mode);
				}

				DeleteGO(this);
			}

		}
		else if (CommandNow == true) {//リタイア
			if (DeleteTimer == 0) {
				TransitionMaker * tm = TransitionMaker::GetInstance();
				tm->TransitionSetting(TransitionMaker::Fade, 12, 0, false);
			}
			if (DeleteTimer == DeleteLimit) {
				TransitionMaker * tm = TransitionMaker::GetInstance();
				tm->TransitionSetting(TransitionMaker::Fade, 12, 20, true);

				GameData * gamedata = GameData::GetInstance();
				gamedata->SetGameMode(GameData::GameEnd);
				DeleteGO(this);
			}
		}

		DeleteTimer++;
	}

	//カーソル上下
	if (CursorFlag == false) {
		position = m_spriteRender[7]->GetPosition();
		position.y += 0.5f;
		m_spriteRender[7]->SetPosition(position);
	}
	else if (CursorFlag == true) {
		position = m_spriteRender[7]->GetPosition();
		position.y -= 0.5f;
		m_spriteRender[7]->SetPosition(position);
	}

	if (CursorCount == 12) {
		CursorFlag = true;
	}else if (CursorCount == 24) {
		CursorFlag = false;
		CursorCount = 0;
	}

	Timer++;
	CursorCount++;
}

void GamePause::CursorUpdate() {
	if (CommandNow == false) {
		m_spriteRender[7]->SetPosition({ 0.0f, -50.0f,0.0f });
		//
		m_spriteRender[5]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		m_spriteRender[6]->SetMulColor({ 0.5f,0.5f,0.5f,0.5f });
	}
	else if (CommandNow == true) {
		m_spriteRender[7]->SetPosition({ 0.0f, -150.0f,0.0f });
		//
		m_spriteRender[6]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		m_spriteRender[5]->SetMulColor({ 0.5f,0.5f,0.5f,0.5f });
	}

	CursorFlag = false;
	CursorCount = 0;
}
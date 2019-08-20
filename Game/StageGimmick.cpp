#include "stdafx.h"
#include "StageGimmick.h"
#include "BackGround.h"
#include "GameData.h"
#include "Train1.h"
#include "Train2.h"
#include "Player.h"

StageGimmick* StageGimmick::m_instance = nullptr;

StageGimmick::StageGimmick()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;
}


StageGimmick::~StageGimmick()
{
	if (GameData::GetInstance()->GetStageNo() == 3) {//電車ギミック

		for (int i = 0; i < m_spriteRender.size(); i++) {
			DeleteGO(m_spriteRender[i]);
		}

	}

	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

bool StageGimmick::Start() {

	if (GameData::GetInstance()->GetStageNo() == 3) {//電車ギミック
													 //モデルデータをロードしてキャッシュに乗せる
			trainModelData1.Load(L"modelData/Train_1.cmo");
			trainModelData2.Load(L"modelData/Train_2.cmo");
			//ビックリ！
			r = NewGO<prefab::CSpriteRender>(9);
			r->Init(L"sprite/bikkuri_Ya.dds", 200.0f, 200.0f);
			r->SetPosition({ 0.0f,200.0f,0.0f });
			r->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
			m_spriteRender.push_back(r);

	}

	return true;
}

void StageGimmick::Update() {

	if (GameData::GetInstance()->GetStageNo() == 3 && (GameData::GetInstance()->GetGameMode() != GameData::Pause && GameData::GetInstance()->GetGameMode() != GameData::Result)) {//電車ギミック
		BackGround * backGround = BackGround::GetInstance();
		
		
		if (TrainFlag == false) {//この処理を最初にしないと初回電車召喚時に一瞬止まる 理由はしらん
			if (timer == 0) {
				
				TrainFlag = true;
			}
		}
		

		if (timer == TrainLimit - 80) {//合図
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/TrainBell.wav");
			ss->SetVolume(1.0f);
			ss->Play(false);

			backGround->PlayBG_Anime(2);
			m_spriteRender[0]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		}

		if (timer == TrainLimit) {

			CVector3 P_pos = Player::GetInstance()->Getm_Position();
			float PosZ = 0.0f;
			if (P_pos.z < 0) {
				PosZ = -1200.0f;
			}
			else {
				PosZ = 1400.0f;
			}

			train1 = NewGO<Train1>(0, "Train1");
			train1->SetPosition({ 0.0f - TrainX, -500.0f, PosZ });
			train1->SetSE_Flag(true);
			train2 = NewGO<Train2>(0, "Train2");
			train2->SetPosition({ -4800.0f - TrainX, -500.0f, PosZ });
			train2->SetSE_Flag(true);
		}

		if (timer == TrainLimit + 180) {//終了

			int random = rand() % 500;
			TrainLimit = 300 + random;

			backGround->PlayBG_Anime(1);
			m_spriteRender[0]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });

			timer = 0;
		}

		timer++;
	}
	if (GameData::GetInstance()->GetStageNo() == 3 && GameData::GetInstance()->GetGameMode() == GameData::Result) {
		m_spriteRender[0]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });

	}
}
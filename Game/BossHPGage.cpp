#include "stdafx.h"
#include "BossHPGage.h"
#include "GameData.h"

//ボスデータ
#include "shisokus.h"
#include "Pairodorago.h"
#include "SS_001.h"

BossHPGage* BossHPGage::m_instance = nullptr;

BossHPGage::BossHPGage()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

}

BossHPGage::~BossHPGage()
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

bool BossHPGage::Start() {

	GameData * gamedata = GameData::GetInstance();
	stage = gamedata->GetStageNo() - 1;

	//ボスHP土台 0
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/BossLifeBar_base.dds", 1100.0f, 100.0f);
	Position = { HPBarX, HPBarY, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	r->SetScale({ 1.0f,1.0f,1.0f });
	r->SetPivot({ 0.5f,0.5f });
	m_spriteRender.push_back(r);
	//ボスHP 1
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/BossLifeBarWhite.dds", 1100.0f, 100.0f);
	Position = { HPBarX-550.0f, HPBarY, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	r->SetPivot({ 0.0f,0.5f });
	r->SetScale({ 1.0f,0.0f,1.0f });
	m_spriteRender.push_back(r);
	//ボスHPダミー 2
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/BossLifeBar.dds", 1100.0f, 100.0f);
	Position = { HPBarX-550.0f, HPBarY, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	r->SetPivot({ 0.0f,0.5f });
	r->SetScale({ 1.0f,0.0f,1.0f });
	m_spriteRender.push_back(r);
	//ボスHP上 3
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/BossLifeBarUe.dds", 1100.0f, 100.0f);
	Position = { HPBarX, HPBarY, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	r->SetScale({ 1.0f,1.0f,1.0f });
	r->SetPivot({ 0.5f,0.5f });
	m_spriteRender.push_back(r);
	//ボスアイコン 4
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/BossIcon.dds", 100.0f, 100.0f);
	Position = { HPBarX+480.0f, HPBarY, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	r->SetScale({ 1.0f,1.0f,1.0f });
	r->SetPivot({ 0.5f,0.5f });
	m_spriteRender.push_back(r);
	//ボスの名前
	f = NewGO<prefab::CFontRender>(1);
	//おわ
	swprintf(bossname, bossname);
	//はい。
	f->SetText(bossname);
	f->SetPosition({ 440.0f, 300.0f });
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	f->SetColor(MulColor);
	f->SetScale(1.0f);
	f->SetPivot({ 1.0f,1.0f });
	m_fontRender.push_back(f);

	return true;
}

void BossHPGage::Update() {

	if (Timer < 80) {//フェード
		MulAlpha += 0.05f;
		if (MulAlpha > 1.0f) {
			MulAlpha = 1.0f;
		}
		MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
		m_spriteRender[0]->SetMulColor(MulColor);
		m_spriteRender[1]->SetMulColor(MulColor);
		m_spriteRender[2]->SetMulColor(MulColor);
		m_spriteRender[3]->SetMulColor(MulColor);
		m_spriteRender[4]->SetMulColor(MulColor);
		m_fontRender[0]->SetColor(MulColor);
	}
	else if (Timer < 160) {
		HogeHP += 2;
		if (HogeHP > 100) {//疑似HPがマックス
			if (HPMAX_Flag == false) {
				//ボスHP演出用 5
				r = NewGO<prefab::CSpriteRender>(1);
				r->Init(L"sprite/BossLifeBarWhite.dds", 1100.0f, 100.0f);
				Position = { HPBarX, HPBarY, 1.0f };//座標
				r->SetPosition(Position);//座標を反映
				MulColor = { 1.0f,1.0f,1.0f,0.0f };
				r->SetMulColor(MulColor);
				r->SetPivot({ 0.5f,0.5f });
				r->SetScale({ 1.0f,1.0f,1.0f });
				m_spriteRender.push_back(r);
				HPMAX_Flag = true;
			}
			else {//白いバーがびゅんってします
				if (HPMAX_FlagYobi == false) {
					MulAlphaYobi += 0.05f;
					if (MulAlphaYobi > 0.4f) {
						HPMAX_FlagYobi = true;
					}
				}
				else {
					MulAlphaYobi -= 0.05f;
					if (MulAlphaYobi < 0.0f) {
						MulAlphaYobi = 0.0f;
					}
				}
				HPMAX_Scale += 0.1f;
				m_spriteRender[5]->SetMulColor({ 1.0f,1.0f,1.0f,MulAlphaYobi });
				m_spriteRender[5]->SetScale({ HPMAX_Scale ,HPMAX_Scale ,HPMAX_Scale });
			}
			m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
			m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
			m_spriteRender[1]->SetScale(BarScale);
			HogeHP = 100;
		}
		else {
			m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,0.5f });
		}
		float BarX = (float)HogeHP / 100.0f;
		BarScale = { BarX,1.0f,1.0f };
		m_spriteRender[2]->SetScale(BarScale);
	}
	else {//バーの更新
		if (stage == 0) {
			//ゲージの拡大率を計算
			shisokus * shiso = FindGO<shisokus>("shiso");
			int NowHP = shiso->GetHP();
			int MAXHP = shiso->GetMAXHP();
			float BarX = (float)NowHP / (float)MAXHP;
			BarScale = { BarX,1.0f,1.0f };
		}
		if (stage == 1) {
			//ゲージの拡大率を計算
			Pairodorago * pairodorago = FindGO<Pairodorago>("Pairodorago");
			int NowHP = pairodorago->GetHP();
			int MAXHP = pairodorago->GetMAXHP();
			float BarX = (float)NowHP / (float)MAXHP;
			BarScale = { BarX,1.0f,1.0f };
		}
		if (stage == 2) {
			//ゲージの拡大率を計算
			SS_001 * ss_001 = FindGO<SS_001>("SS_001");
			int NowHP = ss_001->GetHP();
			int MAXHP = ss_001->GetMAXHP();
			float BarX = (float)NowHP / (float)MAXHP;
			BarScale = { BarX,1.0f,1.0f };
		}

		//緑ゲージの拡大率を取得して差があれば小さくする！
		CVector3 Ue_Gage = m_spriteRender[2]->GetScale();
		CVector3 Sita_Gage = m_spriteRender[1]->GetScale();
		if (Ue_Gage.x < Sita_Gage.x) {
			Sita_Gage.x -= 0.01f;
			if (Ue_Gage.x > Sita_Gage.x) {
				Sita_Gage.x = Ue_Gage.x;
			}
		}

		m_spriteRender[1]->SetScale(Sita_Gage);
		m_spriteRender[2]->SetScale(BarScale);
	}

	//削除演出…
	if (DeleteTimer >= 0) {

		MulColor = { 1.0f,1.0f,1.0f,DeleteMulAlpha };
		m_spriteRender[0]->SetMulColor(MulColor);
		m_spriteRender[1]->SetMulColor(MulColor);
		m_spriteRender[2]->SetMulColor(MulColor);
		m_spriteRender[3]->SetMulColor(MulColor);
		m_spriteRender[4]->SetMulColor(MulColor);
		m_fontRender[0]->SetColor(MulColor);

		DeleteMulAlpha -= 0.01f;
		if (DeleteMulAlpha < 0.0f) {
			DeleteMulAlpha = 0.0f;
		}
		DeleteTimer++;
		if (DeleteTimer == DeleteLimit) {
			DeleteGO(this);
			DeleteTimer = -1;
		}
	}

	Timer++;

}


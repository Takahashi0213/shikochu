#include "stdafx.h"
#include "BossHPGage.h"
#include "GameData.h"

//ボスデータ
#include "shisokus.h"

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

	//ボスHP土台
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/BossLifeBar_base.dds", 1100.0f, 100.0f);
	Position = { 0.0f, HPBarY, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	r->SetScale({ 1.0f,1.0f,1.0f });
	r->SetPivot({ 0.5f,0.5f });
	m_spriteRender.push_back(r);
	//ボスHP
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/BossLifeBar.dds", 1100.0f, 100.0f);
	Position = { -550.0f, HPBarY, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	r->SetPivot({ 0.0f,0.5f });
	r->SetScale({ 1.0f,0.0f,1.0f });
	m_spriteRender.push_back(r);
	//ボスHP上
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/BossLifeBarUe.dds", 1100.0f, 100.0f);
	Position = { 0.0f, HPBarY, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	r->SetScale({ 1.0f,1.0f,1.0f });
	r->SetPivot({ 0.5f,0.5f });
	m_spriteRender.push_back(r);
	//
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
		m_fontRender[0]->SetColor(MulColor);
	}
	else if (Timer < 140) {
		HogeHP += 2;
		if (HogeHP > 100) {
			m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
			HogeHP = 100;
		}
		else {
			m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,0.5f });
		}
		float BarX = (float)HogeHP / 100.0f;
		BarScale = { BarX,1.0f,1.0f };
		m_spriteRender[1]->SetScale(BarScale);
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
		m_spriteRender[1]->SetScale(BarScale);
	}

	Timer++;

}

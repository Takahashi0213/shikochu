#include "stdafx.h"
#include "TitleStandby.h"
#include "Title.h"
#include "GameData.h"
#include "EffectManager.h"
#include "UICamera.h"
#include "SaveData.h"
#include "TransitionMaker.h"

TitleStandby* TitleStandby::m_instance = nullptr;

TitleStandby::TitleStandby()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

}


TitleStandby::~TitleStandby()
{
	for (int i = 0; i < m_spriteRender.size(); i++) {
		DeleteGO(m_spriteRender[i]);
	}

	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;

}

bool TitleStandby::Start() {

	//ゲームデータ
	//NewGO<GameData>(0, "GameData");
	NewGO<EffectManager>(0, "EffectManager");
	NewGO<UICamera>(0, "UICamera");
	//NewGO<SaveData>(0, "SaveData");
	NewGO<TransitionMaker>(0, "TransitionMaker");

	//0番 まっくろ！
	r = NewGO<prefab::CSpriteRender>(11);
	r->Init(L"sprite/Black.dds", 1280.0f, 720.0f);
	r->SetPosition({ 0.0f ,0.0f,0.0f });
	m_spriteRender.push_back(r);
	//1番 ロゴ
	r = NewGO<prefab::CSpriteRender>(11);
	r->Init(L"sprite/mmhiyoko.dds", 770.0f, 440.0f);
	r->SetPosition({ 0.0f ,0.0f,0.0f });
	r->SetMulColor(color);
	m_spriteRender.push_back(r);

	return true;
}

void TitleStandby::Update() {

	if (Timer > 10 && Timer < 30) {
		color = m_spriteRender[1]->GetMulColor();
		color.a += 0.1f;
		if (color.a > 1.0f) {
			color.a = 1.0f;
		}
		m_spriteRender[1]->SetMulColor(color);
	}

	if (Timer == 80) {
		TransitionMaker * tm = TransitionMaker::GetInstance();
		tm->TransitionSetting(TransitionMaker::Fade, 12, 0, false);
	}

	if (Timer == 100) {
		TransitionMaker * tm = TransitionMaker::GetInstance();
		tm->TransitionSetting(TransitionMaker::Fade, 12, 0, true);
		NewGO<Title>(0);
		DeleteGO(this);
	}
	Timer++;
}
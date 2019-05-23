#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "StageSelect.h"
#include "GameData.h"
#include "EffectManager.h"
#include "UICamera.h"

Title* Title::m_instance = nullptr;

Title::Title()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

}


Title::~Title()
{
	for (int i = 0; i < m_spriteRender.size(); i++) {
		DeleteGO(m_spriteRender[i]);
	}
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

bool Title::Start() {

	//ゲームデータ
	NewGO<GameData>(0, "GameData");
	NewGO<EffectManager>(0, "EffectManager");
	NewGO<UICamera>(0, "UICamera");

	//タイトル
	DisableSpecialLigRange();
	prefab::CSpriteRender* r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/rogo.dds", 440.0f, 245.0f);
	m_spriteRender.push_back(r);

	return true;
}

void Title::Update() {
	if (Pad(0).IsPress(enButtonA)) {
		DeleteGOs("UICamera");
		NewGO<StageSelect>(0, "StageSelect");

		DeleteGO(this);
	}
}
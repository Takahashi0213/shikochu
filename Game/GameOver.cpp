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

	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;

}

bool GameOver::Start() {

	//0番→背景
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/gameover.dds", 880.0f, 320.0f);
	r->SetPosition({ 0.0f,200.0f,0.0f });
	m_spriteRender.push_back(r);

	return true;
}

void GameOver::Update() {

	if (Pad(0).IsTrigger(enButtonA) || Pad(0).IsTrigger(enButtonB) || Pad(0).IsTrigger(enButtonY) || Pad(0).IsTrigger(enButtonX)) {
		if (DeleteFlag == false) {
			TransitionMaker * tm = TransitionMaker::GetInstance();
			tm->TransitionSetting(TransitionMaker::Fade, 12, 0, false);
			DeleteFlag = true;
		}
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
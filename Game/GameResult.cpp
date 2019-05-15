#include "stdafx.h"
#include "GameResult.h"

GameResult* GameResult::m_instance = nullptr;

GameResult::GameResult()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

}

GameResult::~GameResult()
{
	for (int i = 0; i < m_spriteRender.size(); i++) {
		DeleteGO(m_spriteRender[i]);
	}
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;

}

bool GameResult::Start() {

	return true;
}

void GameResult::Update() {

}
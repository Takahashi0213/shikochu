#include "stdafx.h"
#include "GameResult.h"

GameResult* GameResult::m_instance = nullptr;

GameResult::GameResult()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;

}

GameResult::~GameResult()
{
	for (int i = 0; i < m_spriteRender.size(); i++) {
		DeleteGO(m_spriteRender[i]);
	}
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;

}

bool GameResult::Start() {

	return true;
}

void GameResult::Update() {

}
#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title* Title::m_instance = nullptr;

Title::Title()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;

}


Title::~Title()
{
	for (int i = 0; i < m_spriteRender.size(); i++) {
		DeleteGO(m_spriteRender[i]);
	}
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
}

bool Title::Start() {

	DisableSpecialLigRange();
	prefab::CSpriteRender* r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/rogo.dds", 440.0f, 245.0f);
	m_spriteRender.push_back(r);

	return true;
}

void Title::Update() {
	if (Pad(0).IsPress(enButtonStart)) {
		NewGO<Game>(0, "game");

		DeleteGO(this);
	}
}
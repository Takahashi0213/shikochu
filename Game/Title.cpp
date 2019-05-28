#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "StageSelect.h"
#include "GameData.h"
#include "EffectManager.h"
#include "UICamera.h"
#include "SaveData.h"
#include "TransitionMaker.h"

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

	//�Q�[���f�[�^
	NewGO<GameData>(0, "GameData");
	NewGO<EffectManager>(0, "EffectManager");
	NewGO<UICamera>(0, "UICamera");
	NewGO<SaveData>(0, "SaveData");
	NewGO<TransitionMaker>(0, "TransitionMaker");

	//�^�C�g��
	DisableSpecialLigRange();
	prefab::CSpriteRender* r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/rogo.dds", 440.0f, 245.0f);
	m_spriteRender.push_back(r);

	return true;
}

void Title::Update() {
	if (Pad(0).IsPress(enButtonA)) {
		NewGO<StageSelect>(0, "StageSelect");

		DeleteGO(this);
	}
}
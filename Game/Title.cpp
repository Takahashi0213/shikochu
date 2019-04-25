#include "stdafx.h"
#include "Title.h"
#include "Game.h"


Title::Title()
{
}


Title::~Title()
{
	for (int i = 0; i < m_spriteRender.size(); i++) {
		DeleteGO(m_spriteRender[i]);
	}
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
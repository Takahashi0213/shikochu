#include "stdafx.h"
#include "BossHPGage.h"


BossHPGage::BossHPGage()
{
}


BossHPGage::~BossHPGage()
{
}

bool BossHPGage::Start() {

	//�{�XHP�y��
	prefab::CSpriteRender* r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/BossLifeBar_base.dds", 1100.0f, 100.0f);
	CVector3 Position = { 0.0f, 326.0f, 1.0f };//���W
	r->SetPosition(Position);//���W�𔽉f
	m_spriteRender.push_back(r);
	//�{�XHP
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/BossLifeBar.dds", 1100.0f, 100.0f);
	Position = { 0.0f, 326.0f, 1.0f };//���W
	r->SetPosition(Position);//���W�𔽉f
	m_spriteRender.push_back(r);
	//�{�XHP��
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/BossLifeBarUe.dds", 1100.0f, 100.0f);
	Position = { 0.0f, 326.0f, 1.0f };//���W
	r->SetPosition(Position);//���W�𔽉f
	m_spriteRender.push_back(r);

	return true;
}

void BossHPGage::Update() {

}

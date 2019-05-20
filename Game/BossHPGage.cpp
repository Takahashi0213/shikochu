#include "stdafx.h"
#include "BossHPGage.h"


BossHPGage::BossHPGage()
{
}


BossHPGage::~BossHPGage()
{
}

bool BossHPGage::Start() {

	//ボスHP土台
	prefab::CSpriteRender* r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/BossLifeBar_base.dds", 1100.0f, 100.0f);
	CVector3 Position = { 0.0f, 326.0f, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	m_spriteRender.push_back(r);
	//ボスHP
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/BossLifeBar.dds", 1100.0f, 100.0f);
	Position = { 0.0f, 326.0f, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	m_spriteRender.push_back(r);
	//ボスHP上
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/BossLifeBarUe.dds", 1100.0f, 100.0f);
	Position = { 0.0f, 326.0f, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	m_spriteRender.push_back(r);

	return true;
}

void BossHPGage::Update() {

}

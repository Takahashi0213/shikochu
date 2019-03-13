#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
	DeleteGO(m_skinModelRender);
}

bool Enemy::Start()
{
	//‚¤‚Ó‚Ó...‚ ‚Í‚ñ
	m_skinModelRender=NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/bunbo-gu0.cmo");

	m_scale = { 2.0f,2.0f,2.0f };
	
	return true;
}

void Enemy::Update()
{
	//ˆÚ“®
	m_skinModelRender->SetPosition(m_position);
	//‰ñ“]
	m_skinModelRender->SetRotation(m_rotation);
	//Šg‘å—¦
	m_skinModelRender->SetScale(m_scale);

}
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
	//うふふ...あはん
	m_skinModelRender=NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/bunbo-gu0.cmo");

	m_scale = { 2.0f,2.0f,2.0f };
	
	return true;
}

void Enemy::Update()
{
	//移動
	m_skinModelRender->SetPosition(m_position);
	//回転
	m_skinModelRender->SetRotation(m_rotation);
	//拡大率
	m_skinModelRender->SetScale(m_scale);

}
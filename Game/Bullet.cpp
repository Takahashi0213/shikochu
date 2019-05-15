#include "stdafx.h"
#include "Bullet.h"
#include "Player.h"
#include "Neoriku.h"

Bullet::Bullet()
{
}


Bullet::~Bullet()
{
	DeleteGO(m_skinModelRender);
}

bool Bullet::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/bullet.cmo");
	Neoriku* neoriku = FindGO<Neoriku>("neo");
	CVector3 N_Position = neoriku->Getm_Position();
	m_position = N_Position;
	m_skinModelRender->SetPosition(m_position);
	return true;
}

void Bullet::Update()
{
	//攻撃ﾀﾞﾖ
	//弾丸を移動させる。
	m_position *= moveSpeed;
	//スキンモデルレンダーに座標を伝える。
	m_skinModelRender->SetPosition(m_position);
	//タイマーを加算する。
	m_timer++;
	if (m_timer == 180) {
		//タイマーが180になったらインスタンスを削除する。
		DeleteGO(this);
	}
}
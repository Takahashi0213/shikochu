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
	//�U�����
	//�e�ۂ��ړ�������B
	m_position *= moveSpeed;
	//�X�L�����f�������_�[�ɍ��W��`����B
	m_skinModelRender->SetPosition(m_position);
	//�^�C�}�[�����Z����B
	m_timer++;
	if (m_timer == 180) {
		//�^�C�}�[��180�ɂȂ�����C���X�^���X���폜����B
		DeleteGO(this);
	}
}
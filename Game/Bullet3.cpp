#include "stdafx.h"
#include "Bullet3.h"
#include "Player.h"
#include "Uminoushi.h"
#include "GameData.h"


Bullet3::Bullet3()
{
}


Bullet3::~Bullet3()
{
	DeleteGO(m_skinModelRender);
}

bool Bullet3::Start()
{
	prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
	ss->Init(L"sound/Bullet.wav", true);
	ss->SetVolume(0.2f);
	ss->Play(false);
	ss->SetPosition(m_position * 0.01f);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/bullet.cmo");

	CVector3 N_Position = m_uminoushi->Getm_Position();
	m_position = N_Position;
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(bulletscale);

	m_skinModelRender->SetEmissionColor(bulletEmissionColor);

	return true;
}

void Bullet3::Update()
{
	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();
	if (mode != GameData::Pause) {

		//�ړ�
		m_position += b_move;

		//���W��`����B
		m_skinModelRender->SetPosition(m_position);

		if (dathflag == true) {
			DeleteGO(this);
		}

		m_timer++;
		if (m_timer == bulletdelete) {
			//���Ԃ���������C���X�^���X���폜����B
			DeleteGO(this);
		}
	}
	if (mode == GameData::GameEnd) {
		DeleteGO(this);
	}

}

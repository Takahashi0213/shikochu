#include "stdafx.h"
#include "Bullet4.h"
#include "Player.h"
#include "Suroku.h"
#include "GameData.h"

Bullet4::Bullet4()
{
}


Bullet4::~Bullet4()
{
	DeleteGO(m_skinModelRender);
}

bool Bullet4::Start()
{
	prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
	ss->Init(L"sound/Bullet.wav", true);
	ss->SetVolume(1.0f);
	ss->Play(false);
	ss->SetPosition(m_position * 0.01f);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/bullet.cmo");

	CVector3 N_Position = m_suroku->Getm_Position();
	m_position = N_Position;
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(bulletscale);

	m_skinModelRender->SetEmissionColor(bulletEmissionColor);

	return true;
}

void Bullet4::Update()
{
	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();
	if (mode != GameData::Pause) {

		//�U�����
		if (keisannflag == false) {
			Player* player = FindGO<Player>("Bug");
			CVector3 P_Position = player->Getm_Position();

			CVector3 Ne_Position = m_suroku->Getm_Position();
			CVector3 diff = P_Position - Ne_Position;
			buvec = diff;
			buvec.Normalize();
			keisannflag = true;
		}
		m_position += buvec * moveSpeed;

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
#include "stdafx.h"
#include "Bullet2.h"
#include "Player.h"
#include "Riritto.h"
#include "GameData.h"

Bullet2::Bullet2()
{
}


Bullet2::~Bullet2()
{
	DeleteGO(m_skinModelRender);
}

bool Bullet2::Start()
{
	prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
	ss->Init(L"sound/Bullet.wav", true);
	ss->SetVolume(1.0f);
	ss->Play(false);
	ss->SetPosition(m_position * 0.01f);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/bullet.cmo");

	CVector3 N_Position = m_riritto->Getm_Position();
	m_position = N_Position;
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(bulletscale);

	random = rand() % 2;
	return true;
}
void Bullet2::follow() {
	//���Ă�����
	bullettime++;
	if(bullettime<bullettuibi){
		Player* player = FindGO<Player>("Bug");
		CVector3 P_Position = player->Getm_Position();
		CVector3 Ri_Position = m_riritto->Getm_Position();
		CVector3 diff = P_Position - Ri_Position;
		diff.Normalize();
		m_position += diff * moveSpeed;
	}
	else {
		if (flag == false) {
			Player* player = FindGO<Player>("Bug");
			CVector3 P_Position = player->Getm_Position();
			CVector3 Ri_Position = m_riritto->Getm_Position();
			CVector3 diff = P_Position - Ri_Position;
			buvec = diff;
			buvec.Normalize();
			flag = true;
		}
		m_position += buvec * moveSpeed;
	}
	m_skinModelRender->SetEmissionColor(bulletEmissionColor2);

}
void Bullet2::move() {
	//�܂�������Ԃ�
	if (keisannflag == false) {
		Player* player = FindGO<Player>("Bug");
		CVector3 P_Position = player->Getm_Position();
		CVector3 Ri_Position = m_riritto->Getm_Position();
		CVector3 diff = P_Position - Ri_Position;
		buvec = diff;
		buvec.Normalize();
		keisannflag = true;
	}


	m_skinModelRender->SetEmissionColor(bulletEmissionColor);
	m_position += buvec * moveSpeed;
}

void Bullet2::Update()
{
	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();
	if (mode != GameData::Pause) {

		//�U�����

		if (random == 0) {
			move();
		}
		else {
			follow();
		}

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
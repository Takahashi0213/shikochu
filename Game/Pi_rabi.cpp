#include "stdafx.h"
#include "Pi_rabi.h"
#include "Player.h"


Pi_rabi::Pi_rabi()
{
}


Pi_rabi::~Pi_rabi()
{
}

bool Pi_rabi::Start() {


	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Rabbit_Level_1.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);
	return true;
}

void Pi_rabi::Piattack() {

}
void Pi_rabi::PiMove() {
	//è„â∫
		movecount++;
		if (movecount <= moveD) {
			m_position.y -= 0.5f;
		}
		else if (movecount <= moveup) {
			m_position.y += 0.5f;
		}
		else if (movecount <= movedown) {
			m_position.y -= 0.5f;

		}
		else {
			movecount = 0;
		}
		Player * player = Player::GetInstance();
		CVector3 P_Position = player->Getm_Position();
		CVector3 diff = P_Position - m_position;
		/*Pivec = diff;
		if (diff.Length() < followstop) {
			//í‚é~ãóó£
			m_position = Pivec * Speed;
		}
		else {
			//í«Ç¢Ç©ÇØÇÈÇÊ!
			Pivec.Normalize();
			m_position = Pivec * followSpeed;

		}
		if (diff.Length() < followleave) {
			//ãﬂÇ¢ÇÊyoó£ÇÍÇÈyo!
			Pivec.Normalize();
			m_position = Pivec * followSpeed * -1.0f;
		}*/

		CVector3 enemyForward = {1.0f, 0.0f, 0.0f };
		//ÉvÉåÉCÉÑÅ[ÇÃå¸Ç´Ç…âÒì]
		diff.y = 0.0f;
		diff.Normalize();
		CQuaternion qRot;
		qRot.SetRotation(enemyForward, diff);
		m_rotation = qRot;
	
}

void Pi_rabi::PiFollow() {

}

void Pi_rabi::PiDeath() {
	DeleteGO(this);
}


void Pi_rabi::Update() {
	switch (m_stete)
	{
	case Estete_Attack:
		Piattack();
		break;
	case Estete_Move:
		PiMove();
		break;
	case Estete_Follow:
		PiFollow();
		break;
	case Estete_Death:
		PiDeath();
		break;
	}

	//à⁄ìÆ
	m_skinModelRender->SetPosition(m_position);
	//âÒì]
	m_skinModelRender->SetRotation(m_rotation);
	//ägëÂó¶
	m_skinModelRender->SetScale(m_scale);

}

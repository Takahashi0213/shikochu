#include "stdafx.h"
#include "Neruk.h"
#include "Player.h"
#include "shisokus.h"
#include "NerukGenerator.h"



Neruk::Neruk()
{
}


Neruk::~Neruk()
{
	DeleteGO(m_skinModelRender);
}
bool Neruk::Start() {
	//�A�j���[�V����
	m_animClips[enAnimationClip_move].Load(L"animData/Neruwalk.tka");
	m_animClips[enAnimationClip_move].SetLoopFlag(true);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Neruk.cmo", m_animClips, enAnimationClip_Num);
	typerandom = rand() % 3;
	posmove = m_nerukGenerator->moverandom;
	animove = m_nerukGenerator->animesionrandom;
	if (posmove == 0) {
		m_position = oldpos1;
	}
	else if (posmove == 1) {
		m_position = oldpos2;

	}
	else if (posmove == 2) {
		m_position = oldpos3;

	}
	else if (posmove == 3) {
		m_position = oldpos4;

	}
	else if (posmove == 4) {
		m_position = oldpos5;

	}
	else if (posmove == 5) {
		m_position = oldpos6;

	}

	m_skinModelRender->SetPosition(m_position);
	m_scale = { 5.0f,5.0f,5.0f };
	return true;
 }

void Neruk::position1() {

	CVector3 diff = pos1 - oldpos1;
	diff /= (float)moveflame1;
	if (moveflag == false) {
		m_position += diff;
		movetimer++;
		if (movetimer > moveflame1) {
			moveflag = true;
		}
	}
	else if (moveflag == true) {
		if (animove == 0) {
			m_stete = Estete_Attack;
		}
		else if (animove == 1) {
			m_stete = Estete_Move;
		}

	}
}
void Neruk::position2() {

	CVector3 diff = pos2 - oldpos2;
	diff /= (float)moveflame1;
	if (moveflag == false) {
		m_position += diff;
		movetimer++;
		if (movetimer > moveflame1) {
			moveflag = true;
		}
	}
	else if (moveflag == true) {
		if (animove == 0) {
			m_stete = Estete_Attack;
		}
		else if (animove == 1) {
			m_stete = Estete_Move;
		}
	}
}
void Neruk::position3() {

	CVector3 diff = pos3 - oldpos3;
	diff /= (float)moveflame1;
	if (moveflag == false) {
		m_position += diff;
		movetimer++;
		if (movetimer > moveflame1) {
			moveflag = true;
		}
	}
	else if (moveflag == true) {
		if (animove == 0) {
			m_stete = Estete_Attack;
		}
		else if (animove == 1) {
			m_stete = Estete_Move;
		}

	}
}
void Neruk::position4() {

	CVector3 diff = pos4 - oldpos4;
	diff /= (float)moveflame1;
	if (moveflag == false) {
		m_position += diff;
		movetimer++;
		if (movetimer > moveflame1) {
			moveflag = true;
		}
	}
	else if (moveflag == true) {
		if (animove == 0) {
			m_stete = Estete_Attack;
		}
		else if (animove == 1) {
			m_stete = Estete_Move;
		}

	}
}
void Neruk::position5() {

	CVector3 diff = pos5 - oldpos5;
	diff /= (float)moveflame1;
	if (moveflag == false) {
		m_position += diff;
		movetimer++;
		if (movetimer > moveflame1) {
			moveflag = true;
		}
	}
	else if (moveflag == true) {
		if (animove == 0) {
			m_stete = Estete_Attack;
		}
		else if (animove == 1) {
			m_stete = Estete_Move;
		}

	}
}
void Neruk::position6() {

	CVector3 diff = pos6 - oldpos6;
	diff /= (float)moveflame1;
	if (moveflag == false) {
		m_position += diff;
		movetimer++;
		if (movetimer > moveflame1) {
			moveflag = true;
		}
	}
	else if (moveflag == true) {
		if (animove == 0) {
			m_stete = Estete_Attack;
		}
		else if (animove == 1) {
			m_stete = Estete_Move;
		}

	}
}


void Neruk::Movetype1() {
	if (movecount < endcount) {
		//�㉺�̈ړ�
		waittimer++;
		if (waittimer <= up) {
			m_position.y += typemove;
		}
		else if (waittimer <= down) {
			m_position.y -= typemove;
		}
		else {
			movecount++;
			waittimer = 0;
		}
	}
	else {
		typeflag = true;
	}
}
void Neruk::Movetype2() {
	if (movecount < endcount) {
		//�㉺�̈ړ�
		waittimer++;
		if (waittimer <= Right) {
			m_position.x += typemove;
		}
		else if (waittimer <= Left) {
			m_position.x -= typemove;
		}
		else {
			movecount++;
			waittimer = 0;
		}
	}
	else {
		typeflag = true;
	}

}
void Neruk::Movetype3() {
	if (movecount < endcount) {
		//�㉺�̈ړ�
		waittimer++;
		if (waittimer <= Rightup) {
			m_position.x += typemove;
			m_position.y += typemove;

		}
		else if (waittimer <= Leftdown) {
			m_position.x -= typemove;
			m_position.y -= typemove;
		}
		else if (waittimer <= Leftup) {
			m_position.x -= typemove;
			m_position.y += typemove;

		}
		else if (waittimer <= Rightdown) {
			m_position.x += typemove;
			m_position.y -= typemove;
		}

		else {
			movecount++;
			waittimer = 0;
		}
	}
	else {
		typeflag = true;
	}

}

void Neruk::NeruAttack() {
	Player* player = FindGO<Player>("Bug");
	int D_stete = player->GetState();
	if (D_stete != Player::Estate_Death) {

		if (attackflag == false) {
			CVector3 P_Position = player->Getm_Position();
			CVector3 diff = P_Position - m_position;
			atmove = diff;
			atmove.Normalize();
			attackflag = true;
		}
		if (deathtimer > deathwait) {
			m_position += atmove * attackmove;
		}
		deathtimer++;
		if (deathtimer > deathattack) {
			DeleteGO(this);
		}
	}
}
void Neruk::NeruMove() {
	if (typeflag ==false) {
		if (typerandom == 0) {
			Movetype1();
		}
		else if (typerandom == 1) {
			Movetype2();
		}
		else if (typerandom == 2) {
			Movetype3();
		}

	}
	else {
		if (posmove == 0) {
			deathdiff = oldpos1 - m_position;
		}
		else if (posmove == 1) {
			deathdiff = oldpos2 - m_position;

		}
		else if (posmove == 2) {
			deathdiff = oldpos3 - m_position;

		}
		else if (posmove == 3) {
			deathdiff = oldpos4 - m_position;

		}
		else if (posmove == 4) {
			deathdiff = oldpos5 - m_position;

		}
		else if (posmove == 5) {
			deathdiff = oldpos6 - m_position;

		}

		deathdiff /= (float)moveflame1;
		m_position += deathdiff;
		movetimer++;
		if (movetimer > deathMove) {
			DeleteGO(this);
		}
	}
}

void Neruk::NeruSelect() {
	//�ړ����Ă���ꏊ����
	if (posmove == 0) {
		position1();
	}
	else if (posmove == 1) {
		position2();

	}
	else if (posmove == 2) {
		position3();

	}
	else if (posmove == 3) {
		position4();
	}
	else if (posmove == 4) {
		position5();

	}
	else if (posmove == 5) {
		position6();

	}

}
void Neruk::NeruDeath() {
		DeleteGO(this);
}
void Neruk::Update() {
	switch (m_stete){
	case Neruk::Estete_Select:
		NeruSelect();
		break;
	case Neruk::Estete_Move:
		NeruMove();
		break;
	case Neruk::Estete_Attack:
		NeruAttack();
		break;

	case Neruk::Estete_Death:
		NeruDeath();
		break;
	}
	shisokus* shisok = FindGO<shisokus>("shiso");
	int s_stete = shisok->GetEState();
	if (s_stete == shisokus::Estete_Death) {
		m_stete = Estete_Death;
	}

	//�ړ�
	m_skinModelRender->SetPosition(m_position);
	//��]
	m_skinModelRender->SetRotation(m_rotation);
	//�g�嗦
	m_skinModelRender->SetScale(m_scale);

}
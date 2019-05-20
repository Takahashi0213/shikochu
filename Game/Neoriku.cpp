#include "stdafx.h"
#include "Neoriku.h"
#include "GameData.h"
#include "Player.h"
#include "Bullet.h"


Neoriku::Neoriku()
{
}


Neoriku::~Neoriku()
{
	DeleteGO(m_skinModelRender);
}

bool Neoriku::Start() {
	//�A�j���[�V�����N���b�v�����[�h�ƃ��[�v�t���O�B
	m_animClips[enAnimationClip_walk].Load(L"animData/Neowalk.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);

	//�X�L�����f��
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/neoriku_0.cmo", m_animClips, enAnimationClip_Num);
	m_skinModelRender->SetForwardRenderFlag(true);

	m_scale = { 2.0f,2.0f,2.0f };
	m_charaCon.Init(
		35.0f,  //�L�����N�^�[�̔��a�B
		10.0f,  //�L�����N�^�[�̍����B
		m_position //�L�����N�^�[�̏������W�B
	);


	return true;
}

void Neoriku::NeoAttack() {
	//��������ł�
	movetimer++;
	if (bulletFlag == false) {
		Bullet* bullet = NewGO<Bullet>(0,"bullet");
		bullet->Init(this);
		bulletFlag = true;
	}
	else if (movetimer < move_starttimer) {
		colorcount -= 1.0f;
		if (colorcount < 0.0f) {
			colorcount = 0.0f;
		}
		m_skinModelRender->SetEmissionColor({ 0.0f , colorcount, colorcount });
	}
	else if (movetimer >= move_starttimer) {
		count = 0;
		timer = 0;
		movetimer = 0;
		m_stete = Estete_Move;
	}

}
void Neoriku::NeoYobi() {
	//�\������ŐF���ω������������
	if (colorflag == false) {
		//���邭
		colortimer++;
		if (colortimer == 1) {
			colorcount+=1.0f;
			colortimer = 0;
			if (colorcount < 30.0f) {
				m_skinModelRender->SetEmissionColor({ 0.0f , colorcount, colorcount });
			}
			else {
				colorflag = true;
			}
		}
	}
	else {
		m_stete = Estete_Attack;
	}
}
void Neoriku::NeoMove() {
	//�ړ���
	Player * player = Player::GetInstance();
	CVector3 P_Position = player->Getm_Position();
	CVector3 diff = P_Position - m_position;
	neoVec = diff;
	if (diff.Length() < followstop) {
		//��~����
		moveVec = neoVec * Speed;	
	}
	else {
		//�ǂ��������!
		neoVec.Normalize();
		moveVec = neoVec * followSpeed;

	}
	if (diff.Length() < followleave) {
		//�߂���yo�����yo!
		neoVec.Normalize();
		moveVec = neoVec * followSpeed * -1.0f;
	}
	//�����_���Ȏ��ԂōU�����郈
	if (count == 0) {
		random = rand() % 8;
		if (random >= 2) {
			count = 1;

		}
		random = random * time;//�����_������
	}
	timer++;
	if (timer > random) {
		bulletFlag = false;
		colorflag = false;
		m_stete = Estete_Yobi;
	}

	CVector3 enemyForward = { -1.0f, 0.0f, 0.0f };
	//�v���C���[�̌����ɉ�]
	diff.y = 0.0f;
	diff.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, diff);
	m_rotation = qRot;
	m_position = m_charaCon.Execute(moveVec);

}
void Neoriku::NeoDeath() {
	GameData * gamedata = GameData::GetInstance();
	gamedata->EnemyCounterGensyou();
	DeleteGO(this);
}


void Neoriku::Update() {
	switch (m_stete) {
		case Estete_Attack://�U��
			NeoAttack();
			break;
		case Estete_Yobi://�\������
			NeoYobi();
			break;
		case Estete_Move://�ړ�
			NeoMove();
			break;
		case Estete_Death:
			NeoDeath();//��
			break;
	}

	if (dathflag == true) {
		DeleteGO(this);
	}

	//�ړ�
	m_skinModelRender->SetPosition(m_position);
	//��]
	m_skinModelRender->SetRotation(m_rotation);
	//�g�嗦
	m_skinModelRender->SetScale(m_scale);

}



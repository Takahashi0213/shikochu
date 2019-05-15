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

	//m_animClips[enAnimationClip_attack1].SetLoopFlag(true);
	//�X�L�����f��
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/neoriku_0.cmo", m_animClips, enAnimationClip_Num);
	m_skinModelRender->SetForwardRenderFlag(true);
	//m_skinModelRender->SetEmissionColor({ 0.0f, 10.0f, 0.0f });
	m_position = { 100.0f,0.0f,0.0f };
	m_skinModelRender->SetPosition(m_position);

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
	if (count == 1) {
		NewGO<Bullet>(0, "bullet");
		count = 0;
	}
	else {
		m_stete = Estete_Move;
	}
}

void Neoriku::NeoMove() {
	//�ړ���
	Player * player = Player::GetInstance();
	CVector3 P_Position = player->Getm_Position();
	CVector3 diff = P_Position - m_position;
	neoVec = diff;
	//dbg::DrawVector(
	//	P_Position,
	//	m_position);
	if (diff.Length() < 400) {
		//��~���U������
		moveVec = neoVec * Speed;
		//m_stete = Estete_yobi;
	}
	else {
		//�ǂ��������!
		neoVec.Normalize();
		moveVec = neoVec * followSpeed;
	}
	//�v���C���[�̌����ɉ�]
	CVector3 enemyForward = { -1.0f, 0.0f, 0.0f };
	diff.y = 0.0f;
	diff.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, diff);
	m_rotation = qRot;
	m_position = m_charaCon.Execute(moveVec);

}
void Neoriku::NeoDeath() {
	//����......��...
	m_position = { 1000.0f,1000.0f,-1000.0f };
	//�ړ�
	m_skinModelRender->SetPosition(m_position);

}
void Neoriku::Neoyobi() {
	//�\������
	/*if ( count == 0) {
		m_stete = Estete_Attack;
		count++;
	}*/
}

void Neoriku::Update() {
	switch (m_stete) {
		case Estete_Attack://�U��
			NeoAttack();
			break;
		case Estete_Move://�ړ�
			NeoMove();
			break;
		case Estete_Death:
			NeoDeath();//��
			break;
		case Estete_yobi:
			Neoyobi();//�\������
			break;
	}
	//�ړ�
	m_skinModelRender->SetPosition(m_position);
	//��]
	m_skinModelRender->SetRotation(m_rotation);
	//�g�嗦
	m_skinModelRender->SetScale(m_scale);

}



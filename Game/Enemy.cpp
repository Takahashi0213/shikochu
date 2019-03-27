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
	//�A�j���[�V�����N���b�v�����[�h�ƃ��[�v�t���O�B
	m_animClips[enAnimationClip_walk].Load(L"animData/walk.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	//�\��
	m_animClips[enAnimationClip_attack1].Load(L"animData/attack_1.tka");
	//�U��
	m_animClips[enAnimationClip_attack01].Load(L"animData/attack_01.tka");

	//m_animClips[enAnimationClip_attack1].SetLoopFlag(true);
	//�X�L�����f��
	m_skinModelRender=NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/bunbo-gu0.cmo", m_animClips, enAnimationClip_Num);
	//m_skinModelRender->PlayAnimation(enAnimationClip_walk);
	m_position = { 100.0f,0.0f,0.0f };
	m_skinModelRender->SetPosition(m_position);

	m_scale = { 2.0f,2.0f,2.0f };
	m_charaCon.Init(
		30.0f,  //�L�����N�^�[�̔��a�B
		30.0f,  //�L�����N�^�[�̍����B
		m_position //�L�����N�^�[�̏������W�B
	);

	
	return true;
}
void Enemy::EnemyAttack()
{
	m_skinModelRender->PlayAnimation(enAnimationClip_attack1);
	timer++;
	CVector3 diff = player->position - m_position;
	 if(timer<=400){
		m_skinModelRender->PlayAnimation(enAnimationClip_attack01);
		attackk = 1;
	}
	else if (attackk <= 1) {
		m_stete = Estete_Move;
	}
}

void Enemy::EnemyMove()
{
	//�ʏ���
	CVector3 diff = player->position - m_position;
	CVector3 df = m_position - m_oldposition;

	moveVec.x = 50.0f * move;
	moveVec.y = 0.0f;
	moveVec.z = 0.0f;
	m_position.x += moveVec.x;
	if (m_position.x - m_oldposition.x > 200.0f) {
		move = -1;
	}
	else if (m_position.x - m_oldposition.x < -200.0f) {
		move = 1;
	}
	else if (diff.Length() < 600.0f) {
		m_stete = Estete_Follow;
	}
	m_position = m_charaCon.Execute(moveVec);
}
void Enemy::EnemyFollow()
{
	//�ǔ����	
	CVector3 diff = player->position - m_position;
	CVector3 df = m_position - m_oldposition;


	enemyVec = diff;
	if (diff.Length() < 600.0f) {
		//�߂Â�
		enemyVec.Normalize();
		enemyVec *= 150;
	}
	else if (diff.Length() > 400.0f) {
		//���̏�ňړ�
		m_stete = Estete_Move;
	}
	if (diff.Length() < 90.0f) {
		//�U��
		m_stete = Estete_Attack;
	}

}
void Enemy::EnemyDeath()
{
	DeleteGO(this);
}
void Enemy::Update()
	{
		switch (m_stete) {
		case Estete_Attack://�U��
			EnemyAttack();
			break;
		case Estete_Move://�ړ�
			EnemyMove();
			break;
		case Estete_Follow://�ǔ�
			EnemyFollow();
			break;
		case Estete_Death:
			EnemyDeath();//��
			break;
		}

	//�ړ�
	m_skinModelRender->SetPosition(m_position);

	//��]
	m_skinModelRender->SetRotation(m_rotation);
	//�g�嗦
	m_skinModelRender->SetScale(m_scale);

}
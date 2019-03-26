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
	m_animClips[enAnimationClip_attack1].Load(L"animData/attack1.tka");
	//m_animClips[enAnimationClip_attack1].SetLoopFlag(true);
	//�X�L�����f��
	m_skinModelRender=NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/bunbo-gu0.cmo", m_animClips, enAnimationClip_Num);
	//m_skinModelRender->PlayAnimation(enAnimationClip_walk);
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
	/*int com = rand() % 3;
	if (com == 0) {
		m_attack = Eattack_1;
	}
	else if (com == 1) {
		m_attack = Eattack_2;
	}
	else if (com == 2) {
		m_attack = Eattack_3;
	}*/
}

void Enemy::EnemyMove()
{
	timer++;
	if (timer >= 300) {
		m_skinModelRender->PlayAnimation(enAnimationClip_attack1);
		if (timer >= 600) {
			timer = 0;
		}
	}
	else if(timer <= 300) {
		m_skinModelRender->PlayAnimation(enAnimationClip_walk);

	}
}
void Enemy::EnemyDeath()
{

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
		case Estete_Death:
			EnemyDeath();//��
			break;
		}

		switch (m_attack) {
		case Eattack_0:
			break;
		case Eattack_1:
			break;
		case Eattack_2:
			break;
		case Eattack_3:
			break;
		}

	//�ړ�
	m_skinModelRender->SetPosition(m_position);

	//��]
	m_skinModelRender->SetRotation(m_rotation);
	//�g�嗦
	m_skinModelRender->SetScale(m_scale);

}
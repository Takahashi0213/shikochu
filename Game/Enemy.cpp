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
		45.0f,  //�L�����N�^�[�̔��a�B
		10.0f,  //�L�����N�^�[�̍����B
		m_position //�L�����N�^�[�̏������W�B
	);

	
	return true;
}
void Enemy::EnemyAttack()
{
	Player * player = FindGO<Player>("Bug");

	timer++;
	if(timer <= attackwait){
		//�U���A�j���[�V����
		m_skinModelRender->PlayAnimation(enAnimationClip_attack01);
		CVector3 diff = player->position - m_position;
		diff.Normalize();
		diff *= 50;
		m_position = m_charaCon.Execute(diff);
	}
	else{
		//�ʏ��Ԃɖ߂�
		timer = 0;
		m_stete = Estete_Move;
	}

}

void Enemy::EnemyMove()
{
	Player * player = FindGO<Player>("Bug");

	//�ʏ���
	CVector3 diff = player->position - m_position;
	CVector3 df = m_position - m_oldposition;

	moveVec.x = 50.0f * move;
	moveVec.y = 0.0f;
	moveVec.z = 0.0f;
	m_position.x += moveVec.x;
	if (m_stete == Estete_Move) {
		//stete��move�̂Ƃ��͕����A�j���[�V����
		m_skinModelRender->PlayAnimation(enAnimationClip_walk);

	}
	//���E�̈ړ�
	if (df.x > rightmove) {
		//�E�ړ�
		move = -1;
	}
	else if (df.x < leftmove) {
		//���ړ�
		move = 1;
	}
	else if (diff.Length() < distancemove) {
		//�������߂��̂Œǔ�����B
		m_stete = Estete_Follow;
	}
	m_position = m_charaCon.Execute(moveVec);
}
void Enemy::EnemyFollow()
{
	Player * player = FindGO<Player>("Bug");

	//�ǔ����	
	CVector3 diff = player->position - m_position;	
	enemyVec = diff;

	if (diff.Length() < 600.0f) {
		//�߂Â�
		enemyVec.Normalize();
		enemyVec *= 80;
	}
	else if (diff.Length() > 600.0f) {
		//���̏�ňړ�
		m_stete = Estete_Move;
	}
	 if (diff.Length() < 80.0f) {
		//�\������
		m_stete = Estete_yobi;
	}
	 //��]�̏���
	 if (fabsf(enemyVec.x) < 0.001f
		 && fabsf(enemyVec.z) < 0.001f) {
		 //�킩���
		 return;
	 }
	 float angle = atan2(enemyVec.x, enemyVec.z);
	 m_rotation.SetRotation(CVector3::AxisY, -angle);
	 
	 m_position = m_charaCon.Execute(enemyVec);

}
void Enemy::EnemyDeath()
{
	//��
}
void Enemy::Enemyyobi() {
	//�\������
	timer++;
	if (timer <= yobiwait) {
		m_skinModelRender->PlayAnimation(enAnimationClip_attack1);
	}
	else {
		m_stete = Estete_Attack;
	}
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
		case Estete_yobi:
			Enemyyobi();//�\������
			break;
		}

	//�ړ�
	m_skinModelRender->SetPosition(m_position);

	//��]
	m_skinModelRender->SetRotation(m_rotation);
	//�g�嗦
	m_skinModelRender->SetScale(m_scale);

}
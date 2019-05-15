#include "stdafx.h"
#include "Bunbogu.h"
#include "GameData.h"
#include "Player.h"

Bunbogu::Bunbogu()
{
}


Bunbogu::~Bunbogu()
{
	DeleteGO(m_skinModelRender);
}

bool Bunbogu::Start()
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
	
	m_skinModelRender->SetPosition(m_position);

	m_scale = { 2.0f,2.0f,2.0f };
	m_charaCon.Init(
		45.0f,  //�L�����N�^�[�̔��a�B
		10.0f,  //�L�����N�^�[�̍����B
		m_position //�L�����N�^�[�̏������W�B
	);
	
	return true;
}
void Bunbogu::EnemyAttack()
{
	Player * player = Player::GetInstance();

	timer++;
	if(timer <= attackwait){
		//�U���A�j���[�V����
		m_skinModelRender->PlayAnimation(enAnimationClip_attack01);

		CVector3 P_Position = player->Getm_Position();
		CVector3 diff = P_Position - m_position;

		diff.Normalize();
		diff *= attackMoveRange;
		m_position = m_charaCon.Execute(diff);
	}
	else{
		//�ʏ��Ԃɖ߂�
		timer = 0;
		m_stete = Estete_Move;
	}

}

void Bunbogu::EnemyMove()
{
	Player * player = Player::GetInstance();
	//�ʏ���
	CVector3 P_Position = player->Getm_Position();
	CVector3 diff = P_Position - m_position;

	count++;
	
	if(count == randomCount){
		random = rand() % 360;//�����_���ŕ���������
		m_rotation.SetRotation(CVector3::AxisY, (float)random);
		CVector3 musi_mae = { 1.0f, 0.0f,0.0f };
		m_rotation.Multiply(musi_mae);
		moveVec = musi_mae * randomSpeed;
		count = 0;
	}

	else if (diff.Length() < followRange) {
		//�������߂��̂Œǔ�����B
		m_stete = Estete_Follow;
	}
	if (m_stete == Estete_Move) {
		//stete��move�̂Ƃ��͕����A�j���[�V����
		m_skinModelRender->PlayAnimation(enAnimationClip_walk);

	}
	 m_position = m_charaCon.Execute(moveVec);

}
void Bunbogu::EnemyFollow()
{
	Player * player = Player::GetInstance();

	//�ǔ����	
	CVector3 P_Position = player->Getm_Position();
	CVector3 diff = P_Position - m_position;
	enemyVec = diff;

	if (diff.Length() < followRange) {
		//�߂Â�
		enemyVec.Normalize();
		enemyVec *= followSpeed;
	}
	else{
		//���̏�ňړ�
		m_stete = Estete_Move;
	}

	 if (diff.Length() < attackRange) {
		//�\������
		m_stete = Estete_yobi;
	}
	 //��]�̏���
	 if (fabsf(enemyVec.x) < 0.001f
		 && fabsf(enemyVec.z) < 0.001f) {
		 //�킩���
		 return;
	 }

	 if (m_stete == Estete_Follow) {
		 //stete��follow�̂Ƃ��͕����A�j���[�V����
		 m_skinModelRender->PlayAnimation(enAnimationClip_walk);

	 }

	 CVector3 enemyForward = { 1.0f, 0.0f, 0.0f };

	 //�@���������������̃x�N�g�����v�Z����B
	 CVector3 targetVector = P_Position - m_position;
	 //�@Y�����͏������Đ��K������BY����������Ƌ���������肷���B
	 targetVector.y = 0.0f;
	 targetVector.Normalize();
	 CQuaternion qRot;
	 qRot.SetRotation(enemyForward, targetVector);
	 m_rotation = qRot;
	 m_position = m_charaCon.Execute(enemyVec);

}
void Bunbogu::EnemyDeath()
{
	DeleteGO(this);
}
void Bunbogu::Enemyyobi() {
	//�\������
	timer++;
	if (timer <= yobiwait) {
		m_skinModelRender->PlayAnimation(enAnimationClip_attack1);
	}
	else {
		m_stete = Estete_Attack;
	}
}
void Bunbogu::Update()
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
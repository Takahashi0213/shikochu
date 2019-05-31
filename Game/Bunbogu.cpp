#include "stdafx.h"
#include "Bunbogu.h"
#include "GameData.h"
#include "Player.h"
#include "EffectManager.h"

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

	timer++;
	if(timer <= attackwait){
		//�U���A�j���[�V����
		m_skinModelRender->PlayAnimation(enAnimationClip_attack01);
			m_position = m_charaCon.Execute(attackVec);

	}
	else{
		//�ʏ��Ԃɖ߂�
		timer = 0;
		keisannflag = false;
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
	prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
	ss->Init(L"sound/E_death.wav");
	ss->SetVolume(1.0f);
	ss->Play(false);

	EffectManager * effectmanager = EffectManager::GetInstance();
	CVector3 EF_Position = m_position;
	EF_Position.y += 50.0f;
	effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });

	GameData * gamedata = GameData::GetInstance();
	gamedata->EnemyCounterGensyou();
	DeleteGO(this);
}
void Bunbogu::Enemyyobi() {
	//�\������
	if (keisannflag == false) {
		Player * player = Player::GetInstance();
		CVector3 P_Position = player->Getm_Position();
		CVector3 diff = P_Position - m_position;
		attackVec = diff;
		attackVec.Normalize();
		attackVec *= attackMoveRange;
		keisannflag = true;
	}
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

	if (SpawnWaitTimer > SpawnMaxWait) {
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
		case Estete_Death2:
			EnemyDeath2();//��
			break;
		case Estete_yobi:
			Enemyyobi();//�\������
			break;
		}

	}

	SpawnWaitTimer++;

	//�ړ�
	m_skinModelRender->SetPosition(m_position);
	//��]
	m_skinModelRender->SetRotation(m_rotation);
	//�g�嗦
	m_skinModelRender->SetScale(m_scale);

}

void Bunbogu::EnemyDeath2() {
	DeleteGO(this);
}
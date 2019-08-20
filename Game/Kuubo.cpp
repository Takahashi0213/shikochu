#include "stdafx.h"
#include "Kuubo.h"
#include "GameData.h"
#include "Player.h"
#include "EffectManager.h"
#include "StarComet_Inseki.h"

Kuubo::Kuubo()
{
}


Kuubo::~Kuubo()
{
	DeleteGO(m_skinModelRender);
}

bool Kuubo::Start()
{
	//�A�j���[�V�����N���b�v�����[�h�ƃ��[�v�t���O�B
	m_animClips[enAnimationClip_walk].Load(L"animData/KuuboWalk.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	//�U��
	m_animClips[enAnimationClip_attack1].Load(L"animData/KuuboAttack.tka");

	//�X�L�����f��
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Kuubo.cmo", m_animClips, enAnimationClip_Num);

	m_skinModelRender->SetPosition(m_position);

	m_scale = { 1.5f,1.5f,1.5f };
	m_charaCon.Init(
		45.0f,  //�L�����N�^�[�̔��a�B
		10.0f,  //�L�����N�^�[�̍����B
		m_position //�L�����N�^�[�̏������W�B
	);

	return true;
}
void Kuubo::EnemyAttack()
{

	timer++;
	if (timer <= attackwait) {
		//�U���A�j���[�V����
		m_position = m_charaCon.Execute(attackVec);

	}
	else {
		//�ʏ��Ԃɖ߂�
		timer = 0;
		keisannflag = false;
		m_stete = Estete_Move;
		m_skinModelRender->PlayAnimation(enAnimationClip_walk, 0.5f);
	}

}

void Kuubo::EnemyMove()
{
	Player * player = Player::GetInstance();
	//�ʏ���
	CVector3 P_Position = player->Getm_Position();
	CVector3 diff = P_Position - m_position;

	count++;

	if (count == randomCount) {
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
		m_skinModelRender->PlayAnimation(enAnimationClip_walk, 0.5f);

	}
	m_position = m_charaCon.Execute(moveVec);

}
void Kuubo::EnemyFollow()
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
	else {
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

	CVector3 enemyForward = { 0.0f, 0.0f, -1.0f };

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
void Kuubo::EnemyDeath()
{
	prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
	ss->Init(L"sound/E_death.wav");
	ss->SetVolume(1.0f);
	ss->Play(false);

	EffectManager * effectmanager = EffectManager::GetInstance();
	CVector3 EF_Position = m_position;
	EF_Position.y += 50.0f;
	effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f }, false, false);

	GameData * gamedata = GameData::GetInstance();
	gamedata->EnemyCounterGensyou();
	gamedata->PlusGekihaEnemy();
	DeleteGO(this);
}
void Kuubo::Enemyyobi() {

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

	if (timer == 0) {
		m_skinModelRender->PlayAnimation(enAnimationClip_attack1, 0.5f);
	}
	else if (timer >= yobiwait) {
		timer = 0;
		m_stete = Estete_Attack;
	}

	timer++;

}
void Kuubo::Update()
{

	if (SpawnWaitTimer > SpawnMaxWait) {

		GameData * gamedata = GameData::GetInstance();
		int mode = gamedata->GetGameMode();
		if (mode != GameData::Pause && mode != GameData::Tutorial) {

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

	}
	SpawnWaitTimer++;

	//�ǂ���覐΂ł�
	QueryGOs<StarComet_Inseki>("StarComet_Inseki", [&](StarComet_Inseki* SCI) {
		CVector3 inseki_position = SCI->Getm_Position();
		CVector3 diff = inseki_position - m_position;
		float Langth_hoge = SCI->GetDamageLength();
		if (diff.Length() < Langth_hoge) { //覐ΏՓ�
			SetDeath();//����������
			SCI->SetDeath();//覐΂�����
		}
		return true;
		});

	//�ړ�
	m_skinModelRender->SetPosition(m_position);
	//��]
	m_skinModelRender->SetRotation(m_rotation);
	//�g�嗦
	m_skinModelRender->SetScale(m_scale);

}

void Kuubo::EnemyDeath2() {
	DeleteGO(this);
}
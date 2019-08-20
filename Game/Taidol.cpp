#include "stdafx.h"
#include "Taidol.h"
#include "GameData.h"
#include "Player.h"
#include "EffectManager.h"
#include "StarComet_Inseki.h"

Taidol::Taidol()
{
}


Taidol::~Taidol()
{
	DeleteGO(m_skinModelRender);
}

bool Taidol::Start()
{
	//�A�j���[�V�����N���b�v�����[�h�ƃ��[�v�t���O�B
	m_animClips[enAnimationClip_walk].Load(L"animData/Taidol.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	//�\��
	m_animClips[enAnimationClip_attack].Load(L"animData/Taidol_Stay.tka");

	//�X�L�����f��
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Taidol.cmo", m_animClips, enAnimationClip_Num);

	m_skinModelRender->SetPosition(m_position);

	m_scale = { 1.0f,1.0f,1.0f };
	m_charaCon.Init(
		45.0f,  //�L�����N�^�[�̔��a�B
		10.0f,  //�L�����N�^�[�̍����B
		m_position //�L�����N�^�[�̏������W�B
	);

	return true;
}
void Taidol::EnemyAttack()
{
	//�h�b�J�[���I�I�I�I
	if (timer == 0) {//�A�^�b�N�����W
		DamageLength *= 2.0f;
		Color += 50.0f;
		EffectManager * effectmanager = EffectManager::GetInstance();
		CVector3 EF_Position = m_position;
		EF_Position.y += 80.0f;
		effectmanager->EffectPlayer(EffectManager::Bakuhatu, EF_Position, { 40.0f,40.0f,40.0f });
	}

	if (timer < attackwait/2) {
		Color += 30.0f;
	}
	else {
		Color -= 100.0f;
		if (Color < 0.0f) {
			Color = 0.0f;
		}
	}

	timer++;

	if (timer == attackwait) {//�I���ԉ�
		timer = 0;
		m_stete = Estete_AttackEnd;
		DamageLength = DamageLengthDEF;
		Color = 0.0f;

	}
	m_skinModelRender->SetEmissionColor({ Color ,0.0f , 0.0f });

}

void Taidol::EnemyMove()
{
	Player * player = Player::GetInstance();
	//�ʏ���
	CVector3 P_Position = player->Getm_Position();
	CVector3 diff = P_Position - m_position;

	count++;

	if (count == randomCount) {
		random = rand() % 360;//�����_���ŕ���������
		m_rotation.SetRotation(CVector3::AxisY, (float)random);
		CVector3 musi_mae = { 0.0f, 0.0f,1.0f };
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
void Taidol::EnemyFollow()
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

	CVector3 enemyForward = { 0.0f, 0.0f, 1.0f };

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
void Taidol::EnemyDeath()
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

void Taidol::Enemyyobi() {

	if (timer == 0) {//�����̂���߂�
		m_skinModelRender->PlayAnimation(enAnimationClip_attack);
	}

	if (timer > 30) {
		Color += 1.0f;
		m_skinModelRender->SetEmissionColor({ Color ,0.0f , 0.0f });
	}

	timer++;
	if (timer == yobiwait) {
		timer = 0;
		m_stete = Estete_Attack;
	}
}

void Taidol::EnemyAttackEnd() {

	CQuaternion RotationY;
	RotationY.SetRotationDeg(CVector3::AxisY, 10.0f);
	m_rotation *= RotationY;
	m_skinModelRender->SetRotation(m_rotation);

	timer++;
	if (timer == Endwait) {
		timer = 0;
		m_stete = Estete_Move;
	}

}

void Taidol::Update()
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
			case Estete_AttackEnd://�U���I��
				EnemyAttackEnd();
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

void Taidol::EnemyDeath2() {
	DeleteGO(this);
}
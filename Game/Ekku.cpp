#include "stdafx.h"
#include "Ekku.h"
#include "GameData.h"
#include "Player.h"
#include "EffectManager.h"



Ekku::Ekku()
{
}


Ekku::~Ekku()
{
	DeleteGO(m_skinModelRender);
}
bool Ekku::Start() {

	m_animClips[enAnimationClip_walk].Load(L"animData/Ekwalk.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	//�\��
	m_animClips[enAnimationClip_attack].Load(L"animData/Ekattack.tka");
	//�U��
	m_animClips[enAnimationClip_yobi].Load(L"animData/Ekyobi.tka");

	//�X�L�����f��

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Ekku.cmo", m_animClips, enAnimationClip_Num);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);

	m_charaCon.Init(
		45.0f,  //�L�����N�^�[�̔��a�B
		10.0f,  //�L�����N�^�[�̍����B
		m_position //�L�����N�^�[�̏������W�B
	);

	return true;
}

void Ekku::EkAttack() {
	timer++;
	if (timer <= attackwait) {
		//�U���A�j���[�V����
		m_skinModelRender->PlayAnimation(enAnimationClip_attack);
		m_position = m_charaCon.Execute(attackVec);

	}
	else {
		//�ʏ��Ԃɖ߂�
		timer = 0;
		keisannflag = false;
		m_stete = Estete_Move;
	}
}
void Ekku::EkMove(){
	Player * player = Player::GetInstance();
	//�ʏ���
	CVector3 P_Position = player->Getm_Position();
	CVector3 diff = P_Position - m_position;

	count++;

	if (count == randomCount) {
		random = rand() % 360;//�����_���ŕ���������
		m_rotation.SetRotation(CVector3::AxisY, (float)random);
		CVector3 ekku_mae = { -1.0f, 0.0f,0.0f };
		m_rotation.Multiply(ekku_mae);
		moveVec = ekku_mae * randomSpeed;
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
void Ekku::EkFollow(){
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
		m_stete = Estete_Yobi;
	}

	if (m_stete == Estete_Follow) {
		//stete��follow�̂Ƃ��������A�j���[�V����
		m_skinModelRender->PlayAnimation(enAnimationClip_walk);

	}

	CVector3 enemyForward = { -1.0f, 0.0f, 0.0f };

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
void Ekku::EkDeath(){
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
void Ekku::Ekyobi() {
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
		m_skinModelRender->PlayAnimation(enAnimationClip_yobi);
	}
	else {
		m_stete = Estete_Attack;

	}

}
void Ekku::Update() {

	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();
	if (mode != GameData::Pause) {

		switch (m_stete) {
		case Estete_Attack://�U��
			EkAttack();
			break;
		case Estete_Move://�ړ�
			EkMove();
			break;
		case Estete_Follow://�ǔ�
			EkFollow();
			break;
		case Estete_Death:
			EkDeath();//��
			break;
		case Estete_Death2:
			EkDeath2();//��
			break;
		case Estete_Yobi:
			Ekyobi();//�\������
			break;
		}
	}
	//�ړ�
	m_skinModelRender->SetPosition(m_position);
	//��]
	m_skinModelRender->SetRotation(m_rotation);
	//�g�嗦
	m_skinModelRender->SetScale(m_scale);
	

}

void Ekku::EkDeath2() {
	DeleteGO(this);
}
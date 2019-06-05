#include "stdafx.h"
#include "Pi_rabi.h"
#include "GameData.h"
#include "Player.h"
#include "EffectManager.h"


Pi_rabi::Pi_rabi()
{
}


Pi_rabi::~Pi_rabi()
{
	DeleteGO(m_skinModelRender);
}

bool Pi_rabi::Start() {
	//�A�j���[�V����
	m_animClips[enAnimationClip_walk].Load(L"animData/P_idel.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	m_animClips[enAnimationClip_attack].Load(L"animData/P_attack.tka");

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Rabbit_Level_1.cmo", m_animClips, enAnimationClip_Num);
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

void Pi_rabi::PiMove() {
	timer++;
	if (timer == randomCount) {
		random = rand() % 360;//�����_���ŕ���������
		m_rotation.SetRotation(CVector3::AxisY, (float)random);
		CVector3 sou_mae = { 0.0f, 0.0f,1.0f };
		m_rotation.Multiply(sou_mae);
		moveVec = sou_mae * randomSpeed;
		movecount++;
		timer = 0;
	}
	else if (movecount >3) {
		//�U��������
		Player * player = Player::GetInstance();
		CVector3 P_Position = player->Getm_Position();
		diff = P_Position - m_position;
		attackVec = diff;
		attackVec.Normalize();

		m_stete = Estete_Follow;
	}
	if (m_stete == Estete_Move) {
		//stete��move�̂Ƃ��͕����A�j���[�V����
		m_skinModelRender->PlayAnimation(enAnimationClip_walk);

	}

	m_position = m_charaCon.Execute(moveVec);

}
void Pi_rabi::Piattack() {
	attacktimer++;
	if (attacktimer <= attacktime) {
		//�U���A�j���[�V����
		m_skinModelRender->PlayAnimation(enAnimationClip_attack);
		m_position = m_charaCon.Execute(attackVec);

	}
	else if (attacktimer >= attacktime) {
		//��������
		moveVec = diff;
		moveVec.Normalize();
		moveVec *= fleeSpeed;
		m_skinModelRender->PlayAnimation(enAnimationClip_walk);
	}
	if (attacktimer >= attackend) {
		//�ړ���Ԃɖ߂�
		movecount = 0;
		attackmoveflag = false;
		m_stete = Estete_Move;
	}
	m_position = m_charaCon.Execute(moveVec);

}

void Pi_rabi::PiFollow() {

	Player * player = Player::GetInstance();

	//�ǔ����	
	CVector3 P_Position = player->Getm_Position();
	moveVec = diff;
	moveVec.Normalize();
	moveVec *= followSpeed;

	if (diff.Length() < followRange) {
		//�߂��Ȃ�����U�������
		if (attackmoveflag == false) {
			attackVec = diff;
			attackVec.Normalize();
			attackVec *= attackMoveRange;
			attackmoveflag = true;
		}
		attacktimer = 0;
		m_stete = Estete_Attack;
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
	m_position = m_charaCon.Execute(moveVec);

}

void Pi_rabi::PiDeath() {
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


void Pi_rabi::Update() {

	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();
	if (mode != GameData::Pause) {

		switch (m_stete)
		{
		case Estete_Attack:
			Piattack();
			break;
		case Estete_Move:
			PiMove();
			break;
		case Estete_Follow:
			PiFollow();
			break;
		case Estete_Death:
			PiDeath();
			break;
		case Estete_Death2:
			PiDeath2();
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

void Pi_rabi::PiDeath2() {
	DeleteGO(this);
}
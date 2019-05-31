#include "stdafx.h"
#include "Morikon.h"
#include "GameData.h"
#include "Player.h"
#include "EffectManager.h"

Morikon::Morikon()
{
}


Morikon::~Morikon()
{
	DeleteGO(m_skinModelRender);
}

bool Morikon::Start() {
	//�A�j���[�V����
	m_animClips[enAnimationClip_walk].Load(L"animData/Mori_idel.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	m_animClips[enAnimationClip_attack].Load(L"animData/Mori_attack.tka");


	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Bat_Level_1.cmo", m_animClips, enAnimationClip_Num);
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
void Morikon::Momove() {

	if (m_stete == Estete_Move) {
		//stete��move�̂Ƃ��͕����A�j���[�V����
		m_skinModelRender->PlayAnimation(enAnimationClip_walk);

	}

	Player * player = Player::GetInstance();
	CVector3 P_Position = player->Getm_Position();
	CVector3 diff = P_Position - m_position;
	MoriVec = diff;
	if (diff.Length() < followstop) {
		//��~����
		moveVec = MoriVec * Speed;
	}
	else {
		//�ǂ��������!
		MoriVec.Normalize();
		moveVec = MoriVec * followSpeed;

	}
	if (diff.Length() < followleave) {
		//�߂���yo�����yo!
		MoriVec.Normalize();
		moveVec = MoriVec * followSpeed * -1.0f;
	}
	//�����_���Ȏ��ԂōU�����郈
	if (count == 0) {
		random = rand() % 6;
		if (random >= 2) {
			count = 1;

		}
		random = random * time;//�����_������
	}
	timer++;
	if (timer > random) {
		m_stete = Estete_Follow;
	}

	CVector3 enemyForward = { 0.0f, 0.0f, 1.0f };
	//�v���C���[�̌����ɉ�]
	diff.y = 0.0f;
	diff.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, diff);
	m_rotation = qRot;
	m_position = m_charaCon.Execute(moveVec);
}
void Morikon::Mofollow()
{		
	Player * player = Player::GetInstance();

	//�ǔ����	
	CVector3 P_Position = player->Getm_Position();
	CVector3 diff = P_Position - m_position;
	moveVec = diff;
	moveVec.Normalize();
	moveVec *= followSpeed;
	if (diff.Length() < attackRange) {
		//�U�������
		if (attackmoveflag == false) {
			attackVec = diff;
			attackVec.Normalize();
			attackVec *= attackMoveRange;
			attackmoveflag = true;
		}
		attacktimer = 0;
		m_stete = Estete_Attack;
	}
	m_position = m_charaCon.Execute(moveVec);

}
void Morikon::Moattack()
{
	attacktimer++;
	if (attacktimer <= attacktime) {
		//�U���A�j���[�V����
		m_skinModelRender->PlayAnimation(enAnimationClip_attack);
		m_position = m_charaCon.Execute(attackVec);

	}
	else {
		//�ʏ��Ԃɖ߂�
		attackmoveflag = false;
		timer = 0;
		count = 0;
		m_stete = Estete_Move;
	}

}

void Morikon::Modeath() {
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
void Morikon::Update() {
	switch (m_stete) {
	case Estete_Move://�ړ�
		Momove();
		break;
	case Estete_Follow://�ǔ�
		Mofollow();
		break;
	case Estete_Attack://�U��
		Moattack();
		break;
	case Estete_Death:
		Modeath();//��
		break;
	}

	//�ړ�
	m_skinModelRender->SetPosition(m_position);
	//��]
	m_skinModelRender->SetRotation(m_rotation);
	//�g�嗦
	m_skinModelRender->SetScale(m_scale);

}

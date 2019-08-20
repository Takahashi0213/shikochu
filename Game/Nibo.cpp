#include "stdafx.h"
#include "Nibo.h"
#include "GameData.h"
#include "EffectManager.h"
#include "Player.h"
#include "StarComet_Inseki.h"

Nibo::Nibo()
{
}


Nibo::~Nibo()
{
	DeleteGO(m_skinModelRender);
}

bool Nibo::Start() {
	//�A�j���[�V�����N���b�v�����[�h�ƃ��[�v�t���O�B
	m_animClips[enAnimationClip_walk].Load(L"animData/NiboWalk.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	//�U��
	m_animClips[enAnimationClip_attack1].Load(L"animData/NiboAttack.tka");

	//�X�L�����f��
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Nibo.cmo", m_animClips, enAnimationClip_Num);

	m_skinModelRender->SetPosition(m_position);

	m_scale = { 2.0f,2.0f,2.0f };
	m_charaCon.Init(
		45.0f,  //�L�����N�^�[�̔��a�B
		10.0f,  //�L�����N�^�[�̍����B
		m_position //�L�����N�^�[�̏������W�B
	);

	return true;
}

void Nibo::Update() {
	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();
	if (mode != GameData::Pause) {

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
		case Estete_Death2:
			EnemyDeath2();//��
			break;
		case Estete_yobi:
			Enemyyobi();//�\������
			break;
		}

	}

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

void Nibo::EnemyAttack() {
	timer++;
	if (timer <= attackwait) {
		//�U��
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

void Nibo::EnemyMove() {
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
	else if (movecount >4) {
		m_stete = Estete_yobi;
		movecount = 0;
		timer = 0;
	}
	m_position = m_charaCon.Execute(moveVec);
}

void Nibo::EnemyDeath() {
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

void Nibo::EnemyDeath2() {
	DeleteGO(this);

}

void Nibo::Enemyyobi() {
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
	if (timer == 1) {
		m_skinModelRender->PlayAnimation(enAnimationClip_attack1, 0.5f);
	}
	else if (timer == yobiwait) {
		m_stete = Estete_Attack;
		timer = 0;
	}

}

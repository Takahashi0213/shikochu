#include "stdafx.h"
#include "Kirabi.h"
#include "GameData.h"
#include "EffectManager.h"
#include "Player.h"
#include "StarComet_Inseki.h"

Kirabi::Kirabi()
{
}


Kirabi::~Kirabi()
{
	DeleteGO(m_skinModelRender);
}

bool Kirabi::Start() {
	//�A�j���[�V�����N���b�v�����[�h�ƃ��[�v�t���O�B
	m_animClips[enAnimationClip_walk].Load(L"animData/Kira_Move.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	//�U��
	m_animClips[enAnimationClip_attack1].Load(L"animData/Kira_Attack.tka");

	//�X�L�����f��
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Kirabin.cmo", m_animClips, enAnimationClip_Num);

	m_skinModelRender->SetPosition(m_position);

	m_scale = { 1.0f,1.0f,1.0f };
	m_charaCon.Init(
		30.0f,  //�L�����N�^�[�̔��a�B
		10.0f,  //�L�����N�^�[�̍����B
		m_position //�L�����N�^�[�̏������W�B
	);

	return true;
}

void Kirabi::Update() {
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
	//�ړ�
	m_skinModelRender->SetPosition(m_position);
	//��]
	m_skinModelRender->SetRotation(m_rotation);
	//�g�嗦
	m_skinModelRender->SetScale(m_scale);

}

void Kirabi::EnemyAttack() {
	timer++;
	if (timer <= attackwait) {

		//�U����
	}
	else {
		//�ʏ��Ԃɖ߂�
		timer = 0;
		m_stete = Estete_Move;
		m_skinModelRender->PlayAnimation(enAnimationClip_walk, 0.5f);
	}

}

void Kirabi::EnemyMove() {
	timer++;
	if (timer == randomCount) {
		if (movecount == 2) {
			Player* player = FindGO<Player>("Bug");
			CVector3 P_Position = player->Getm_Position();

			CVector3 diff = P_Position - m_position;
			buvec = diff;
			buvec.Normalize();
			moveVec = buvec * randomSpeed;
			movecount++;
			timer = 0;
		}
		else {
			random = rand() % 360;//�����_���ŕ���������
			m_rotation.SetRotation(CVector3::AxisY, (float)random);
			CVector3 sou_mae = { 0.0f, 0.0f,1.0f };
			m_rotation.Multiply(sou_mae);
			moveVec = sou_mae * randomSpeed;
			movecount++;
			timer = 0;
		}
	}
	else if (movecount >4) {
		m_stete = Estete_yobi;
		movecount = 0;
		timer = 0;
	}
	m_position = m_charaCon.Execute(moveVec);
}

void Kirabi::EnemyDeath() {
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

void Kirabi::EnemyDeath2() {
	DeleteGO(this);

}

void Kirabi::Enemyyobi() {
	//�\������
	timer++;
	if (timer == 0) {
		m_skinModelRender->PlayAnimation(enAnimationClip_attack1);
	}
	else if (timer >= yobiwait) {
		timer = 0;
		m_stete = Estete_Attack;
	}

}
#include "stdafx.h"
#include "Tizutyo.h"
#include "GameData.h"
#include "Player.h"
#include "Bullet5.h"
#include "EffectManager.h"
#include "StarComet_Inseki.h"

Tizutyo::Tizutyo()
{
}


Tizutyo::~Tizutyo()
{
	DeleteGO(m_skinModelRender);
}

bool Tizutyo::Start() {
	//�A�j���[�V�����N���b�v�����[�h�ƃ��[�v�t���O�B
	m_animClips[enAnimationClip_walk].Load(L"animData/Tizutyo.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);

	//�X�L�����f��
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Tizutyo.cmo", m_animClips, enAnimationClip_Num);
	m_skinModelRender->SetForwardRenderFlag(true);

	m_scale = { 2.0f,2.0f,2.0f };
	m_charaCon.Init(
		45.0f,  //�L�����N�^�[�̔��a�B
		10.0f,  //�L�����N�^�[�̍����B
		m_position //�L�����N�^�[�̏������W�B
	);

	return true;
}

void Tizutyo::NeoAttack() {

	//��������ł�
	movetimer++;
	if (bulletFlag == false) {
		Bullet5* bullet5 = NewGO<Bullet5>(0, "bullet5");
		bullet5->Init(this);
		bulletFlag = true;
	}
	else {
		CVector3 enemyForward = { 0.0f, 0.0f, 1.0f };
		//�v���C���[�̌����ɉ�]
		Player * player = Player::GetInstance();
		CVector3 P_Position = player->Getm_Position();
		CVector3 diff = P_Position - m_position;
		neoVec = diff;
		diff.y = 0.0f;
		diff.Normalize();
		CQuaternion qRot;
		qRot.SetRotation(enemyForward, diff);
		m_rotation = qRot;
	}

	if (movetimer == 30) {
		Bullet5* bullet5 = NewGO<Bullet5>(0, "bullet5");
		bullet5->Init(this);
	}

	if (movetimer == 60) {
		Bullet5* bullet5 = NewGO<Bullet5>(0, "bullet5");
		bullet5->Init(this);
	}

	if (movetimer > 60 && movetimer < move_starttimer) {
		colorcount -= 1.0f;
		if (colorcount < 0.0f) {
			colorcount = 0.0f;
		}
		m_skinModelRender->SetEmissionColor({ 0.0f , colorcount, colorcount });
	}
	else if (movetimer >= move_starttimer) {
		count = 0;
		timer = 0;
		movetimer = 0;
		m_stete = Estete_Move;
	}

}
void Tizutyo::NeoYobi() {

	CVector3 enemyForward = { 0.0f, 0.0f, 1.0f };
	//�v���C���[�̌����ɉ�]
	Player * player = Player::GetInstance();
	CVector3 P_Position = player->Getm_Position();
	CVector3 diff = P_Position - m_position;
	neoVec = diff;
	diff.y = 0.0f;
	diff.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, diff);
	m_rotation = qRot;

	//�\������ŐF���ω������������
	if (colorflag == false) {
		//���邭
		colortimer++;
		if (colortimer == 1) {
			colorcount += 0.5f;
			colortimer = 0;
			if (colorcount < 30.0f) {
				m_skinModelRender->SetEmissionColor({ 0.0f , colorcount, colorcount });
			}
			else {
				colorflag = true;
			}
		}
	}
	else {
		m_stete = Estete_Attack;
	}
}
void Tizutyo::NeoMove() {
	//�ړ���
	Player * player = Player::GetInstance();
	CVector3 P_Position = player->Getm_Position();
	CVector3 diff = P_Position - m_position;
	neoVec = diff;
	if (diff.Length() < followstop) {
		//��~����
		moveVec = neoVec * Speed;
	}
	else {
		//�ǂ��������!
		neoVec.Normalize();
		moveVec = neoVec * followSpeed;

	}
	if (diff.Length() < followleave) {
		//�߂���yo�����yo!
		neoVec.Normalize();
		moveVec = neoVec * followSpeed * -1.0f;
	}
	//�����_���Ȏ��ԂōU�����郈
	if (count == 0) {
		random = rand() % 7;
		if (random >= 4) {
			count = 1;
		}
		random = random * time;//�����_������
	}
	timer++;
	if (timer > random) {
		EffectManager * effectmanager = EffectManager::GetInstance();
		CVector3 EF_Position = m_position;
		EF_Position.y += 50.0f;
		effectmanager->EffectPlayer_Post(EffectManager::BulletYobi, EF_Position, { 40.0f,40.0f,40.0f });

		bulletFlag = false;
		colorflag = false;
		m_stete = Estete_Yobi;
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
void Tizutyo::NeoDeath() {

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


void Tizutyo::Update() {

	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();
	if (mode != GameData::Pause) {

		switch (m_stete) {
		case Estete_Attack://�U��
			NeoAttack();
			break;
		case Estete_Yobi://�\������
			NeoYobi();
			break;
		case Estete_Move://�ړ�
			NeoMove();
			break;
		case Estete_Death:
			NeoDeath();//��
			break;
		case Estete_Death2:
			NeoDeath2();//��
			break;
		}

		if (dathflag == true) {
			DeleteGO(this);
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

void Tizutyo::NeoDeath2() {
	DeleteGO(this);
}
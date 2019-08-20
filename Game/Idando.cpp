#include "stdafx.h"
#include "Idando.h"
#include "GameData.h"
#include "EffectManager.h"
#include "Kodan.h"
#include "StarComet_Inseki.h"

Idando::Idando()
{
}


Idando::~Idando()
{
	DeleteGO(m_skinModelRender);
}

bool Idando::Start() {
	//�A�j���[�V�����N���b�v�����[�h�ƃ��[�v�t���O�B
	m_animClips[enAnimationClip_walk].Load(L"animData/Ida_Stay.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	//�\��
	m_animClips[enAnimationClip_attack_yobi].Load(L"animData/Ida_Yobi.tka");
	//�U��
	m_animClips[enAnimationClip_attack].Load(L"animData/Ida_Attack.tka");
	//�I��
	m_animClips[enAnimationClip_attack_return].Load(L"animData/Ida_Return.tka");

	//�X�L�����f��
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Idando.cmo", m_animClips, enAnimationClip_Num);

	m_skinModelRender->SetPosition(m_position);

	m_scale = { 1.0f,1.0f,1.0f };
	m_charaCon.Init(
		45.0f,  //�L�����N�^�[�̔��a�B
		10.0f,  //�L�����N�^�[�̍����B
		m_position //�L�����N�^�[�̏������W�B
	);

	return true;
}

void Idando::Update() {
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
		case Estete_return://�I��
			EnemyReturn();
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

void Idando::EnemyAttack() {
	if (timer == 0) {
		m_skinModelRender->PlayAnimation(enAnimationClip_attack);
	}
	bool flag = m_skinModelRender->IsPlayingAnimation(); //�Đ����łȂ��Ȃ�I������
	if (flag == false) {
		if (timer2 == 30) {
			timer = -1;
			timer2 = 0;
			m_stete = Estete_return;
		}
		timer2++;
	}

	timer++;
}

void Idando::EnemyMove() {

	if (timer == randomCount) {
		timer = -1;
		int random = rand() % 3;
		if (random == 0) {
			//�U�����܂��I
			m_stete = Estete_yobi;
		}
	}

	timer++;

}

void Idando::EnemyDeath() {
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

	//�R�_������
	for (int i = 0; i < 3; i++) {
		Kodan*kodan = NewGO<Kodan>(0, "Kodan");
		CVector3 Pos = m_position;
		int PosHoge = rand() % 50;
		int random = rand() % 2;
		if (random == 1) {
			PosHoge *= -1;
		}
		Pos.x += (float)PosHoge;
		PosHoge = rand() % 50;
		random = rand() % 2;
		if (random == 1) {
			PosHoge *= -1;
		}
		Pos.z += (float)PosHoge;
		kodan->SetPosition(Pos);

		//�����X�^�[�̐��𑝂₷�I
		int X = gamedata->GetEnemyCounter();
		X++;
		gamedata->EnemyCounterSet(X);
	}

	DeleteGO(this);

}

void Idando::EnemyDeath2() {
	DeleteGO(this);

}

void Idando::Enemyyobi() {

	if (timer == 0) {
		m_skinModelRender->PlayAnimation(enAnimationClip_attack_yobi);
	}
	bool flag = m_skinModelRender->IsPlayingAnimation(); //�Đ����łȂ��Ȃ�I������
	if (flag == false) {
		timer = -1;
		m_stete = Estete_Attack;
	}

	timer++;

}

void Idando::EnemyReturn() {


	if (timer == 0) {
		m_skinModelRender->PlayAnimation(enAnimationClip_attack_return);
	}
	bool flag = m_skinModelRender->IsPlayingAnimation(); //�Đ����łȂ��Ȃ�I������
	if (flag == false) {
		m_skinModelRender->PlayAnimation(enAnimationClip_walk);
		timer = -1;
		m_stete = Estete_Move;
	}

	timer++;

}
#include "stdafx.h"
#include "Metoporisu.h"
#include "GameData.h"
#include "EffectManager.h"
#include "Bullet6.h"
#include "StarComet_Inseki.h"

Metoporisu::Metoporisu()
{
}


Metoporisu::~Metoporisu()
{
	DeleteGO(m_skinModelRender);
}

bool Metoporisu::Start() {

	//�A�j���[�V�����N���b�v�����[�h�ƃ��[�v�t���O�B
	m_animClips[enAnimationClip_walk].Load(L"animData/Metoporisu.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Metoporisu.cmo", m_animClips, enAnimationClip_Num);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);

	m_scale = { 2.0f,2.0f,2.0f };
	m_charaCon.Init(
		45.0f,  //�L�����N�^�[�̔��a�B
		10.0f,  //�L�����N�^�[�̍����B
		m_position //�L�����N�^�[�̏������W�B
	);

	return true;
}

void Metoporisu::Update() {

	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();
	if (mode != GameData::Pause) {

		switch (m_stete)
		{
		case Estete_Move:
			Move();
			break;
		case Estete_Death:
			Death();
			break;
		case Estete_Death2:
			Death2();
			break;
		}

		C_timer++;
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

void Metoporisu::Move() {

	if (timer == 0) {
		int random = rand() % 360;//�����_���ŕ���������
		m_rotation.SetRotation(CVector3::AxisY, (float)random);
		CVector3 Aru_mae = { 0.0f, 0.0f, -1.0f };
		m_rotation.Multiply(Aru_mae);
		moveVec = Aru_mae * randomSpeed;
	}
	else if (timer == randomcount) {
		timer = -1;
	}
	m_position = m_charaCon.Execute(moveVec);

	if (AttackTimer > AttackLimit - 60) {//�F�ω�
		colorcount += 1.0f;
		m_skinModelRender->SetEmissionColor({ colorcount , 0.0f, 0.0f });
	}
	if (AttackTimer == AttackLimit - 60) {//�\������G�t�F�N�g
		EffectManager * effectmanager = EffectManager::GetInstance();
		CVector3 EF_Position = m_position;
		EF_Position.y += 50.0f;
		effectmanager->EffectPlayer_Post(EffectManager::BulletYobi, EF_Position, { 40.0f,40.0f,40.0f });
	}//�o���b�g�͂�����`
	if (AttackTimer == AttackLimit) {
		Bullet6* bullet6 = NewGO<Bullet6>(0, "bullet6");
		bullet6->Init(this);
		bullet6->SetMoveVec(moveVec);
		m_skinModelRender->SetEmissionColor({ 0.0f , 0.0f, 0.0f });
		colorcount = 0.0f;

		AttackTimer = -1;
	}

	timer++;
	AttackTimer++;

}

void Metoporisu::Death() {
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

void Metoporisu::Death2() {
	DeleteGO(this);
}
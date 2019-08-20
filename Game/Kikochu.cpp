#include "stdafx.h"
#include "Kikochu.h"
#include "GameData.h"
#include "EffectManager.h"
#include "StarComet_Inseki.h"

Kikochu::Kikochu()
{
}


Kikochu::~Kikochu()
{
	DeleteGO(m_skinModelRender);
}

bool Kikochu::Start() {

	//�A�j���[�V�����N���b�v�����[�h�ƃ��[�v�t���O�B
	m_animClips[enAnimationClip_walk].Load(L"animData/KikoWalk.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Kikochu.cmo", m_animClips, enAnimationClip_Num);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);

	m_charaCon.Init(
		45.0f,  //�L�����N�^�[�̔��a�B
		10.0f,  //�L�����N�^�[�̍����B
		m_position //�L�����N�^�[�̏������W�B
	);

	return true;
}

void Kikochu::Update() {

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

void Kikochu::Move() {

	timer++;
	EF_timer++;
	if (timer == randomcount) {
		int random = rand() % 360;//�����_���ŕ���������
		m_rotation.SetRotation(CVector3::AxisY, (float)random);
		CVector3 Aru_mae = { 0.0f, 0.0f,1.0f };
		m_rotation.Multiply(Aru_mae);
		moveVec = Aru_mae * randomSpeed;
		timer = 0;
	}

	if (EF_timer == Ef_Limit) { //���G�t�F�N�g��\������
		EffectManager * effectmanager = EffectManager::GetInstance();
		CVector3 ef_position = m_position;
		effectmanager->EffectPlayer(EffectManager::star, ef_position, SpawnEffectScale / 2);
		effectmanager->EffectPlayer(EffectManager::star, ef_position, SpawnEffectScale / 2);
		effectmanager->EffectPlayer(EffectManager::star, ef_position, SpawnEffectScale / 2);
		effectmanager->EffectPlayer(EffectManager::star, ef_position, SpawnEffectScale / 2);
		EF_timer = 0;
	}

	m_position = m_charaCon.Execute(moveVec);

}

void Kikochu::Death() {

	prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
	ss->Init(L"sound/E_death.wav");
	ss->SetVolume(1.0f);
	ss->Play(false);

	EffectManager * effectmanager = EffectManager::GetInstance();
	CVector3 EF_Position = m_position;
	EF_Position.y += 50.0f;
	effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f }, false, false);

	//�L�R�E�`���E�t���O���I����
	GameData * gamedata = GameData::GetInstance();
	gamedata->SetKikoFlag();

	DeleteGO(this);
}

void Kikochu::Death2() {
	DeleteGO(this);
}
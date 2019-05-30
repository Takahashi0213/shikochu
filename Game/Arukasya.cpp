#include "stdafx.h"
#include "Player.h"
#include "Arukasya.h"
#include "EffectManager.h"
#include "GameData.h"

Arukasya::Arukasya()
{
}


Arukasya::~Arukasya()
{
	DeleteGO(m_skinModelRender);
}
bool Arukasya::Start() {

	//�A�j���[�V�����N���b�v�����[�h�ƃ��[�v�t���O�B
	m_animClips[enAnimationClip_walk].Load(L"animData/Aruwalk.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	//�\��
	m_animClips[enAnimationClip_back].Load(L"animData/Aruback.tka");
	m_animClips[enAnimationClip_back].SetLoopFlag(true);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Arukasya.cmo", m_animClips, enAnimationClip_Num);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);

	m_charaCon.Init(
		45.0f,  //�L�����N�^�[�̔��a�B
		10.0f,  //�L�����N�^�[�̍����B
		m_position //�L�����N�^�[�̏������W�B
	);

	return true;
}

void Arukasya::AruMove() {

	timer++;
	if (timer == randomcount) {
		random = rand() % 360;//�����_���ŕ���������
		m_rotation.SetRotation(CVector3::AxisY, (float)random);
		CVector3 Aru_mae = { 0.0f, 0.0f,1.0f };
		m_rotation.Multiply(Aru_mae);
		moveVec = Aru_mae * randomSpeed;
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

		attime = 0;
		m_stete = Estete_Attack;
	}
	
	m_position = m_charaCon.Execute(moveVec);

}
void Arukasya::AruAttack() {
	attime++;
	if (attime < waittimer) {
		//�o�b�N�����
		moveVec = attackVec * back;

	}
	else if (attime > waittimer && attime < backtime) {
		//�ːi��
		moveVec += attackVec * rush;

	}
	else if (attime > backtime) {
		//��ނ����Ⴄ��
		moveVec += attackVec * backk;

	}
	if (attime > endtime) {
		//�����_���ړ��ɖ߂�
		moveVec = attackVec * 0.0f;
		timer = 0;
		movecount = 0;
		m_stete = Estete_Move;
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


void Arukasya::AruDeath() {
	prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
	ss->Init(L"sound/E_death.wav");
	ss->SetVolume(0.5f);
	ss->Play(false);

	EffectManager * effectmanager = EffectManager::GetInstance();
	CVector3 EF_Position = m_position;
	EF_Position.y += 50.0f;
	effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });

	GameData * gamedata = GameData::GetInstance();
	gamedata->EnemyCounterGensyou();
	DeleteGO(this);

}

void Arukasya::Update() {
	switch (m_stete)
	{
	case Estete_Attack:
		AruAttack();
		break;
	case Estete_Move:
		AruMove();
		break;
	case Estete_Death:
		AruDeath();
		break;
	}

	//�ړ�
	m_skinModelRender->SetPosition(m_position);
	//��]
	m_skinModelRender->SetRotation(m_rotation);
	//�g�嗦
	m_skinModelRender->SetScale(m_scale);
	
}
#include "stdafx.h"
#include "Sekuteimu.h"
#include "Player.h"
#include "GameData.h"
#include "EffectManager.h"
#include "StarComet_Inseki.h"

Sekuteimu::Sekuteimu()
{
}


Sekuteimu::~Sekuteimu()
{
	DeleteGO(m_skinModelRender);
}

bool Sekuteimu::Start() {
	m_animClips[enAnimationClip_move].Load(L"animData/SektWalk.tka");
	m_animClips[enAnimationClip_move].SetLoopFlag(true);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Sekuteia.cmo", m_animClips, enAnimationClip_Num);

	m_scale = { 50.0f,50.0f,50.0f };
	m_charaCon.Init(
		45.0f,  //�L�����N�^�[�̔��a�B
		10.0f,  //�L�����N�^�[�̍����B
		m_position //�L�����N�^�[�̏������W�B
	);

	m_skinModelRender->SetEmissionColor({ 10.0f,0.0f,2.0f });

	return true;
}
void Sekuteimu::Soumove() {

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
	else if (movecount >1) {
		//�U��������
		Player * player = Player::GetInstance();
		CVector3 P_Position = player->Getm_Position();
		diff = P_Position - m_position;
		attackVec = diff;
		attackVec.Normalize();

		timecount = 0;
		m_stete = Estete_Attack;
	}
	m_position = m_charaCon.Execute(moveVec);
}
void Sekuteimu::Souattack() {
	timecount++;
	if (timecount < waittimer) {
		//�o�b�N�����
		moveVec = attackVec * back;

	}
	else if (timecount > waittimer) {
		//�ːi��
		moveVec += attackVec * rush;

	}
	if (timecount > attacktime) {
		//�����_���ړ��ɖ߂�
		moveVec = attackVec * 0.0f;
		timer = 0;
		movecount = 0;
		m_stete = Estete_Move;
	}

	CVector3 enemyForward = { 0.0f, 0.0f,1.0f };
	//�v���C���[�̌����ɉ�]
	diff.y = 0.0f;
	diff.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, diff);
	m_rotation = qRot;
	m_position = m_charaCon.Execute(moveVec);

}
void Sekuteimu::Soudeath() {

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
	DeleteGO(this);
}
void Sekuteimu::Update() {

	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();
	if (mode != GameData::Pause) {

		switch (m_stete) {
		case Estete_Move://�ړ�
			Soumove();
			break;
		case Estete_Attack://�U��1
			Souattack();
			break;
		case Estete_Death://���
			Soudeath();
			break;
		case Estete_Death2://���
			Soudeath2();
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

void Sekuteimu::Soudeath2() {
	DeleteGO(this);
}
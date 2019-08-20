#include "stdafx.h"
#include "Fairo.h"
#include "Player.h"
#include "GameData.h"
#include "EffectManager.h"
#include "StarComet_Inseki.h"


Fairo::Fairo()
{
}


Fairo::~Fairo()
{
	DeleteGO(m_skinModelRender);
}

bool Fairo::Start() {
	//�A�j���[�V����
	m_animClips[enAnimationClip_walk].Load(L"animData/Faiwalk.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	m_animClips[enAnimationClip_dash].Load(L"animData/Faidash.tka");
	m_animClips[enAnimationClip_dash].SetLoopFlag(true);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Fairo.cmo", m_animClips, enAnimationClip_Num);
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
void Fairo::Faimove() {
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

		timecount = 0;
		m_stete = Estete_Attack;
	}
	if (m_stete == Estete_Move) {
		//stete��move�̂Ƃ��͕����A�j���[�V����
		m_skinModelRender->PlayAnimation(enAnimationClip_walk);

	}

	m_position = m_charaCon.Execute(moveVec);

}
void Fairo::Faiattack() {
	timecount++;
	if (timecount < waittimer) {
		//�o�b�N�����
		moveVec = attackVec * back;

	}
	else if (timecount > waittimer) {
		//�ːi��
		moveVec += attackVec * rush;
		m_skinModelRender->PlayAnimation(enAnimationClip_dash);
	}
	if (timecount > attacktime) {
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
void Fairo::Faideath() {
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


void Fairo::Update() {
	
	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();
	if (mode != GameData::Pause) {

		switch (m_stete) {
		case Estete_Move://�ړ�
			Faimove();
			break;
		case Estete_Attack://�U��
			Faiattack();
			break;
		case Estete_Death://���
			Faideath();
			break;
		case Estete_Death2://���
			Faideath2();
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

void Fairo::Faideath2() {
	DeleteGO(this);
}
#include "stdafx.h"
#include "Riritto.h"
#include "GameData.h"
#include "Player.h"
#include "Bullet2.h"
#include "EffectManager.h"


Riritto::Riritto()
{
}


Riritto::~Riritto()
{
	DeleteGO(m_skinModelRender);
}

bool Riritto::Start() {

	//�A�j���[�V�����N���b�v�����[�h�ƃ��[�v�t���O�B
	m_animClips[enAnimationClip_walk].Load(L"animData/Ririwalk.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);

	//�X�L�����f��
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Riritto.cmo", m_animClips, enAnimationClip_Num);
	m_skinModelRender->SetForwardRenderFlag(true);

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
void Riritto::RiAttack() {
	//��������ł�
	movetimer++;
	if (bulletFlag == false) {
		Bullet2* bullet2 = NewGO<Bullet2>(0, "bullet2");
		bullet2->Init(this);
		bulletFlag = true;
	}
	else if (movetimer < move_starttimer) {
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
void Riritto::RiYobi() {
	//�\������ŐF���ω������������
	if (colorflag == false) {
		//���邭
		colortimer++;
		if (colortimer == 1) {
			colorcount += 1.0f;
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
void Riritto::RiMove() {
	//�ړ���
	Player * player = Player::GetInstance();
	CVector3 P_Position = player->Getm_Position();
	CVector3 diff = P_Position - m_position;
	RiVec = diff;
	if (diff.Length() < followstop) {
		//��~����
		moveVec = RiVec * Speed;
	}
	else {
		//�ǂ��������!
		RiVec.Normalize();
		moveVec = RiVec * followSpeed;

	}
	if (diff.Length() < followleave) {
		//�߂���yo�����yo!
		RiVec.Normalize();
		moveVec = RiVec * followSpeed * -1.0f;
	}
	//�����_���Ȏ��ԂōU�����郈
	if (count == 0) {
		random = rand() % 8;
		if (random >= 2) {
			count = 1;

		}
		random = random * time;//�����_������
	}
	timer++;
	if (timer > random) {
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
void Riritto::RiDeath() {
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
void Riritto::Update() {
	switch (m_stete) {
	case Estete_Attack://�U��
		RiAttack();
		break;
	case Estete_Yobi://�\������
		RiYobi();
		break;
	case Estete_Move://�ړ�
		RiMove();
		break;
	case Estete_Death:
		RiDeath();//��
		break;
	}

	if (dathflag == true) {
		DeleteGO(this);
	}

	//�ړ�
	m_skinModelRender->SetPosition(m_position);
	//��]
	m_skinModelRender->SetRotation(m_rotation);
	//�g�嗦
	m_skinModelRender->SetScale(m_scale);

}
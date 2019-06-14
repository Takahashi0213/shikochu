#include "stdafx.h"
#include "Uminoushi.h"
#include "Player.h"
#include "Bullet3.h"
#include "GameData.h"
#include "EffectManager.h"


Uminoushi::Uminoushi()
{
}


Uminoushi::~Uminoushi()
{
	DeleteGO(m_skinModelRender);
}

bool Uminoushi::Start() {

	m_animClips[enAnimationClip_move].Load(L"animData/umiWalk.tka");
	m_animClips[enAnimationClip_move].SetLoopFlag(true);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/umino.cmo", m_animClips, enAnimationClip_Num);

	m_charaCon.Init(
		45.0f,  //�L�����N�^�[�̔��a�B
		10.0f,  //�L�����N�^�[�̍����B
		m_position //�L�����N�^�[�̏������W�B
	);

	return true;
}

void Uminoushi::Update() {

	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();
	if (mode != GameData::Pause) {

		switch (m_stete) {
		case Estete_Move://�ړ�
			move();
			break;
		case Estete_Yobi://�\��
			yobi();
			break;
		case Estete_Attack://�U��1
			attack();
			break;
		case Estete_Death://���
			death();
			break;
		case Estete_Death2://���
			death2();
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

void Uminoushi::move() {
	timer++;
	if (timer == randomCount) {
		random = rand() % 360;//�����_���ŕ���������
		m_rotation.SetRotation(CVector3::AxisY, (float)random);
		CVector3 sou_mae = { -1.0f, 0.0f,0.0f };
		m_rotation.Multiply(sou_mae);
		moveVec = sou_mae * randomSpeed;
		movecount++;
		timer = 0;
	}
	else if (movecount >3) {
		m_stete = Estete_Yobi; 
		movecount = 0;
		timer = 0;
	}
	m_position = m_charaCon.Execute(moveVec);
}

void Uminoushi::yobi() {

	timer++;

	CQuaternion RotationY;
	RotationY.SetRotationDeg(CVector3::AxisY, 6.0f);
	m_rotation *= RotationY;
	m_skinModelRender->SetRotation(m_rotation);

	if (timer == 120) {
		m_stete = Estete_Attack;
		timer = 0;
	}

}


void Uminoushi::attack() {

	timer++;

	CQuaternion RotationY;
	RotationY.SetRotationDeg(CVector3::AxisY, 60.0f);
	m_rotation *= RotationY;
	m_skinModelRender->SetRotation(m_rotation);


	if (B_Flag == false) {

		for (int i = 0; i < 9; i++) {
		
			CVector3 move = CVector3::Zero;
			switch (i)
			{
			case 0:
				move = { 1.0f,0.0f,0.0f };
				break;
			case 1:
				move = { 0.8f,0.0f,0.8f };
				break;
			case 2:
				move = { 0.0f,0.0f,1.0f };
				break;
			case 3:
				move = { -0.8f,0.0f,0.8f };
				break;
			case 4:
				move = { 0.8f,0.0f,0.8f };
				break;
			case 5:
				move = { -1.0f,0.0f,0.0f };
				break;
			case 6:
				move = { -0.8f,0.0f,-0.8f };
				break;
			case 7:
				move = { 0.0f,0.0f,-1.0f };
				break;
			case 8:
				move = { 0.8f,0.0f,-0.8f };
				break;
			}		
			move *= B_MoveSpeed;

			Bullet3* bullet3 = NewGO<Bullet3>(0, "bullet3");
			bullet3->Init(this);
			bullet3->SetMove(move);
			
		}

		B_Flag = true;
	}

	if (timer == 24) {
		m_stete = Estete_Move;
		timer = 0;
		B_Flag = false;
	}

}

void Uminoushi::death() {
	prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
	ss->Init(L"sound/E_death.wav");
	ss->SetVolume(1.0f);
	ss->Play(false);

	EffectManager * effectmanager = EffectManager::GetInstance();
	CVector3 EF_Position = m_position;
	EF_Position.y += 50.0f;
	effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });

	GameData * gamedata = GameData::GetInstance();
	gamedata->EnemyCounterGensyou();
	DeleteGO(this);
}

void Uminoushi::death2() {
	DeleteGO(this);
}
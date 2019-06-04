#include "stdafx.h"
#include "SS_001.h"
#include "Misairu.h"
#include "EffectManager.h"
#include "GameData.h"
#include "BossHPGage.h"

SS_001::SS_001()
{
}


SS_001::~SS_001()
{
	DeleteGO(m_skinModelRender);
}

bool SS_001::Start() {

	//�A�j���[�V����
	m_animClips[enAnimationClip_move].Load(L"animData/SSwalk.tka");
	m_animClips[enAnimationClip_move].SetLoopFlag(true);
	m_animClips[enAnimationClip_wait].Load(L"animData/SSwait.tka");
	m_animClips[enAnimationClip_wait].SetLoopFlag(true);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/SS_001.cmo", m_animClips, enAnimationClip_Num);
	//m_skinModelRender->SetForwardRenderFlag(true);
	m_rotation.SetRotationDeg(CVector3::AxisY, -180.0f);


	m_scale = { 10.0f,10.0f,10.0f };
	//m_position = { 0.0f,1000.0f,5000.0f };

	m_skinModelRender->SetPosition(m_position);

	DefPos = m_position;

	//m_charaCon.Init(
	//	350.0f,  //�L�����N�^�[�̔��a�B
	//	100.0f,  //�L�����N�^�[�̍����B
	//	m_position //�L�����N�^�[�̏������W�B
	//);

	return true;
}

void SS_001::Update() {

	switch (m_stete) {
	case Estete_Move://�ړ�
		SSMove();
		break;
	case Estete_Yobi1://�\������1
		SSYobi1();
		break;
	case Estete_Attack1://�U��1
		SSAttack1();
		break;
	case Estete_Yobi2://�\������2
		SSYobi2();
		break;
	case Estete_Attack2://�U��2
		SSAttack2();
		break;
	case Estete_Death://���
		SSDeath();
		break;
	case Estete_Death2://���
		SSDeath2();
		break;
	}

	//HP��0�Ȃ玀��
	if (NowHP == 0) {
		m_stete = Estete_Death;
	}

	//�ړ�
	m_skinModelRender->SetPosition(m_position);
	//��]
	m_skinModelRender->SetRotation(m_rotation);
	//�g�嗦
	m_skinModelRender->SetScale(m_scale);

}

void SS_001::SSMove() {

	//�������ԂɂȂ����Ƃ����s
	if (AttackTimer == AttackLimit) {
		int random = rand() % 2;
		if (random == 0) {//�U�����܂�
			random = rand() % 2;
			//random = 1; //�e�X�g�p
			if (random == 0) {
				m_stete = Estete_Yobi1; //�~�T�C��
			}
			else {
				m_stete = Estete_Yobi2; //�r�[��
			}
		}
		AttackTimer = 0;
	}

	AttackTimer++;
}

void SS_001::SSYobi1() {
	m_skinModelRender->PlayAnimation(enAnimationClip_wait, 0.5f);

	m_stete = Estete_Attack1; //�~�T�C���ֈڍs
}

void SS_001::SSAttack1() {

	if (MisairuTimer == 0) {
		int random = rand() % 4;
		if (random == 0) {
			MisairuMove = { 20.0f,20.0f,0.0f };
		}
		else if (random == 1) {
			MisairuMove = { -20.0f,20.0f,0.0f };
		}
		else if (random == 2) {
			MisairuMove = { 20.0f,0.0f,0.0f };
		}
		else if (random == 3) {
			MisairuMove = { -20.0f,0.0f,0.0f };
		}
		//�~�T�C�������񐔂�HP�Őݒ肷��
		if (NowHP < MAXHP / 4) {
			MisairuCountMAX = 10;
		}
		else if ( NowHP < MAXHP / 2) {
			MisairuCountMAX = 8;
		}
		else {
			MisairuCountMAX = 6;
		}

		ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/missile.wav");
		ss->SetVolume(0.5f);
		ss->SetFrequencyRatio(2.0f);
		ss->Play(false);

		//�~�T�C������		
		NewGO<Misairu>(0, "Misairu");
	}

	//�ړ����x�Z�b�g
	QueryGOs<Misairu>("Misairu", [&](Misairu* misairu) {
		if (misairu->GetFlag() == true) { //�����ݒ�ς݂Ȃ�X���[����`
			return true;
		}
		//�ݒ�̎��Ԃ�
		misairu->SetPosition(m_position);
		misairu->SetMoveSpeed(MisairuMove);
		misairu->SettingFlag();

		return true;
		});

	//�����̈ړ�
	if (MisairuTimer < MisairuLimit / 4) {
		MyMove = CVector3::Zero;
		m_position -= MisairuMove * 2;
	}
	else {
		if (MyMove.x == 0.0f) {
			MyMove = DefPos - m_position;
			MyMove = MyMove / (((float)MisairuLimit / 4.0f) * 3.0f);
		}
		m_position += MyMove;
	}

	if (MisairuTimer == MisairuLimit) {
		MisairuTimer = -1;
		MisairuCounter++;
		if (MisairuCounter >= MisairuCountMAX) {
			//�U���I��
			m_skinModelRender->PlayAnimation(enAnimationClip_move, 0.5f);
			MisairuCounter = 0;
			m_stete = Estete_Move;
		}
	}

	MisairuTimer++;

}

void SS_001::SSYobi2() {

	if (BeamYobiTimer == 0) {
		m_skinModelRender->PlayAnimation(enAnimationClip_wait, 0.5f);
		ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/beamcharge.wav");
		ss->SetVolume(0.8f);
		ss->SetFrequencyRatio(2.0f);
		ss->Play(false);

		//Effect�Đ�
		EffectManager * effectmanager = EffectManager::GetInstance();
		effectmanager->EffectPlayer(EffectManager::Beam, { m_position.x,m_position.y,m_position.z - 2000.0f }, { 500.0f,500.0f,500.0f });
	}

	if (BeamYobiTimer >= BeamYobiLimit) {
		BeamYobiTimer = -1;
		m_stete = Estete_Attack2; //�r�[���ֈڍs
	}

	BeamYobiTimer++;

}

void SS_001::SSAttack2() {

	if (BeamTimer == 0) {
		ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/beam.wav");
		ss->SetVolume(0.5f);
		ss->Play(false);

		//Effect�Đ�
		EffectManager * effectmanager = EffectManager::GetInstance();
		effectmanager->EffectPlayer(EffectManager::BeamHassya, { m_position.x,m_position.y,m_position.z - 2000.0f }, { 1000.0f,1000.0f,1000.0f });
	}

	if (BeamTimer < 40) {
		m_position.z += 10.0f;
	}

	if (BeamTimer > BeamLimit - 40) {
		m_position.z -= 10.0f;
	}

	if (BeamTimer >= BeamLimit) {
		//�U���I��
		m_skinModelRender->PlayAnimation(enAnimationClip_move, 0.5f);
		BeamTimer = -1;
		m_stete = Estete_Move;
	}

	BeamTimer++;
}

void SS_001::SSDeath() {

	//�������
	if (DeathTimer == 0) {
		//��Ԃ����U���g�ɁI
		GameData * gamedata = GameData::GetInstance();
		BossHPGage * bossHPGage = BossHPGage::GetInstance();
		gamedata->SetGameMode(GameData::Result);
		bossHPGage->DeleteGage();
	}

	if (DeathTimer == 12) {
		//Effect�Đ�
		EffectManager * effectmanager = EffectManager::GetInstance();
		effectmanager->EffectPlayer(EffectManager::Bakuhatu, m_position, { 500.0f,500.0f,500.0f });
	}
	if (DeathTimer == 70) {
		//Effect�Đ�
		EffectManager * effectmanager = EffectManager::GetInstance();
		effectmanager->EffectPlayer(EffectManager::Bakuhatu, m_position, { 500.0f,500.0f,500.0f });
	}
	if (DeathTimer == 160) {
		//Effect�Đ�
		EffectManager * effectmanager = EffectManager::GetInstance();
		effectmanager->EffectPlayer(EffectManager::Bakuhatu, m_position, { 500.0f,500.0f,500.0f });
	}
	if (DeathTimer == 230) {
		//Effect�Đ�
		EffectManager * effectmanager = EffectManager::GetInstance();
		effectmanager->EffectPlayer(EffectManager::Bakuhatu, { m_position.x + 500.0f,m_position.y, m_position.z - 2000.0f }, { 1000.0f,1000.0f,1000.0f });
	}


	if (ToumeiTimeMAX == DeathTimer) {
		prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/Boss_death.wav");
		ss->SetVolume(0.5f);
		ss->SetFrequencyRatio(0.5f);
		ss->Play(false);

		m_scale = CVector3::Zero;
	}

	if (DeathTimeMAX == DeathTimer) {
		GameData * gamedata = GameData::GetInstance();
		gamedata->EnemyCounterGensyou();
		DeleteGO(this);
	}

	DeathTimer++;

}

void SS_001::SSDeath2() {

	DeleteGO(this);
}


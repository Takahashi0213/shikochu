#include "stdafx.h"
#include "Pairodorago.h"
#include "GameData.h"
#include "BossHPGage.h"
#include "EffectManager.h"

Pairodorago::Pairodorago()
{
}


Pairodorago::~Pairodorago()
{
	DeleteGO(m_skinModelRender);
}

bool Pairodorago::Start() {

	//�A�j���[�V����
	m_animClips[enAnimationClip_move].Load(L"animData/piro_Bigidle.tka");
	m_animClips[enAnimationClip_move].SetLoopFlag(true);
	m_animClips[enAnimationClip_yobi].Load(L"animData/Piro_Bigattack2.tka");
	m_animClips[enAnimationClip_attack].Load(L"animData/Piro_Bigattack4.tka");

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/DragonTerrorBringerMesh.cmo", m_animClips, enAnimationClip_Num);
	//m_skinModelRender->SetForwardRenderFlag(true);
	m_rotation.SetRotationDeg(CVector3::AxisY, -180.0f);

	//m_position = { 0.0f,-500.0f,5000.0f };
	m_scale = { 750.0f,750.0f,750.0f };

	m_skinModelRender->SetPosition(m_position);


	//m_charaCon.Init(
	//	350.0f,  //�L�����N�^�[�̔��a�B
	//	100.0f,  //�L�����N�^�[�̍����B
	//	m_position //�L�����N�^�[�̏������W�B
	//);

	//�n�[�h���[�h�Ȃ�{�X��HP�ɕ␳
	GameData * gamedata = GameData::GetInstance();
	bool HardFlag = gamedata->GetHardModeFlag();
	if (HardFlag == true) {
		float Hosei = gamedata->GetHardBossHosei();
		MAXHP *= Hosei;
		NowHP *= Hosei;
	}

	return true;
}

void Pairodorago::Update() {

	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();
	if (mode != GameData::Pause) {

		switch (m_stete) {
		case Estete_Move://�ړ�
			PairoMove();
			break;
		case Estete_Yobi1://�\������1
			PairoYobi1();
			break;
		case Estete_Attack1://�U��1
			PairoAttack1();
			break;
		case Estete_Yobi2://�\������2
			PairoYobi2();
			break;
		case Estete_Attack2://�U��2
			PairoAttack2();
			break;
		case Estete_Death://���
			PairoDeath();
			break;
		case Estete_Death2://���
			PairoDeath2();
			break;

		}
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

void Pairodorago::PairoMove() {

	if (MoveTimer >= MoveLimit) {

		int random = rand() % 3;
		if (random == 0) {
			//�U�����܂��I
			m_stete = Estete_Yobi1;
		}
		MoveTimer = -1;
	}


	MoveTimer++;
}

void Pairodorago::PairoYobi1() {

	if (YobiTimer == 0) {
		m_skinModelRender->PlayAnimation(enAnimationClip_yobi, 0.5f);
	}
	
	if (YobiTimer == 10) {
		ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/gaoooo.wav");
		ss->SetVolume(2.0f);
		ss->Play(false);

		//Effect�Đ�
		EffectManager * effectmanager = EffectManager::GetInstance();
		effectmanager->EffectPlayer(EffectManager::Gao, { m_position.x ,m_position.y + 2000.0f, m_position.z - 3000.0f }, { 1000.0f,1000.0f,1000.0f });
	}

	if (YobiTimer >= YobiLimit) {//���Ԑ؂�I
		YobiTimer = -1;
		m_skinModelRender->PlayAnimation(enAnimationClip_attack, 0.5f);
		m_stete = Estete_Attack1;
	}

	YobiTimer++;
}

void Pairodorago::PairoAttack1() {

	if (AttackTimer == AttackTiming) {
		ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/kamituki.wav");
		ss->SetVolume(1.0f);
		ss->SetFrequencyRatio(0.5f);
		ss->Play(false);

		DamageLength = DamageLengthDEF * 1.5f;
	}
	else {
		DamageLength = DamageLengthDEF;
	}


	if (AttackTimer >= AttackLimit) {//���Ԑ؂�I
		AttackTimer = -1;
		m_skinModelRender->PlayAnimation(enAnimationClip_move, 0.5f);
		m_stete = Estete_Move;
	}

	AttackTimer++;
}

void Pairodorago::PairoYobi2() {

}

void Pairodorago::PairoAttack2() {

}

void Pairodorago::PairoDeath() {
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
		effectmanager->EffectPlayer(EffectManager::Bakuhatu, m_position, { 1000.0f,1000.0f,1000.0f });
	}
	if (DeathTimer == 160) {
		//Effect�Đ�
		EffectManager * effectmanager = EffectManager::GetInstance();
		effectmanager->EffectPlayer(EffectManager::Bakuhatu, m_position, { 1000.0f,1000.0f,1000.0f });
	}
	if (DeathTimer == 230) {
		//Effect�Đ�
		EffectManager * effectmanager = EffectManager::GetInstance();
		effectmanager->EffectPlayer(EffectManager::Bakuhatu, { m_position.x + 500.0f,m_position.y, m_position.z - 2000.0f }, { 2000.0f,2000.0f,2000.0f });
	}


	if (ToumeiTimeMAX == DeathTimer) {
		ss = NewGO<prefab::CSoundSource>(0);
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

void Pairodorago::PairoDeath2() {
		DeleteGO(this);
}
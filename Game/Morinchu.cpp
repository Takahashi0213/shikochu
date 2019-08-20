#include "stdafx.h"
#include "Morinchu.h"
#include "GameData.h"
#include "BossHPGage.h"
#include "EffectManager.h"
#include "AppleBomb.h"
#include "StarComet_Inseki.h"

Morinchu::Morinchu()
{
}


Morinchu::~Morinchu()
{
	DeleteGO(m_skinModelRender);
}

bool Morinchu::Start() {

	//�A�j���[�V����
	m_animClips[enAnimationClip_move].Load(L"animData/kyo_idle.tka");
	m_animClips[enAnimationClip_move].SetLoopFlag(true);
	m_animClips[enAnimationClip_yobi].Load(L"animData/kyo_jump.tka");
	m_animClips[enAnimationClip_attack].Load(L"animData/kyo_attack.tka");
	m_animClips[enAnimationClip_dead].Load(L"animData/kyo_dead.tka");
	m_animClips[enAnimationClip_yobi_L].Load(L"animData/kyo_jump.tka");
	m_animClips[enAnimationClip_yobi_L].SetLoopFlag(true);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/kyozin.cmo", m_animClips, enAnimationClip_Num);
	//m_skinModelRender->SetForwardRenderFlag(true);
	m_rotation.SetRotationDeg(CVector3::AxisY, -180.0f);

	//m_position = { 0.0f,-500.0f,5000.0f };
	m_scale = { 100.0f,100.0f,100.0f };

	m_position.z -= 400.0f;
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
		float MH = (int)MAXHP * Hosei;
		MAXHP = (int)MH;
		NowHP = (int)MH;
	}

	return true;
}

void Morinchu::Update() {

	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();
	if (mode != GameData::Pause) {

		switch (m_stete) {
		case Estete_Move://�ړ�
			MoriMove();
			break;
		case Estete_Yobi1://�\������1
			MoriYobi1();
			break;
		case Estete_Attack1://�U��1
			MoriAttack1();
			break;
		case Estete_Attack2://�U��1
			MoriAttack2();
			break;
		case Estete_Death://���
			MoriDeath();
			break;
		case Estete_Death2://���
			MoriDeath2();
			break;

		}
	}
	//HP��0�Ȃ玀��
	if (NowHP == 0) {
		if (gamedata->GetLastDamage_StarDashFlag() == true && m_stete != Estete_Death) { //�����_�b�V���Ńg�h�����h�����񐔂𑝂₷
			gamedata->PlusLastStarDash();
		}
		m_stete = Estete_Death;
	}

	//�ǂ���覐΂ł�
	QueryGOs<StarComet_Inseki>("StarComet_Inseki", [&](StarComet_Inseki* SCI) {
		CVector3 inseki_position = SCI->Getm_Position();
		CVector3 diff = inseki_position - m_position;
		float Langth_hoge = SCI->GetDamageLength();
		Langth_hoge *= 10.0f;
		if (diff.Length() < Langth_hoge && gamedata->GetGameMode()!=GameData::GameOver) { //覐ΏՓ�
			int Damages = gamedata->GetATK();
			Damage(Damages); //�_���[�W
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

void Morinchu::MoriMove() {

	if (MoveTimer >= MoveLimit) {

		int random = rand() % 1;
		if (random == 0) {
			//�U�����܂��I
			random = rand() % 2;
			//random = 1; //�e�X�g�p
			if (random == 0) {
				m_stete = Estete_Yobi1;
			}
			else {
				m_stete = Estete_Attack2;
			}
		}
		MoveTimer = -1;
	}


	MoveTimer++;
}

void Morinchu::MoriYobi1() {

	if (YobiTimer == 0) {
		m_skinModelRender->PlayAnimation(enAnimationClip_yobi, 0.5f);
	}

	if (YobiTimer >= YobiLimit) {//���Ԑ؂�I
		YobiTimer = -1;
		m_skinModelRender->PlayAnimation(enAnimationClip_attack, 0.5f);
		m_stete = Estete_Attack1;
	}

	YobiTimer++;
}

void Morinchu::MoriAttack1() {

	if (AttackTimer == AttackTiming) {

		DamageLength = DamageLengthDEF * 1.2f;
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

void Morinchu::MoriAttack2() {

	if (AttackTimer== 0) {
		m_skinModelRender->PlayAnimation(enAnimationClip_yobi_L);
	}
	if (AttackTimer % Attack2Ave == 0) {

			//�����S����&����
			int AppleX = rand() % 1000;
			int random = rand() % 2;
			if (random == 1) {
				AppleX *= -1;
			}
			float ApplePosX = (float)AppleX;

			AppleBomb*appleBomb = NewGO<AppleBomb>(0, "AppleBomb");
			CVector3 Pos = { ApplePosX ,6000.0f,2000.0f };
			CVector3 T_Pos = { ApplePosX ,-800,2000.0f };
			appleBomb->SetPosition(Pos);
			appleBomb->SetTargetPos(T_Pos);

	}

	if (AttackTimer >= AttackLimit2) {//���Ԑ؂�I
		AttackTimer = -1;
		m_skinModelRender->PlayAnimation(enAnimationClip_move, 0.5f);
		m_stete = Estete_Move;
	}

	AttackTimer++;
}

void Morinchu::MoriDeath() {
	//�������
	if (DeathTimer == 0) {
		m_skinModelRender->PlayAnimation(enAnimationClip_dead, 0.5f);

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

void Morinchu::MoriDeath2() {
	DeleteGO(this);
}
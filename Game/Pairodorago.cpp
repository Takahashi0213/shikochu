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

	//アニメーション
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
	//	350.0f,  //キャラクターの半径。
	//	100.0f,  //キャラクターの高さ。
	//	m_position //キャラクターの初期座標。
	//);

	//ハードモードならボスのHPに補正
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

void Pairodorago::Update() {

	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();
	if (mode != GameData::Pause) {

		switch (m_stete) {
		case Estete_Move://移動
			PairoMove();
			break;
		case Estete_Yobi1://予備動作1
			PairoYobi1();
			break;
		case Estete_Attack1://攻撃1
			PairoAttack1();
			break;
		case Estete_Yobi2://予備動作2
			PairoYobi2();
			break;
		case Estete_Attack2://攻撃2
			PairoAttack2();
			break;
		case Estete_Death://死ﾇ
			PairoDeath();
			break;
		case Estete_Death2://死ﾇ
			PairoDeath2();
			break;

		}
	}
	//HPが0なら死ぬ
	if (NowHP == 0) {
		m_stete = Estete_Death;
	}

	//移動
	m_skinModelRender->SetPosition(m_position);
	//回転
	m_skinModelRender->SetRotation(m_rotation);
	//拡大率
	m_skinModelRender->SetScale(m_scale);

}

void Pairodorago::PairoMove() {

	if (MoveTimer >= MoveLimit) {

		int random = rand() % 3;
		if (random == 0) {
			//攻撃します！
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

		//Effect再生
		EffectManager * effectmanager = EffectManager::GetInstance();
		effectmanager->EffectPlayer(EffectManager::Gao, { m_position.x ,m_position.y + 2000.0f, m_position.z - 3000.0f }, { 1000.0f,1000.0f,1000.0f });
	}

	if (YobiTimer >= YobiLimit) {//時間切れ！
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


	if (AttackTimer >= AttackLimit) {//時間切れ！
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
	//ﾔﾗﾚﾀ･･･
	if (DeathTimer == 0) {
		//状態をリザルトに！
		GameData * gamedata = GameData::GetInstance();
		BossHPGage * bossHPGage = BossHPGage::GetInstance();
		gamedata->SetGameMode(GameData::Result);
		bossHPGage->DeleteGage();
	}

	if (DeathTimer == 12) {
		//Effect再生
		EffectManager * effectmanager = EffectManager::GetInstance();
		effectmanager->EffectPlayer(EffectManager::Bakuhatu, m_position, { 500.0f,500.0f,500.0f });
	}
	if (DeathTimer == 70) {
		//Effect再生
		EffectManager * effectmanager = EffectManager::GetInstance();
		effectmanager->EffectPlayer(EffectManager::Bakuhatu, m_position, { 1000.0f,1000.0f,1000.0f });
	}
	if (DeathTimer == 160) {
		//Effect再生
		EffectManager * effectmanager = EffectManager::GetInstance();
		effectmanager->EffectPlayer(EffectManager::Bakuhatu, m_position, { 1000.0f,1000.0f,1000.0f });
	}
	if (DeathTimer == 230) {
		//Effect再生
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
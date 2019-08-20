#include "stdafx.h"
#include "Teruosuka.h"
#include "EffectManager.h"
#include "GameData.h"
#include "BossHPGage.h"
#include "Misairu.h"
#include "StarComet_Inseki.h"

Teruosuka::Teruosuka()
{
}


Teruosuka::~Teruosuka()
{
	DeleteGO(m_skinModelRender);
}

bool Teruosuka::Start() {

	//アニメーション
	m_animClips[enAnimationClip_TankWait].Load(L"animData/Teru_TankWait.tka");
	m_animClips[enAnimationClip_TankWait].SetLoopFlag(true);
	m_animClips[enAnimationClip_TankAttack].Load(L"animData/Teru_TankAttack.tka");
	m_animClips[enAnimationClip_TankToPlane].Load(L"animData/Teru_TankToPlane.tka");
	m_animClips[enAnimationClip_PlaneWait].Load(L"animData/Teru_PlaneWalk.tka");
	m_animClips[enAnimationClip_PlaneWait].SetLoopFlag(true);
	m_animClips[enAnimationClip_PlaneToHuman].Load(L"animData/Teru_PlaneToHuman.tka");
	m_animClips[enAnimationClip_HumanWait].Load(L"animData/Teru_HumanWait.tka");
	m_animClips[enAnimationClip_HumanWait].SetLoopFlag(true);
	m_animClips[enAnimationClip_HumanAttack].Load(L"animData/Teru_HumanAttack.tka");
	m_animClips[enAnimationClip_HumanDeath].Load(L"animData/Teru_HumanDeath.tka");

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Teruosuka.cmo", m_animClips, enAnimationClip_Num);
	//m_skinModelRender->SetForwardRenderFlag(true);
	m_rotation.SetRotationDeg(CVector3::AxisY, -180.0f);

	m_scale = { 200.0f,200.0f,200.0f };
	m_position = { 0.0f, -200.0f,1500.0f };

	m_skinModelRender->SetPosition(m_position);

	DefPos = m_position;

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

void Teruosuka::Update() {

	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();
	if (mode != GameData::Pause) {

		switch (m_stete) {
		case Estete_TankMove:
			Teru_TankMove();
			break;
		case Estete_TankAttack:
			Teru_TankAttack();
			break;
		case Estete_TankToPlane:
			Teru_TankToPlane();
			break;
		case Estete_PlaneMove:
			Teru_PlaneMove();
			break;
		case Estete_PlaneToHuman:
			Teru_PlaneToHuman();
			break;		
		case Estete_HumanMove:
			Teru_HumanMove();
			break;		
		case Estete_HumanAttackWait:
			Teru_HumanAttackWait();
			break;
		case Estete_HumanAttack:
			Teru_HumanAttack();
			break;
		case Estete_Death://死ﾇ
			TeruDeath();
			break;
		case Estete_Death2://死ﾇ
			TeruDeath2();
			break;
		}
	}
	//HPが0なら死ぬ
	if (NowHP == 0) {
		if (gamedata->GetLastDamage_StarDashFlag() == true && m_stete != Estete_Death) { //流星ダッシュでトドメを刺した回数を増やす
			gamedata->PlusLastStarDash();
		}
		m_stete = Estete_Death;
	}

	//どうも隕石です
	QueryGOs<StarComet_Inseki>("StarComet_Inseki", [&](StarComet_Inseki* SCI) {
		CVector3 inseki_position = SCI->Getm_Position();
		CVector3 diff = inseki_position - m_position;
		float Langth_hoge = SCI->GetDamageLength();
		Langth_hoge *= 10.0f;
		if (diff.Length() < Langth_hoge && gamedata->GetGameMode() != GameData::GameOver) { //隕石衝突
			int Damages = gamedata->GetATK();
			Damage(Damages); //ダメージ
			SCI->SetDeath();//隕石も死ぬ
		}
		return true;
		});

	//移動
	m_skinModelRender->SetPosition(m_position);
	//回転
	m_skinModelRender->SetRotation(m_rotation);
	//拡大率
	m_skinModelRender->SetScale(m_scale);

}

void Teruosuka::Teru_TankMove() {
	//制限時間になったとき実行
	if (AttackTimer == AttackLimit) {
		int random = rand() % 2;
		if (random == 0) {//攻撃します
			m_skinModelRender->PlayAnimation(enAnimationClip_TankAttack, 0.5f);
			m_stete = Estete_TankAttack;
		}
		AttackTimer = -1;
	}
	AttackTimer++;

	//もしHPが3分の2以下ならレッツゴー変形
	if (NowHP < ((MAXHP / 3) * 2)) {
		m_skinModelRender->PlayAnimation(enAnimationClip_TankToPlane, 0.5f);
		m_stete = Estete_TankToPlane;
		AttackTimer = 0;
	}
}

void Teruosuka::Teru_TankAttack(){

	if (AttackTimer == 0 || AttackTimer == 10 || AttackTimer == 20) {

		if (AttackTimer == 0) {
			MisairuMove = { 20.0f,10.0f,-10.0f };
		}
		else if (AttackTimer == 10) {
			MisairuMove = { 0.0f,20.0f,-10.0f };
		}
		else if (AttackTimer == 20) {
			MisairuMove = { -20.0f,10.0f,-20.0f };
		}

		ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/missile.wav");
		ss->SetVolume(0.5f);
		ss->SetFrequencyRatio(2.0f);
		ss->Play(false);

		//ミサイル生成		
		NewGO<Misairu>(0, "Misairu");
	}

	//移動速度セット
	QueryGOs<Misairu>("Misairu", [&](Misairu* misairu) {
		if (misairu->GetFlag() == true) { //もし設定済みならスルーする～
			return true;
		}
		//設定の時間だ
		CVector3 MisairuPos = m_position;
		MisairuPos.z -= 2000.0f;
		MisairuPos.y += 1500.0f;
		misairu->SetPosition(MisairuPos);
		misairu->SetMoveSpeed(MisairuMove);
		misairu->SetTeruFlag();
		misairu->SettingFlag();

		return true;
		});

	AttackTimer++;

	if (AttackTimer == MisairuLimit) {
		AttackTimer = -1;
		m_stete = Estete_TankMove;
		m_skinModelRender->PlayAnimation(Estete_TankMove, 0.5f);

	}
}

void Teruosuka::Teru_TankToPlane() {

	m_position.z += 20.0f;
	m_position.y += 10.0f;

	bool flag = m_skinModelRender->IsPlayingAnimation(); //再生中でないなら終了する
	if (flag == false) {
		Teru_Mode = Plane;
		m_stete = Estete_PlaneMove;
		m_skinModelRender->PlayAnimation(enAnimationClip_PlaneWait, 0.5f);
	}

}

void Teruosuka::Teru_PlaneMove() {

	//上下移動
	if (AttackTimer < 240) {
		m_position.y += 10.0f;
	}
	else if (AttackTimer < 480) {
		m_position.y -= 10.0f;
	}
	else {
		AttackTimer = -1;
	}

	AttackTimer++;

	//もしHPが3分の1以下ならレッツゴー変形
	if (NowHP < MAXHP / 3 ) {
		m_stete = Estete_PlaneToHuman;
		AttackTimer = 0;
	}

}

void Teruosuka::Teru_PlaneToHuman() {

	if (AttackTimer < 30) {
		m_scale *= 0.98f;
		m_position.z -= 60.0f;
		m_position.y -= 100.0f;
		if (m_position.y < DefPos.y - 650.0f) {
			m_position.y = DefPos.y - 650.0f;
		}
	}
	else if (AttackTimer == 30) {
		m_position.y = DefPos.y - 650.0f;
		m_skinModelRender->PlayAnimation(enAnimationClip_PlaneToHuman, 0.5f);
	}
	else {
		bool flag = m_skinModelRender->IsPlayingAnimation(); //再生中でないなら終了する
		if (flag == false) {
			Teru_Mode = Human;
			m_stete = Estete_HumanMove;
			m_skinModelRender->PlayAnimation(enAnimationClip_HumanWait, 0.5f);
			AttackTimer = -1;
		}
	}

	AttackTimer++;

}

void Teruosuka::Teru_HumanMove() {

	//制限時間になったとき実行
	if (AttackTimer == AttackLimit) {
		int random = rand() % 2;
		if (random == 0) {//攻撃します
			m_stete = Estete_HumanAttackWait;
		}
		AttackTimer = -1;
	}
	AttackTimer++;

}

void Teruosuka::Teru_HumanAttackWait() {

	HumanColor += 0.5f;
	m_skinModelRender->SetEmissionColor({ HumanColor , 0.0f, 0.0f });

	if (AttackTimer > HumanAttackLimit) {
		m_stete = Estete_HumanAttack;
		m_skinModelRender->PlayAnimation(enAnimationClip_HumanAttack, 0.5f);
		AttackTimer = -1;
	}

	AttackTimer++;

}

void Teruosuka::Teru_HumanAttack() {

	HumanColor -= 20.0f;
	if (HumanColor < 0.0f) {
		HumanColor = 0.0f;
	}
	m_skinModelRender->SetEmissionColor({ HumanColor , 0.0f, 0.0f });


	bool flag = m_skinModelRender->IsPlayingAnimation(); //再生中でないなら終了する
	if (flag == false) {
		m_stete = Estete_HumanMove;
		m_skinModelRender->PlayAnimation(enAnimationClip_HumanWait, 0.5f);
	}
}

void Teruosuka::TeruDeath() {


	//ﾔﾗﾚﾀ･･･
	if (DeathTimer == 0) {
		//状態をリザルトに！
		GameData * gamedata = GameData::GetInstance();
		BossHPGage * bossHPGage = BossHPGage::GetInstance();
		gamedata->SetGameMode(GameData::Result);
		bossHPGage->DeleteGage();

		m_skinModelRender->SetEmissionColor({ 0.0f , 0.0f, 0.0f });

		m_skinModelRender->PlayAnimation(enAnimationClip_HumanDeath, 0.5f);

	}

	if (DeathTimer == 12) {
		//Effect再生
		EffectManager * effectmanager = EffectManager::GetInstance();
		effectmanager->EffectPlayer(EffectManager::Bakuhatu, m_position, { 500.0f,500.0f,500.0f });
	}
	if (DeathTimer == 70) {
		//Effect再生
		EffectManager * effectmanager = EffectManager::GetInstance();
		effectmanager->EffectPlayer(EffectManager::Bakuhatu, m_position, { 500.0f,500.0f,500.0f });
	}
	if (DeathTimer == 160) {
		//Effect再生
		EffectManager * effectmanager = EffectManager::GetInstance();
		effectmanager->EffectPlayer(EffectManager::Bakuhatu, m_position, { 500.0f,500.0f,500.0f });
	}
	if (DeathTimer == 230) {
		//Effect再生
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

void Teruosuka::TeruDeath2() {
	DeleteGO(this);
}
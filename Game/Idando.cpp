#include "stdafx.h"
#include "Idando.h"
#include "GameData.h"
#include "EffectManager.h"
#include "Kodan.h"
#include "StarComet_Inseki.h"

Idando::Idando()
{
}


Idando::~Idando()
{
	DeleteGO(m_skinModelRender);
}

bool Idando::Start() {
	//アニメーションクリップをロードとループフラグ。
	m_animClips[enAnimationClip_walk].Load(L"animData/Ida_Stay.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	//予備
	m_animClips[enAnimationClip_attack_yobi].Load(L"animData/Ida_Yobi.tka");
	//攻撃
	m_animClips[enAnimationClip_attack].Load(L"animData/Ida_Attack.tka");
	//終了
	m_animClips[enAnimationClip_attack_return].Load(L"animData/Ida_Return.tka");

	//スキンモデル
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Idando.cmo", m_animClips, enAnimationClip_Num);

	m_skinModelRender->SetPosition(m_position);

	m_scale = { 1.0f,1.0f,1.0f };
	m_charaCon.Init(
		45.0f,  //キャラクターの半径。
		10.0f,  //キャラクターの高さ。
		m_position //キャラクターの初期座標。
	);

	return true;
}

void Idando::Update() {
	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();
	if (mode != GameData::Pause) {

		switch (m_stete) {
		case Estete_Attack://攻撃
			EnemyAttack();
			break;
		case Estete_Move://移動
			EnemyMove();
			break;
		case Estete_return://終了
			EnemyReturn();
			break;
		case Estete_Death:
			EnemyDeath();//死
			break;
		case Estete_Death2:
			EnemyDeath2();//死
			break;
		case Estete_yobi:
			Enemyyobi();//予備動作
			break;
		}

	}

	//どうも隕石です
	QueryGOs<StarComet_Inseki>("StarComet_Inseki", [&](StarComet_Inseki* SCI) {
		CVector3 inseki_position = SCI->Getm_Position();
		CVector3 diff = inseki_position - m_position;
		float Langth_hoge = SCI->GetDamageLength();
		if (diff.Length() < Langth_hoge) { //隕石衝突
			SetDeath();//自分が死ぬ
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

void Idando::EnemyAttack() {
	if (timer == 0) {
		m_skinModelRender->PlayAnimation(enAnimationClip_attack);
	}
	bool flag = m_skinModelRender->IsPlayingAnimation(); //再生中でないなら終了する
	if (flag == false) {
		if (timer2 == 30) {
			timer = -1;
			timer2 = 0;
			m_stete = Estete_return;
		}
		timer2++;
	}

	timer++;
}

void Idando::EnemyMove() {

	if (timer == randomCount) {
		timer = -1;
		int random = rand() % 3;
		if (random == 0) {
			//攻撃します！
			m_stete = Estete_yobi;
		}
	}

	timer++;

}

void Idando::EnemyDeath() {
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

	//コダン召喚
	for (int i = 0; i < 3; i++) {
		Kodan*kodan = NewGO<Kodan>(0, "Kodan");
		CVector3 Pos = m_position;
		int PosHoge = rand() % 50;
		int random = rand() % 2;
		if (random == 1) {
			PosHoge *= -1;
		}
		Pos.x += (float)PosHoge;
		PosHoge = rand() % 50;
		random = rand() % 2;
		if (random == 1) {
			PosHoge *= -1;
		}
		Pos.z += (float)PosHoge;
		kodan->SetPosition(Pos);

		//モンスターの数を増やす！
		int X = gamedata->GetEnemyCounter();
		X++;
		gamedata->EnemyCounterSet(X);
	}

	DeleteGO(this);

}

void Idando::EnemyDeath2() {
	DeleteGO(this);

}

void Idando::Enemyyobi() {

	if (timer == 0) {
		m_skinModelRender->PlayAnimation(enAnimationClip_attack_yobi);
	}
	bool flag = m_skinModelRender->IsPlayingAnimation(); //再生中でないなら終了する
	if (flag == false) {
		timer = -1;
		m_stete = Estete_Attack;
	}

	timer++;

}

void Idando::EnemyReturn() {


	if (timer == 0) {
		m_skinModelRender->PlayAnimation(enAnimationClip_attack_return);
	}
	bool flag = m_skinModelRender->IsPlayingAnimation(); //再生中でないなら終了する
	if (flag == false) {
		m_skinModelRender->PlayAnimation(enAnimationClip_walk);
		timer = -1;
		m_stete = Estete_Move;
	}

	timer++;

}
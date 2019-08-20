#include "stdafx.h"
#include "Akoyadokari.h"
#include "GameData.h"
#include "EffectManager.h"
#include "StarComet_Inseki.h"

Akoyadokari::Akoyadokari()
{
}


Akoyadokari::~Akoyadokari()
{
	DeleteGO(m_skinModelRender);
}

bool Akoyadokari::Start() {
	//アニメーションクリップをロードとループフラグ。
	m_animClips[enAnimationClip_walk].Load(L"animData/AkoWalk.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	//予備
	m_animClips[enAnimationClip_attack1].Load(L"animData/AkoYobi.tka");
	//攻撃
	m_animClips[enAnimationClip_attack01].Load(L"animData/AkoAttack.tka");

	//スキンモデル
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Akoyadokari.cmo", m_animClips, enAnimationClip_Num);

	m_skinModelRender->SetPosition(m_position);

	m_scale = { 2.0f,2.0f,2.0f };
	m_charaCon.Init(
		45.0f,  //キャラクターの半径。
		10.0f,  //キャラクターの高さ。
		m_position //キャラクターの初期座標。
	);

	return true;
}

void Akoyadokari::Update() {
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

void Akoyadokari::EnemyAttack() {
	timer++;
	if (timer <= attackwait) {
		//攻撃アニメーション
		m_skinModelRender->PlayAnimation(enAnimationClip_attack01);

	}
	else {
		//通常状態に戻る
		timer = 0;
		m_stete = Estete_Move;
		m_skinModelRender->PlayAnimation(enAnimationClip_walk, 0.5f);
	}

}

void Akoyadokari::EnemyMove() {
	timer++;
	if (timer == randomCount) {
		random = rand() % 360;//ランダムで方向を決定
		m_rotation.SetRotation(CVector3::AxisY, (float)random);
		CVector3 sou_mae = { 0.0f, 0.0f,-1.0f };
		m_rotation.Multiply(sou_mae);
		moveVec = sou_mae * randomSpeed;
		movecount++;
		timer = 0;
	}
	else if (movecount >1) {
		m_stete = Estete_yobi;
		movecount = 0;
		timer = 0;
	}
	m_position = m_charaCon.Execute(moveVec);
}

void Akoyadokari::EnemyDeath() {
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

void Akoyadokari::EnemyDeath2() {
	DeleteGO(this);

}

void Akoyadokari::Enemyyobi() {
	//予備動作
	timer++;
	if (timer <= yobiwait) {
		m_skinModelRender->PlayAnimation(enAnimationClip_attack1);
	}
	else {
		timer = 0;
		m_stete = Estete_Attack;
	}

}

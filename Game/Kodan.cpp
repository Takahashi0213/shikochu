#include "stdafx.h"
#include "Kodan.h"
#include "GameData.h"
#include "EffectManager.h"
#include "StarComet_Inseki.h"

Kodan::Kodan()
{
}


Kodan::~Kodan()
{
	DeleteGO(m_skinModelRender);
}

bool Kodan::Start() {

	//アニメーションクリップをロードとループフラグ。
	m_animClips[enAnimationClip_walk].Load(L"animData/Kodan_Walk.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Kodan.cmo", m_animClips, enAnimationClip_Num);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);

	m_charaCon.Init(
		0.0f,  //キャラクターの半径。
		0.0f,  //キャラクターの高さ。
		m_position //キャラクターの初期座標。
	);

	return true;
}

void Kodan::Update() {

	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();
	if (mode != GameData::Pause) {

		switch (m_stete)
		{
		case Estete_Move:
			Move();
			break;
		case Estete_Death:
			Death();
			break;
		case Estete_Death2:
			Death2();
			break;
		}

		if (C_timer == 30) {
			m_charaCon.SetRadius(30.0f);
			m_charaCon.SetHeight(10.0f);
		}

		C_timer++;
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

void Kodan::Move() {

	if (timer == 0) {
		int random = rand() % 360;//ランダムで方向を決定
		m_rotation.SetRotation(CVector3::AxisY, (float)random);
		CVector3 Aru_mae = { 0.0f, 0.0f,1.0f };
		m_rotation.Multiply(Aru_mae);
		moveVec = Aru_mae * randomSpeed;
	}
	else if (timer == randomcount) {
		timer = -1;
	}
	m_position = m_charaCon.Execute(moveVec);

	timer++;

}

void Kodan::Death() {
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

void Kodan::Death2() {
	DeleteGO(this);
}
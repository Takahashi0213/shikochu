#include "stdafx.h"
#include "Kikochu.h"
#include "GameData.h"
#include "EffectManager.h"
#include "StarComet_Inseki.h"

Kikochu::Kikochu()
{
}


Kikochu::~Kikochu()
{
	DeleteGO(m_skinModelRender);
}

bool Kikochu::Start() {

	//アニメーションクリップをロードとループフラグ。
	m_animClips[enAnimationClip_walk].Load(L"animData/KikoWalk.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Kikochu.cmo", m_animClips, enAnimationClip_Num);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);

	m_charaCon.Init(
		45.0f,  //キャラクターの半径。
		10.0f,  //キャラクターの高さ。
		m_position //キャラクターの初期座標。
	);

	return true;
}

void Kikochu::Update() {

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

void Kikochu::Move() {

	timer++;
	EF_timer++;
	if (timer == randomcount) {
		int random = rand() % 360;//ランダムで方向を決定
		m_rotation.SetRotation(CVector3::AxisY, (float)random);
		CVector3 Aru_mae = { 0.0f, 0.0f,1.0f };
		m_rotation.Multiply(Aru_mae);
		moveVec = Aru_mae * randomSpeed;
		timer = 0;
	}

	if (EF_timer == Ef_Limit) { //光エフェクトを表示する
		EffectManager * effectmanager = EffectManager::GetInstance();
		CVector3 ef_position = m_position;
		effectmanager->EffectPlayer(EffectManager::star, ef_position, SpawnEffectScale / 2);
		effectmanager->EffectPlayer(EffectManager::star, ef_position, SpawnEffectScale / 2);
		effectmanager->EffectPlayer(EffectManager::star, ef_position, SpawnEffectScale / 2);
		effectmanager->EffectPlayer(EffectManager::star, ef_position, SpawnEffectScale / 2);
		EF_timer = 0;
	}

	m_position = m_charaCon.Execute(moveVec);

}

void Kikochu::Death() {

	prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
	ss->Init(L"sound/E_death.wav");
	ss->SetVolume(1.0f);
	ss->Play(false);

	EffectManager * effectmanager = EffectManager::GetInstance();
	CVector3 EF_Position = m_position;
	EF_Position.y += 50.0f;
	effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f }, false, false);

	//キコウチュウフラグをオンに
	GameData * gamedata = GameData::GetInstance();
	gamedata->SetKikoFlag();

	DeleteGO(this);
}

void Kikochu::Death2() {
	DeleteGO(this);
}
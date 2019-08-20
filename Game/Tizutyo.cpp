#include "stdafx.h"
#include "Tizutyo.h"
#include "GameData.h"
#include "Player.h"
#include "Bullet5.h"
#include "EffectManager.h"
#include "StarComet_Inseki.h"

Tizutyo::Tizutyo()
{
}


Tizutyo::~Tizutyo()
{
	DeleteGO(m_skinModelRender);
}

bool Tizutyo::Start() {
	//アニメーションクリップをロードとループフラグ。
	m_animClips[enAnimationClip_walk].Load(L"animData/Tizutyo.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);

	//スキンモデル
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Tizutyo.cmo", m_animClips, enAnimationClip_Num);
	m_skinModelRender->SetForwardRenderFlag(true);

	m_scale = { 2.0f,2.0f,2.0f };
	m_charaCon.Init(
		45.0f,  //キャラクターの半径。
		10.0f,  //キャラクターの高さ。
		m_position //キャラクターの初期座標。
	);

	return true;
}

void Tizutyo::NeoAttack() {

	//遠距離やでで
	movetimer++;
	if (bulletFlag == false) {
		Bullet5* bullet5 = NewGO<Bullet5>(0, "bullet5");
		bullet5->Init(this);
		bulletFlag = true;
	}
	else {
		CVector3 enemyForward = { 0.0f, 0.0f, 1.0f };
		//プレイヤーの向きに回転
		Player * player = Player::GetInstance();
		CVector3 P_Position = player->Getm_Position();
		CVector3 diff = P_Position - m_position;
		neoVec = diff;
		diff.y = 0.0f;
		diff.Normalize();
		CQuaternion qRot;
		qRot.SetRotation(enemyForward, diff);
		m_rotation = qRot;
	}

	if (movetimer == 30) {
		Bullet5* bullet5 = NewGO<Bullet5>(0, "bullet5");
		bullet5->Init(this);
	}

	if (movetimer == 60) {
		Bullet5* bullet5 = NewGO<Bullet5>(0, "bullet5");
		bullet5->Init(this);
	}

	if (movetimer > 60 && movetimer < move_starttimer) {
		colorcount -= 1.0f;
		if (colorcount < 0.0f) {
			colorcount = 0.0f;
		}
		m_skinModelRender->SetEmissionColor({ 0.0f , colorcount, colorcount });
	}
	else if (movetimer >= move_starttimer) {
		count = 0;
		timer = 0;
		movetimer = 0;
		m_stete = Estete_Move;
	}

}
void Tizutyo::NeoYobi() {

	CVector3 enemyForward = { 0.0f, 0.0f, 1.0f };
	//プレイヤーの向きに回転
	Player * player = Player::GetInstance();
	CVector3 P_Position = player->Getm_Position();
	CVector3 diff = P_Position - m_position;
	neoVec = diff;
	diff.y = 0.0f;
	diff.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, diff);
	m_rotation = qRot;

	//予備動作で色が変化すっっっるよ
	if (colorflag == false) {
		//明るく
		colortimer++;
		if (colortimer == 1) {
			colorcount += 0.5f;
			colortimer = 0;
			if (colorcount < 30.0f) {
				m_skinModelRender->SetEmissionColor({ 0.0f , colorcount, colorcount });
			}
			else {
				colorflag = true;
			}
		}
	}
	else {
		m_stete = Estete_Attack;
	}
}
void Tizutyo::NeoMove() {
	//移動中
	Player * player = Player::GetInstance();
	CVector3 P_Position = player->Getm_Position();
	CVector3 diff = P_Position - m_position;
	neoVec = diff;
	if (diff.Length() < followstop) {
		//停止距離
		moveVec = neoVec * Speed;
	}
	else {
		//追いかけるよ!
		neoVec.Normalize();
		moveVec = neoVec * followSpeed;

	}
	if (diff.Length() < followleave) {
		//近いよyo離れるyo!
		neoVec.Normalize();
		moveVec = neoVec * followSpeed * -1.0f;
	}
	//ランダムな時間で攻撃するヨ
	if (count == 0) {
		random = rand() % 7;
		if (random >= 4) {
			count = 1;
		}
		random = random * time;//ランダム時間
	}
	timer++;
	if (timer > random) {
		EffectManager * effectmanager = EffectManager::GetInstance();
		CVector3 EF_Position = m_position;
		EF_Position.y += 50.0f;
		effectmanager->EffectPlayer_Post(EffectManager::BulletYobi, EF_Position, { 40.0f,40.0f,40.0f });

		bulletFlag = false;
		colorflag = false;
		m_stete = Estete_Yobi;
	}

	CVector3 enemyForward = { 0.0f, 0.0f, 1.0f };
	//プレイヤーの向きに回転
	diff.y = 0.0f;
	diff.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, diff);
	m_rotation = qRot;
	m_position = m_charaCon.Execute(moveVec);
}
void Tizutyo::NeoDeath() {

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


void Tizutyo::Update() {

	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();
	if (mode != GameData::Pause) {

		switch (m_stete) {
		case Estete_Attack://攻撃
			NeoAttack();
			break;
		case Estete_Yobi://予備動作
			NeoYobi();
			break;
		case Estete_Move://移動
			NeoMove();
			break;
		case Estete_Death:
			NeoDeath();//死
			break;
		case Estete_Death2:
			NeoDeath2();//死
			break;
		}

		if (dathflag == true) {
			DeleteGO(this);
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

void Tizutyo::NeoDeath2() {
	DeleteGO(this);
}
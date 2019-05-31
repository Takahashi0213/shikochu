#include "stdafx.h"
#include "Riritto.h"
#include "GameData.h"
#include "Player.h"
#include "Bullet2.h"
#include "EffectManager.h"


Riritto::Riritto()
{
}


Riritto::~Riritto()
{
	DeleteGO(m_skinModelRender);
}

bool Riritto::Start() {

	//アニメーションクリップをロードとループフラグ。
	m_animClips[enAnimationClip_walk].Load(L"animData/Ririwalk.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);

	//スキンモデル
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Riritto.cmo", m_animClips, enAnimationClip_Num);
	m_skinModelRender->SetForwardRenderFlag(true);

	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);

	m_charaCon.Init(
		45.0f,  //キャラクターの半径。
		10.0f,  //キャラクターの高さ。
		m_position //キャラクターの初期座標。
	);

	return true;
}
void Riritto::RiAttack() {
	//遠距離やでで
	movetimer++;
	if (bulletFlag == false) {
		Bullet2* bullet2 = NewGO<Bullet2>(0, "bullet2");
		bullet2->Init(this);
		bulletFlag = true;
	}
	else if (movetimer < move_starttimer) {
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
void Riritto::RiYobi() {
	//予備動作で色が変化すっっっるよ
	if (colorflag == false) {
		//明るく
		colortimer++;
		if (colortimer == 1) {
			colorcount += 1.0f;
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
void Riritto::RiMove() {
	//移動中
	Player * player = Player::GetInstance();
	CVector3 P_Position = player->Getm_Position();
	CVector3 diff = P_Position - m_position;
	RiVec = diff;
	if (diff.Length() < followstop) {
		//停止距離
		moveVec = RiVec * Speed;
	}
	else {
		//追いかけるよ!
		RiVec.Normalize();
		moveVec = RiVec * followSpeed;

	}
	if (diff.Length() < followleave) {
		//近いよyo離れるyo!
		RiVec.Normalize();
		moveVec = RiVec * followSpeed * -1.0f;
	}
	//ランダムな時間で攻撃するヨ
	if (count == 0) {
		random = rand() % 8;
		if (random >= 2) {
			count = 1;

		}
		random = random * time;//ランダム時間
	}
	timer++;
	if (timer > random) {
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
void Riritto::RiDeath() {
	prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
	ss->Init(L"sound/E_death.wav");
	ss->SetVolume(1.0f);
	ss->Play(false);

	EffectManager * effectmanager = EffectManager::GetInstance();
	CVector3 EF_Position = m_position;
	EF_Position.y += 50.0f;
	effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });

	GameData * gamedata = GameData::GetInstance();
	gamedata->EnemyCounterGensyou();
	DeleteGO(this);
}
void Riritto::Update() {
	switch (m_stete) {
	case Estete_Attack://攻撃
		RiAttack();
		break;
	case Estete_Yobi://予備動作
		RiYobi();
		break;
	case Estete_Move://移動
		RiMove();
		break;
	case Estete_Death:
	RiDeath();//死
	break;
	case Estete_Death2:
		RiDeath2();//死
		break;	
	}

	if (dathflag == true) {
		DeleteGO(this);
	}

	//移動
	m_skinModelRender->SetPosition(m_position);
	//回転
	m_skinModelRender->SetRotation(m_rotation);
	//拡大率
	m_skinModelRender->SetScale(m_scale);

}

void Riritto::RiDeath2() {
	DeleteGO(this);
}
#include "stdafx.h"
#include "Neoriku.h"
#include "GameData.h"
#include "Player.h"
#include "Bullet.h"
#include "EffectManager.h"

Neoriku::Neoriku()
{
}


Neoriku::~Neoriku()
{
	DeleteGO(m_skinModelRender);
}

bool Neoriku::Start() {
	//アニメーションクリップをロードとループフラグ。
	m_animClips[enAnimationClip_walk].Load(L"animData/Neowalk.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);

	//スキンモデル
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/neoriku_0.cmo", m_animClips, enAnimationClip_Num);
	m_skinModelRender->SetForwardRenderFlag(true);

	m_scale = { 2.0f,2.0f,2.0f };
	m_charaCon.Init(
		35.0f,  //キャラクターの半径。
		10.0f,  //キャラクターの高さ。
		m_position //キャラクターの初期座標。
	);


	return true;
}

void Neoriku::NeoAttack() {
	//遠距離やでで
	movetimer++;
	if (bulletFlag == false) {
		Bullet* bullet = NewGO<Bullet>(0,"bullet");
		bullet->Init(this);
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
void Neoriku::NeoYobi() {
	//予備動作で色が変化すっっっるよ
	if (colorflag == false) {
		//明るく
		colortimer++;
		if (colortimer == 1) {
			colorcount+=1.0f;
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
void Neoriku::NeoMove() {
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

	CVector3 enemyForward = { -1.0f, 0.0f, 0.0f };
	//プレイヤーの向きに回転
	diff.y = 0.0f;
	diff.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, diff);
	m_rotation = qRot;
	m_position = m_charaCon.Execute(moveVec);

}
void Neoriku::NeoDeath() {

	EffectManager * effectmanager = EffectManager::GetInstance();
	CVector3 EF_Position = m_position;
	EF_Position.y += 50.0f;
	effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });

	GameData * gamedata = GameData::GetInstance();
	gamedata->EnemyCounterGensyou();
	DeleteGO(this);
}


void Neoriku::Update() {
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



#include "stdafx.h"
#include "Morikon.h"
#include "GameData.h"
#include "Player.h"
#include "EffectManager.h"
#include "StarComet_Inseki.h"

Morikon::Morikon()
{
}


Morikon::~Morikon()
{
	DeleteGO(m_skinModelRender);
}

bool Morikon::Start() {
	//アニメーション
	m_animClips[enAnimationClip_walk].Load(L"animData/Mori_idel.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	m_animClips[enAnimationClip_attack].Load(L"animData/Mori_attack.tka");


	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Bat_Level_1.cmo", m_animClips, enAnimationClip_Num);
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
void Morikon::Momove() {

	if (m_stete == Estete_Move) {
		//steteがmoveのときは歩きアニメーション
		m_skinModelRender->PlayAnimation(enAnimationClip_walk);

	}

	Player * player = Player::GetInstance();
	CVector3 P_Position = player->Getm_Position();
	CVector3 diff = P_Position - m_position;
	MoriVec = diff;
	if (diff.Length() < followstop) {
		//停止距離
		moveVec = MoriVec * Speed;
	}
	else {
		//追いかけるよ!
		MoriVec.Normalize();
		moveVec = MoriVec * followSpeed;

	}
	if (diff.Length() < followleave) {
		//近いよyo離れるyo!
		MoriVec.Normalize();
		moveVec = MoriVec * followSpeed * -1.0f;
	}
	//ランダムな時間で攻撃するヨ
	if (count == 0) {
		random = rand() % 6;
		if (random >= 2) {
			count = 1;

		}
		random = random * time;//ランダム時間
	}
	timer++;
	if (timer > random) {
		m_stete = Estete_Follow;
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
void Morikon::Mofollow()
{		
	Player * player = Player::GetInstance();

	//追尾状態	
	CVector3 P_Position = player->Getm_Position();
	CVector3 diff = P_Position - m_position;
	moveVec = diff;
	moveVec.Normalize();
	moveVec *= followSpeed;
	if (diff.Length() < attackRange) {
		//攻撃するよ
		if (attackmoveflag == false) {
			attackVec = diff;
			attackVec.Normalize();
			attackVec *= attackMoveRange;
			attackmoveflag = true;
		}
		attacktimer = 0;
		m_stete = Estete_Attack;
	}
	m_position = m_charaCon.Execute(moveVec);

}
void Morikon::Moattack()
{
	attacktimer++;
	if (attacktimer <= attacktime) {
		//攻撃アニメーション
		m_skinModelRender->PlayAnimation(enAnimationClip_attack);
		m_position = m_charaCon.Execute(attackVec);

	}
	else {
		//通常状態に戻る
		attackmoveflag = false;
		timer = 0;
		count = 0;
		m_stete = Estete_Move;
	}

}

void Morikon::Modeath() {
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
void Morikon::Update() {

	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();
	if (mode != GameData::Pause) {

		switch (m_stete) {
		case Estete_Move://移動
			Momove();
			break;
		case Estete_Follow://追尾
			Mofollow();
			break;
		case Estete_Attack://攻撃
			Moattack();
			break;
		case Estete_Death:
			Modeath();//死
			break;
		case Estete_Death2:
			Modeath2();//死
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

void Morikon::Modeath2() {
	DeleteGO(this);
}
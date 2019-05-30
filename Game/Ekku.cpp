#include "stdafx.h"
#include "Ekku.h"
#include "GameData.h"
#include "Player.h"
#include "EffectManager.h"



Ekku::Ekku()
{
}


Ekku::~Ekku()
{
	DeleteGO(m_skinModelRender);
}
bool Ekku::Start() {

	m_animClips[enAnimationClip_walk].Load(L"animData/Ekwalk.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	//予備
	m_animClips[enAnimationClip_attack].Load(L"animData/Ekattack.tka");
	//攻撃
	m_animClips[enAnimationClip_yobi].Load(L"animData/Ekyobi.tka");

	//スキンモデル

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Ekku.cmo", m_animClips, enAnimationClip_Num);
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

void Ekku::EkAttack() {
	timer++;
	if (timer <= attackwait) {
		//攻撃アニメーション
		m_skinModelRender->PlayAnimation(enAnimationClip_attack);
		m_position = m_charaCon.Execute(attackVec);

	}
	else {
		//通常状態に戻る
		timer = 0;
		keisannflag = false;
		m_stete = Estete_Move;
	}
}
void Ekku::EkMove(){
	Player * player = Player::GetInstance();
	//通常状態
	CVector3 P_Position = player->Getm_Position();
	CVector3 diff = P_Position - m_position;

	count++;

	if (count == randomCount) {
		random = rand() % 360;//ランダムで方向を決定
		m_rotation.SetRotation(CVector3::AxisY, (float)random);
		CVector3 ekku_mae = { -1.0f, 0.0f,0.0f };
		m_rotation.Multiply(ekku_mae);
		moveVec = ekku_mae * randomSpeed;
		count = 0;
	}

	else if (diff.Length() < followRange) {
		//距離が近いので追尾する。
		m_stete = Estete_Follow;
	}
	if (m_stete == Estete_Move) {
		//steteがmoveのときは歩きアニメーション
		m_skinModelRender->PlayAnimation(enAnimationClip_walk);

	}
	m_position = m_charaCon.Execute(moveVec);

}
void Ekku::EkFollow(){
	Player * player = Player::GetInstance();

	//追尾状態	
	CVector3 P_Position = player->Getm_Position();
	CVector3 diff = P_Position - m_position;
	enemyVec = diff;

	if (diff.Length() < followRange) {
		//近づく
		enemyVec.Normalize();
		enemyVec *= followSpeed;
	}
	else {
		//その場で移動
		m_stete = Estete_Move;
	}

	if (diff.Length() < attackRange) {
		//予備動作
		m_stete = Estete_Yobi;
	}

	if (m_stete == Estete_Follow) {
		//steteがfollowのときも歩きアニメーション
		m_skinModelRender->PlayAnimation(enAnimationClip_walk);

	}

	CVector3 enemyForward = { -1.0f, 0.0f, 0.0f };

	//　向かせたい方向のベクトルを計算する。
	CVector3 targetVector = P_Position - m_position;
	//　Y成分は除去して正規化する。Y成分を入れると空を向いたりするよ。
	targetVector.y = 0.0f;
	targetVector.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, targetVector);
	m_rotation = qRot;
	m_position = m_charaCon.Execute(enemyVec);

}
void Ekku::EkDeath(){
	prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
	ss->Init(L"sound/E_death.wav");
	ss->SetVolume(0.5f);
	ss->Play(false);

	EffectManager * effectmanager = EffectManager::GetInstance();
	CVector3 EF_Position = m_position;
	EF_Position.y += 50.0f;
	effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });

	GameData * gamedata = GameData::GetInstance();
	gamedata->EnemyCounterGensyou();
	DeleteGO(this);
}
void Ekku::Ekyobi() {
	//予備動作
	if (keisannflag == false) {
		Player * player = Player::GetInstance();
		CVector3 P_Position = player->Getm_Position();
		CVector3 diff = P_Position - m_position;
		attackVec = diff;
		attackVec.Normalize();
		attackVec *= attackMoveRange;
		keisannflag = true;
	}
	timer++;
	if (timer <= yobiwait) {
		m_skinModelRender->PlayAnimation(enAnimationClip_yobi);
	}
	else {
		m_stete = Estete_Attack;

	}

}
void Ekku::Update() {
	switch (m_stete) {
	case Estete_Attack://攻撃
		EkAttack();
		break;
	case Estete_Move://移動
		EkMove();
		break;
	case Estete_Follow://追尾
		EkFollow();
		break;
	case Estete_Death:
		EkDeath();//死
		break;
	case Estete_Yobi:
		Ekyobi();//予備動作
		break;
	}

	//移動
	m_skinModelRender->SetPosition(m_position);
	//回転
	m_skinModelRender->SetRotation(m_rotation);
	//拡大率
	m_skinModelRender->SetScale(m_scale);
	

}
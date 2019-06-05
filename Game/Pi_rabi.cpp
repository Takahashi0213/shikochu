#include "stdafx.h"
#include "Pi_rabi.h"
#include "GameData.h"
#include "Player.h"
#include "EffectManager.h"


Pi_rabi::Pi_rabi()
{
}


Pi_rabi::~Pi_rabi()
{
	DeleteGO(m_skinModelRender);
}

bool Pi_rabi::Start() {
	//アニメーション
	m_animClips[enAnimationClip_walk].Load(L"animData/P_idel.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	m_animClips[enAnimationClip_attack].Load(L"animData/P_attack.tka");

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Rabbit_Level_1.cmo", m_animClips, enAnimationClip_Num);
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

void Pi_rabi::PiMove() {
	timer++;
	if (timer == randomCount) {
		random = rand() % 360;//ランダムで方向を決定
		m_rotation.SetRotation(CVector3::AxisY, (float)random);
		CVector3 sou_mae = { 0.0f, 0.0f,1.0f };
		m_rotation.Multiply(sou_mae);
		moveVec = sou_mae * randomSpeed;
		movecount++;
		timer = 0;
	}
	else if (movecount >3) {
		//攻撃するよよ
		Player * player = Player::GetInstance();
		CVector3 P_Position = player->Getm_Position();
		diff = P_Position - m_position;
		attackVec = diff;
		attackVec.Normalize();

		m_stete = Estete_Follow;
	}
	if (m_stete == Estete_Move) {
		//steteがmoveのときは歩きアニメーション
		m_skinModelRender->PlayAnimation(enAnimationClip_walk);

	}

	m_position = m_charaCon.Execute(moveVec);

}
void Pi_rabi::Piattack() {
	attacktimer++;
	if (attacktimer <= attacktime) {
		//攻撃アニメーション
		m_skinModelRender->PlayAnimation(enAnimationClip_attack);
		m_position = m_charaCon.Execute(attackVec);

	}
	else if (attacktimer >= attacktime) {
		//逃げるよよ
		moveVec = diff;
		moveVec.Normalize();
		moveVec *= fleeSpeed;
		m_skinModelRender->PlayAnimation(enAnimationClip_walk);
	}
	if (attacktimer >= attackend) {
		//移動状態に戻る
		movecount = 0;
		attackmoveflag = false;
		m_stete = Estete_Move;
	}
	m_position = m_charaCon.Execute(moveVec);

}

void Pi_rabi::PiFollow() {

	Player * player = Player::GetInstance();

	//追尾状態	
	CVector3 P_Position = player->Getm_Position();
	moveVec = diff;
	moveVec.Normalize();
	moveVec *= followSpeed;

	if (diff.Length() < followRange) {
		//近くなったら攻撃するよ
		if (attackmoveflag == false) {
			attackVec = diff;
			attackVec.Normalize();
			attackVec *= attackMoveRange;
			attackmoveflag = true;
		}
		attacktimer = 0;
		m_stete = Estete_Attack;
	}

	CVector3 enemyForward = { 0.0f, 0.0f, 1.0f };

	//　向かせたい方向のベクトルを計算する。
	CVector3 targetVector = P_Position - m_position;
	//　Y成分は除去して正規化する。Y成分を入れると空を向いたりするよ。
	targetVector.y = 0.0f;
	targetVector.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, targetVector);
	m_rotation = qRot;
	m_position = m_charaCon.Execute(moveVec);

}

void Pi_rabi::PiDeath() {
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


void Pi_rabi::Update() {

	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();
	if (mode != GameData::Pause) {

		switch (m_stete)
		{
		case Estete_Attack:
			Piattack();
			break;
		case Estete_Move:
			PiMove();
			break;
		case Estete_Follow:
			PiFollow();
			break;
		case Estete_Death:
			PiDeath();
			break;
		case Estete_Death2:
			PiDeath2();
			break;
		}
	}
	//移動
	m_skinModelRender->SetPosition(m_position);
	//回転
	m_skinModelRender->SetRotation(m_rotation);
	//拡大率
	m_skinModelRender->SetScale(m_scale);

}

void Pi_rabi::PiDeath2() {
	DeleteGO(this);
}
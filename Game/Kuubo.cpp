#include "stdafx.h"
#include "Kuubo.h"
#include "GameData.h"
#include "Player.h"
#include "EffectManager.h"
#include "StarComet_Inseki.h"

Kuubo::Kuubo()
{
}


Kuubo::~Kuubo()
{
	DeleteGO(m_skinModelRender);
}

bool Kuubo::Start()
{
	//アニメーションクリップをロードとループフラグ。
	m_animClips[enAnimationClip_walk].Load(L"animData/KuuboWalk.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	//攻撃
	m_animClips[enAnimationClip_attack1].Load(L"animData/KuuboAttack.tka");

	//スキンモデル
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Kuubo.cmo", m_animClips, enAnimationClip_Num);

	m_skinModelRender->SetPosition(m_position);

	m_scale = { 1.5f,1.5f,1.5f };
	m_charaCon.Init(
		45.0f,  //キャラクターの半径。
		10.0f,  //キャラクターの高さ。
		m_position //キャラクターの初期座標。
	);

	return true;
}
void Kuubo::EnemyAttack()
{

	timer++;
	if (timer <= attackwait) {
		//攻撃アニメーション
		m_position = m_charaCon.Execute(attackVec);

	}
	else {
		//通常状態に戻る
		timer = 0;
		keisannflag = false;
		m_stete = Estete_Move;
		m_skinModelRender->PlayAnimation(enAnimationClip_walk, 0.5f);
	}

}

void Kuubo::EnemyMove()
{
	Player * player = Player::GetInstance();
	//通常状態
	CVector3 P_Position = player->Getm_Position();
	CVector3 diff = P_Position - m_position;

	count++;

	if (count == randomCount) {
		random = rand() % 360;//ランダムで方向を決定
		m_rotation.SetRotation(CVector3::AxisY, (float)random);
		CVector3 musi_mae = { 1.0f, 0.0f,0.0f };
		m_rotation.Multiply(musi_mae);
		moveVec = musi_mae * randomSpeed;
		count = 0;
	}

	else if (diff.Length() < followRange) {
		//距離が近いので追尾する。
		m_stete = Estete_Follow;
	}
	if (m_stete == Estete_Move) {
		//steteがmoveのときは歩きアニメーション
		m_skinModelRender->PlayAnimation(enAnimationClip_walk, 0.5f);

	}
	m_position = m_charaCon.Execute(moveVec);

}
void Kuubo::EnemyFollow()
{
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
		m_stete = Estete_yobi;
	}
	//回転の処理
	if (fabsf(enemyVec.x) < 0.001f
		&& fabsf(enemyVec.z) < 0.001f) {
		//わからん
		return;
	}

	if (m_stete == Estete_Follow) {
		//steteがfollowのときは歩きアニメーション
		m_skinModelRender->PlayAnimation(enAnimationClip_walk);

	}

	CVector3 enemyForward = { 0.0f, 0.0f, -1.0f };

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
void Kuubo::EnemyDeath()
{
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
void Kuubo::Enemyyobi() {

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

	if (timer == 0) {
		m_skinModelRender->PlayAnimation(enAnimationClip_attack1, 0.5f);
	}
	else if (timer >= yobiwait) {
		timer = 0;
		m_stete = Estete_Attack;
	}

	timer++;

}
void Kuubo::Update()
{

	if (SpawnWaitTimer > SpawnMaxWait) {

		GameData * gamedata = GameData::GetInstance();
		int mode = gamedata->GetGameMode();
		if (mode != GameData::Pause && mode != GameData::Tutorial) {

			switch (m_stete) {
			case Estete_Attack://攻撃
				EnemyAttack();
				break;
			case Estete_Move://移動
				EnemyMove();
				break;
			case Estete_Follow://追尾
				EnemyFollow();
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

	}
	SpawnWaitTimer++;

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

void Kuubo::EnemyDeath2() {
	DeleteGO(this);
}
#include "stdafx.h"
#include "Taidol.h"
#include "GameData.h"
#include "Player.h"
#include "EffectManager.h"
#include "StarComet_Inseki.h"

Taidol::Taidol()
{
}


Taidol::~Taidol()
{
	DeleteGO(m_skinModelRender);
}

bool Taidol::Start()
{
	//アニメーションクリップをロードとループフラグ。
	m_animClips[enAnimationClip_walk].Load(L"animData/Taidol.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	//予備
	m_animClips[enAnimationClip_attack].Load(L"animData/Taidol_Stay.tka");

	//スキンモデル
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Taidol.cmo", m_animClips, enAnimationClip_Num);

	m_skinModelRender->SetPosition(m_position);

	m_scale = { 1.0f,1.0f,1.0f };
	m_charaCon.Init(
		45.0f,  //キャラクターの半径。
		10.0f,  //キャラクターの高さ。
		m_position //キャラクターの初期座標。
	);

	return true;
}
void Taidol::EnemyAttack()
{
	//ドッカーン！！！！
	if (timer == 0) {//アタックレンジ
		DamageLength *= 2.0f;
		Color += 50.0f;
		EffectManager * effectmanager = EffectManager::GetInstance();
		CVector3 EF_Position = m_position;
		EF_Position.y += 80.0f;
		effectmanager->EffectPlayer(EffectManager::Bakuhatu, EF_Position, { 40.0f,40.0f,40.0f });
	}

	if (timer < attackwait/2) {
		Color += 30.0f;
	}
	else {
		Color -= 100.0f;
		if (Color < 0.0f) {
			Color = 0.0f;
		}
	}

	timer++;

	if (timer == attackwait) {//終里赤音
		timer = 0;
		m_stete = Estete_AttackEnd;
		DamageLength = DamageLengthDEF;
		Color = 0.0f;

	}
	m_skinModelRender->SetEmissionColor({ Color ,0.0f , 0.0f });

}

void Taidol::EnemyMove()
{
	Player * player = Player::GetInstance();
	//通常状態
	CVector3 P_Position = player->Getm_Position();
	CVector3 diff = P_Position - m_position;

	count++;

	if (count == randomCount) {
		random = rand() % 360;//ランダムで方向を決定
		m_rotation.SetRotation(CVector3::AxisY, (float)random);
		CVector3 musi_mae = { 0.0f, 0.0f,1.0f };
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
		m_skinModelRender->PlayAnimation(enAnimationClip_walk);

	}
	m_position = m_charaCon.Execute(moveVec);

}
void Taidol::EnemyFollow()
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

	CVector3 enemyForward = { 0.0f, 0.0f, 1.0f };

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
void Taidol::EnemyDeath()
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

void Taidol::Enemyyobi() {

	if (timer == 0) {//歩くのをやめる
		m_skinModelRender->PlayAnimation(enAnimationClip_attack);
	}

	if (timer > 30) {
		Color += 1.0f;
		m_skinModelRender->SetEmissionColor({ Color ,0.0f , 0.0f });
	}

	timer++;
	if (timer == yobiwait) {
		timer = 0;
		m_stete = Estete_Attack;
	}
}

void Taidol::EnemyAttackEnd() {

	CQuaternion RotationY;
	RotationY.SetRotationDeg(CVector3::AxisY, 10.0f);
	m_rotation *= RotationY;
	m_skinModelRender->SetRotation(m_rotation);

	timer++;
	if (timer == Endwait) {
		timer = 0;
		m_stete = Estete_Move;
	}

}

void Taidol::Update()
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
			case Estete_AttackEnd://攻撃終了
				EnemyAttackEnd();
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

void Taidol::EnemyDeath2() {
	DeleteGO(this);
}
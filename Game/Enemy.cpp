#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
	DeleteGO(m_skinModelRender);
}

bool Enemy::Start()
{
	//アニメーションクリップをロードとループフラグ。
	m_animClips[enAnimationClip_walk].Load(L"animData/walk.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	//予備
	m_animClips[enAnimationClip_attack1].Load(L"animData/attack_1.tka");
	//攻撃
	m_animClips[enAnimationClip_attack01].Load(L"animData/attack_01.tka");

	//m_animClips[enAnimationClip_attack1].SetLoopFlag(true);
	//スキンモデル
	m_skinModelRender=NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/bunbo-gu0.cmo", m_animClips, enAnimationClip_Num);
	//m_skinModelRender->PlayAnimation(enAnimationClip_walk);
	m_position = { 100.0f,0.0f,0.0f };
	m_skinModelRender->SetPosition(m_position);

	m_scale = { 2.0f,2.0f,2.0f };
	m_charaCon.Init(
		45.0f,  //キャラクターの半径。
		10.0f,  //キャラクターの高さ。
		m_position //キャラクターの初期座標。
	);

	
	return true;
}
void Enemy::EnemyAttack()
{
	Player * player = FindGO<Player>("Bug");

	timer++;
	if(timer <= attackwait){
		//攻撃アニメーション
		m_skinModelRender->PlayAnimation(enAnimationClip_attack01);

		CVector3 P_Position = player->Getm_Position();
		CVector3 diff = P_Position - m_position;

		diff.Normalize();
		diff *= 50;
		m_position = m_charaCon.Execute(diff);
	}
	else{
		//通常状態に戻る
		timer = 0;
		m_stete = Estete_Move;
	}

}

void Enemy::EnemyMove()
{
	Player * player = FindGO<Player>("Bug");

	//通常状態]
	CVector3 P_Position = player->Getm_Position();
	CVector3 diff = P_Position - m_position;
	CVector3 df = m_position - m_oldposition;

	moveVec.x = 50.0f * move;
	moveVec.y = 0.0f;
	moveVec.z = 0.0f;
	m_position.x += moveVec.x;
	if (m_stete == Estete_Move) {
		//steteがmoveのときは歩きアニメーション
		m_skinModelRender->PlayAnimation(enAnimationClip_walk);

	}
	//左右の移動
	if (df.x > rightmove) {
		//右移動
		move = -1;
	}
	else if (df.x < leftmove) {
		//左移動
		move = 1;
	}
	else if (diff.Length() < distancemove) {
		//距離が近いので追尾する。
		m_stete = Estete_Follow;
	}
	m_position = m_charaCon.Execute(moveVec);
}
void Enemy::EnemyFollow()
{
	Player * player = FindGO<Player>("Bug");

	//追尾状態	
	CVector3 P_Position = player->Getm_Position();
	CVector3 diff = P_Position - m_position;
	enemyVec = diff;

	if (diff.Length() < 600.0f) {
		//近づく
		enemyVec.Normalize();
		enemyVec *= 80;
	}
	else if (diff.Length() > 600.0f) {
		//その場で移動
		m_stete = Estete_Move;
	}
	 if (diff.Length() < 120.0f) {
		//予備動作
		m_stete = Estete_yobi;
	}
	 //回転の処理
	 if (fabsf(enemyVec.x) < 0.001f
		 && fabsf(enemyVec.z) < 0.001f) {
		 //わからん
		 return;
	 }
	 CVector3 enemyForward = { 1.0f, 0.0f, 0.0f };

	 //②　向かせたい方向のベクトルを計算する。
	 CVector3 targetVector = P_Position - m_position;
	 //③　Y成分は除去して正規化する。Y成分を入れると空を向いたりするよ。
	 targetVector.y = 0.0f;
	 targetVector.Normalize();
	 CQuaternion qRot;
	 qRot.SetRotation(enemyForward, targetVector);
	 m_rotation = qRot;
	 m_position = m_charaCon.Execute(enemyVec);

}
void Enemy::EnemyDeath()
{
	//死
}
void Enemy::Enemyyobi() {
	//予備動作
	timer++;
	if (timer <= yobiwait) {
		m_skinModelRender->PlayAnimation(enAnimationClip_attack1);
	}
	else {
		m_stete = Estete_Attack;
	}
}
void Enemy::Update()
	{

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
		case Estete_yobi:
			Enemyyobi();//予備動作
			break;
		}

	//移動
	m_skinModelRender->SetPosition(m_position);
	//回転
	m_skinModelRender->SetRotation(m_rotation);
	//拡大率
	m_skinModelRender->SetScale(m_scale);

}
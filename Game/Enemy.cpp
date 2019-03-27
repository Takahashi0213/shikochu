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
		30.0f,  //キャラクターの半径。
		30.0f,  //キャラクターの高さ。
		m_position //キャラクターの初期座標。
	);

	
	return true;
}
void Enemy::EnemyAttack()
{
	m_skinModelRender->PlayAnimation(enAnimationClip_attack1);
	timer++;
	CVector3 diff = player->position - m_position;
	 if(timer<=400){
		m_skinModelRender->PlayAnimation(enAnimationClip_attack01);
		attackk = 1;
	}
	else if (attackk <= 1) {
		m_stete = Estete_Move;
	}
}

void Enemy::EnemyMove()
{
	//通常状態
	CVector3 diff = player->position - m_position;
	CVector3 df = m_position - m_oldposition;

	moveVec.x = 50.0f * move;
	moveVec.y = 0.0f;
	moveVec.z = 0.0f;
	m_position.x += moveVec.x;
	if (m_position.x - m_oldposition.x > 200.0f) {
		move = -1;
	}
	else if (m_position.x - m_oldposition.x < -200.0f) {
		move = 1;
	}
	else if (diff.Length() < 600.0f) {
		m_stete = Estete_Follow;
	}
	m_position = m_charaCon.Execute(moveVec);
}
void Enemy::EnemyFollow()
{
	//追尾状態	
	CVector3 diff = player->position - m_position;
	CVector3 df = m_position - m_oldposition;


	enemyVec = diff;
	if (diff.Length() < 600.0f) {
		//近づく
		enemyVec.Normalize();
		enemyVec *= 150;
	}
	else if (diff.Length() > 400.0f) {
		//その場で移動
		m_stete = Estete_Move;
	}
	if (diff.Length() < 90.0f) {
		//攻撃
		m_stete = Estete_Attack;
	}

}
void Enemy::EnemyDeath()
{
	DeleteGO(this);
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
		}

	//移動
	m_skinModelRender->SetPosition(m_position);

	//回転
	m_skinModelRender->SetRotation(m_rotation);
	//拡大率
	m_skinModelRender->SetScale(m_scale);

}
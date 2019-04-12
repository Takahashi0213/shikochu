#pragma once
#include "Player.h"
class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();

	enum Estete {
		Estete_Attack,  //攻撃
		Estete_Move, //移動
		Estete_Follow, //追尾
		Estete_turn, //追尾
		Estete_Death, //死
		Estete_yobi	//予備動作
	};
	enum EnAnimationClip {
		enAnimationClip_walk, //歩き
		enAnimationClip_attack1, //動作1
		enAnimationClip_attack01, //攻撃1
		enAnimationClip_Num,  //アニメーションクリップ
	};
	bool Start();
	void Update();
	//状態
	void EnemyAttack();
	void EnemyMove();
	void EnemyFollow();
	void EnemyDeath();
	void Enemyyobi();
	//ポジションを返す関数
	CVector3 Enemy::Getm_Position(){
		return m_position;
	}
	//ステートを返す関数
	int Enemy::GetEState() {
		return m_stete;
	}
	//自分が死ぬ関数
	int Enemy::SetDeath() {
		m_stete = Estete_Death;
		return 0;
	}
private:

	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダラー。
	CVector3 m_position = CVector3::Zero; // 座標。
	CQuaternion m_rotation = CQuaternion::Identity; //回転。
	CVector3 m_scale = CVector3::One; // 拡大率。

	CVector3 moveVec;
	CVector3 enemyVec;
	Estete m_stete = Estete_Move;		 //状態
	CCharacterController m_charaCon; //キャラコン

	//移動関連
	const float followRange = 1000.0f; //追尾する距離（追尾を諦めるまでの距離）
	const float attackRange = 120.0f; //攻撃する距離
	const int followSpeed = 80; //追尾の速度

	//ランダム移動関連
	int count = 0; //ランダム移動のタイマー
	int random = 0; //ランダム移動の方向乱数
	const int randomCount = 60; //ランダム移動方向切り替えタイマー
	const float randomSpeed = 30.3f; //ランダム移動速度

	//攻撃関連
	int timer = 0; //攻撃のタイマー
	const int yobiwait = 50; //予備動作の時間
	const int attackwait = 120; //攻撃動作の時間
	const int attackMoveRange = 50; //攻撃時の前進距離と速度

};


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
		Estete_Death //死
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

private:
	Player * player = FindGO<Player>("Bug");

	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダラー。
	CVector3 m_position = CVector3::Zero; // 座標。
	CQuaternion m_rotation = CQuaternion::Identity; //回転。
	CVector3 m_scale = CVector3::One; // 拡大率。

	CVector3 m_oldposition;
	CVector3 moveVec;
	CVector3 enemyVec;
	int move = 1;
	int attackk = 0;
	Estete m_stete = Estete_Move;		 //状態
	CCharacterController m_charaCon; //キャラコン
	int timer = 0;
};


#pragma once
class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();

	enum Estete {
		Estete_Attack,  //攻撃
		Estete_Move, //移動
		Estete_Death //死
	};
	enum EnAnimationClip {
		enAnimationClip_walk, //歩き
		enAnimationClip_attack1, //攻撃1
		enAnimationClip_Num,  //アニメーションクリップ
	};
	enum Eattack {
		Eattack_0, //何もしない
		Eattack_1,
		Eattack_2,
		Eattack_3,
	};

	bool Start();
	void Update();
	//状態
	void EnemyAttack();
	void EnemyMove();
	void EnemyDeath();

private:
	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダラー。
	CVector3 m_position = CVector3::Zero; // 座標。
	CQuaternion m_rotation = CQuaternion::Identity; //回転。
	CVector3 m_scale = CVector3::One; // 拡大率。

	int attackcount = 0;
	Estete m_stete = Estete_Move;		 //状態
	Eattack m_attack = Eattack_1;		//攻撃
	CCharacterController m_charaCon; //キャラコン
	int timer = 0;
};


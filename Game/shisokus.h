#pragma once
class shisokus : public IGameObject
{
public:
	shisokus();
	~shisokus();

	enum Estete {
		Estete_Move,	//移動
		Estete_Attack1,  //攻撃1
		Estete_Yobi1,	//予備動作1
		Estete_Attack2,  //攻撃2
		Estete_Yobi2,	//予備動作2
		Estete_Death	 //死ﾇ

	};

	enum EnAnimationClip {
		enAnimationClip_move, //動作
		enAnimationClip_attack1, //攻撃1
		enAnimationClip_yobi1, //予備動作1
		/*enAnimationClip_attack2, //攻撃2
		enAnimationClip_yobi2, //予備動作2*/
		enAnimationClip_Num,  //アニメーションクリップ
	};

	bool Start();
	void Update();

	void shisoMove();
	void shisoYobi1();
	void shisoAttack1();
	void shisoYobi2();
	void shisoAttack2();
	void shisoDeath();

	CVector3 shisokus::Getm_Position() {
		return m_position;
	}
	//ステートを返す関数
	int shisokus::GetEState() {
		return m_stete;
	}
	//自分が死ぬ関数
	int shisokus::SetDeath() {
		m_stete = Estete_Death;
		return 0;
	}
private:
	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダラー。
	CVector3 m_position = CVector3::Zero; // 座標。
	CQuaternion m_rotation = CQuaternion::Identity; //回転。
	CVector3 m_scale = CVector3::One; // 拡大率。
	CVector3 shisoVec;

	Estete m_stete = Estete_Move; //状態
	CCharacterController m_charaCon; //キャラコン

	//移動関連
	const float yobi1Range = 1500.0f; //攻撃する距離

	//予備動作関連
	bool keisanflag = false;
	int yobitimer = 0;
	const float yobiwait = 60.0f;
	//攻撃関連


};


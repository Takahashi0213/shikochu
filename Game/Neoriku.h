#pragma once
class Neoriku : public IGameObject
{
public:
	Neoriku();
	~Neoriku();

	enum Estete {
		Estete_Attack,  //攻撃
		Estete_Move, //移動
		Estete_Death, //死
		Estete_yobi	//予備動作
	};

	enum EnAnimationClip {
		enAnimationClip_walk, //歩き
		enAnimationClip_move, //動作
		enAnimationClip_attack, //攻撃
		enAnimationClip_Num,  //アニメーションクリップ

	};

	bool Start();
	void Update();

	void NeoAttack();
	void NeoMove();
	void NeoDeath();
	void Neoyobi();

	CVector3 Neoriku::Getm_Position() {
		return m_position;
	}
	//ステートを返す関数
	int Neoriku::GetEState() {
		return m_stete;
	}
	//自分が死ぬ関数
	int Neoriku::SetDeath() {
		m_stete = Estete_Death;
		return 0;
	}
	//座標を設定。
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	//回転を設定。
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}


private:
	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダラー。
	CVector3 m_position = CVector3::Zero; // 座標。
	CQuaternion m_rotation = CQuaternion::Identity; //回転。
	CVector3 m_scale = CVector3::One; // 拡大率。

	CVector3 moveVec;
	CVector3 neoVec;

	Estete m_stete = Estete_Move; //状態
	CCharacterController m_charaCon; //キャラコン

	//移動関連
	const float followRange = 500.0f; //再度追尾する距離（追尾を諦めるまでの距離）
	const float followstop = 300.0f; //停止する距離(近いい）
	const float followSpeed = 30.0f; //追尾の速度
	const float Speed = 0.0f; //追尾の速度
	//予備動作関連
	int timer = 0; //攻撃開始までのタイマー
	int count = 0; //カウント


};


#pragma once
class Pi_rabi : public IGameObject
{
public:
	Pi_rabi();
	~Pi_rabi();

	enum Estete {
		Estete_Attack,  //攻撃
		Estete_Move, //移動
		Estete_Follow, //予備
		Estete_Death, //死
	};
	enum EnAnimationClip {
		enAnimationClip_walk, //歩き
		enAnimationClip_attack, //攻撃
		enAnimationClip_Num,  //アニメーションクリップ
	};

	bool Start();
	void Update();


	//ポジションを返す関数
	CVector3 Pi_rabi::Getm_Position() {
		return m_position;
	}
	//ステートを返す関数
	int Pi_rabi::GetEState() {
		return m_stete;
	}
	//自分が死ぬ関数
	int Pi_rabi::SetDeath() {
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
	//ダメージ範囲を教える関数
	float GetDamageLength() {
		return DamageLength;
	}
	//所属Waveをセット
	void SetWave(int x) {
		waveNo = x;
	}
	//所属Waveを返す
	int GetWave() {
		return waveNo;
	}
	
private:
	void Piattack();
	void PiMove();
	void PiFollow();
	void PiDeath();

	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダラー。
	CVector3 m_position = CVector3::Zero; // 座標。
	CQuaternion m_rotation = CQuaternion::Identity; //回転。
	CVector3 m_scale = { 30.0f,30.0f,30.0f }; // 拡大率。

	Estete m_stete = Estete_Move; //状態
	CCharacterController m_charaCon; //キャラコン

	//移動関連
	int movecount = 0;
	int random = 0;
	int timer = 0;
	const float randomCount = 90.0f;
	const float randomSpeed = 120.0f;
	CVector3 moveVec = CVector3::Zero;
	CVector3 attackVec = CVector3::Zero;
	CVector3 diff = CVector3::Zero;
	//追尾関連
	const float followRange = 300.0f; //追尾する距離（追尾を諦めるまでの距離）
	const float followSpeed = 60.0f; //追尾の速度
	const float fleeSpeed = 120.0f; //追尾の速度
	bool attackmoveflag = false;
	const float attackMoveRange = 240.0f; //攻撃時の前進距離と速度
	//攻撃関連
	int attacktimer = 0; //攻撃開始までのタイマー
	const float attackend = 150.0f; //追尾の速度
	const float attacktime = 40.0f;




	const float DamageLength = 80.0f; //ダメメージを受けけるは範囲だだよ

	int waveNo = 0; //自分が属するWaveの番号

};


#pragma once
class Morikon : public IGameObject
{
public:
	Morikon();
	~Morikon();
	enum Estete {
		Estete_Move,
		Estete_Attack,
		Estete_Follow,
		Estete_Death,
	};
	enum EnAnimationClip {
		enAnimationClip_walk, //動作
		enAnimationClip_attack, //攻撃
		enAnimationClip_Num,  //アニメーションクリップ
	};
	bool Start();
	void Update();


	//ポジションを返す関数
	CVector3 Morikon::Getm_Position() {
		return m_position;
	}
	//ステートを返す関数
	int Morikon::GetEState() {
		return m_stete;
	}
	//自分が死ぬ関数
	int Morikon::SetDeath() {
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

	void Momove();
	void Mofollow();
	void Moattack();
	void Modeath();

	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダラー。
	CVector3 m_position = CVector3::Zero; // 座標。
	CQuaternion m_rotation = CQuaternion::Identity; //回転。
	CVector3 m_scale = { 10.0f,10.0f,10.0f }; // 拡大率。

	CVector3 attackVec = CVector3::Zero;
	CVector3 moveVec = CVector3::Zero;
	CVector3 MoriVec = CVector3::Zero;

	Estete m_stete = Estete_Move; //状態
	CCharacterController m_charaCon; //キャラコン

	//移動関連
	const float followstop = 310.0f; //停止する距離(近いい）
	const float followleave = 300.0f; //離れる距離(近いい）
	const float followSpeed = 100.0f; //追尾の速度
	const float Speed = 0.0f; //停止の速度
	int movecount = 0; //ぜっ前進中か後進中か判別するカウント
	int timer = 0; //攻撃開始までのタイマー

	//攻撃関連
	int count = 0; //攻撃判別カウント
	int attacktimer = 0; //攻撃開始までのタイマー
	int  random = 0; //乱数用
	const int time = 60; //乱数に使うタイマー
	const float attackRange = 80.0f; //攻撃する距離
	const float attacktime = 40.0f;
	bool attackmoveflag = false;
	const float attackMoveRange = 120.0f; //攻撃時の前進距離と速度

	const float DamageLength = 80.0f; //ダメメージを受けけるは範囲だだよ

	int waveNo = 0; //自分が属するWaveの番号

};


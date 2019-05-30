#pragma once
class Neoriku : public IGameObject
{
public:
	Neoriku();
	~Neoriku();

	enum Estete {
		Estete_Attack,  //攻撃
		Estete_Yobi,  //予備動作
		Estete_Move, //移動
		Estete_Death, //死
	};

	enum EnAnimationClip {
		enAnimationClip_walk, //歩き
		enAnimationClip_Num,  //アニメーションクリップ

	};

	bool Start();
	void Update();


	//ポジションを返す関数
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

	void NeoAttack();
	void NeoYobi();
	void NeoMove();
	void NeoDeath();

	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダラー。
	CVector3 m_position = CVector3::Zero; // 座標。
	CQuaternion m_rotation = CQuaternion::Identity; //回転。
	CVector3 m_scale = CVector3::One; // 拡大率。

	CVector3 moveVec = CVector3::Zero;
	CVector3 neoVec = CVector3::Zero;

	Estete m_stete = Estete_Move; //状態
	CCharacterController m_charaCon; //キャラコン

	//移動関連
	const float followstop = 310.0f; //停止する距離(近いい）
	const float followleave = 300.0f; //離れる距離(近いい）
	const float followSpeed = 100.0f; //追尾の速度
	const float Speed = 0.0f; //停止の速度
	int movecount = 0; //ぜっ前進中か後進中か判別するカウント
	//攻撃関連
	bool bulletFlag = false;//弾丸用カウント
	int count = 0; //攻撃判別カウント
	int timer = 0; //攻撃開始までのタイマー
	int  random = 0; //乱数用
	const int time = 60; //乱数に使うタイマー
	int movetimer = 0; //再移動用
	const int move_starttimer = 60; //再移動するタイマー
	//予備動作関連
	bool colorflag = false;		//消滅
	int colortimer = 0;			//色を変化させるタイマー
	float colorcount = 0.0f;  //色の値を変化させるよ
	//死
	const float DamageLength = 80.0f; //ダメメージを受けけるは範囲だだよ
	bool dathflag = false;		//消滅

	int waveNo = 0; //自分が属するWaveの番号

};


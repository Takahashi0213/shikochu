#pragma once

class Metoporisu;
class Bullet6 : public IGameObject
{
public:
	Bullet6();
	~Bullet6();
	bool Start();
	void Update();
	//ポジションを返す関数
	CVector3 Bullet6::Getm_Position() {
		return m_position;
	}
	//自分が死ぬ関数
	int Bullet6::SetDeath() {
		dathflag = true;
		return 0;
	}

	//ダメージ範囲を教える関数
	float GetDamageLength() {
		return DamageLength;
	}
	//初期化
	void Init(Metoporisu* metoporisu)
	{
		m_metoporisu = metoporisu;
	}

	//移動速度の設定
	void SetMoveVec(CVector3 Move) {
		buvec = Move;
	}

private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダー	
	CVector3 m_position = CVector3::Zero;	//座標。
	const float moveSpeed = 7.0f; //速度

	CVector3 buvec;

	int m_timer = 0;				//玉が消えるまでのタイマー。
	bool keisannflag = false;		//ライト
	const int bulletdelete = 120; //玉を消すまでのタイマー
	const CVector3 bulletscale = { 2.0f,2.0f,2.0f }; //玉の大きさ
	const CVector3 bulletEmissionColor = { 80.0f,0.0f,200.0f }; //玉の色

	const float DamageLength = 50.0f; //ダメメージを受けけるは範囲だだよ
	Metoporisu* m_metoporisu = nullptr;		//発射したやつ
	bool dathflag = false;		//玉を消すやつ


};


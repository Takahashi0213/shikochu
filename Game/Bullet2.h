#pragma once

class Riritto;
class Bullet2 : public IGameObject
{
public:
	Bullet2();
	~Bullet2();
	bool Start();
	void Update();

	//ポジションを返す関数
	CVector3 Bullet2::Getm_Position() {
		return m_position;
	}
	//自分が死ぬ関数
	int Bullet2::SetDeath() {
		dathflag = true;
		return 0;
	}

	//ダメージ範囲を教える関数
	float GetDamageLength() {
		return DamageLength;
	}
	//初期化
	void Init(Riritto* riritto)
	{
		m_riritto = riritto;
	}
private:

	void follow();
	void move();
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダー	
	CVector3 m_position = CVector3::Zero;	//座標。
	const float moveSpeed = 7.0f; //速度

	CVector3 buvec;
	int random = 0;//玉の種類を決めるやつ
	int bullettime = 0;
	const float bullettuibi = 60.0f; //玉
	bool flag = false;		//玉を消すやつ

	int m_timer = 0;				//玉が消えるまでのタイマー。
	bool keisannflag = false;		//ライト
	const int bulletdelete = 120; //玉を消すまでのタイマー
	const CVector3 bulletscale = { 2.0f,2.0f,2.0f }; //玉の大きさ
	const CVector3 bulletEmissionColor = { 0.0f,100.0f,0.0f }; //玉の色
	const CVector3 bulletEmissionColor2 = { 100.0f,0.0f,0.0f }; //玉の色

	const float DamageLength = 50.0f; //ダメメージを受けけるは範囲だだよ
	Riritto* m_riritto = nullptr;		//発射したやつ
	bool dathflag = false;		//玉を消すやつ
};


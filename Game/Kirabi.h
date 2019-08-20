#pragma once
class Kirabi : public IGameObject
{
public:
	Kirabi();
	~Kirabi();
	bool Start();
	void Update();

	enum Estete {
		Estete_Attack,  //攻撃
		Estete_Move, //移動
		Estete_Death, //死
		Estete_yobi,	//予備動作
		Estete_Death2, //死
	};
	enum EnAnimationClip {
		enAnimationClip_walk, //歩き
		enAnimationClip_attack1, //攻撃1
		enAnimationClip_Num,  //アニメーションクリップ
	};

	//ポジションを返す関数
	CVector3 Kirabi::Getm_Position() {
		return m_position;
	}
	//ステートを返す関数
	int Kirabi::GetEState() {
		return m_stete;
	}
	//自分が死ぬ関数
	int Kirabi::SetDeath() {
		m_stete = Estete_Death;
		return 0;
	}
	//自分が死ぬ関数2
	void Kirabi::SetDeath2() {
		m_stete = Estete_Death2;
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

	//状態
	void EnemyAttack();
	void EnemyMove();
	void EnemyDeath();
	void EnemyDeath2();
	void Enemyyobi();

	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダラー。
	CVector3 m_position = CVector3::Zero; // 座標。
	CQuaternion m_rotation = CQuaternion::Identity; //回転。
	CVector3 m_scale = CVector3::One; // 拡大率。

	CVector3 moveVec = CVector3::Zero;
	CVector3 enemyVec = CVector3::Zero;
	Estete m_stete = Estete_Move; //状態
	CCharacterController m_charaCon; //キャラコン

	CVector3 buvec;
	//移動関連
	int movecount = 0;
	int random = 0;
	int timer = 0;
	const int randomCount = 80;
	const float randomSpeed = 80.0f;

	//攻撃関連
	const int yobiwait = 26; //予備動作の時間
	const int attackwait = 14; //攻撃動作の時間

	const float DamageLength = 80.0f; //ダメメージを受けけるは範囲だだよ

	int waveNo = 0; //自分が属するWaveの番号


};


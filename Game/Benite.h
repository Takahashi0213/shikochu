#pragma once
class Benite : public IGameObject
{
public:
	Benite();
	~Benite();
	enum Estete {
		Estete_Attack,  //攻撃
		Estete_Move, //移動
		Estete_Follow, //追尾
		Estete_Death, //死
		Estete_yobi,	//予備動作
		Estete_Death2, //死
	};
	enum EnAnimationClip {
		enAnimationClip_walk, //歩き
		enAnimationClip_attack1, //動作1
		enAnimationClip_Num,  //アニメーションクリップ
	};
	bool Start();
	void Update();

	//ポジションを返す関数
	CVector3 Benite::Getm_Position() {
		return m_position;
	}
	//ステートを返す関数
	int Benite::GetEState() {
		return m_stete;
	}
	//自分が死ぬ関数
	int Benite::SetDeath() {
		m_stete = Estete_Death;
		return 0;
	}
	//自分が死ぬ関数2
	void Benite::SetDeath2() {
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
	void EnemyFollow();
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
	CVector3 attackVec = CVector3::Zero;
	Estete m_stete = Estete_Move; //状態
	CCharacterController m_charaCon; //キャラコン

									 //移動関連
	const float followRange = 200.0f; //追尾する距離（追尾を諦めるまでの距離）
	const float attackRange = 80.0f; //攻撃する距離
	const float followSpeed =100.0f; //追尾の速度

									 //ランダム移動関連
	int count = 0; //ランダム移動のタイマー
	int random = 0; //ランダム移動の方向乱数
	const int randomCount = 60; //ランダム移動方向切り替えタイマー
	const float randomSpeed = 30.3f; //ランダム移動速度

									 //攻撃関連
	int timer = 0; //攻撃のタイマー
	const int yobiwait = 10; //予備動作の時間
	const int attackwait = 30; //攻撃動作の時間
	const float attackMoveRange = 120.0f; //攻撃時の前進距離と速度
	bool keisannflag = false;		//フラグ
									//ステータス
	const float DamageLength = 80.0f; //ダメメージを受けけるは範囲だだよ

	int waveNo = 0; //自分が属するWaveの番号
	int SpawnWaitTimer = 0;
	const int SpawnMaxWait = 12;

};


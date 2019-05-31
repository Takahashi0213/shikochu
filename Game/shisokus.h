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
		Estete_Death,	 //死ﾇ
		Estete_Death2, //意図せず死んだ

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
	void shisoDeath2();

	//ポジションを返す関数

	CVector3 shisokus::Getm_Position() {
		return m_position;
	}
	//ステートを返す関数
	int shisokus::GetEState() {
		return m_stete;
	}
	//ダメージ範囲を教える関数
	float GetDamageLength() {
		return DamageLength;
	}

	//自分が死ぬ関数
	int shisokus::SetDeath() {
		m_stete = Estete_Death2;
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

	//引数分HPを減少させる
	void Damage(int x) {
		NowHP -= x;
		if (NowHP < 0) {//負の数にならないようにしておく
			NowHP = 0;
		}
	}

	//現在HPを返す
	int GetHP() {
		return NowHP;
	}
	
	//最大HPを返す
	int GetMAXHP() {
		return MAXHP;
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
	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダラー。
	CVector3 m_position = CVector3::Zero; // 座標。
	CQuaternion m_rotation = CQuaternion::Identity; //回転。
	CVector3 m_scale = CVector3::One; // 拡大率。
	CVector3 shisoVec;

	Estete m_stete = Estete_Move; //状態
	CCharacterController m_charaCon; //キャラコン

	//移動関連
	int random = 0;//乱数
	int count = 0; //予備動作
	const int time = 60; //乱数に使うタイマー
	int timer = 60; //予備動作に移るタイマー
	const float yobi1Range = 1500.0f; //攻撃する距離

	//予備動作関連
	bool keisanflag = false;
	int yobitimer = 0;
	const float yobiwait = 50.0f;
	//攻撃関連
	int attacktimer = 0;

	int DeathTimer = 0; //HPが0になってからDeleteGOされるまでのタイマー 演出用
	const int ToumeiTimeMAX = 240; //この時間になると透明になる
	const int DeathTimeMAX = 360; //↑の上限

	const float DamageLength = 2680.0f; //ダメメージを受けけるは範囲だだよ

	int waveNo = 0; //自分が属するWaveの番号

	const int MAXHP = 4000; //最大HP
	int NowHP = MAXHP; //現在HP

};


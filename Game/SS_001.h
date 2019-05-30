#pragma once
class SS_001 : public IGameObject
{
public:
	SS_001();
	~SS_001();
	bool Start();
	void Update();

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
		enAnimationClip_wait, //静止
		enAnimationClip_Num,  //アニメーションクリップ
	};

	//ポジションを返す関数

	CVector3 SS_001::Getm_Position() {
		return m_position;
	}
	//ステートを返す関数
	int SS_001::GetEState() {
		return m_stete;
	}
	//ダメージ範囲を教える関数
	float GetDamageLength() {
		return DamageLength;
	}

	//自分が死ぬ関数
	int SS_001::SetDeath() {
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

	/*
	攻撃1→ミサイル
	攻撃2→ビーム！
	*/

	void SSMove();
	void SSYobi1();
	void SSAttack1();
	void SSYobi2();
	void SSAttack2();
	void SSDeath();

	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダラー。
	CVector3 m_position = CVector3::Zero; // 座標。
	CQuaternion m_rotation = CQuaternion::Identity; //回転。
	CVector3 m_scale = CVector3::One; // 拡大率。

	Estete m_stete = Estete_Move; //状態
	CCharacterController m_charaCon; //キャラコン

	const float DamageLength = 2680.0f; //ダメメージを受けけるは範囲だだよ

	int waveNo = 0; //自分が属するWaveの番号

	CVector3 DefPos = CVector3::Zero;

	const int MAXHP = 10000; //最大HP
	int NowHP = MAXHP; //現在HP

	////////////////////////////////////////////////////////////

	int AttackTimer = 0; //攻撃に遷移するまでのタイマー
	const int AttackLimit = 30; //攻撃に遷移するまでの制限時間

	int MisairuTimer = 0; //ミサイル用タイマー
	const int MisairuLimit = 24; //1発ミサイルを撃つのにかかる時間
	int MisairuCounter = 0; //ミサイル用カウンタ
	int MisairuCountMAX = 4; //ミサイルを撃つ回数（可変）
	CVector3 MisairuMove = CVector3::Zero; //ミサイルの移動速度
	CVector3 MyMove = CVector3::Zero; //自分が動く速度（ミサイル用一時）

	//

	int BeamYobiTimer = 0; //ビーム準備用タイマー
	const int BeamYobiLimit = 80; //ビーム準備制限時間
	int BeamTimer = 0; //ビーム発射中タイマー
	const int BeamLimit = 100; //ビーム制限時間

	//

	int DeathTimer = 0; //HPが0になってからDeleteGOされるまでのタイマー 演出用
	const int ToumeiTimeMAX = 240; //この時間になると透明になる
	const int DeathTimeMAX = 360; //↑の上限

};


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
		Estete_Death	 //死ﾇ

	};

	enum EnAnimationClip {
		enAnimationClip_move, //動作
		enAnimationClip_attack1, //攻撃1
		enAnimationClip_attack2, //攻撃2
		enAnimationClip_yobi1, //予備動作1
		enAnimationClip_yobi2, //予備動作2
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

	CVector3 shisokus::Getm_Position() {
		return m_position;
	}
	//ステートを返す関数
	int shisokus::GetEState() {
		return m_stete;
	}
	//自分が死ぬ関数
	int shisokus::SetDeath() {
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
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダラー。
	CVector3 m_position = CVector3::Zero; // 座標。
	CQuaternion m_rotation = CQuaternion::Identity; //回転。
	CVector3 m_scale = CVector3::One; // 拡大率。

	Estete m_stete = Estete_Move; //状態
	CCharacterController m_charaCon; //キャラコン

	int waveNo = 0; //自分が属するWaveの番号

	const int MAXHP = 10000; //最大HP
	int NowHP = MAXHP; //現在HP
};


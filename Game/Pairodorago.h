#pragma once
class Pairodorago : public IGameObject
{
public:
	Pairodorago();
	~Pairodorago();
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
		enAnimationClip_yobi, //予備
		enAnimationClip_attack, //攻撃
		enAnimationClip_Num,  //アニメーションクリップ
	};

	//ポジションを返す関数

	CVector3 Pairodorago::Getm_Position() {
		return m_position;
	}
	//ステートを返す関数
	int Pairodorago::GetEState() {
		return m_stete;
	}
	//ダメージ範囲を教える関数
	float GetDamageLength() {
		return DamageLength;
	}

	//自分が死ぬ関数
	int Pairodorago::SetDeath() {
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

	void PairoMove();
	void PairoYobi1();
	void PairoAttack1();
	void PairoYobi2();
	void PairoAttack2();
	void PairoDeath();

	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダラー。
	CVector3 m_position = CVector3::Zero; // 座標。
	CQuaternion m_rotation = CQuaternion::Identity; //回転。
	CVector3 m_scale = CVector3::One; // 拡大率。
	CVector3 shisoVec;

	Estete m_stete = Estete_Move; //状態
	CCharacterController m_charaCon; //キャラコン

	const float DamageLengthDEF = 2680.0f; //ダメージレンジデフォルト！（そのまんま）
	float DamageLength = 2680.0f; //ダメメージを受けけるは範囲だだよ

	int waveNo = 0; //自分が属するWaveの番号

	const int MAXHP = 10000; //最大HP
	int NowHP = MAXHP; //現在HP

	//

	int MoveTimer = 0;
	const int MoveLimit = 20;

	//

	int YobiTimer = 0; //予備動作タイマー
	const int YobiLimit = 80; //予備動作制限時間

	int AttackTimer = 0; //攻撃動作タイマー
	const int AttackLimit = 40; //攻撃動作制限時間
	const int AttackTiming = 10; //攻撃判定が発生するタイミング

	//

	int DeathTimer = 0; //HPが0になってからDeleteGOされるまでのタイマー 演出用
	const int ToumeiTimeMAX = 240; //この時間になると透明になる
	const int DeathTimeMAX = 360; //↑の上限

};


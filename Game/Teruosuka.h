#pragma once
class Teruosuka : public IGameObject
{
public:
	Teruosuka();
	~Teruosuka();
	bool Start();
	void Update();

	enum Estete {
		Estete_TankMove,
		Estete_TankAttack,
		Estete_TankToPlane,
		Estete_PlaneMove,
		Estete_PlaneToHuman,
		Estete_HumanMove,
		Estete_HumanAttackWait,
		Estete_HumanAttack,
		Estete_Death,	 //死ﾇ
		Estete_Death2,	 //死ﾇ

	};

	enum TeruMode {
		Tank,
		Plane,
		Human,
	};

	enum EnAnimationClip {
		enAnimationClip_TankWait,
		enAnimationClip_TankAttack,
		enAnimationClip_TankToPlane,
		enAnimationClip_PlaneWait,
		enAnimationClip_PlaneToHuman,
		enAnimationClip_HumanWait,
		enAnimationClip_HumanAttack,
		enAnimationClip_HumanDeath,
		enAnimationClip_Num,  //アニメーションクリップ
	};

	//ポジションを返す関数

	CVector3 Teruosuka::Getm_Position() {
		return m_position;
	}
	//ステートを返す関数
	int Teruosuka::GetEState() {
		return m_stete;
	}

	//ティルオスカモードを返す関数
	int Teruosuka::GetTeruMode() {
		return Teru_Mode;
	}

	//ダメージ範囲を教える関数
	float GetDamageLength() {
		return DamageLength;
	}

	//自分が死ぬ関数
	int Teruosuka::SetDeath() {
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

	/*
	戦車モード ミサイル
	飛行機モード 移動する
	人モード パンチする
	*/

	void Teru_TankMove();
	void Teru_TankAttack();
	void Teru_TankToPlane();
	void Teru_PlaneMove();
	void Teru_PlaneToHuman();
	void Teru_HumanMove();
	void Teru_HumanAttackWait(); 
	void Teru_HumanAttack();
	void TeruDeath();
	void TeruDeath2();

	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダラー。
	CVector3 m_position = CVector3::Zero; // 座標。
	CQuaternion m_rotation = CQuaternion::Identity; //回転。
	CVector3 m_scale = CVector3::One; // 拡大率。
	prefab::CSoundSource* ss;

	Estete m_stete = Estete_TankMove; //状態
	CCharacterController m_charaCon; //キャラコン
	TeruMode Teru_Mode = Tank;

	const float DamageLength = 2680.0f; //ダメメージを受けけるは範囲だだよ

	int waveNo = 0; //自分が属するWaveの番号

	CVector3 DefPos = CVector3::Zero;

	int MAXHP = 9000; //最大HP
	int NowHP = MAXHP; //現在HP

	////////////////////////////////////////////////////////////

	int AttackTimer = 0; //攻撃に遷移するまでのタイマー
	const int AttackLimit = 60; //攻撃に遷移するまでの制限時間

	const int MisairuLimit = 30; //攻撃に遷移するまでの制限時間
	CVector3 MisairuMove = CVector3::Zero; //ミサイルの移動速度

	const int HumanAttackLimit = 90;
	float HumanColor = 0.0f;

	int DeathTimer = 0; //HPが0になってからDeleteGOされるまでのタイマー 演出用
	const int ToumeiTimeMAX = 240; //この時間になると透明になる
	const int DeathTimeMAX = 360; //↑の上限

};


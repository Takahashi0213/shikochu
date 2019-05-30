#pragma once
class Arukasya : public IGameObject
{
public:
	enum Estete {
		Estete_Attack,  //攻撃
		Estete_Move, //移動
		Estete_Death, //死
	};
	enum EnAnimationClip {
		enAnimationClip_walk, //歩き
		enAnimationClip_back, //後退
		enAnimationClip_Num,  //アニメーションクリップ
	};

	Arukasya();
	~Arukasya();

	bool Start();
	void Update();

	//ポジションを返す関数
	CVector3 Arukasya::Getm_Position() {
		return m_position;
	}
	//ステートを返す関数
	int Arukasya::GetEState() {
		return m_stete;
	}
	//自分が死ぬ関数
	int Arukasya::SetDeath() {
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

	void AruAttack();
	void AruMove();
	void AruDeath();

	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダラー。
	CVector3 m_position = CVector3::Zero; // 座標。
	CQuaternion m_rotation = CQuaternion::Identity; //回転。
	CVector3 m_scale = { 1.0f,1.0f,1.0f }; // 拡大率。

	Estete m_stete = Estete_Move; //状態
	CCharacterController m_charaCon; //キャラコン

	CVector3 moveVec = CVector3::Zero;
	CVector3 diff = CVector3::Zero;
	CVector3 attackVec = CVector3::Zero;
	//移動関連
	int movecount = 0;
	int timer = 0;
	const float randomcount = 60.0f;
	int random = 0;
	const float randomSpeed = 40.0f;

	//攻撃関連
	int attime = 0;
	const float waittimer = 60.0f;
	const float endtime = 240.0f;
	const float backtime = 150.0f;
	const float back = -20.0f;
	const float rush = 5.0f;
	const float backk = -10.0f;


	//ステータス
	const float DamageLength = 80.0f; //ダメメージを受けけるは範囲だだよ

	int waveNo = 0; //自分が属するWaveの番号

};


#pragma once
class Kodan : public IGameObject
{
public:

	enum Estete {
		Estete_Move, //移動
		Estete_Death, //死
		Estete_Death2, //死
	};
	enum EnAnimationClip {
		enAnimationClip_walk, //歩き
		enAnimationClip_Num,  //アニメーションクリップ
	};

	Kodan();
	~Kodan();
	bool Start();
	void Update();

	//ポジションを返す関数
	CVector3 Kodan::Getm_Position() {
		return m_position;
	}
	//ステートを返す関数
	int Kodan::GetEState() {
		return m_stete;
	}
	//自分が死ぬ関数
	int Kodan::SetDeath() {
		m_stete = Estete_Death;
		return 0;
	}

	//自分が死ぬ関数2
	void Kodan::SetDeath2() {
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

	void Move();
	void Death();
	void Death2();

	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダラー。
	CVector3 m_position = CVector3::Zero; // 座標。
	CQuaternion m_rotation = CQuaternion::Identity; //回転。
	CVector3 m_scale = { 1.0f,1.0f,1.0f }; // 拡大率。

	Estete m_stete = Estete_Move; //状態
	CCharacterController m_charaCon; //キャラコン

	CVector3 moveVec = CVector3::Zero;
	CVector3 diff = CVector3::Zero;

	int timer = 0;
	int C_timer = 0;

	//ステータス
	const float DamageLength = 80.0f; //ダメメージを受けけるは範囲だだよ
	const CVector3 SpawnEffectScale = { 40.0f,40.0f,40.0f }; //スポーンエフェクトの大きさ
	const float randomSpeed = 100.0f; //移動速度
	const int randomcount = 140; //方向転換のタイミング

	int waveNo = 0; //自分が属するWaveの番号

};


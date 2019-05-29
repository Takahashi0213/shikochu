#pragma once
class Pi_rabi : public IGameObject
{
public:
	Pi_rabi();
	~Pi_rabi();

	enum Estete {
		Estete_Attack,  //攻撃
		Estete_Move, //移動
		Estete_Follow, //予備
		Estete_Death, //死
	};
	enum EnAnimationClip {
		enAnimationClip_walk, //歩き
		enAnimationClip_Num,  //アニメーションクリップ
	};

	bool Start();
	void Update();

	void Piattack();
	void PiMove();
	void PiFollow();
	void PiDeath();

	//ポジションを返す関数
	CVector3 Pi_rabi::Getm_Position() {
		return m_position;
	}
	//ステートを返す関数
	int Pi_rabi::GetEState() {
		return m_stete;
	}
	//自分が死ぬ関数
	int Pi_rabi::SetDeath() {
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
	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダラー。
	CVector3 m_position = CVector3::Zero; // 座標。
	CQuaternion m_rotation = CQuaternion::Identity; //回転。
	CVector3 m_scale = { 30.0f,30.0f,30.0f }; // 拡大率。

	Estete m_stete = Estete_Move; //状態
	CCharacterController m_charaCon; //キャラコン

	//移動関連
	int movecount = 0;
	const float moveD = 15.0f;
	const float moveup = 45.0f;
	const float movedown = 60.0f;
	CVector3 Pivec;
	const float followstop = 310.0f; //停止する距離(近いい）
	const float followleave = 300.0f; //離れる距離(近いい）
	const float followSpeed = 100.0f; //追尾の速度
	const float Speed = 0.0f; //停止の速度

	const float DamageLength = 80.0f; //ダメメージを受けけるは範囲だだよ

	int waveNo = 0; //自分が属するWaveの番号

};


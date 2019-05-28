#pragma once
class soukabuto : public IGameObject
{
public:
	soukabuto();
	~soukabuto();

	enum Estete {
		Estete_Move,
		Estete_Attack,
		Estete_Death,
	};
	enum EnAnimationClip {
		enAnimationClip_move, //動作
		enAnimationClip_attack1, //攻撃1
		enAnimationClip_Num,  //アニメーションクリップ
	};

	bool Start();
	void Update();

	void Soumove();
	void Souattack();
	void Soudeath();

	//ポジションを返す関数
	CVector3 soukabuto::Getm_Position() {
		return m_position;
	}
	//ステートを返す関数
	int soukabuto::GetEState() {
		return m_stete;
	}
	//自分が死ぬ関数
	int soukabuto::SetDeath() {
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
	CVector3 m_scale = CVector3::One; // 拡大率。

	Estete m_stete = Estete_Move; //状態
	CCharacterController m_charaCon; //キャラコン

	//移動関連
	int movecount = 0;
	int random = 0;
	int timer = 0;
	const float randomCount = 90.0f;
	const float randomSpeed = 120.0f;
	CVector3 moveVec;
	//攻撃関連
	int timecount = 0;
	const float waittimer = 60.0f;
	const float attacktime = 150.0f;
	const float back = -20.0f;
	const float rush = 10.0f;
	CVector3 attackVec;
	CVector3 diff;
	bool attackflag = false;

	const float DamageLength = 80.0f; //ダメメージを受けけるは範囲だだよ

	int waveNo = 0; //自分が属するWaveの番号
	int SpawnWaitTimer = 0;
	const int SpawnMaxWait = 12;
};




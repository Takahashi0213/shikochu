#pragma once
class AppleBomb : public IGameObject
{
public:
	AppleBomb();
	~AppleBomb();
	bool Start();
	void Update();

	enum Estete {
		Estete_Move,	//移動
		Estete_Death,	 //死ﾇ
		Estete_Death2,	 //死ﾇ
	};
	enum EnAnimationClip {
		enAnimationClip_move, //動作
		enAnimationClip_Num,  //アニメーションクリップ
	};

	//座標を設定。
	void AppleBomb::SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

	//目標座標を設定。
	void AppleBomb::SetTargetPos(CVector3 pos)
	{
		Target_position = pos;
	}


	//ポジションを返す関数
	CVector3 AppleBomb::Getm_Position() {
		return m_position;
	}
	//自分が死ぬ関数
	void AppleBomb::SetDeath() {
		m_stete = Estete_Death;
	}
	//自分が死ぬ関数2
	void AppleBomb::SetDeath2() {
		m_stete = Estete_Death2;
	}

	float GetDamageLength();

	//所属Waveをセット
	void SetWave(int x) {
		waveNo = x;
	}
	//所属Waveを返す
	int GetWave() {
		return waveNo;
	}

private:
	void AppleMove();

	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダー	
	CVector3 m_scale = CVector3::One; // 拡大率。
	CVector3 m_position = CVector3::Zero;	//座標。
	const float DamageLength = 50.0f; //ダメメージを受けけるは範囲だだよ
	Estete m_stete = Estete_Move; //状態
	int waveNo = 0; //自分が属するWaveの番号
	CVector3 Target_position = CVector3::Zero;	//目標座標

	const float MoveSpeed = 50.0f;//移動速度

};


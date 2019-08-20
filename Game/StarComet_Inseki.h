#pragma once
class StarComet_Inseki : public IGameObject
{
public:
	StarComet_Inseki();
	~StarComet_Inseki();
	bool Start();
	void Update();

	//座標を設定。
	void StarComet_Inseki::SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

	//移動速度を設定。
	void StarComet_Inseki::SetMoveSpeed(CVector3 mov)
	{
		MoveSpeed = mov;
	}

	//座標を返す
	CVector3 StarComet_Inseki::Getm_Position() {
		return m_position;
	}

	//ダメージ範囲を教える関数
	float StarComet_Inseki::GetDamageLength() {
		return DamageLength;
	}

	//実行したら隕石爆発！
	void StarComet_Inseki::SetDeath() {
		DeleteTimer = DeleteLimit;
	}

private:

	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダラー。
	CVector3 m_position = CVector3::Zero; // 座標。
	CQuaternion m_rotation = CQuaternion::Identity; //回転。
	CVector3 m_scale = CVector3::One; // 拡大率。
	CVector3 MoveSpeed = CVector3::Zero; //移動速度

	const float MoveHosei = 30.0f; //移動速度補正

	short DeleteTimer = 0;
	const short DeleteLimit = 300; //自死までの時間
	const float DamageLength = 80.0f;

};


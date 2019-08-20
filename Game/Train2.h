#pragma once
class Train2 : public IGameObject
{
public:
	Train2();
	~Train2();
	bool Start();
	void Update();

	//ポジションを返す関数
	CVector3 Train2::Getm_Position() {
		return m_position;
	}

	//ダメージ範囲を教える関数
	float GetDamageLength() {
		return DamageLength;
	}

	//座標を設定。
	void Train2::SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

	void Train2::SetSE_Flag(bool flag) {
		SE_Flag = flag;
	}


	void Train2::DeleteNow();

private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダー	

	CVector3 m_position = CVector3::Zero;	//座標。
	CVector3 m_scale = { 5.0f,5.0f,5.0f };//大きさ
	CQuaternion m_rotation = CQuaternion::Identity; //回転。

	std::vector<prefab::CSoundSource*> m_soundRender;
	prefab::CSoundSource* ss;

	const float DamageLength = 800.0f; //ダメメージを受けけるは範囲だだよ

	int Timer = 0;

	const float Speed = 200.0f;
	const int Limit = 1000;

	const int LoopLimit = 20; //サウンドソースの設置数
	const float TrainNagasa = 4000.0f; //電車の全長
	CVector3 SE_Pos = CVector3::Zero;
	const float PosZHosei = 400.0f;

	bool SE_Flag = false;

};
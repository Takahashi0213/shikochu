#pragma once
class Rock : public IGameObject
{
public:
	Rock();
	~Rock();
	bool Start();
	void Update();

	//座標を設定。
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

	void Rock::DeleteNow();

private:

	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダラー。
	CVector3 m_position = CVector3::Zero; // 座標。
	CQuaternion m_rotation = CQuaternion::Identity; //回転。
	CVector3 m_scale = CVector3::One; // 拡大率。

	int Timer = 0;
	const int DeleteTimer = 3000;
	int random = 0;

	CVector3 MoveSpeed = { 2.0f,0.5f,0.0f };

	//回転
	float RollX = 0.0f;
	float RollY = 0.0f;
	float RollZ = 0.0f;
};


#pragma once
class Bullet : public IGameObject
{
public:
	Bullet();
	~Bullet();
	bool Start();
	void Update();

private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダー	
	CVector3 m_position = CVector3::Zero;	//座標。
	const float moveSpeed = 0.4f; //移動速度
	int m_timer = 0;						//タイマー。

};


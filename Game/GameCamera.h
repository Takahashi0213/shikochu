#pragma once
class GameCamera : public IGameObject
{
	static GameCamera* m_instance;

public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

	//インスタンスの取得
	static GameCamera* GameCamera::GetInstance() {
		return m_instance;
	}

private:
	CVector3 cameraTarget;
	CVector3 cameraPos;
};


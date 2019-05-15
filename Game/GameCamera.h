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
	CVector3 cameraSwap = CVector3::Zero; //移動用
	CVector3 swapParameter = CVector3::Zero; //移動する量を保存する場所
	int swapTimer = -1; //フレームタイマー

	//定数
	const CVector3 camera2D_DEF = { 0.0f,250.0f,-5.0f };
	const CVector3 camera3D_DEF = { 0.0f,0.0f,-200.0f };
	const int swapTimerDEF = 90; //ここで決めたフレーム数かけてカメラを移動する

};


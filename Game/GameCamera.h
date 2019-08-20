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
	int DashTimer3D = 0; //3Dモード用ダッシュタイマー
	float DashHoseiZ = 0.0f;
	bool ResultCameraFlag = false;
	bool ResultCameraMoveFlag = false;

	CVector3 targetToPos = { 3500.0f, 150.0f, -1500.0f };

	prefab::CSoundSource* ss;
	float BMG_V = 1.0f;

	bool BGM_Flag = false;

	float DashCameraHosei = 0.0f; //ダッシュ用カメラ補正補間
	CVector3 P_MoveSpeed = CVector3::Zero; //プレイヤー移動速度保存用

	//定数
	const CVector3 camera2D_DEF = { 0.0f,250.0f,-5.0f };
	const CVector3 camera3D_DEF = { 0.0f,0.0f,-200.0f };
	const int swapTimerDEF = 90; //ここで決めたフレーム数かけてカメラを移動する
	const int swapWaitTimer = 80; //ここで決めたフレーム数カメラ移動を待つ（WaveEffectが終わるまで待つ）
	const int DashTimerMAX = 30; //3Dダッシュ時に引くカメラの量

	const float MaxDashHosei = 40.0f; //ダッシュでカメラが遅れる最大距離
	const float MaxDashHosei_Plus = 1.8f; //カメラ補正加算補正（うまく説明できん！）
	const float MaxDashHosei_Minus = 0.8f; //カメラ補正減算補正
};


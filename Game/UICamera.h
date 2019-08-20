#pragma once
class UICamera : public IGameObject
{
	static UICamera* m_instance;
public:
	UICamera();
	~UICamera();
	bool Start();
	void Update();
	void CameraFlag(bool X) {
		C_Flag = X;
	}
	//インスタンスの取得
	static UICamera* UICamera::GetInstance() {
		return m_instance;
	}

private:
	CVector3 cameraTarget;
	CVector3 cameraPos;

	bool C_Flag = false; //カメェラァのフラグ

	//座標関連
	CVector3 CameraDefPos = { 0.0f,50.0f,180.0f }; //ステージセレクトでの位置
	CVector3 CameraDefPosC = { 0.0f,150.0f,180.0f }; //図鑑での位置

};


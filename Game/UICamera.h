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
	//�C���X�^���X�̎擾
	static UICamera* UICamera::GetInstance() {
		return m_instance;
	}

private:
	CVector3 cameraTarget;
	CVector3 cameraPos;

	bool C_Flag = false; //�J���F���@�̃t���O
};


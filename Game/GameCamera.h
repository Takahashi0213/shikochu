#pragma once
class GameCamera : public IGameObject
{
	static GameCamera* m_instance;

public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

	//�C���X�^���X�̎擾
	static GameCamera* GameCamera::GetInstance() {
		return m_instance;
	}

private:

	CVector3 cameraTarget;
	CVector3 cameraPos;
	CVector3 cameraSwap = CVector3::Zero; //�ړ��p
	CVector3 swapParameter = CVector3::Zero; //�ړ�����ʂ�ۑ�����ꏊ
	int swapTimer = -1; //�t���[���^�C�}�[

	//�萔
	const CVector3 camera2D_DEF = { 0.0f,250.0f,-5.0f };
	const CVector3 camera3D_DEF = { 0.0f,0.0f,-200.0f };
	const int swapTimerDEF = 90; //�����Ō��߂��t���[���������ăJ�������ړ�����

};


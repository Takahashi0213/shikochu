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
	int DashTimer3D = 0; //3D���[�h�p�_�b�V���^�C�}�[
	float DashHoseiZ = 0.0f;
	bool ResultCameraFlag = false;
	bool ResultCameraMoveFlag = false;

	CVector3 targetToPos = { 3500.0f, 150.0f, -1500.0f };

	prefab::CSoundSource* ss;
	float BMG_V = 1.0f;

	//�萔
	const CVector3 camera2D_DEF = { 0.0f,250.0f,-5.0f };
	const CVector3 camera3D_DEF = { 0.0f,0.0f,-200.0f };
	const int swapTimerDEF = 90; //�����Ō��߂��t���[���������ăJ�������ړ�����
	const int swapWaitTimer = 80; //�����Ō��߂��t���[�����J�����ړ���҂iWaveEffect���I���܂ő҂j
	const int DashTimerMAX = 30; //3D�_�b�V�����Ɉ����J�����̗�
};


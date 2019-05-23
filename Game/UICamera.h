#pragma once
class UICamera : public IGameObject
{
	static UICamera* m_instance;
public:
	UICamera();
	~UICamera();
	bool Start();
	void Update();

	//�C���X�^���X�̎擾
	static UICamera* UICamera::GetInstance() {
		return m_instance;
	}

private:
	CVector3 cameraTarget;
	CVector3 cameraPos;

};


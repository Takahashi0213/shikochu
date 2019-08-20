#pragma once
class Rock : public IGameObject
{
public:
	Rock();
	~Rock();
	bool Start();
	void Update();

	//���W��ݒ�B
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

	void Rock::DeleteNow();

private:

	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero; // ���W�B
	CQuaternion m_rotation = CQuaternion::Identity; //��]�B
	CVector3 m_scale = CVector3::One; // �g�嗦�B

	int Timer = 0;
	const int DeleteTimer = 3000;
	int random = 0;

	CVector3 MoveSpeed = { 2.0f,0.5f,0.0f };

	//��]
	float RollX = 0.0f;
	float RollY = 0.0f;
	float RollZ = 0.0f;
};


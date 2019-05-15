#pragma once
class Bullet : public IGameObject
{
public:
	Bullet();
	~Bullet();
	bool Start();
	void Update();

private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_�[	
	CVector3 m_position = CVector3::Zero;	//���W�B
	const float moveSpeed = 0.4f; //�ړ����x
	int m_timer = 0;						//�^�C�}�[�B

};


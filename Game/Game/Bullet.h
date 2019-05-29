#pragma once

class Neoriku;
class Bullet : public IGameObject
{
public:
	Bullet();
	~Bullet();
	bool Start();
	void Update();

	//�|�W�V������Ԃ��֐�
	CVector3 Bullet::Getm_Position() {
		return m_position;
	}
	//���������ʊ֐�
	int Bullet::SetDeath() {
		dathflag = true;
		return 0;
	}

	//�_���[�W�͈͂�������֐�
	float GetDamageLength() {
		return DamageLength;
	}
	//������
	void Init(Neoriku* neoriku)
	{
		m_neoriku = neoriku;
	}
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_�[	
	CVector3 m_position = CVector3::Zero;	//���W�B
	const float moveSpeed = 7.0f; //���x

	CVector3 buvec;					

	int m_timer = 0;				//�ʂ�������܂ł̃^�C�}�[�B
	bool keisannflag = false;		//���C�g
	const float bulletdelete = 120.0f; //�ʂ������܂ł̃^�C�}�[
	const CVector3 bulletscale = { 2.0f,2.0f,2.0f }; //�ʂ̑傫��
	const CVector3 bulletEmissionColor = { 80.0f,0.0f,200.0f }; //�ʂ̑傫��

	const float DamageLength = 50.0f; //�_�����[�W���󂯂���͔͈͂�����
	Neoriku* m_neoriku = nullptr;		//���˂������
	bool dathflag = false;		//�ʂ��������
};


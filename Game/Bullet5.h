#pragma once

class Tizutyo;
class Bullet5 : public IGameObject
{
public:
	Bullet5();
	~Bullet5();
	bool Start();
	void Update();
	//�|�W�V������Ԃ��֐�
	CVector3 Bullet5::Getm_Position() {
		return m_position;
	}
	//���������ʊ֐�
	int Bullet5::SetDeath() {
		dathflag = true;
		return 0;
	}

	//�_���[�W�͈͂�������֐�
	float GetDamageLength() {
		return DamageLength;
	}
	//������
	void Init(Tizutyo* tizutyo)
	{
		m_tizutyo = tizutyo;
	}
private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_�[	
	CVector3 m_position = CVector3::Zero;	//���W�B
	const float moveSpeed = 7.0f; //���x

	CVector3 buvec;

	int m_timer = 0;				//�ʂ�������܂ł̃^�C�}�[�B
	bool keisannflag = false;		//���C�g
	const int bulletdelete = 120; //�ʂ������܂ł̃^�C�}�[
	const CVector3 bulletscale = { 2.0f,2.0f,2.0f }; //�ʂ̑傫��
	const CVector3 bulletEmissionColor = { 80.0f,0.0f,200.0f }; //�ʂ̐F

	const float DamageLength = 50.0f; //�_�����[�W���󂯂���͔͈͂�����
	Tizutyo* m_tizutyo = nullptr;		//���˂������
	bool dathflag = false;		//�ʂ��������


};


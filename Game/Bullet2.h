#pragma once

class Riritto;
class Bullet2 : public IGameObject
{
public:
	Bullet2();
	~Bullet2();
	bool Start();
	void Update();

	//�|�W�V������Ԃ��֐�
	CVector3 Bullet2::Getm_Position() {
		return m_position;
	}
	//���������ʊ֐�
	int Bullet2::SetDeath() {
		dathflag = true;
		return 0;
	}

	//�_���[�W�͈͂�������֐�
	float GetDamageLength() {
		return DamageLength;
	}
	//������
	void Init(Riritto* riritto)
	{
		m_riritto = riritto;
	}
private:

	void follow();
	void move();
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_�[	
	CVector3 m_position = CVector3::Zero;	//���W�B
	const float moveSpeed = 7.0f; //���x

	CVector3 buvec;
	int random = 0;//�ʂ̎�ނ����߂���
	int bullettime = 0;
	const float bullettuibi = 60.0f; //��
	bool flag = false;		//�ʂ��������

	int m_timer = 0;				//�ʂ�������܂ł̃^�C�}�[�B
	bool keisannflag = false;		//���C�g
	const float bulletdelete = 120.0f; //�ʂ������܂ł̃^�C�}�[
	const CVector3 bulletscale = { 2.0f,2.0f,2.0f }; //�ʂ̑傫��
	const CVector3 bulletEmissionColor = { 0.0f,100.0f,0.0f }; //�ʂ̐F
	const CVector3 bulletEmissionColor2 = { 100.0f,0.0f,0.0f }; //�ʂ̐F

	const float DamageLength = 50.0f; //�_�����[�W���󂯂���͔͈͂�����
	Riritto* m_riritto = nullptr;		//���˂������
	bool dathflag = false;		//�ʂ��������
};

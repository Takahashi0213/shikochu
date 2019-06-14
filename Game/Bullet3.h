#pragma once

class Uminoushi;
class Bullet3 : public IGameObject
{
public:
	Bullet3();
	~Bullet3();
	bool Start();
	void Update();

	//�|�W�V������Ԃ��֐�
	CVector3 Bullet3::Getm_Position() {
		return m_position;
	}
	//���������ʊ֐�
	int Bullet3::SetDeath() {
		dathflag = true;
		return 0;
	}

	//�ړ�������ݒ肷��
	void Bullet3::SetMove(CVector3 move) {
		b_move = move;
	}

	//�_���[�W�͈͂�������֐�
	float GetDamageLength() {
		return DamageLength;
	}
	//������
	void Init(Uminoushi* uminoushi)
	{
		m_uminoushi = uminoushi;
	}

private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_�[	
	CVector3 m_position = CVector3::Zero;	//���W�B
	const float moveSpeed = 7.0f; //���x
	CVector3 b_move = CVector3::Zero;

	CVector3 buvec;

	int m_timer = 0;				//�ʂ�������܂ł̃^�C�}�[�B
	bool keisannflag = false;		//���C�g
	const int bulletdelete = 120; //�ʂ������܂ł̃^�C�}�[
	const CVector3 bulletscale = { 2.0f,2.0f,2.0f }; //�ʂ̑傫��
	const CVector3 bulletEmissionColor = { 80.0f,0.0f,200.0f }; //�ʂ̑傫��

	const float DamageLength = 50.0f; //�_�����[�W���󂯂���͔͈͂�����
	Uminoushi* m_uminoushi = nullptr;		//���˂������
	bool dathflag = false;		//�ʂ��������

};


#pragma once
class Misairu : public IGameObject
{
public:
	Misairu();
	~Misairu();
	bool Start();
	void Update();

	enum Estete {
		Estete_Move,	//�ړ�
		Estete_Attack,  //�U��
		Estete_Death	 //���
	};

	//�ړ����x��ݒ肷��֐�
	void Misairu::SetMoveSpeed(CVector3 move) {
		moveSpeed = move;
	}

	//�t���O�̊Ǘ�
	void Misairu::SetTeruFlag() {
		TeruFlag = true;
	}

	//�t���O�̊Ǘ�
	void Misairu::SettingFlag() {
		SetFlag = true;
	}

	bool Misairu::GetFlag() {
		return SetFlag;
	}

	//�|�W�V������ݒ肷��֐�
	void Misairu::SetPosition(CVector3 pos) {
		m_position = pos;
	}

	//�|�W�V������Ԃ��֐�
	CVector3 Misairu::Getm_Position() {
		return m_position;
	}
	//�X�e�[�g��Ԃ��֐�
	int Misairu::GetEState() {
		return m_stete;
	}
	//�_���[�W�͈͂�������֐�
	float GetDamageLength() {
		return DamageLength;
	}

	//���������ʊ֐�
	int Misairu::SetDeath() {
		m_stete = Estete_Death;
		return 0;
	}

private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero; // ���W�B
	CQuaternion m_rotation = CQuaternion::Identity; //��]�B
	CVector3 m_scale = CVector3::One; // �g�嗦�B

	CVector3 moveSpeed = CVector3::Zero;

	Estete m_stete = Estete_Move; //���

	const float DamageLength = 100.0f; //�_�����[�W���󂯂���͔͈͂�����

	CVector3 atmove = CVector3::Zero;
	bool SetFlag = false;
	bool TeruFlag = false;

	//�^�C�}�[
	int Timer = 0;
	//
	const int MoveLimit = 120; //�ړ��̐�������
	const int AttackLimit = 300; //�U���̐�������
	const int TeruMoveLimit = 60; //�e�B���I�X�J���[�h�̈ړ��̐�������
	//
	const float AttackMoveSpeed = 30.0f; //�U���̈ړ����x
	const int TuibiLimit = 120; //�ړ��̐�������
	const int TuibiLimit_Teru = 5; //�ړ��̐�������_Teru

};


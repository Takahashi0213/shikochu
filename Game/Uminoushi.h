#pragma once
class Uminoushi : public IGameObject
{
public:
	Uminoushi();
	~Uminoushi();
	bool Start();
	void Update();

	void move();
	void yobi();
	void attack();
	void death();
	void death2();

	enum Estete {
	Estete_Move,
	Estete_Attack,
	Estete_Yobi,
	Estete_Death,
	Estete_Death2,
	};
	enum EnAnimationClip {
		enAnimationClip_move, //����
		enAnimationClip_Num,  //�A�j���[�V�����N���b�v
	};

	//�|�W�V������Ԃ��֐�
	CVector3 Uminoushi::Getm_Position() {
		return m_position;
	}
	//�X�e�[�g��Ԃ��֐�
	int Uminoushi::GetEState() {
		return m_stete;
	}
	//���������ʊ֐�
	int Uminoushi::SetDeath() {
		m_stete = Estete_Death;
		return 0;
	}
	//���������ʊ֐�2
	void Uminoushi::SetDeath2() {
		m_stete = Estete_Death2;
	}
	//���W��ݒ�B
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	//��]��ݒ�B
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	//�_���[�W�͈͂�������֐�
	float GetDamageLength() {
		return DamageLength;
	}
	//����Wave���Z�b�g
	void SetWave(int x) {
		waveNo = x;
	}
	//����Wave��Ԃ�
	int GetWave() {
		return waveNo;
	}

private:
	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero; // ���W�B
	CQuaternion m_rotation = CQuaternion::Identity; //��]�B
	CVector3 m_scale = CVector3::One; // �g�嗦�B

	Estete m_stete = Estete_Move; //���
	CCharacterController m_charaCon; //�L�����R��

	//�ړ��֘A
	int movecount = 0;
	int random = 0;
	int timer = 0;
	const float randomCount = 120.0f;
	const float randomSpeed = 80.0f;
	CVector3 moveVec = CVector3::Zero;
	bool B_Flag = false;
	const float DamageLength = 80.0f; //�_�����[�W���󂯂���͔͈͂�����

	int waveNo = 0; //������������Wave�̔ԍ�

	const float B_MoveSpeed = 7.0f; //�e�̈ړ����x
};

#pragma once
class Pi_rabi : public IGameObject
{
public:
	Pi_rabi();
	~Pi_rabi();

	enum Estete {
		Estete_Attack,  //�U��
		Estete_Move, //�ړ�
		Estete_Follow, //�\��
		Estete_Death, //��
	};
	enum EnAnimationClip {
		enAnimationClip_walk, //����
		enAnimationClip_Num,  //�A�j���[�V�����N���b�v
	};

	bool Start();
	void Update();

	void Piattack();
	void PiMove();
	void PiFollow();
	void PiDeath();

	//�|�W�V������Ԃ��֐�
	CVector3 Pi_rabi::Getm_Position() {
		return m_position;
	}
	//�X�e�[�g��Ԃ��֐�
	int Pi_rabi::GetEState() {
		return m_stete;
	}
	//���������ʊ֐�
	int Pi_rabi::SetDeath() {
		m_stete = Estete_Death;
		return 0;
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
	CVector3 m_scale = { 30.0f,30.0f,30.0f }; // �g�嗦�B

	Estete m_stete = Estete_Move; //���
	CCharacterController m_charaCon; //�L�����R��

	//�ړ��֘A
	int movecount = 0;
	const float moveD = 15.0f;
	const float moveup = 45.0f;
	const float movedown = 60.0f;
	CVector3 Pivec;
	const float followstop = 310.0f; //��~���鋗��(�߂����j
	const float followleave = 300.0f; //����鋗��(�߂����j
	const float followSpeed = 100.0f; //�ǔ��̑��x
	const float Speed = 0.0f; //��~�̑��x

	const float DamageLength = 80.0f; //�_�����[�W���󂯂���͔͈͂�����

	int waveNo = 0; //������������Wave�̔ԍ�

};


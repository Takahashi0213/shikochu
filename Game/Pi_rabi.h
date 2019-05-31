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
		Estete_Death2, //��
	};
	enum EnAnimationClip {
		enAnimationClip_walk, //����
		enAnimationClip_attack, //�U��
		enAnimationClip_Num,  //�A�j���[�V�����N���b�v
	};

	bool Start();
	void Update();


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

	//���������ʊ֐�
	void Pi_rabi::SetDeath2() {
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
	void Piattack();
	void PiMove();
	void PiFollow();
	void PiDeath();
	void PiDeath2();

	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero; // ���W�B
	CQuaternion m_rotation = CQuaternion::Identity; //��]�B
	CVector3 m_scale = { 30.0f,30.0f,30.0f }; // �g�嗦�B

	Estete m_stete = Estete_Move; //���
	CCharacterController m_charaCon; //�L�����R��

	//�ړ��֘A
	int movecount = 0;
	int random = 0;
	int timer = 0;
	const float randomCount = 90.0f;
	const float randomSpeed = 120.0f;
	CVector3 moveVec = CVector3::Zero;
	CVector3 attackVec = CVector3::Zero;
	CVector3 diff = CVector3::Zero;
	//�ǔ��֘A
	const float followRange = 300.0f; //�ǔ����鋗���i�ǔ�����߂�܂ł̋����j
	const float followSpeed = 60.0f; //�ǔ��̑��x
	const float fleeSpeed = 120.0f; //�ǔ��̑��x
	bool attackmoveflag = false;
	const float attackMoveRange = 240.0f; //�U�����̑O�i�����Ƒ��x
	//�U���֘A
	int attacktimer = 0; //�U���J�n�܂ł̃^�C�}�[
	const float attackend = 150.0f; //�ǔ��̑��x
	const float attacktime = 40.0f;




	const float DamageLength = 80.0f; //�_�����[�W���󂯂���͔͈͂�����

	int waveNo = 0; //������������Wave�̔ԍ�

};


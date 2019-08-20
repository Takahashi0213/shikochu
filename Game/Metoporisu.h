#pragma once
class Metoporisu : public IGameObject
{
public:
	Metoporisu();
	~Metoporisu();

	enum Estete {
		Estete_Move, //�ړ�
		Estete_Death, //��
		Estete_Death2, //��
	};
	enum EnAnimationClip {
		enAnimationClip_walk, //����
		enAnimationClip_Num,  //�A�j���[�V�����N���b�v
	};

	bool Start();
	void Update();

	//�|�W�V������Ԃ��֐�
	CVector3 Metoporisu::Getm_Position() {
		return m_position;
	}
	//�X�e�[�g��Ԃ��֐�
	int Metoporisu::GetEState() {
		return m_stete;
	}
	//���������ʊ֐�
	int Metoporisu::SetDeath() {
		m_stete = Estete_Death;
		return 0;
	}

	//���������ʊ֐�2
	void Metoporisu::SetDeath2() {
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

	void Move();
	void Death();
	void Death2();

	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero; // ���W�B
	CQuaternion m_rotation = CQuaternion::Identity; //��]�B
	CVector3 m_scale = { 1.0f,1.0f,1.0f }; // �g�嗦�B

	Estete m_stete = Estete_Move; //���
	CCharacterController m_charaCon; //�L�����R��

	CVector3 moveVec = CVector3::Zero;
	CVector3 diff = CVector3::Zero;

	int timer = 0;
	int C_timer = 0;
	int AttackTimer = 0;
	const int AttackLimit = 180;
	float colorcount = 0.0f;  //�F�̒l��ω��������
	CVector3 attackVec = CVector3::Zero;

	//�X�e�[�^�X
	const float DamageLength = 80.0f; //�_�����[�W���󂯂���͔͈͂�����
	const CVector3 SpawnEffectScale = { 40.0f,40.0f,40.0f }; //�X�|�[���G�t�F�N�g�̑傫��
	const float randomSpeed = 60.0f; //�ړ����x
	const int randomcount = 200; //�����]���̃^�C�~���O

	int waveNo = 0; //������������Wave�̔ԍ�


};


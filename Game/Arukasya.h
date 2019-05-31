#pragma once
class Arukasya : public IGameObject
{
public:
	enum Estete {
		Estete_Attack,  //�U��
		Estete_Move, //�ړ�
		Estete_Death, //��
		Estete_Death2, //��
	};
	enum EnAnimationClip {
		enAnimationClip_walk, //����
		enAnimationClip_back, //���
		enAnimationClip_Num,  //�A�j���[�V�����N���b�v
	};

	Arukasya();
	~Arukasya();

	bool Start();
	void Update();

	//�|�W�V������Ԃ��֐�
	CVector3 Arukasya::Getm_Position() {
		return m_position;
	}
	//�X�e�[�g��Ԃ��֐�
	int Arukasya::GetEState() {
		return m_stete;
	}
	//���������ʊ֐�
	int Arukasya::SetDeath() {
		m_stete = Estete_Death;
		return 0;
	}

	//���������ʊ֐�2
	void Arukasya::SetDeath2() {
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

	void AruAttack();
	void AruMove();
	void AruDeath();
	void AruDeath2();

	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero; // ���W�B
	CQuaternion m_rotation = CQuaternion::Identity; //��]�B
	CVector3 m_scale = { 1.0f,1.0f,1.0f }; // �g�嗦�B

	Estete m_stete = Estete_Move; //���
	CCharacterController m_charaCon; //�L�����R��

	CVector3 moveVec = CVector3::Zero;
	CVector3 diff = CVector3::Zero;
	CVector3 attackVec = CVector3::Zero;
	//�ړ��֘A
	int movecount = 0;
	int timer = 0;
	const float randomcount = 60.0f;
	int random = 0;
	const float randomSpeed = 40.0f;

	//�U���֘A
	int attime = 0;
	const float waittimer = 60.0f;
	const float endtime = 240.0f;
	const float backtime = 150.0f;
	const float back = -20.0f;
	const float rush = 5.0f;
	const float backk = -10.0f;


	//�X�e�[�^�X
	const float DamageLength = 80.0f; //�_�����[�W���󂯂���͔͈͂�����

	int waveNo = 0; //������������Wave�̔ԍ�

};


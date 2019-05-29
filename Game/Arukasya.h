#pragma once
class Arukasya : public IGameObject
{
public:
	enum Estete {
		Estete_Attack,  //�U��
		Estete_Move, //�ړ�
		Estete_Yobi, //�\��
		Estete_Death, //��
	};
	enum EnAnimationClip {
		enAnimationClip_walk, //����
		enAnimationClip_back, //���
		enAnimationClip_Num,  //�A�j���[�V�����N���b�v
	};

	Arukasya();
	~Arukasya();

	void AruAttack();
	void AruMove();
	void AruYobi();
	void AruDeath();

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

	CVector3 moveVec;
	//�ړ��֘A
	int count = 0;
	int random = 0;
	const float randomCount = 60.0f;
	const float randomSpeed = 30.0f;
	const float followRange = 4.0f;
	int Attackcount = 0;
	//�\���֘A

	//�U���֘A
	int timer = 0;
	const float waittimer = 30.0f;

	//�X�e�[�^�X
	const float DamageLength = 80.0f; //�_�����[�W���󂯂���͔͈͂�����

	int waveNo = 0; //������������Wave�̔ԍ�

};


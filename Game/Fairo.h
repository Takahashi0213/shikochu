#pragma once
class Fairo : public IGameObject
{
public:
	Fairo();
	~Fairo();
	bool Start();
	void Update();

	enum Estete {
		Estete_Move,
		Estete_Attack,
		Estete_Death,
	};
	enum EnAnimationClip {
		enAnimationClip_walk, //����
		enAnimationClip_dash, //�_�b�V��
		enAnimationClip_Num,  //�A�j���[�V�����N���b�v
	};
	//�|�W�V������Ԃ��֐�
	CVector3 Fairo::Getm_Position() {
		return m_position;
	}
	//�X�e�[�g��Ԃ��֐�
	int Fairo::GetEState() {
		return m_stete;
	}
	//���������ʊ֐�
	int Fairo::SetDeath() {
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

	void Faimove();
	void Faiattack();
	void Faideath();

	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero; // ���W�B
	CQuaternion m_rotation = CQuaternion::Identity; //��]�B
	CVector3 m_scale = {0.8f,0.8f,0.8f}; // �g�嗦�B

	Estete m_stete = Estete_Move; //���
	CCharacterController m_charaCon; //�L�����R��

	//�ړ��֘A
	int movecount = 0;
	int random = 0;
	int timer = 0;
	const float randomCount = 90.0f;
	const float randomSpeed = 80.0f;
	CVector3 moveVec = CVector3::Zero;

	//�U���֘A
	int timecount = 0;
	const float waittimer = 60.0f;
	const float attacktime = 150.0f;
	const float back = -20.0f;
	const float rush = 7.0f;
	CVector3 attackVec = CVector3::Zero;
	CVector3 diff = CVector3::Zero;
	bool attackflag = false;

	const float DamageLength = 80.0f; //�_�����[�W���󂯂���͔͈͂�����

	int waveNo = 0; //������������Wave�̔ԍ�

};


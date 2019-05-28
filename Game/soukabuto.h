#pragma once
class soukabuto : public IGameObject
{
public:
	soukabuto();
	~soukabuto();

	enum Estete {
		Estete_Move,
		Estete_Attack,
		Estete_Death,
	};
	enum EnAnimationClip {
		enAnimationClip_move, //����
		enAnimationClip_attack1, //�U��1
		enAnimationClip_Num,  //�A�j���[�V�����N���b�v
	};

	bool Start();
	void Update();

	void Soumove();
	void Souattack();
	void Soudeath();

	//�|�W�V������Ԃ��֐�
	CVector3 soukabuto::Getm_Position() {
		return m_position;
	}
	//�X�e�[�g��Ԃ��֐�
	int soukabuto::GetEState() {
		return m_stete;
	}
	//���������ʊ֐�
	int soukabuto::SetDeath() {
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
	CVector3 m_scale = CVector3::One; // �g�嗦�B

	Estete m_stete = Estete_Move; //���
	CCharacterController m_charaCon; //�L�����R��

	//�ړ��֘A
	int movecount = 0;
	int random = 0;
	int timer = 0;
	const float randomCount = 90.0f;
	const float randomSpeed = 120.0f;
	CVector3 moveVec;
	//�U���֘A
	int timecount = 0;
	const float waittimer = 60.0f;
	const float attacktime = 150.0f;
	const float back = -20.0f;
	const float rush = 10.0f;
	CVector3 attackVec;
	CVector3 diff;
	bool attackflag = false;

	const float DamageLength = 80.0f; //�_�����[�W���󂯂���͔͈͂�����

	int waveNo = 0; //������������Wave�̔ԍ�
	int SpawnWaitTimer = 0;
	const int SpawnMaxWait = 12;
};




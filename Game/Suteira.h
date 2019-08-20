#pragma once
class Suteira : public IGameObject
{
public:
	Suteira();
	~Suteira();
	enum Estete {
		Estete_Move,
		Estete_Attack,
		Estete_Death,
		Estete_Death2,
	};
	enum EnAnimationClip {
		enAnimationClip_move, //����
		enAnimationClip_Num,  //�A�j���[�V�����N���b�v
	};

	bool Start();
	void Update();

	//�|�W�V������Ԃ��֐�
	CVector3 Suteira::Getm_Position() {
		return m_position;
	}
	//�X�e�[�g��Ԃ��֐�
	int Suteira::GetEState() {
		return m_stete;
	}
	//���������ʊ֐�
	int Suteira::SetDeath() {
		m_stete = Estete_Death;
		return 0;
	}
	//���������ʊ֐�2
	void Suteira::SetDeath2() {
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
	void Soumove();
	void Souattack();
	void Soudeath();
	void Soudeath2();

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
	const float randomSpeed = 100.0f;
	CVector3 moveVec = CVector3::Zero;
	//�U���֘A
	int timecount = 0;
	const float waittimer = 60.0f;
	const float attacktime = 200.0f;
	const float back = -20.0f;
	const float rush = 5.0f;
	CVector3 attackVec = CVector3::Zero;
	CVector3 diff = CVector3::Zero;
	bool attackflag = false;

	const float DamageLength = 80.0f; //�_�����[�W���󂯂���͔͈͂�����

	int waveNo = 0; //������������Wave�̔ԍ�
	int SpawnWaitTimer = 0;
	const int SpawnMaxWait = 12;

};


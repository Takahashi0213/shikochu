#pragma once
class Kirabi : public IGameObject
{
public:
	Kirabi();
	~Kirabi();
	bool Start();
	void Update();

	enum Estete {
		Estete_Attack,  //�U��
		Estete_Move, //�ړ�
		Estete_Death, //��
		Estete_yobi,	//�\������
		Estete_Death2, //��
	};
	enum EnAnimationClip {
		enAnimationClip_walk, //����
		enAnimationClip_attack1, //�U��1
		enAnimationClip_Num,  //�A�j���[�V�����N���b�v
	};

	//�|�W�V������Ԃ��֐�
	CVector3 Kirabi::Getm_Position() {
		return m_position;
	}
	//�X�e�[�g��Ԃ��֐�
	int Kirabi::GetEState() {
		return m_stete;
	}
	//���������ʊ֐�
	int Kirabi::SetDeath() {
		m_stete = Estete_Death;
		return 0;
	}
	//���������ʊ֐�2
	void Kirabi::SetDeath2() {
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

	//���
	void EnemyAttack();
	void EnemyMove();
	void EnemyDeath();
	void EnemyDeath2();
	void Enemyyobi();

	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero; // ���W�B
	CQuaternion m_rotation = CQuaternion::Identity; //��]�B
	CVector3 m_scale = CVector3::One; // �g�嗦�B

	CVector3 moveVec = CVector3::Zero;
	CVector3 enemyVec = CVector3::Zero;
	Estete m_stete = Estete_Move; //���
	CCharacterController m_charaCon; //�L�����R��

	CVector3 buvec;
	//�ړ��֘A
	int movecount = 0;
	int random = 0;
	int timer = 0;
	const int randomCount = 80;
	const float randomSpeed = 80.0f;

	//�U���֘A
	const int yobiwait = 26; //�\������̎���
	const int attackwait = 14; //�U������̎���

	const float DamageLength = 80.0f; //�_�����[�W���󂯂���͔͈͂�����

	int waveNo = 0; //������������Wave�̔ԍ�


};


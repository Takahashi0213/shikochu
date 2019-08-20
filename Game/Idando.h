#pragma once
class Idando : public IGameObject
{
public:
	Idando();
	~Idando();
	bool Start();
	void Update();

	enum Estete {
		Estete_Attack,  //�U��
		Estete_Move, //�ړ�
		Estete_Death, //��
		Estete_yobi,	//�\������
		Estete_return,	//�I��
		Estete_Death2, //��
	};
	enum EnAnimationClip {
		enAnimationClip_walk, //����
		enAnimationClip_attack_yobi,
		enAnimationClip_attack,
		enAnimationClip_attack_return,
		enAnimationClip_Num,  //�A�j���[�V�����N���b�v
	};

	//�|�W�V������Ԃ��֐�
	CVector3 Idando::Getm_Position() {
		return m_position;
	}
	//�X�e�[�g��Ԃ��֐�
	int Idando::GetEState() {
		return m_stete;
	}
	//���������ʊ֐�
	int Idando::SetDeath() {
		m_stete = Estete_Death;
		return 0;
	}
	//���������ʊ֐�2
	void Idando::SetDeath2() {
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
	void EnemyReturn();
	void EnemyDeath();
	void EnemyDeath2();
	void Enemyyobi();

	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero; // ���W�B
	CQuaternion m_rotation = CQuaternion::Identity; //��]�B
	CVector3 m_scale = CVector3::One; // �g�嗦�B

	Estete m_stete = Estete_Move; //���
	CCharacterController m_charaCon; //�L�����R��

	//�ړ��֘A
	int timer = 0;
	int timer2 = 0;
	const int randomCount = 60;

	//�U���֘A
	const int yobiwait = 60; //�\������̎���
	const int attackwait = 40; //�U������̎���

	const float DamageLength = 80.0f; //�_�����[�W���󂯂���͔͈͂�����

	int waveNo = 0; //������������Wave�̔ԍ�


};


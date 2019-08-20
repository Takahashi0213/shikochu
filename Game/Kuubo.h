#pragma once
class Kuubo : public IGameObject
{
public:
	Kuubo();
	~Kuubo();
	bool Start();
	void Update();

	enum Estete {
		Estete_Attack,  //�U��
		Estete_Move, //�ړ�
		Estete_Follow, //�ǔ�
		Estete_Death, //��
		Estete_yobi,	//�\������
		Estete_Death2, //��
	};
	enum EnAnimationClip {
		enAnimationClip_walk, //����
		enAnimationClip_attack1, //����1
		enAnimationClip_Num,  //�A�j���[�V�����N���b�v
	};

	//�|�W�V������Ԃ��֐�
	CVector3 Kuubo::Getm_Position() {
		return m_position;
	}
	//�X�e�[�g��Ԃ��֐�
	int Kuubo::GetEState() {
		return m_stete;
	}
	//���������ʊ֐�
	int Kuubo::SetDeath() {
		m_stete = Estete_Death;
		return 0;
	}
	//���������ʊ֐�2
	void Kuubo::SetDeath2() {
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
	void EnemyFollow();
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
	CVector3 attackVec = CVector3::Zero;
	Estete m_stete = Estete_Move; //���
	CCharacterController m_charaCon; //�L�����R��

	//�ړ��֘A
	const float followRange = 600.0f; //�ǔ����鋗���i�ǔ�����߂�܂ł̋����j
	const float attackRange = 180.0f; //�U�����鋗��
	const float followSpeed = 60.0f; //�ǔ��̑��x

									 //�����_���ړ��֘A
	int count = 0; //�����_���ړ��̃^�C�}�[
	int random = 0; //�����_���ړ��̕�������
	const int randomCount = 120; //�����_���ړ������؂�ւ��^�C�}�[
	const float randomSpeed = 40.0f; //�����_���ړ����x

									 //�U���֘A
	int timer = 0; //�U���̃^�C�}�[
	const int yobiwait = 40; //�\������̎���
	const int attackwait = 20; //�U������̎���
	const float attackMoveRange = 40.0f; //�U�����̑O�i�����Ƒ��x
	bool keisannflag = false;		//�t���O
									//�X�e�[�^�X
	const float DamageLength = 80.0f; //�_�����[�W���󂯂���͔͈͂�����

	int waveNo = 0; //������������Wave�̔ԍ�
	int SpawnWaitTimer = 0;
	const int SpawnMaxWait = 12;

};

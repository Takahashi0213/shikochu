#pragma once
class Ekku : public IGameObject
{
public:
	Ekku();
	~Ekku();

	enum Estete {
		Estete_Move,//�ړ�
		Estete_Follow, //�ǔ�
		Estete_Attack, //�U��
		Estete_Yobi,//�\������
		Estete_Death,//��
	};
	enum EnAnimationClip {
		enAnimationClip_walk, //�ړ�
		enAnimationClip_attack, //�U��
		enAnimationClip_yobi, //�\������
		enAnimationClip_Num,  //�A�j���[�V�����N���b�v
	};



	bool Start();
	void Update();

	//�|�W�V������Ԃ��֐�
	CVector3 Ekku::Getm_Position() {
		return m_position;
	}
	//�X�e�[�g��Ԃ��֐�
	int Ekku::GetEState() {
		return m_stete;
	}
	//���������ʊ֐�
	int Ekku::SetDeath() {
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

	void EkAttack();
	void EkMove();
	void EkFollow();
	void EkDeath();
	void Ekyobi();

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
	const float followRange = 300.0f; //�ǔ����鋗���i�ǔ�����߂�܂ł̋����j
	const float attackRange = 120.0f; //�U�����鋗��
	const float followSpeed = 80.0f; //�ǔ��̑��x

									 //�����_���ړ��֘A
	int count = 0; //�����_���ړ��̃^�C�}�[
	int random = 0; //�����_���ړ��̕�������
	const int randomCount = 60; //�����_���ړ������؂�ւ��^�C�}�[
	const float randomSpeed = 30.3f; //�����_���ړ����x

									 //�U���֘A
	int timer = 0; //�U���̃^�C�}�[
	const int yobiwait = 70; //�\������̎���
	const int attackwait = 90; //�U������̎���
	const float attackMoveRange = 120.0f; //�U�����̑O�i�����Ƒ��x
	bool keisannflag = false;		//�t���O


	const float DamageLength = 80.0f; //�_�����[�W���󂯂���͔͈͂�����

	int waveNo = 0; //������������Wave�̔ԍ�

};


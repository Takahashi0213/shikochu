#pragma once
class Morikon : public IGameObject
{
public:
	Morikon();
	~Morikon();
	enum Estete {
		Estete_Move,
		Estete_Attack,
		Estete_Follow,
		Estete_Death,
		Estete_Death2,
	};
	enum EnAnimationClip {
		enAnimationClip_walk, //����
		enAnimationClip_attack, //�U��
		enAnimationClip_Num,  //�A�j���[�V�����N���b�v
	};
	bool Start();
	void Update();


	//�|�W�V������Ԃ��֐�
	CVector3 Morikon::Getm_Position() {
		return m_position;
	}
	//�X�e�[�g��Ԃ��֐�
	int Morikon::GetEState() {
		return m_stete;
	}
	//���������ʊ֐�
	int Morikon::SetDeath() {
		m_stete = Estete_Death;
		return 0;
	}

	//���������ʊ֐�2
	void Morikon::SetDeath2() {
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

	void Momove();
	void Mofollow();
	void Moattack();
	void Modeath();
	void Modeath2();

	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero; // ���W�B
	CQuaternion m_rotation = CQuaternion::Identity; //��]�B
	CVector3 m_scale = { 10.0f,10.0f,10.0f }; // �g�嗦�B

	CVector3 attackVec = CVector3::Zero;
	CVector3 moveVec = CVector3::Zero;
	CVector3 MoriVec = CVector3::Zero;

	Estete m_stete = Estete_Move; //���
	CCharacterController m_charaCon; //�L�����R��

	//�ړ��֘A
	const float followstop = 310.0f; //��~���鋗��(�߂����j
	const float followleave = 300.0f; //����鋗��(�߂����j
	const float followSpeed = 100.0f; //�ǔ��̑��x
	const float Speed = 0.0f; //��~�̑��x
	int movecount = 0; //�����O�i������i�������ʂ���J�E���g
	int timer = 0; //�U���J�n�܂ł̃^�C�}�[

	//�U���֘A
	int count = 0; //�U�����ʃJ�E���g
	int attacktimer = 0; //�U���J�n�܂ł̃^�C�}�[
	int  random = 0; //�����p
	const int time = 60; //�����Ɏg���^�C�}�[
	const float attackRange = 80.0f; //�U�����鋗��
	const float attacktime = 40.0f;
	bool attackmoveflag = false;
	const float attackMoveRange = 120.0f; //�U�����̑O�i�����Ƒ��x

	const float DamageLength = 80.0f; //�_�����[�W���󂯂���͔͈͂�����

	int waveNo = 0; //������������Wave�̔ԍ�

};


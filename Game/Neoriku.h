#pragma once
class Neoriku : public IGameObject
{
public:
	Neoriku();
	~Neoriku();

	enum Estete {
		Estete_Attack,  //�U��
		Estete_Yobi,  //�\������
		Estete_Move, //�ړ�
		Estete_Death, //��
		Estete_Death2, //��
	};

	enum EnAnimationClip {
		enAnimationClip_walk, //����
		enAnimationClip_Num,  //�A�j���[�V�����N���b�v

	};

	bool Start();
	void Update();


	//�|�W�V������Ԃ��֐�
	CVector3 Neoriku::Getm_Position() {
		return m_position;
	}
	//�X�e�[�g��Ԃ��֐�
	int Neoriku::GetEState() {
		return m_stete;
	}
	//���������ʊ֐�
	int Neoriku::SetDeath() {
		m_stete = Estete_Death;
		return 0;
	}

	//���������ʊ֐�2
	void Neoriku::SetDeath2() {
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

	void NeoAttack();
	void NeoYobi();
	void NeoMove();
	void NeoDeath();
	void NeoDeath2();

	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero; // ���W�B
	CQuaternion m_rotation = CQuaternion::Identity; //��]�B
	CVector3 m_scale = CVector3::One; // �g�嗦�B

	CVector3 moveVec = CVector3::Zero;
	CVector3 neoVec = CVector3::Zero;

	Estete m_stete = Estete_Move; //���
	CCharacterController m_charaCon; //�L�����R��

	//�ړ��֘A
	const float followstop = 310.0f; //��~���鋗��(�߂����j
	const float followleave = 300.0f; //����鋗��(�߂����j
	const float followSpeed = 100.0f; //�ǔ��̑��x
	const float Speed = 0.0f; //��~�̑��x
	int movecount = 0; //�����O�i������i�������ʂ���J�E���g
	//�U���֘A
	bool bulletFlag = false;//�e�ۗp�J�E���g
	int count = 0; //�U�����ʃJ�E���g
	int timer = 0; //�U���J�n�܂ł̃^�C�}�[
	int  random = 0; //�����p
	const int time = 60; //�����Ɏg���^�C�}�[
	int movetimer = 0; //�Ĉړ��p
	const int move_starttimer = 60; //�Ĉړ�����^�C�}�[
	//�\������֘A
	bool colorflag = false;		//����
	int colortimer = 0;			//�F��ω�������^�C�}�[
	float colorcount = 0.0f;  //�F�̒l��ω��������
	//��
	const float DamageLength = 80.0f; //�_�����[�W���󂯂���͔͈͂�����
	bool dathflag = false;		//����

	int waveNo = 0; //������������Wave�̔ԍ�

};


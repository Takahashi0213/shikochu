#pragma once
class Teruosuka : public IGameObject
{
public:
	Teruosuka();
	~Teruosuka();
	bool Start();
	void Update();

	enum Estete {
		Estete_TankMove,
		Estete_TankAttack,
		Estete_TankToPlane,
		Estete_PlaneMove,
		Estete_PlaneToHuman,
		Estete_HumanMove,
		Estete_HumanAttackWait,
		Estete_HumanAttack,
		Estete_Death,	 //���
		Estete_Death2,	 //���

	};

	enum TeruMode {
		Tank,
		Plane,
		Human,
	};

	enum EnAnimationClip {
		enAnimationClip_TankWait,
		enAnimationClip_TankAttack,
		enAnimationClip_TankToPlane,
		enAnimationClip_PlaneWait,
		enAnimationClip_PlaneToHuman,
		enAnimationClip_HumanWait,
		enAnimationClip_HumanAttack,
		enAnimationClip_HumanDeath,
		enAnimationClip_Num,  //�A�j���[�V�����N���b�v
	};

	//�|�W�V������Ԃ��֐�

	CVector3 Teruosuka::Getm_Position() {
		return m_position;
	}
	//�X�e�[�g��Ԃ��֐�
	int Teruosuka::GetEState() {
		return m_stete;
	}

	//�e�B���I�X�J���[�h��Ԃ��֐�
	int Teruosuka::GetTeruMode() {
		return Teru_Mode;
	}

	//�_���[�W�͈͂�������֐�
	float GetDamageLength() {
		return DamageLength;
	}

	//���������ʊ֐�
	int Teruosuka::SetDeath() {
		m_stete = Estete_Death2;
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

	//������HP������������
	void Damage(int x) {
		NowHP -= x;
		if (NowHP < 0) {//���̐��ɂȂ�Ȃ��悤�ɂ��Ă���
			NowHP = 0;
		}
	}

	//����HP��Ԃ�
	int GetHP() {
		return NowHP;
	}

	//�ő�HP��Ԃ�
	int GetMAXHP() {
		return MAXHP;
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

	/*
	��ԃ��[�h �~�T�C��
	��s�@���[�h �ړ�����
	�l���[�h �p���`����
	*/

	void Teru_TankMove();
	void Teru_TankAttack();
	void Teru_TankToPlane();
	void Teru_PlaneMove();
	void Teru_PlaneToHuman();
	void Teru_HumanMove();
	void Teru_HumanAttackWait(); 
	void Teru_HumanAttack();
	void TeruDeath();
	void TeruDeath2();

	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero; // ���W�B
	CQuaternion m_rotation = CQuaternion::Identity; //��]�B
	CVector3 m_scale = CVector3::One; // �g�嗦�B
	prefab::CSoundSource* ss;

	Estete m_stete = Estete_TankMove; //���
	CCharacterController m_charaCon; //�L�����R��
	TeruMode Teru_Mode = Tank;

	const float DamageLength = 2680.0f; //�_�����[�W���󂯂���͔͈͂�����

	int waveNo = 0; //������������Wave�̔ԍ�

	CVector3 DefPos = CVector3::Zero;

	int MAXHP = 9000; //�ő�HP
	int NowHP = MAXHP; //����HP

	////////////////////////////////////////////////////////////

	int AttackTimer = 0; //�U���ɑJ�ڂ���܂ł̃^�C�}�[
	const int AttackLimit = 60; //�U���ɑJ�ڂ���܂ł̐�������

	const int MisairuLimit = 30; //�U���ɑJ�ڂ���܂ł̐�������
	CVector3 MisairuMove = CVector3::Zero; //�~�T�C���̈ړ����x

	const int HumanAttackLimit = 90;
	float HumanColor = 0.0f;

	int DeathTimer = 0; //HP��0�ɂȂ��Ă���DeleteGO�����܂ł̃^�C�}�[ ���o�p
	const int ToumeiTimeMAX = 240; //���̎��ԂɂȂ�Ɠ����ɂȂ�
	const int DeathTimeMAX = 360; //���̏��

};


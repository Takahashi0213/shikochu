#pragma once
class SS_001 : public IGameObject
{
public:
	SS_001();
	~SS_001();
	bool Start();
	void Update();

	enum Estete {
		Estete_Move,	//�ړ�
		Estete_Attack1,  //�U��1
		Estete_Yobi1,	//�\������1
		Estete_Attack2,  //�U��2
		Estete_Yobi2,	//�\������2
		Estete_Death,	 //���
		Estete_Death2,	 //���

	};

	enum EnAnimationClip {
		enAnimationClip_move, //����
		enAnimationClip_wait, //�Î~
		enAnimationClip_Num,  //�A�j���[�V�����N���b�v
	};

	//�|�W�V������Ԃ��֐�

	CVector3 SS_001::Getm_Position() {
		return m_position;
	}
	//�X�e�[�g��Ԃ��֐�
	int SS_001::GetEState() {
		return m_stete;
	}
	//�_���[�W�͈͂�������֐�
	float GetDamageLength() {
		return DamageLength;
	}

	//���������ʊ֐�
	int SS_001::SetDeath() {
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
	�U��1���~�T�C��
	�U��2���r�[���I
	*/

	void SSMove();
	void SSYobi1();
	void SSAttack1();
	void SSYobi2();
	void SSAttack2();
	void SSDeath();
	void SSDeath2();

	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero; // ���W�B
	CQuaternion m_rotation = CQuaternion::Identity; //��]�B
	CVector3 m_scale = CVector3::One; // �g�嗦�B
	prefab::CSoundSource* ss;

	Estete m_stete = Estete_Move; //���
	CCharacterController m_charaCon; //�L�����R��

	const float DamageLength = 2680.0f; //�_�����[�W���󂯂���͔͈͂�����

	int waveNo = 0; //������������Wave�̔ԍ�

	CVector3 DefPos = CVector3::Zero;

	int MAXHP = 10000; //�ő�HP
	int NowHP = MAXHP; //����HP

	////////////////////////////////////////////////////////////

	int AttackTimer = 0; //�U���ɑJ�ڂ���܂ł̃^�C�}�[
	const int AttackLimit = 30; //�U���ɑJ�ڂ���܂ł̐�������

	int MisairuTimer = 0; //�~�T�C���p�^�C�}�[
	const int MisairuLimit = 24; //1���~�T�C�������̂ɂ����鎞��
	int MisairuCounter = 0; //�~�T�C���p�J�E���^
	int MisairuCountMAX = 4; //�~�T�C�������񐔁i�ρj
	CVector3 MisairuMove = CVector3::Zero; //�~�T�C���̈ړ����x
	CVector3 MyMove = CVector3::Zero; //�������������x�i�~�T�C���p�ꎞ�j

	//

	int BeamYobiTimer = 0; //�r�[�������p�^�C�}�[
	const int BeamYobiLimit = 80; //�r�[��������������
	int BeamTimer = 0; //�r�[�����˒��^�C�}�[
	const int BeamLimit = 100; //�r�[����������

	//

	int DeathTimer = 0; //HP��0�ɂȂ��Ă���DeleteGO�����܂ł̃^�C�}�[ ���o�p
	const int ToumeiTimeMAX = 240; //���̎��ԂɂȂ�Ɠ����ɂȂ�
	const int DeathTimeMAX = 360; //���̏��

};


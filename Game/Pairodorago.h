#pragma once
class Pairodorago : public IGameObject
{
public:
	Pairodorago();
	~Pairodorago();
	bool Start();
	void Update();

	enum Estete {
		Estete_Move,	//�ړ�
		Estete_Attack1,  //�U��1
		Estete_Yobi1,	//�\������1
		Estete_Attack2,  //�U��2
		Estete_Yobi2,	//�\������2
		Estete_Death	 //���

	};

	enum EnAnimationClip {
		enAnimationClip_move, //����
		enAnimationClip_yobi, //�\��
		enAnimationClip_attack, //�U��
		enAnimationClip_Num,  //�A�j���[�V�����N���b�v
	};

	//�|�W�V������Ԃ��֐�

	CVector3 Pairodorago::Getm_Position() {
		return m_position;
	}
	//�X�e�[�g��Ԃ��֐�
	int Pairodorago::GetEState() {
		return m_stete;
	}
	//�_���[�W�͈͂�������֐�
	float GetDamageLength() {
		return DamageLength;
	}

	//���������ʊ֐�
	int Pairodorago::SetDeath() {
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

	void PairoMove();
	void PairoYobi1();
	void PairoAttack1();
	void PairoYobi2();
	void PairoAttack2();
	void PairoDeath();

	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero; // ���W�B
	CQuaternion m_rotation = CQuaternion::Identity; //��]�B
	CVector3 m_scale = CVector3::One; // �g�嗦�B
	CVector3 shisoVec;

	Estete m_stete = Estete_Move; //���
	CCharacterController m_charaCon; //�L�����R��

	const float DamageLengthDEF = 2680.0f; //�_���[�W�����W�f�t�H���g�I�i���̂܂�܁j
	float DamageLength = 2680.0f; //�_�����[�W���󂯂���͔͈͂�����

	int waveNo = 0; //������������Wave�̔ԍ�

	const int MAXHP = 10000; //�ő�HP
	int NowHP = MAXHP; //����HP

	//

	int MoveTimer = 0;
	const int MoveLimit = 20;

	//

	int YobiTimer = 0; //�\������^�C�}�[
	const int YobiLimit = 80; //�\�����쐧������

	int AttackTimer = 0; //�U������^�C�}�[
	const int AttackLimit = 40; //�U�����쐧������
	const int AttackTiming = 10; //�U�����肪��������^�C�~���O

	//

	int DeathTimer = 0; //HP��0�ɂȂ��Ă���DeleteGO�����܂ł̃^�C�}�[ ���o�p
	const int ToumeiTimeMAX = 240; //���̎��ԂɂȂ�Ɠ����ɂȂ�
	const int DeathTimeMAX = 360; //���̏��

};


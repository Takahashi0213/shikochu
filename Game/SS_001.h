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
		Estete_Death	 //���

	};

	enum EnAnimationClip {
		enAnimationClip_move, //����
		enAnimationClip_Num,  //�A�j���[�V�����N���b�v
	};

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

	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero; // ���W�B
	CQuaternion m_rotation = CQuaternion::Identity; //��]�B
	CVector3 m_scale = CVector3::One; // �g�嗦�B

	Estete m_stete = Estete_Move; //���
	CCharacterController m_charaCon; //�L�����R��

	int waveNo = 0; //������������Wave�̔ԍ�

	const int MAXHP = 500; //�ő�HP
	int NowHP = MAXHP; //����HP

};


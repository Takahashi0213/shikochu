#pragma once
class shisokus : public IGameObject
{
public:
	shisokus();
	~shisokus();

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
		enAnimationClip_attack1, //�U��1
		enAnimationClip_yobi1, //�\������1
		/*enAnimationClip_attack2, //�U��2
		enAnimationClip_yobi2, //�\������2*/
		enAnimationClip_Num,  //�A�j���[�V�����N���b�v
	};

	bool Start();
	void Update();

	void shisoMove();
	void shisoYobi1();
	void shisoAttack1();
	void shisoYobi2();
	void shisoAttack2();
	void shisoDeath();

	CVector3 shisokus::Getm_Position() {
		return m_position;
	}
	//�X�e�[�g��Ԃ��֐�
	int shisokus::GetEState() {
		return m_stete;
	}
	//���������ʊ֐�
	int shisokus::SetDeath() {
		m_stete = Estete_Death;
		return 0;
	}
private:
	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero; // ���W�B
	CQuaternion m_rotation = CQuaternion::Identity; //��]�B
	CVector3 m_scale = CVector3::One; // �g�嗦�B
	CVector3 shisoVec;

	Estete m_stete = Estete_Move; //���
	CCharacterController m_charaCon; //�L�����R��

	//�ړ��֘A
	const float yobi1Range = 1500.0f; //�U�����鋗��

	//�\������֘A
	bool keisanflag = false;
	int yobitimer = 0;
	const float yobiwait = 60.0f;
	//�U���֘A


};


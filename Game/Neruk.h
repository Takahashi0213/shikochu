#pragma once
class NerukGenerator;
class Neruk : public IGameObject
{
public:
	Neruk();
	~Neruk();
	enum Estete {
		Estete_Select,
		Estete_Move,//�ړ�
		Estete_Attack,//�ړ�
		Estete_Death,	//��
		Estete_Death2,	//��
	};
	enum EnAnimationClip {
		enAnimationClip_move, //����
		enAnimationClip_Num,  //�A�j���[�V�����N���b�v
	};

	bool Start();
	void Update();

	//�|�W�V������Ԃ��֐�
	CVector3 Neruk::Getm_Position() {
		return m_position;
	}
	//�X�e�[�g��Ԃ��֐�
	int Neruk::GetEState() {
		return m_stete;
	}
	//���������ʊ֐�
	int Neruk::SetDeath() {
		m_stete = Estete_Death;
		return 0;
	}
	//���������ʊ֐�2
	int Neruk::SetDeath2() {
		m_stete = Estete_Death2;
		return 0;
	}

	//�_���[�W�͈͂�������֐�
	float GetDamageLength() {
		return DamageLength;
	}

	//������
	void Init(NerukGenerator* nerukGenerator)
	{
		m_nerukGenerator = nerukGenerator;
	}

private:
	void position1();
	void position2();
	void position3();
	void position4();
	void position5();
	void position6();

	void NeruSelect();
	void NeruMove();
	void NeruAttack();
	void NeruDeath();
	void NeruDeath2();

	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity; //��]�B
	CVector3 m_scale = CVector3::One; // �g�嗦�B
	CAnimationClip m_animClips[enAnimationClip_Num]; //�A�j���[�V�����N���b�v

	Estete m_stete = Estete_Select; //���

	CCharacterController m_charaCon; //�L�����R��

	//�ړ��֘A
	int posmove = 0;
	int animove = 0;

	//pos�֘A
	bool moveflag = false;
	int movetimer = 0;
	CVector3 pomove;
	//position1��
	const CVector3 oldpos1 = { 0.0f,6000.0f,1800.0f };
	const CVector3 pos1 = { 0.0f, 1200.0f, 1800.0f };
	const int moveflame1 = 300;
	//position2�E��
	const CVector3 oldpos2 = { 4000.0f,6000.0f,2300.0f };
	const CVector3 pos2 = { 1000.0f,500.0f,2300.0f };
	//position3����
	const CVector3 oldpos3 = { -4000.0f,6000.0f,2300.0f };
	const CVector3 pos3 = { -1000.0f,700.0f,2300.0f };

	//position4�E��
	const CVector3 oldpos4 = { 4000.0f,6000.0f,2300.0f };
	const CVector3 pos4 = { 600.0f,1200.0f,2300.0f };

	//position5����
	const CVector3 oldpos5 = { -4000.0f,6000.0f,2300.0f };
	const CVector3 pos5 = { -800.0f,300.0f,2300.0f };

	//position6�h�h�h�^��
	const CVector3 oldpos6 = { 0.0f,6000.0f,2000.0f };
	const CVector3 pos6 = { 0.0f,500.0f,2000.0f };


	//�U��
	bool attackflag = false;
	const float attackmove = 30.0f;
	int deathtimer = 0;
	CVector3 atmove;

	//�ړ��֘A
	int waittimer = 0;
	int timer = 0;
	const float GameOverMove = 30.0f;

	//movetype1
	const float up = 60.f;
	const float down = 120.f;

	//movetype2
	const float Right = 60.f;
	const float Left = 120.f;

	//movetype3
	const float Rightup = 30.f;
	const float Leftdown = 60.f;
	const float Leftup = 90.f;
	const float Rightdown = 120.f;

	//��
	const float deathMove = 420.0f;
	const float deathwait = 30.0f;
	const float deathattack = 120.f;
	CVector3 deathdiff;
	//�����_��
	int  moverandom = 0; //�����ꏊ�����p
	int  animesionrandom = 0; //�A�j���[�V���������p

	int oldmovecount = 3;

	const float DamageLength = 100.0f; //�_�����[�W���󂯂���͔͈͂�����
	NerukGenerator* m_nerukGenerator = nullptr;

};


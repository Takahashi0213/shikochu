#pragma once
class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();

	enum Estete {
		Estete_Attack,  //�U��
		Estete_Move, //�ړ�
		Estete_Death //��
	};

	enum Eattack {
		Eattack_0, //�������Ȃ�
		Eattack_1,
		Eattack_2,
		Eattack_3,
	};

	bool Start();
	void Update();
	//���
	void EnemyAttack();
	void EnemyMove();
	void EnemyDeath();

	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero; // ���W�B
	CQuaternion m_rotation = CQuaternion::Identity; //��]�B
	CVector3 m_scale = CVector3::One; // �g�嗦�B

	int attackcount = 0;
	Estete m_stete = Estete_Attack;		 //���
	Eattack m_attack = Eattack_1;		//�U��
	CCharacterController m_charaCon; //�L�����R��

};


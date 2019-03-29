#pragma once
#include "Player.h"
class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();

	enum Estete {
		Estete_Attack,  //�U��
		Estete_Move, //�ړ�
		Estete_Follow, //�ǔ�
		Estete_turn, //�ǔ�
		Estete_Death, //��
		Estete_yobi	//�\������
	};
	enum EnAnimationClip {
		enAnimationClip_walk, //����
		enAnimationClip_attack1, //����1
		enAnimationClip_attack01, //�U��1
		enAnimationClip_Num,  //�A�j���[�V�����N���b�v
	};
	bool Start();
	void Update();
	//���
	void EnemyAttack();
	void EnemyMove();
	void EnemyFollow();
	void EnemyDeath();
	void Enemyyobi();
	//�|�W�V������Ԃ��֐�
	CVector3 Enemy::Getm_Position(){
		return m_position;
	}
	//�X�e�[�g��Ԃ��֐�
	int Enemy::GetEState() {
		return m_stete;
	}
	//���������ʊ֐�
	int Enemy::SetDeath() {
		m_stete = Estete_Death;
		return 0;
	}
private:

	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero; // ���W�B
	CQuaternion m_rotation = CQuaternion::Identity; //��]�B
	CVector3 m_scale = CVector3::One; // �g�嗦�B

	CVector3 m_oldposition;
	CVector3 moveVec;
	CVector3 enemyVec;
	int move = 1;
	Estete m_stete = Estete_Move;		 //���
	CCharacterController m_charaCon; //�L�����R��
	int timer = 0;
	const int yobiwait = 50;//�\������̎���
	const int attackwait = 120;//�U������̎���
	const int rightmove = 200;//�E�ړ�
	const int leftmove = -200;//�E�ړ�
	const int distancemove = 600;//�ǔ��ɂȂ鋗��


};


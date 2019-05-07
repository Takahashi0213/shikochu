#pragma once

class Bunbogu : public IGameObject
{
public:
	Bunbogu();
	~Bunbogu();

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
	CVector3 Bunbogu::Getm_Position(){
		return m_position;
	}
	//�X�e�[�g��Ԃ��֐�
	int Bunbogu::GetEState() {
		return m_stete;
	}
	//���������ʊ֐�
	int Bunbogu::SetDeath() {
		m_stete = Estete_Death;
		return 0;
	}
private:

	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero; // ���W�B
	CQuaternion m_rotation = CQuaternion::Identity; //��]�B
	CVector3 m_scale = CVector3::One; // �g�嗦�B

	CVector3 moveVec;
	CVector3 enemyVec;
	Estete m_stete = Estete_Move; //���
	CCharacterController m_charaCon; //�L�����R��

	//�ړ��֘A
	const float followRange = 1000.0f; //�ǔ����鋗���i�ǔ�����߂�܂ł̋����j
	const float attackRange = 120.0f; //�U�����鋗��
	const float followSpeed = 80.0f; //�ǔ��̑��x

	//�����_���ړ��֘A
	int count = 0; //�����_���ړ��̃^�C�}�[
	int random = 0; //�����_���ړ��̕�������
	const int randomCount = 60; //�����_���ړ������؂�ւ��^�C�}�[
	const float randomSpeed = 30.3f; //�����_���ړ����x

	//�U���֘A
	int timer = 0; //�U���̃^�C�}�[
	const int yobiwait = 50; //�\������̎���
	const int attackwait = 120; //�U������̎���
	const float attackMoveRange = 50.0f; //�U�����̑O�i�����Ƒ��x

};


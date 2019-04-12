#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"

#include "Enemy.h"

class Player : public IGameObject
{
public:

	enum Player_State2D {
		Estate_Stay, //�ҋ@
		Estate_Dash, //�_�b�V��
		Estate_Death, //���S
	};
	enum Player_State3D {
		Estate_Stay2, //�ҋ@
		Estate_Dash2, //�_�b�V��
		Estate_Death2, //���S
	};

	Player();
	~Player();
	bool Start();
	void Update();
	void PlayerReset();//���񂾂Ƃ��ɐF�X���������܂�

	int Player::GetLife() {

		return m_Life;
	}

	//�|�W�V������Ԃ��֐�
	CVector3 Player::Getm_Position() {
		return position;
	}

private:

	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	CVector3 position = CVector3::Zero;
	CQuaternion rotation = CQuaternion::Identity;
	CVector3 m_scale = CVector3::One; // �g�嗦�B

	CVector3 m_moveSpeed = CVector3::Zero;	//�ړ����x�B
	CCharacterController m_charaCon;		//�L�����N�^�[�R���g���[���[�B
	
	Player_State2D player_state = Estate_Stay;		 //���
	Player_State3D player_state2 = Estate_Stay2;		 //3D���

	//�����Z�o�p
	CVector3 playerVec;
	//�ړ����x
	const float moveCrossKey = 20.0f; //�\���L�[���͎��̍ō����x
	const float moveSpeedMAX = 1000.0f; //���i�̍ō����x
	const float playerMoveSpeed = 4.0f;//�����̐��l��������ƈړ����x�ς��
	//����
	int m_Life = 0; //�����̎���
	int m_LifeCounter = 0; //���������J�E���^�[
	const int m_LifeSpeed = 5; //������������Ǝ����������x�ς��
	//���Z�b�g�p
	int ResetTimer = 0;
};


#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"

class Player : public IGameObject
{
public:

	enum Player_State {
		Estate_Stay, //�ҋ@
		Estate_Move, //�ړ�
		Estate_Dash, //�_�b�V��
		Estate_Death, //���S
	};

	Player();
	~Player();
	bool Start();
	void Update();
	int GetLife();

	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	CVector3 position = CVector3::Zero;
	CQuaternion rotation = CQuaternion::Identity;

	CVector3 m_moveSpeed = CVector3::Zero;	//�ړ����x�B
	CCharacterController m_charaCon;		//�L�����N�^�[�R���g���[���[�B

private:
	//�ړ����x
	const float moveCrossKey = 10.0f; //�\���L�[���͎��̍ō����x
	const float moveSpeedMAX = 1000.0f; //���i�̍ō����x
	const float playerMoveSpeed = 4.0f;//�����̐��l��������ƈړ����x�ς��
	//����
	int m_Life = 0; //�����̎���
	int m_LifeCounter = 0; //���������J�E���^�[
};


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

	const float moveCrossKey = 10.0f; //�\���L�[���͎��̍ō����x
	const float moveSpeedMAX = 200.0f; //���i�̍ō����x

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
	//����
	int m_Life = 0; //�����̎���
};


#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"
#include "tkEngine/light/tkPointLight.h"
#include "Enemy.h"

class Player : public IGameObject
{
public:

	enum Player_State {
		Estate_Stay, //�ҋ@
		Estate_Dash, //�_�b�V��
		Estate_Death, //���S
	};

	Player();
	~Player();
	bool Start();
	void Update();
	float Player::GetLifePercent(int x); 	//���݂̎���������float�ŕԂ����I

	//������Ԃ��֐�
	int Player::GetLife() {

		return m_Life;
	}

	//�|�W�V������Ԃ��֐�
	CVector3 Player::Getm_Position() {
		return position;
	}

	//�X�e�[�g��Ԃ��֐�
	int Player::GetState() {
			return player_state;
	}

private:

	//�����������x���Z�b�g
	void LifeSpeedReset() {
		m_LifeSpeed = m_LifeSpeedDEF;
	}

	//���C�g�������l�ɂ���֐�
	void LightReset() {
		PlayerEmission = PlayerEmissionDEF;
		PlayerLight = PlayerLightDEF;
		PlayerLightAttn = PlayerLightAttnDEF;
	}

	void PlayerReset(); //���񂾂Ƃ��ɐF�X���������܂�
	void PlayerJudge(); //���S����F�X

	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	CVector3 position = CVector3::Zero;
	CQuaternion rotation = CQuaternion::Identity;
	CVector3 m_scale = CVector3::One; //�g�嗦

	CVector3 m_moveSpeed = CVector3::Zero;	//�ړ����x�B
	CCharacterController m_charaCon;		//�L�����N�^�[�R���g���[���[�B
	
	Player_State player_state = Estate_Stay;		 //���

	//�����Z�o�p
	CVector3 playerVec;
	//�ړ����x
	const float moveCrossKey = 20.0f; //�\���L�[���͎��̍ō����x
	const float moveSpeedMAX = 1000.0f; //���i�̍ō����x
	const float playerMoveSpeed = 4.0f; //�����̐��l��������ƈړ����x�ς��
	const float dashSpeed2D = 100.0f; //2D���[�h���̑O�i���x
	const float dashSpeed3D = 10.0f; //3D���[�h���̑O�i���x
	//����
	int m_Life = 0; //�����̎���
	int m_LifeCounter = 0; //���������J�E���^�[
	const int m_Life_Decrease = 1; //�����l
	int m_LifeSpeed = 5; //������������Ǝ����������x�ς��
	const int m_LifeSpeedDEF = 5; //�f�t�H���g�����������x
	const int DashLife = 2; //�_�b�V�����͎�����0�ɂȂ�Ȃ��悤�ɂ���A���̍ŏ��l
	const int DashLifeSpeed = 2; //�_�b�V�����̎����������x
	//���Z�b�g�p
	int ResetTimer = 0; //���Z�b�g�p�^�C�}�[�B���̂܂܂̈Ӗ�
	const int ResetAverage = 60; //���������X�|�[������Ԋu
	//���֘A
	prefab::CPointLight* m_pointLig;	//�_�����B
	CVector3 PlayerEmission = CVector3::One; //�����̔����
	CVector3 PlayerLight = CVector3::One; //���͂̌�
	CVector3 PlayerLightAttn = CVector3::One; //����
	const CVector3 PlayerEmissionDEF = { 0.1f, 0.1f, 0.1f }; //�����̔�����f�t�H
	const CVector3 PlayerLightDEF = { 500.0f, 500.0f, 500.0f }; //���͂̌��f�t�H
	const CVector3 PlayerLightAttnDEF = { 50.0f, 2.0f, 0.0f }; //�����f�t�H
	const float LightXDEF = 100.0f;//�㏸�l
	const float AttnXDEF = 1.0f;//�㏸�l
	const float LightSpeed = 50.0f; //���������Ȃ�X�s�[�h ����������Ƌ�������悤�ɂȂ�
	const float AttnSpeed = 5000.0f;//����͈͂��L���Ȃ�X�s�[�h ����������Ƌ�������悤�ɂȂ�

};


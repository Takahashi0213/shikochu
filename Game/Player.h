#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"
#include "tkEngine/light/tkPointLight.h"

class Player : public IGameObject
{
	static Player* m_instance;
public:

	enum Player_State {
		Estate_Stay, //�ҋ@
		Estate_Dash, //�_�b�V��
		Estate_Death, //���S
	};
	//3D���[�h�ł̉��������X�e�[�g
	enum Dash_State3D{
		Estate_DEF, //�ʏ�
		Estate_Front, //����
		Estate_Back, //����
	};

	Player();
	~Player();
	bool Start();
	void Update();

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

	//3D�X�e�[�g��Ԃ��֐�
	int Player::GetState3D() {
		return Dash_state3D;
	}

	//��������������
	void Player::SetLife(int x) {
		m_Life -= x;
		if (m_Life < 0) {
			m_Life = 0;
		}
	}

	//���G���Ԓ��Ȃ�true�A�����łȂ����false��Ԃ�
	bool Player::MutekiChecker() {
		//���G���ԃ^�C�}�[���Q��
		if (MutekiTimer >= 0) {			
			return true; //���G����
		}
		else {
			return false; //���G�łȂ�
		}
	}

	//�C���X�^���X�̎擾
	static Player* Player::GetInstance(){
		return m_instance;
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
	void MutekiSupporter(); //���G���Ԓ��Ɏ��s���邺�`�`�`�`�`
	void LightStatusSupporter(); //�ĂԂ���������X�V�����

	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	CVector3 position = CVector3::Zero;
	CQuaternion rotation = CQuaternion::Identity;
	CVector3 m_scale = CVector3::One; //�g�嗦

	CVector3 m_moveSpeed = CVector3::Zero;	//�ړ����x�B
	CCharacterController m_charaCon;		//�L�����N�^�[�R���g���[���[�B
	
	Player_State player_state = Estate_Stay;		 //���
	Dash_State3D Dash_state3D = Estate_DEF;			 //3D�ł̑O�i���

	bool LaderFlag = false;

	//�����Z�o�p
	CVector3 playerVec;
	const float PosY_Min3D = -350.0f; //3D���[�h���A�n�ʂɖ��܂�Ȃ��悤�ɂ���̂�
	//�ړ����x
	const float moveCrossKey = 12.0f; //�\���L�[���͎��̍ō����x
	const float moveSpeedMAX = 600.0f; //���i�̍ō����x
	const float playerMoveSpeed = 12.0f; //�����̐��l��������ƈړ����x�ς��
	const float dashSpeed2D = 50.0f; //2D���[�h���̗����_�b�V�����x
	const float dashSpeed3D = 2.0f; //3D���[�h���̗����_�b�V�����x
	const float Advance3D = 200.0f; //3D���[�h���̃f�t�H���g�O�i���x
	const float Advance3D_PM = 100.0f; //3D���[�h���̉���������
	const float Advance3D_FrontHosei = 10.0f; //3D���[�h���̉����␳
	const float Advance3D_Move = 6.0f; //3D���[�h���̈ړ��␳
	const float A_DashSpeed = 2000.0f; //A�_�b�V���̑�����
	//����
	int m_Life = 0; //�����̎���
	int m_LifeCounter = 0; //���������J�E���^�[
	const int m_Life_Decrease = 1; //�����l
	int m_LifeSpeed = 5; //������������Ǝ����������x�ς��
	const int m_LifeSpeedDEF = 5; //�f�t�H���g�����������x
	const int DashLife = 2; //�_�b�V�����͎�����0�ɂȂ�Ȃ��悤�ɂ���A���̍ŏ��l
	const int DashLifeSpeed = 2; //�_�b�V�����̎����������x
	const int Dash_LifeGensyo = 5; //�_�b�V�����̎��������l
	//A�_�b�V������
	bool DashFlag = false; //�_�b�V������
	int DashTimeCount = -1; //�_�b�V���^�C���𐔂����
	const int DashTimeMAX = 60; //�_�b�V�����؂��t���[��
	//���Z�b�g�p
	int ResetTimer = 0; //���Z�b�g�p�^�C�}�[�B���̂܂܂̈Ӗ�
	const int ResetAverage = 60; //���������X�|�[������Ԋu
	//���֘A
	prefab::CPointLight* m_pointLig;	//�_�����B
	CVector3 PlayerEmission = CVector3::One; //�����̔����
	CVector3 PlayerLight = CVector3::One; //���͂̌�
	CVector3 PlayerLightAttn = CVector3::One; //����
	const float LightPosHosei = 30.0f; //�|�C���g���C�g��Y���␳�i2D���[�h�j
	const float LightPosHoseiZ = -30.0f; //�|�C���g���C�g��Z���␳�i3D���[�h�j
	const float LightHosei = 0.01f; //�͂��Ɍ���
	const CVector3 PlayerEmissionDEF = { 0.1f, 0.1f, 0.1f }; //�����̔�����f�t�H
	const CVector3 PlayerLightDEF = { 500.0f, 500.0f, 500.0f }; //���͂̌��f�t�H
	const CVector3 PlayerLightAttnDEF = { 50.0f, 2.0f, 0.0f }; //�����f�t�H
	const CVector3 EmissionColorDEF{ 2.0f,2.0f,2.0f }; //���f���̌��f�t�H
	const float LightXDEF = 500000.0f;//�㏸�l
	const float AttnXDEF = 0.2f;//�㏸�l
	const float LightSpeed = 5.0f; //���������Ȃ�X�s�[�h ����������Ƌ�������悤�ɂȂ�
	const float AttnSpeed = 10000.0f;//����͈͂��L���Ȃ�X�s�[�h ����������Ƌ�������悤�ɂȂ�
	const float DeathLight = 1.5f; //���񂾏u�ԂɃh�J���ƌ���{��
	const float DeathLight_Syusoku = 0.8f; //���񂾏u�Ԃ̌�����������{��
	const int DeathLightTime = 12; //���񂾏u�ԂɌ��鎞��
	//���͂̌�
	const float LightStatusDEF = 0.5f; //������f�t�H���g
	const float LightStatusMAX = 0.4f; //�����ɂ���Ė��邳�ɕ␳��������A���̍ő�l
	float LightStatus = LightStatusDEF; //����������
	const float LightHosei3D = 4.0f; //3D���[�h�ł̕␳����
	float Light_Nakama = 4.0f; //���Ԃ����񂾂Ƃ��̃��C�g�␳�̑傫��
	float minRange = 0.3f; //�ŏ��͈�
	float maxRange = 2.0f; //DEF�ő�͈� ���Ȃ킿�U���L�[��������MAX�̎��̖��邳�͈�
	//���G����
	const int MutekiAverage = 60 + ResetAverage; //���G�����܂ł̎��ԁi���X�|�[���Ԋu���܂ށj
	int MutekiTimer = -1; //���G���ԃ^�C�}�[ 0�ȏ�Ȃ�J�E���g�J�n����̂ŕ��i��-1
	//�G�t�F�N�g�֘A
	const CVector3 SpawnEffectScale = { 40.0f,40.0f,40.0f }; //�X�|�[���G�t�F�N�g�̑傫��
	const CVector3 DashEffectScale = { 20.0f,20.0f,20.0f }; //�X�|�[���G�t�F�N�g�̑傫��
	const float SpawnEffectY = 50.0f;//�X�|�[���G�t�F�N�g��Y�␳
	//�l���N
	bool bikkuriflag = false;
	//
	const float StarRange = 1.5f; //�����_�b�V�����̓����蔻��g���{��

	int StarPointTimer = 0; //�X�^�[�Q�[�W�㏸�^�C�}�[
	const int StarPointLimit = 60; //�X�^�[�Q�[�W�̏㏸��������

};


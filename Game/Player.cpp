#include "stdafx.h"
#include "Player.h"
#include "tkEngine/character/tkCharacterController.h"
#include "GameData.h"

Player::Player()
{
}

Player::~Player()
{
}

bool Player::Start() {

	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(30, 100, position);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0,"Bug");
	m_skinModelRender->Init(L"modelData/bug.cmo", nullptr, 0);

	//�Q�[���f�[�^����ő���������������Ă���
	GameData * gamedata = FindGO<GameData>("GameData");
	m_Life = gamedata->GetDEF_Life();

	return true;
}

void Player::Update() {

		//�ړ�
		if (Pad(0).IsPress(enButtonUp)) {
			m_moveSpeed.z += moveCrossKey;
		}
		if (Pad(0).IsPress(enButtonDown)) {
			m_moveSpeed.z -= moveCrossKey;
		}
		if (Pad(0).IsPress(enButtonRight)) {
			m_moveSpeed.x += moveCrossKey;
		}
		if (Pad(0).IsPress(enButtonLeft)) {
			m_moveSpeed.x -= moveCrossKey;
		}

		CVector3 stick = CVector3::Zero;
		stick.x = Pad(0).GetLStickXF();
		stick.y = 0.0f;
		stick.z = Pad(0).GetLStickYF();
		m_moveSpeed += stick * playerMoveSpeed;
		//�X�e�B�b�N���͂���ĂȂ���Ίɂ₩�X�g�b�v
		if (stick.x == 0.0f) {
			m_moveSpeed.x /= 1.2f;
		}
		if (stick.z == 0.0f) {
			m_moveSpeed.z /= 1.2f;
		}
		//�ړ����x���
		if (m_moveSpeed.x > moveSpeedMAX) {
			m_moveSpeed.x = moveSpeedMAX;
		}
		else if (m_moveSpeed.x < -moveSpeedMAX) {
			m_moveSpeed.x = -moveSpeedMAX;

		}
		if (m_moveSpeed.z > moveSpeedMAX) {
			m_moveSpeed.z = moveSpeedMAX;
		}
		else if (m_moveSpeed.z < -moveSpeedMAX) {
			m_moveSpeed.z = -moveSpeedMAX;

		}

	//�_�b�V���@�\
	if (Pad(0).IsTrigger(enButtonA)) {

		CVector3 Dash_Speed = m_moveSpeed;
		Dash_Speed.Normalize();
		Dash_Speed *= 1000.0f;
		m_moveSpeed += Dash_Speed;

		m_Life -= 5;
		if (m_Life < 0) {
			m_Life = 0; //0��菬�������Ȃ�
		}
	}

	//��������
	m_LifeCounter++;
	if (m_LifeCounter > 5) {
		m_LifeCounter = 0;
		m_Life -= 1;
		if (m_Life < 0) {
			m_Life = 0; //0��菬�������Ȃ�
		}
	}

	position = m_charaCon.Execute(m_moveSpeed);

	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		//�킩���
	}
	float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
	rotation.SetRotation(CVector3::AxisY, angle);

	//���f
	m_skinModelRender->SetPosition(position);
	m_skinModelRender->SetRotation(rotation);

}

int Player::GetLife() {

	return m_Life;
}
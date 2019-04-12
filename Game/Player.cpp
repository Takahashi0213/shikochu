#include "stdafx.h"
#include "Player.h"
#include "tkEngine/character/tkCharacterController.h"
#include "GameData.h"

Player::Player()
{
}

Player::~Player()
{
	DeleteGO(m_skinModelRender);
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

	GameData * gameData = FindGO<GameData>("GameData");
	int mode = gameData->GetGameMode();
	if (mode == 0) {

		switch (player_state) {

		case Estate_Stay://�ҋ@
		{
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

			//�����_�b�V��
			if (Pad(0).IsTrigger(enButtonY)) {
				GameData * gamedata = FindGO<GameData>("GameData");
				//�Q�[�W�̐F�X���擾����
				int Now_Star_Power = gamedata->GetStar_Power();
				int MAX_Star_Power = gamedata->GetMAXStar_Power();
				//�Q�[�W��MAX�Ȃ�
				if (Now_Star_Power == MAX_Star_Power) {
					//�_�b�V����ԂɂȂ邼�I�I�I�I�I�I
					player_state = Estate_Dash;
				}
			}
		}
		break;
		//case Estate_Dash://�_�b�V��
			//	break;
			//case Estate_Death://����ł���
			//	break;
		}

		//��������
		m_LifeCounter++;
		if (m_LifeCounter > m_LifeSpeed) {
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

		//�G�Ƃ̋������v�Z
		Enemy * enemy = FindGO<Enemy>("Enemy");
		CVector3 enemy_position = enemy->Getm_Position();
		CVector3 diff = enemy_position - position;
		playerVec = diff;

		if (diff.Length() < 80.0f) {
			m_Life = 0;//�G�ɂԂ�����
			int EState = enemy->GetEState();
			if (EState != 0) {//�G���U�����̎��łȂ�
				enemy->SetDeath();
			}
		}

		//�������c
		if (m_Life == 0) {
			//�����Ŏ���
			PlayerReset();
		}
	}
	else if (mode == 1) {
		switch (player_state2) {

		case Estate_Stay2://�ҋ@
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
			stick.y = Pad(0).GetLStickYF();
			stick.z = 0.0f;
			m_moveSpeed += stick * playerMoveSpeed;
			//�X�e�B�b�N���͂���ĂȂ���Ίɂ₩�X�g�b�v
			if (stick.x == 0.0f) {
				m_moveSpeed.x /= 1.2f;
			}
			if (stick.y == 0.0f) {
				m_moveSpeed.y /= 1.2f;
			}
			//�ړ����x���
			if (m_moveSpeed.x > moveSpeedMAX) {
				m_moveSpeed.x = moveSpeedMAX;
			}
			else if (m_moveSpeed.x < -moveSpeedMAX) {
				m_moveSpeed.x = -moveSpeedMAX;

			}
			if (m_moveSpeed.y > moveSpeedMAX) {
				m_moveSpeed.y = moveSpeedMAX;
			}
			else if (m_moveSpeed.y < -moveSpeedMAX) {
				m_moveSpeed.y = -moveSpeedMAX;

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
			break;
			//case Estate_Dash://�_�b�V��
			//	break;
			//case Estate_Death://����ł���
			//	break;
		}

		//��������
		m_LifeCounter++;
		if (m_LifeCounter > m_LifeSpeed) {
			m_LifeCounter = 0;
			m_Life -= 1;
			if (m_Life < 0) {
				m_Life = 0; //0��菬�������Ȃ�
			}
		}

		position = m_charaCon.Execute(m_moveSpeed);

		//�G�Ƃ̋������v�Z
		Enemy * enemy = FindGO<Enemy>("Enemy");
		CVector3 enemy_position = enemy->Getm_Position();
		CVector3 diff = enemy_position - position;
		playerVec = diff;

		if (diff.Length() < 80.0f) {
			m_Life = 0;//�G�ɂԂ�����
			int EState = enemy->GetEState();
			if (EState != 0) {//�G���U�����̎��łȂ�
				enemy->SetDeath();
			}
		}

		//�������c
		if (m_Life == 0) {
			//�����Ŏ���
			PlayerReset();
		}
	}
	//���f
	m_skinModelRender->SetPosition(position);
	m_skinModelRender->SetRotation(rotation);
	m_skinModelRender->SetScale(m_scale);

}

void Player::PlayerReset() {

	if (ResetTimer == 0) {
		player_state = Estate_Death;
		m_scale = CVector3::Zero;
		m_skinModelRender->SetScale(m_scale);

	}
	if (ResetTimer == 60) {
		//�Q�[���f�[�^����ő���������������Ă���
		GameData * gamedata = FindGO<GameData>("GameData");
		m_Life = gamedata->GetDEF_Life();
		ResetTimer = -1;
		gamedata->SetZanki(-1);//�c�@����
		player_state = Estate_Stay;
		//�����������x���߂�
		LifeSpeedReset();
		//���ɖ߂�
		position = { 0.0f,0.0f,0.0f };
		rotation = CQuaternion::Identity;
		m_scale = CVector3::One;
		m_moveSpeed = CVector3::Zero;
		m_skinModelRender->SetPosition(position);
		m_skinModelRender->SetRotation(rotation);
		m_skinModelRender->SetScale(m_scale);
	}
	ResetTimer++;

}
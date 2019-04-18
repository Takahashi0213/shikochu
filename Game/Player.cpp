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
	DeleteGO(m_pointLig);
}

bool Player::Start() {

	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(30, 100, position);

	//���C�g�̐��l��������
	LightReset();

	//�o��
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0,"Bug");
	m_skinModelRender->Init(L"modelData/bug.cmo", nullptr, 0);
	m_skinModelRender->SetEmissionColor(PlayerEmission);

	//�Q�[���f�[�^����ő���������������Ă���
	GameData * gamedata = FindGO<GameData>("GameData");
	m_Life = gamedata->GetDEF_Life();

	m_pointLig = NewGO<prefab::CPointLight>(0, "StarLight");
	m_pointLig->SetColor(PlayerLight);
	m_pointLig->SetAttn(PlayerLightAttn);

	return true;
}

void Player::Update() {

	//���݃��[�h
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
					m_LifeSpeed = 1;
					player_state = Estate_Dash;
				}
			}
		}
		break;
		case Estate_Dash://�_�b�V��

			CVector3 Dash_Speed = m_moveSpeed;
			Dash_Speed.Normalize();
			Dash_Speed *= dashSpeed2D;
			m_moveSpeed += Dash_Speed;
			//�����Q�[�W������
			GameData * gamedata = FindGO<GameData>("GameData");
			gamedata->Star_PowerChange(-DashLifeSpeed);
			//���������Q�[�W��0�Ȃ玀��
			int NowStarPower = gamedata->GetStar_Power();
			if (NowStarPower == 0) {
				m_Life = 0;
			}
		
		break;
		//case Estate_Death://����ł���

		//break;
		}

		//��������
		m_LifeCounter++;
		if (m_LifeCounter > m_LifeSpeed) {
			m_LifeCounter = 0;
			m_Life -= m_Life_Decrease;
			if (player_state == Estate_Dash) {
				if (m_Life < DashLife) {
					m_Life = DashLife; //DashLife��菬�������Ȃ�
				}
			}
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

		PlayerJudge();

	}
	else if (mode == 1) {

		switch (player_state) {

		case Estate_Stay://�ҋ@
		{
			//�ړ�
			if (Pad(0).IsPress(enButtonUp)) {
				m_moveSpeed.y += moveCrossKey;
			}
			if (Pad(0).IsPress(enButtonDown)) {
				m_moveSpeed.y -= moveCrossKey;
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

			if (Pad(0).IsTrigger(enButtonY)) {
				GameData * gamedata = FindGO<GameData>("GameData");
				//�Q�[�W�̐F�X���擾����
				int Now_Star_Power = gamedata->GetStar_Power();
				int MAX_Star_Power = gamedata->GetMAXStar_Power();
				//�Q�[�W��MAX�Ȃ�
				if (Now_Star_Power == MAX_Star_Power) {
					//�_�b�V����ԂɂȂ邼�I�I�I�I�I�I
					m_LifeSpeed = 1;
					player_state = Estate_Dash;
				}
			}
		}
			break;
		case Estate_Dash://�_�b�V��

			m_moveSpeed.z += dashSpeed3D; //�S���O�i�I
			//�����Q�[�W������
			GameData * gamedata = FindGO<GameData>("GameData");
			gamedata->Star_PowerChange(-DashLifeSpeed);
			//���������Q�[�W��0�Ȃ玀��
			int NowStarPower = gamedata->GetStar_Power();
			if (NowStarPower == 0) {
				m_Life = 0;
			}

			break;
			//case Estate_Death://����ł���
			//	break;
		}

		//��������
		m_LifeCounter++;
		if (m_LifeCounter > m_LifeSpeed) {
			m_LifeCounter = 0;
			m_Life -= m_Life_Decrease;
			if (player_state == Estate_Dash) {
				if (m_Life < DashLife) {
					m_Life = DashLife; //DashLife��菬�������Ȃ�
				}
			}
			if (m_Life < 0) {
				m_Life = 0; //0��菬�������Ȃ�
			}
		}

		position = m_charaCon.Execute(m_moveSpeed);

		PlayerJudge();

	}

	//����ł��Ȃ���Ό���
	if (player_state != Estate_Death) {

		//������������ɉ����Ē�������
		int LightLoop = GetLifePercent(1);
		int LoopX = 0;
		float LightX = LightXDEF;//�㏸�l
		float AttnX = AttnXDEF;
		LightReset();
		for (; LightLoop > 0; LightLoop--) {
			PlayerLight.x = PlayerLight.x + LightX;
			PlayerLight.y = PlayerLight.y + LightX;
			PlayerLight.z = PlayerLight.z + LightX;
			PlayerLightAttn.x = PlayerLightAttn.x + AttnX;

			LoopX++;

			LightX = LightXDEF;//�㏸�l
			AttnX = AttnXDEF;
			LightX += (float)(LoopX * LoopX / LightSpeed);
			AttnX += (float)(LoopX * LoopX / AttnSpeed);

		}

	}

	//���C�g
	m_pointLig->SetPosition(position);
	m_pointLig->SetColor(PlayerLight);
	m_pointLig->SetAttn(PlayerLightAttn);
	//���f
	m_skinModelRender->SetPosition(position);
	m_skinModelRender->SetRotation(rotation);
	m_skinModelRender->SetScale(m_scale);

}

void Player::PlayerJudge(){

	//�G�Ƃ̋������v�Z
	Enemy * enemy = FindGO<Enemy>("Enemy");
	CVector3 enemy_position = enemy->Getm_Position();
	CVector3 diff = enemy_position - position;
	playerVec = diff;

	//����ł��Ȃ���ΐڐG����
	if (player_state != Estate_Dash) {
		if (diff.Length() < 80.0f) {
			m_Life = 0;//�G�ɂԂ�����
			int EState = enemy->GetEState();
			if (EState != 0) {//�G���U�����̎��łȂ�
				enemy->SetDeath();
			}
		}
	}

	//�������c
	if (m_Life == 0) {
		//�_�b�V�����Ȃ痬���Q�[�W��0�ɂ���
		if (player_state == Estate_Dash) {
			GameData * gamedata = FindGO<GameData>("GameData");
			gamedata->StarPowerZero();
		}
		//�����Ŏ���
		PlayerReset();
	}
}

void Player::PlayerReset() {

	if (ResetTimer == 0) {

		//����ł��܂����I
		player_state = Estate_Death;
		
		//���C�g�߂�
		LightReset();

		//�ړ���~
		m_moveSpeed = CVector3::Zero;

		//m_scale���[���ɂ��Ď��񂾂悤�Ɍ���������
		m_scale = CVector3::Zero;
		m_skinModelRender->SetScale(m_scale);

	}
	if (ResetTimer == ResetAverage) {
		//�Q�[���f�[�^����ő���������������Ă���
		GameData * gamedata = FindGO<GameData>("GameData");
		m_Life = gamedata->GetDEF_Life();
		ResetTimer = -1;
		gamedata->SetZanki(-1);//�c�@����
		//��Ԃ�߂�
		player_state = Estate_Stay;
		//�����������x���߂�
		LifeSpeedReset();
		//�����������߂�
		position = { 0.0f,0.0f,0.0f };
		rotation = CQuaternion::Identity;
		m_scale = CVector3::One;
		//�͂��B
		m_skinModelRender->SetPosition(position);
		m_skinModelRender->SetRotation(rotation);
		m_skinModelRender->SetScale(m_scale);
	}

	ResetTimer++;

}

float Player::GetLifePercent(int x){//x=0�Ŋ������Ax=1�Ō����l��Ԃ�

	//�Q�[���f�[�^����ő���������������Ă���
	GameData * gamedata = FindGO<GameData>("GameData");
	int DEF_Life = gamedata->GetDEF_Life();

	if (x == 0) {
		float player_percent = m_Life / DEF_Life;
		return player_percent;
	}
	else if (x == 1) {
		int player_Gensyou = DEF_Life - m_Life;
		return player_Gensyou;
	}

}

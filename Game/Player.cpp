#include "stdafx.h"
#include "Player.h"
#include "tkEngine/character/tkCharacterController.h"
#include "GameData.h"
#include "EffectManager.h"
#include "Bunbogu.h"
#include "Bullet.h"
#include "Neoriku.h"
#include "Radar.h"
#include "shisokus.h"

Player* Player::m_instance = nullptr;

Player::Player()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɃv���C���[���o�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;

}

Player::~Player()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(m_pointLig);

	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
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
	GameData * gamedata = GameData::GetInstance();
	m_Life = gamedata->GetDEF_Life();

	m_pointLig = NewGO<prefab::CPointLight>(0, "StarLight");
	m_pointLig->SetColor(PlayerLight);
	m_pointLig->SetAttn(PlayerLightAttn);

	NewGO<Radar>(0);

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
			m_moveSpeed *= 0.98f;
			/*if (stick.x == 0.0f) {
				m_moveSpeed.x /= 1.2f;
			}
			if (stick.z == 0.0f) {
				m_moveSpeed.z /= 1.2f;
			}*/
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
				Dash_Speed *= A_DashSpeed;
				m_moveSpeed += Dash_Speed;

				//�_�b�V���t���O�Z�b�g
				DashFlag = true;
				if (DashTimeCount == -1) {
					DashTimeCount = 0;
				}

				m_Life -= Dash_LifeGensyo;
				if (m_Life < 0) {
					m_Life = 0; //0��菬�������Ȃ�
				}
			}

			//�_�b�V����ԃJ�E���g
			if (DashTimeCount >= -1) {
				DashTimeCount++;
				if (DashTimeCount >= DashTimeMAX) { //�_�b�V����Ԃ����Ԑ؂�Ȃ�
					DashTimeCount = -1;
					DashFlag = false;
				}
			}

			//�����_�b�V��
			if (Pad(0).IsTrigger(enButtonY)) {
				GameData * gamedata = GameData::GetInstance();
				//�Q�[�W�̐F�X���擾����
				int Now_Star_Power = gamedata->GetStar_Power();
				int MAX_Star_Power = gamedata->GetMAXStar_Power();
				//�Q�[�W��MAX�Ȃ�
				if (Now_Star_Power == MAX_Star_Power) {
					//�_�b�V����ԂɂȂ邼�I�I�I�I�I�I
					m_LifeSpeed = 1;
					player_state = Estate_Dash;
					DashFlag = true;
					DashTimeCount = -2; //��������Ȃ��_�b�V����ԂɂȂ�
				}
			}
		}
		break;
		case Estate_Dash://�_�b�V��

			EffectManager * effectmanager = EffectManager::GetInstance();
			effectmanager->EffectPlayer(EffectManager::star, position, SpawnEffectScale/2);
			effectmanager->EffectPlayer(EffectManager::star, position, SpawnEffectScale / 2);
			effectmanager->EffectPlayer(EffectManager::star, position, SpawnEffectScale / 2);
			effectmanager->EffectPlayer(EffectManager::star, position, SpawnEffectScale / 2);

			//�ړ�
			CVector3 Dash_Speed = m_moveSpeed;
			Dash_Speed.Normalize();
			Dash_Speed *= dashSpeed2D;
			m_moveSpeed += Dash_Speed;
			//�����Q�[�W������
			GameData * gamedata = GameData::GetInstance();
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

		//���G���Ԓ��Ȃ���s
		if (MutekiTimer >= 0) {
			//���G��Ԃ͓G���ђʂ������̂ŁA�L�����R�����g�킸�ɓ������B

			CVector3 addPos = m_moveSpeed * GameTime().GetFrameDeltaTime();
			position += addPos;
			//�L�����R�����Ǐ]�����Ă����Ȃ��ƁA���G���Ԃ��I������Ƃ��ɖ߂���Ă��܂��̂�
			//�L�����R���ɍ��W��ݒ肵�Ă����B
			m_charaCon.SetPosition(position);
		}
		else {
			position = m_charaCon.Execute(m_moveSpeed);
		}
		if (fabsf(m_moveSpeed.x) < 0.001f
			&& fabsf(m_moveSpeed.z) < 0.001f) {
			//�킩���
		}
		float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
		rotation.SetRotation(CVector3::AxisY, angle);

		PlayerJudge();

	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	else if (mode == 1) {

		switch (player_state) {

		case Estate_Stay://�ҋ@
		{
			//�ړ�
			if (Pad(0).IsPress(enButtonUp)) {
				m_moveSpeed.y += moveCrossKey * (Advance3D_Move + Advance3D_Move);
			}
			if (Pad(0).IsPress(enButtonDown)) {
				m_moveSpeed.y -= moveCrossKey * (Advance3D_Move + Advance3D_Move);
			}
			if (Pad(0).IsPress(enButtonRight)) {
				m_moveSpeed.x += moveCrossKey * (Advance3D_Move + Advance3D_Move);
			}
			if (Pad(0).IsPress(enButtonLeft)) {
				m_moveSpeed.x -= moveCrossKey * (Advance3D_Move + Advance3D_Move);
			}

			CVector3 stick = CVector3::Zero;
			stick.x = Pad(0).GetLStickXF();
			stick.y = Pad(0).GetLStickYF();
			stick.z = 0.0f;
			m_moveSpeed += stick * (playerMoveSpeed*Advance3D_Move);
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

			//��������
			if (Pad(0).IsPress(enButtonA)) {
				//������Ԃ�
				m_Life -= 2;
				DashFlag = true;
				Dash_state3D = Estate_Front;
			}
			else if (Pad(0).IsPress(enButtonB)) {
				//������Ԃ�
				DashFlag = false;
				Dash_state3D = Estate_Back;
			}
			else {
				//�ʏ��Ԃ�
				DashFlag = false;
				Dash_state3D = Estate_DEF;
			}

			//�����_�b�V��
			if (Pad(0).IsTrigger(enButtonY)) {
				GameData * gamedata = GameData::GetInstance();
				//�Q�[�W�̐F�X���擾����
				int Now_Star_Power = gamedata->GetStar_Power();
				int MAX_Star_Power = gamedata->GetMAXStar_Power();
				//�Q�[�W��MAX�Ȃ�
				if (Now_Star_Power == MAX_Star_Power) {
					//�_�b�V����ԂɂȂ邼�I�I�I�I�I�I
					m_LifeSpeed = 2;
					DashFlag = true;
					player_state = Estate_Dash;
				}
			}
		}
		//�����O�i
		switch (Dash_state3D) {
		case Estate_DEF:
			m_moveSpeed.z = Advance3D;
			break;
		case Estate_Front:
			m_moveSpeed.z = Advance3D + Advance3D_PM * Advance3D_FrontHosei;
			break;
		case Estate_Back:
			m_moveSpeed.z = Advance3D - Advance3D_PM;
			break;
		}
			break;
		case Estate_Dash://�_�b�V��

			EffectManager * effectmanager = EffectManager::GetInstance();
			CVector3 ef_position = position;
			ef_position.z += 200.0f;
			effectmanager->EffectPlayer(EffectManager::star, ef_position, SpawnEffectScale / 2);
			effectmanager->EffectPlayer(EffectManager::star, ef_position, SpawnEffectScale / 2);
			effectmanager->EffectPlayer(EffectManager::star, ef_position, SpawnEffectScale / 2);
			effectmanager->EffectPlayer(EffectManager::star, ef_position, SpawnEffectScale / 2);

			m_moveSpeed.z = Advance3D + Advance3D_PM * (Advance3D_FrontHosei*dashSpeed3D); //�S���O�i�I
			//�����Q�[�W������
			GameData * gamedata = GameData::GetInstance();
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

		//���G���Ԓ��Ȃ���s
		if (MutekiTimer >= 0) {
			//���G��Ԃ͓G���ђʂ������̂ŁA�L�����R�����g�킸�ɓ������B
			CVector3 addPos = m_moveSpeed * GameTime().GetFrameDeltaTime();
			position += addPos;
			//�L�����R�����Ǐ]�����Ă����Ȃ��ƁA���G���Ԃ��I������Ƃ��ɖ߂���Ă��܂��̂�
			//�L�����R���ɍ��W��ݒ肵�Ă����B
			m_charaCon.SetPosition(position);
		}
		else {
			position = m_charaCon.Execute(m_moveSpeed);
		}

		//�n�ʂɖ��܂�Ȃ��悤�ɂ���
		if (position.y < PosY_Min3D) {
			position.y = PosY_Min3D;
		}

		PlayerJudge();

	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	else if (mode == 2) {

		PlayerJudge();

		}
	else if (mode == 3) {

		//�Ȃ�������
		SetActiveFlag(false);
		//m_scale���[���ɂ��Ď��񂾂悤�Ɍ���������
		m_scale = CVector3::Zero;
		position = { 10000.0f,10000.0f,0.0f };

	}
	//����ł��Ȃ���Ό���
	if (player_state != Estate_Death) {

		//������������ɉ����Ē�������
		GameData * gamedata = GameData::GetInstance();
		int LightLoop = (int)gamedata->GetLifePercent(1);
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

	//���G���Ԓ��Ȃ���s
	if (MutekiTimer >= 0) {
		MutekiSupporter();
	}

	//���[�h�ɉ����ă��C�g������ς��܂�
	if (mode == 0 || mode == 3) {
		CVector3 pos = position;
		pos.y += LightPosHosei;
		m_pointLig->SetPosition(pos);
		m_pointLig->SetColor(PlayerLight * LightHosei);
		m_pointLig->SetAttn(PlayerLightAttn);
		m_skinModelRender->SetEmissionColor(EmissionColorDEF);
		GraphicsEngine().GetTonemap().SetLuminance(0.56f);
	}
	else if (mode == 1) {
		CVector3 pos = position;
		pos.z += LightPosHoseiZ;
		m_pointLig->SetPosition(pos);
		m_pointLig->SetColor(PlayerLight * LightHosei);
		m_pointLig->SetAttn(PlayerLightAttn);
		m_skinModelRender->SetEmissionColor(EmissionColorDEF);
		GraphicsEngine().GetTonemap().SetLuminance(0.28f);
	}
	/////////////////////////////////////////////
	if (mode == 3) {//���U���g���͐�Ύ��ȂȂ��I
		//�Q�[���f�[�^����ő���������������Ă���
		GameData * gamedata = GameData::GetInstance();
		m_Life = gamedata->GetDEF_Life();
	}
	/////////////////////////////////////////////

	//��������C�g
	if (player_state != Estate_Death) {
		LightStatusSupporter(); //����łȂ��Ƃ�������
	}
	//���f
	m_skinModelRender->SetPosition(position);
	m_skinModelRender->SetRotation(rotation);
	m_skinModelRender->SetScale(m_scale);

}

//�����F�X
void Player::PlayerJudge() {

	//�u���{�[�O�Ƃ̋������v�Z
	QueryGOs<Bunbogu>("bun", [&](Bunbogu* bunbogu) {
		if (bunbogu->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 enemy_position = bunbogu->Getm_Position();
		CVector3 diff = enemy_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = bunbogu->GetDamageLength();
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�M���M���{�[�i�X���������邩�m�F
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//�������[����
					m_Life = 0;

					int EState = bunbogu->GetEState();
					if (EState != 0 && DashFlag == true) {//�G���U�����̎��łȂ����_�b�V����ԂȂ�c

						bunbogu->SetDeath();//���O������

						if (Hantei == true) {
							//�M���M���{�[�i�X�J�E���g��+1
							gamedata->GiriCounter();
							//�{�[�i�X�����̃G�t�F�N�g��\��
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::spawn, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}
				}
			}
		}
		return true;
		});

	//�ʂƂ̋������v�Z
	QueryGOs<Bullet>("bullet", [&](Bullet* bullet) {
		CVector3 bullet_position = bullet->Getm_Position();
		CVector3 diff = bullet_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = bullet->GetDamageLength();
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�������[����
					m_Life = 0;

					bullet->SetDeath();//���O������

				}
			}
		}
		return true;
		});

	//�l�I���N�Ƃ̋������v�Z
	QueryGOs<Neoriku>("neo", [&](Neoriku* neoriku) {
		if (neoriku->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 neoriku_position = neoriku->Getm_Position();
		CVector3 diff = neoriku_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = neoriku->GetDamageLength();
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�M���M���{�[�i�X���������邩�m�F
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//�������[����
					m_Life = 0;

					if (DashFlag == true) {//�_�b�V����ԂȂ�c

						neoriku->SetDeath();//���O������

						if (Hantei == true) {
							//�M���M���{�[�i�X�J�E���g��+1
							gamedata->GiriCounter();
							//�{�[�i�X�����̃G�t�F�N�g��\��
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::spawn, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//�V�[�\�[�N�X�Ƃ̋������v�Z
	QueryGOs<shisokus>("shiso", [&](shisokus* Shisok) {
		if (Shisok->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 Shisok_position = Shisok->Getm_Position();
		CVector3 diff = Shisok_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = Shisok->GetDamageLength();
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�_���[�W��O�����Čv�Z
					GameData * gamedata = GameData::GetInstance();
					bool dash;
					if (player_state == Estate_Dash) {
						dash = true;
					}
					else {
						dash = false;
					}
					int Damage = (int)gamedata->DamageKeisan(dash);

					//�������[����
					m_Life = 0;

					int EState = Shisok->GetEState();
					if (EState != 1 && DashFlag == true) {//�G���U�����̎��łȂ����_�b�V����ԂȂ�c

						//�I���@�I
						Shisok->Damage(Damage);

					}


				}
			}
		}
		return true;
		});



	//�������c
	if (m_Life == 0) {
		//�_�b�V�����Ȃ痬���Q�[�W��0�ɂ���
		if (player_state == Estate_Dash) {
			GameData * gamedata = GameData::GetInstance();
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
		
		//�ړ���~
		m_moveSpeed = CVector3::Zero;

		//���G���Ԃ̏����I
		MutekiTimer = 0;

	}
	
	//����Ŕ������鎞��
	if (ResetTimer <= DeathLightTime/2){
		//���̔���
		PlayerEmission *= DeathLight;
		PlayerLight *= DeathLight;
	}
	else if (ResetTimer < DeathLightTime) {
		//���̔�������
		PlayerEmission *= DeathLight_Syusoku;
		PlayerLight *= DeathLight_Syusoku;
	}
	else if (ResetTimer == DeathLightTime) {

		//���C�g�߂�
		LightReset();

		//m_scale���[���ɂ��Ď��񂾂悤�Ɍ���������
		m_scale = CVector3::Zero;
		m_skinModelRender->SetScale(m_scale);

	}
	//
	//�C���^�[�o���I��
	//
	if (ResetTimer == ResetAverage) {
		//�Q�[���f�[�^����ő���������������Ă���
		GameData * gamedata = GameData::GetInstance();
		m_Life = gamedata->GetDEF_Life();
		int mode = gamedata->GetGameMode();
			//���`�`�`�`�`�`
			ResetTimer = -1;
			gamedata->SetZanki(-1);//�c�@����
			 //��Ԃ�߂�
			player_state = Estate_Stay;
			//�����������x���߂�
			LifeSpeedReset();
			//�����������߂�
			position = CVector3::Zero;
			m_charaCon.SetPosition(position); //�L�����R�����߂���
			rotation = CQuaternion::Identity;
			m_scale = CVector3::One;
			LightStatus = LightStatusDEF;
			//�͂��B
			m_skinModelRender->SetPosition(position);
			m_skinModelRender->SetRotation(rotation);
			m_skinModelRender->SetScale(m_scale);
			//�ړ����I������̂ŃG�t�F�N�g���Đ��i�ړ���ɂ��Ȃ��Ǝ��񂾏ꏊ�ōĐ�����Ă��܂��̂Łj
			EffectManager * effectmanager = EffectManager::GetInstance();
			if (mode == 0) {
				effectmanager->EffectPlayer(EffectManager::spawn, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale);
			}
			else if (mode == 1) {
				effectmanager->EffectPlayer(EffectManager::spawn, { position.x,position.y,position.z + SpawnEffectY }, SpawnEffectScale);
			}

		//�Վ����[�h�`�F���W
		//gamedata->SwapGameMode();

	}

	ResetTimer++;

}

void Player::MutekiSupporter() {

	//�^�C�}�[���Z
	MutekiTimer++;

	if (MutekiTimer >= ResetAverage) {
		//�����œ_�ŏ���
		static int TenmetuTimer = 0;
		if (TenmetuTimer % 2 == 0) {
			//����
			m_skinModelRender->SetActiveFlag(true);
		}
		else {
			//�
			m_skinModelRender->SetActiveFlag(false);
		}
		TenmetuTimer++;
	}

	//���Ԑ؂�
	if (MutekiTimer >= MutekiAverage) {
		MutekiTimer = -1; //���G��߂�
		m_skinModelRender->SetActiveFlag(true);
	}
}

void Player::LightStatusSupporter() {

	//�Ăяo��
	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();
	float RightHosei = 1.0f - gamedata->ZankiWariai(); //�t���c
	float range = minRange * (1.0f - RightHosei) + maxRange * RightHosei;

	//LightStatus�̒l��ݒ�
	float LightX = gamedata->GetLifePercent(0);
	LightX = 1.0f - LightX; //����Ŋ������킩��܂��I�I�I�I
	LightStatus = LightStatusMAX * LightX;
	range += LightStatus;

	//�ӂ͂͂�
	if (mode == 1) {
		LightStatus *= LightHosei3D;
	}

	//�Z�b�g(^_-)-��
	SetSpecialLigRange(range);

}
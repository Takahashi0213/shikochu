#include "stdafx.h"
#include "Player.h"
#include "tkEngine/character/tkCharacterController.h"
#include "GameData.h"
#include "EffectManager.h"
#include "Bullet.h"
#include "Bullet2.h"
#include "Bullet3.h"
#include "Bullet4.h"
#include "Bullet5.h"
#include "Bullet6.h"
#include "Radar.h"
#include "NakamaLight.h"
#include "SaveData.h"
#include "SkillData.h"
#include "StarComet.h"

//Enemy
#include "Neoriku.h"
#include "Neruk.h"
#include "shisokus.h"
#include "soukabuto.h"
#include "Nerubikkuri.h"
#include "Bunbogu.h"
#include "Benite.h"
#include "Nibo.h"
#include "Sekuteimu.h"
#include "Ekku.h"
#include "Pi_rabi.h"
#include "Fairo.h"
#include "Pairodorago.h"
#include "Morikon.h"
#include "Riritto.h"
#include "Arukasya.h"
#include "SS_001.h"
#include "Misairu.h"
#include "Kikochu.h"
#include "Uminoushi.h"
#include "Akoyadokari.h"
#include "Morinchu.h"
#include "Kirabi.h"
#include "Suteira.h"
#include "Idando.h"
#include "Kodan.h"
#include "Taidol.h"
#include "Suroku.h"
#include "Mimitto.h"
#include "Tizutyo.h"
#include "Kuubo.h"
#include "Toripipi.h"
#include "Teruosuka.h"
#include "Atsukaru.h"
#include "Metoporisu.h"

//�M�~�b�N
#include "AppleBomb.h"
#include "Train1.h"
#include "Train2.h"

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
	if (LaderFlag == false) {
		DeleteGOs("Radar");
	}
	//DeleteGOs("NakamaLight");
	DeleteGOs("StarComet");

	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
}

bool Player::Start() {

	SoundEngine().SetListenerFront({0.0f, 0.0f, 1.0f});
	SoundEngine().SetListenerUp({ 0.0f, 1.0f, 0.0f });

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

	SaveData * savedata = SaveData::GetInstance();
	if (savedata->GetSkill(false) == 18) { //�J�~�J�[�o�g��
		m_LifeSpeed = m_LifeSpeedDEF / 2;
	}
	else {
		m_LifeSpeed = m_LifeSpeedDEF;
	}

	NewGO<Radar>(0, "Radar");
	NewGO<StarComet>(0, "StarComet");
	//NewGO<NakamaLight>(0, "NakamaLight");

	return true;
}

void Player::Update() {

	//���݃��[�h
	GameData * gameData = GameData::GetInstance();
	SaveData * savedata = SaveData::GetInstance();
	int mode = gameData->GetGameMode();

	if (mode == 0) {

		switch (player_state) {

		case Estate_Stay://�ҋ@
		{
			//�ړ�
			float Hosei = 0.0f;
			if (NowSkillNo == 8) { //�i�K���{�V���Ȃ�␳��ݒ肷��
				Hosei += Nagareboshi;
			}
			if (savedata->GetSkill(false) == 18) { //�J�~�J�[�o�g��
				Hosei += Kamikaze;
			}
			if (savedata->GetSkill(false) == 19) { //�A�N��
				Hosei += Akumu;
			}

			if (Pad(0).IsPress(enButtonUp)) {
				m_moveSpeed.z += (moveCrossKey + Hosei);
			}
			if (Pad(0).IsPress(enButtonDown)) {
				m_moveSpeed.z -= (moveCrossKey + Hosei);
			}
			if (Pad(0).IsPress(enButtonRight)) {
				m_moveSpeed.x += (moveCrossKey + Hosei);
			}
			if (Pad(0).IsPress(enButtonLeft)) {
				m_moveSpeed.x -= (moveCrossKey + Hosei);
			}

			CVector3 stick = CVector3::Zero;
			stick.x = Pad(0).GetLStickXF();
			stick.y = 0.0f;
			stick.z = Pad(0).GetLStickYF();

			m_moveSpeed += stick * (playerMoveSpeed + Hosei);

			m_moveSpeed *= 0.98f;

			//�X�e�B�b�N���͂���ĂȂ���Ίɂ₩�X�g�b�v
			if (NowSkillNo == 8) {
				//�ړ����x���
				if (m_moveSpeed.Length() > moveSpeedMAX * 2.0f) {
					m_moveSpeed.Normalize();
					m_moveSpeed *= (moveSpeedMAX * 2.0f);
				}
			}
			else {
				//�ړ����x���
				if (m_moveSpeed.Length() > moveSpeedMAX) {
					m_moveSpeed.Normalize();
					m_moveSpeed *= moveSpeedMAX;
				}
			}

			//�_�b�V���@�\
			if (Pad(0).IsTrigger(enButtonA)) {

				prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
				//SE�Đ�
				ss->Init(L"sound/dash.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				CVector3 Dash_Speed = m_moveSpeed;
				Dash_Speed.Normalize();
				Dash_Speed *= A_DashSpeed;
				m_moveSpeed += Dash_Speed;

				CVector3 E_Pos = position;
				E_Pos.y += SpawnEffectY;
				EffectManager * effectmanager = EffectManager::GetInstance();
				effectmanager->EffectPlayer(EffectManager::Dash, E_Pos, DashEffectScale, true);
				effectmanager->EffectPlayer(EffectManager::Dash2, E_Pos, DashEffectScale, true, true);

				//�_�b�V���t���O�Z�b�g
				DashFlag = true;
				A_DashFlag = true;
				if (DashTimeCount == -1) {
					DashTimeCount = 0;
				}

				if (savedata->GetSkill(false) == 15 || savedata->GetSkill(true) == 15) { //�Z�c���N
					m_Life -= Dash_LifeGensyo / 2;
				}
				else {
					m_Life -= Dash_LifeGensyo;
				}

				if (savedata->GetSkill(false) == 16 || savedata->GetSkill(true) == 16) { //�C�m�`�J���Q��
					if (NowSkillNo == -1) {
						gameData->Star_PowerChange(1);
					}
				}

				if (m_Life < 0) {
					m_Life = 0; //0��菬�������Ȃ�
				}
				if (NowSkillNo == 7 && m_Life < 1) {
					m_Life = 1; //1��菬�������Ȃ�
				}

			}

			//�_�b�V����ԃJ�E���g
			if (DashTimeCount > -1) {
				DashTimeCount++;

				if (DashTimeCount >= DashTimeMAX) { //�_�b�V����Ԃ����Ԑ؂�Ȃ�
					DashTimeCount = -1;
					DashFlag = false;
					A_DashFlag = false;
				}
			}

			//�X�L��
			if (Pad(0).IsTrigger(enButtonY)) {
				//�R���b�g�L���m�����Ȃ甭�˂���
				if (NowSkillNo == 10) {
					StarComet * starComet = StarComet::GetInstance();
					starComet->Comet_Hassya(m_moveSpeed, position);
					gameData->Star_PowerChange(-10);
					SkillTimer += 10;
				}

				GameData * gamedata = GameData::GetInstance();
				//�F�X���擾����
				int Now_Star_Power = gamedata->GetStar_Power();
				int SkillNo = savedata->GetSkill(false);
				int SkillCost = Skill_Data[SkillNo].StarPower;
				//int MAX_Star_Power = gamedata->GetMAXStar_Power();
				if (SkillCost > 0 && Now_Star_Power >= SkillCost && NowSkillNo == -1) { //�����^���X�^�[�Q�[�W������Ă���Ȃ甭��
					SkillYobidashi(SkillNo);
				}
				else {
					//�������Ȃ�u���b�v
					prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
					ss->Init(L"sound/blip.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);
				}
			}
			//�X�L��
			if (Pad(0).IsTrigger(enButtonX)) {
				//�R���b�g�L���m�����Ȃ甭�˂���
				if (NowSkillNo == 10) {
					StarComet * starComet = StarComet::GetInstance();
					starComet->Comet_Hassya(m_moveSpeed, position);
					gameData->Star_PowerChange(-10);
					SkillTimer += 10;
				}

				GameData * gamedata = GameData::GetInstance();
				//�F�X���擾����
				int Now_Star_Power = gamedata->GetStar_Power();
				int SkillNo = savedata->GetSkill(true);
				int SkillCost = Skill_Data[SkillNo].StarPower;
				//int MAX_Star_Power = gamedata->GetMAXStar_Power();
				if (SkillCost > 0 && Now_Star_Power >= SkillCost && NowSkillNo == -1) { //�����^���X�^�[�Q�[�W������Ă���Ȃ甭��
					SkillYobidashi(SkillNo);
				}
				else {
					//�������Ȃ�u���b�v
					prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
					ss->Init(L"sound/blip.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);
				}
			}

		}break;
		case Estate_Dash://�_�b�V��
		{
			EffectManager * effectmanager = EffectManager::GetInstance();
			effectmanager->EffectPlayer(EffectManager::star, position, SpawnEffectScale / 2);
			effectmanager->EffectPlayer(EffectManager::star, position, SpawnEffectScale / 2);
			effectmanager->EffectPlayer(EffectManager::star, position, SpawnEffectScale / 2);
			effectmanager->EffectPlayer(EffectManager::star, position, SpawnEffectScale / 2);
			effectmanager->EffectPlayer(EffectManager::StarDash, position, DashEffectScale, true, true);
			effectmanager->EffectPlayer(EffectManager::Dash2, position, DashEffectScale, true, true);

			//�ړ�
			CVector3 Dash_Speed = m_moveSpeed;
			Dash_Speed.Normalize();
			Dash_Speed *= dashSpeed2D;
			m_moveSpeed += Dash_Speed;

			//���������_�b�V���Ȃ瑀��\
			if (NowSkillNo == 2) {
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
				//�ړ����x���
				if (m_moveSpeed.Length() > moveSpeedMAX) {
					m_moveSpeed.Normalize();
					m_moveSpeed *= moveSpeedMAX;
				}
			}

			//�����Q�[�W������
			GameData * gamedata = GameData::GetInstance();
			gamedata->Star_PowerChange(-DashLifeSpeed);
			//���������Q�[�W��0�Ȃ玀��
			int NowStarPower = gamedata->GetStar_Power();
			if (NowStarPower == 0) {
				effectmanager->EffectPlayer(EffectManager::Bonus, position, SpawnEffectScale);
				m_Life = 0;
			}

		}break;
		//case Estate_Death://����ł���

		//break;
		case Estate_Frea://�\�E���t���A�I
		{
			//�ړ��͂ł��Ȃ����ǌ����͂��܂�
			m_moveSpeed *= 0.98f;

			SoulFlareTimer++;

			if (SoulFlareTimer == SoulFlareLimit) { //�ǂ����[��
				EffectManager * effectmanager = EffectManager::GetInstance();
				effectmanager->EffectPlayer_Post(EffectManager::Bakuhatu, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale, true);

				DashFlag = true;
				SoulFlareFlag = true;
				MutekiTimer = -1; //���G�������Ȃ��ƃ_���[�W��^�����Ȃ���ł���
				DashTimeCount = -2; //��������Ȃ��_�b�V����ԂɂȂ�
			}
			else if (SoulFlareTimer == SoulFlareLimit + 1) { //�\�E���t���A�I���Ȃ̂ł��ɂ܁[��
				DashFlag = false;
				SoulFlareFlag = false;
				SoulFlareTimer = 0;
				m_Life = 0;
			}

		}break;
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
			if (NowSkillNo == 7 && m_Life < 1) {
				m_Life = 1; //1��菬�������Ȃ�
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
			//return;
		}
		float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
		rotation.SetRotation(CVector3::AxisY, angle);

		PlayerJudge();
		SkillUpdate();

		//�v���C���[�̍��W�𐳋K�����W�n�ɕϊ�����B
		CVector2 playerPosInSeikika;
		MainCamera().CalcScreenPositionFromWorldPosition(playerPosInSeikika, position);
		playerPosInSeikika.x /= (float)GraphicsEngine().Get2DSpaceScreenWidth() * 0.5f;
		playerPosInSeikika.y /= (float)GraphicsEngine().Get2DSpaceScreenHeight() * 0.5f;
		GraphicsEngine().GetPostEffect().GetDithering().SetPlayerPosition(playerPosInSeikika);

	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	else if (mode == 1) {

		switch (player_state) {

		case Estate_Stay://�ҋ@
		{

			//�ړ�
			float Hosei = 0.0f;
			if (NowSkillNo == 8) { //�i�K���{�V���Ȃ�␳��ݒ肷��
				Hosei += Nagareboshi;
			}
			if (savedata->GetSkill(false) == 18) { //�J�~�J�[�o�g��
				Hosei += Kamikaze;
			}
			if (savedata->GetSkill(false) == 19) { //�A�N��
				Hosei += Akumu;
			}

			if (Pad(0).IsPress(enButtonUp)) {
				m_moveSpeed.y += moveCrossKey * (Advance3D_Move + Advance3D_Move + Hosei);
			}
			if (Pad(0).IsPress(enButtonDown)) {
				m_moveSpeed.y -= moveCrossKey * (Advance3D_Move + Advance3D_Move + Hosei);
			}
			if (Pad(0).IsPress(enButtonRight)) {
				m_moveSpeed.x += moveCrossKey * (Advance3D_Move + Advance3D_Move + Hosei);
			}
			if (Pad(0).IsPress(enButtonLeft)) {
				m_moveSpeed.x -= moveCrossKey * (Advance3D_Move + Advance3D_Move + Hosei);
			}

			CVector3 stick = CVector3::Zero;
			stick.x = Pad(0).GetLStickXF();
			stick.y = Pad(0).GetLStickYF();
			stick.z = 0.0f;
			m_moveSpeed += stick * (playerMoveSpeed*Advance3D_Move + Hosei);

			//�X�e�B�b�N���͂���ĂȂ���Ίɂ₩�X�g�b�v

			m_moveSpeed.x *= 0.98f;
			m_moveSpeed.y *= 0.98f;

			if (NowSkillNo == 8) {
				//�ړ����x���
				if (m_moveSpeed.Length() > moveSpeedMAX * 2.0f) {
					m_moveSpeed.Normalize();
					m_moveSpeed *= (moveSpeedMAX * 2.0f);
				}
			}
			else {
				//�ړ����x���
				if (m_moveSpeed.Length() > moveSpeedMAX) {
					m_moveSpeed.Normalize();
					m_moveSpeed *= moveSpeedMAX;
				}
			}

			//��������
			if (Pad(0).IsPress(enButtonA)) {
				//������Ԃ�
				m_Life -= 2;
				if (NowSkillNo == 7 && m_Life < 1) {
					m_Life = 1; //1��菬�������Ȃ�
				}
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

			//�X�L��
			if (Pad(0).IsTrigger(enButtonY)) {
				//�R���b�g�L���m�����Ȃ甭�˂���
				if (NowSkillNo == 10) {
					StarComet * starComet = StarComet::GetInstance();
					starComet->Comet_Hassya({ 0.0f , 0.0f , 0.0f }, position);
					gameData->Star_PowerChange(-10);
					SkillTimer += 10;
				}

				GameData * gamedata = GameData::GetInstance();
				//�F�X���擾����
				int Now_Star_Power = gamedata->GetStar_Power();
				int SkillNo = savedata->GetSkill(false);
				int SkillCost = Skill_Data[SkillNo].StarPower;
				//int MAX_Star_Power = gamedata->GetMAXStar_Power();
				if (SkillCost > 0 && Now_Star_Power >= SkillCost && NowSkillNo == -1) { //�����^���X�^�[�Q�[�W������Ă���Ȃ甭��
					SkillYobidashi(SkillNo);
				}
				else {
					//�������Ȃ�u���b�v
					prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
					ss->Init(L"sound/blip.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);
				}
			}
			//�X�L��
			if (Pad(0).IsTrigger(enButtonX)) {
				//�R���b�g�L���m�����Ȃ甭�˂���
				if (NowSkillNo == 10) {
					StarComet * starComet = StarComet::GetInstance();
					starComet->Comet_Hassya({ 0.0f , 0.0f , 0.0f }, position);
					gameData->Star_PowerChange(-10);
					SkillTimer += 10;
				}

				GameData * gamedata = GameData::GetInstance();
				//�F�X���擾����
				int Now_Star_Power = gamedata->GetStar_Power();
				int SkillNo = savedata->GetSkill(true);
				int SkillCost = Skill_Data[SkillNo].StarPower;
				//int MAX_Star_Power = gamedata->GetMAXStar_Power();
				if (SkillCost > 0 && Now_Star_Power >= SkillCost && NowSkillNo == -1) { //�����^���X�^�[�Q�[�W������Ă���Ȃ甭��
					SkillYobidashi(SkillNo);
				}
				else {
					//�������Ȃ�u���b�v
					prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
					ss->Init(L"sound/blip.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);
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
			m_moveSpeed.z = Advance3D - Advance3D_PM - Advance3D_Back;
			break;
		}
			break;
		case Estate_Dash://�_�b�V��
		{
			EffectManager * effectmanager = EffectManager::GetInstance();
			CVector3 ef_position = position;
			ef_position.z += 200.0f;
			effectmanager->EffectPlayer(EffectManager::star, ef_position, SpawnEffectScale / 2);
			effectmanager->EffectPlayer(EffectManager::star, ef_position, SpawnEffectScale / 2);
			effectmanager->EffectPlayer(EffectManager::star, ef_position, SpawnEffectScale / 2);
			effectmanager->EffectPlayer(EffectManager::star, ef_position, SpawnEffectScale / 2);

			m_moveSpeed.z = Advance3D + Advance3D_PM * (Advance3D_FrontHosei*dashSpeed3D); //�S���O�i�I

			//���������_�b�V���Ȃ瑀��\
			if (NowSkillNo == 2) {
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
			}

			//�����Q�[�W������
			GameData * gamedata = GameData::GetInstance();
			gamedata->Star_PowerChange(-DashLifeSpeed);
			//���������Q�[�W��0�Ȃ玀��
			int NowStarPower = gamedata->GetStar_Power();
			if (NowStarPower == 0) {
				m_Life = 0;
			}

		}break;
		//case Estate_Death://����ł���
		//	break;
		case Estate_Frea://�\�E���t���A�I
		{
			SoulFlareTimer++;

			if (SoulFlareTimer == SoulFlareLimit) { //�ǂ����[��
				EffectManager * effectmanager = EffectManager::GetInstance();
				effectmanager->EffectPlayer_Post(EffectManager::Bakuhatu, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale, true);

				DashFlag = true;
				SoulFlareFlag = true;
				MutekiTimer = -1; //���G�������Ȃ��ƃ_���[�W��^�����Ȃ���ł���
				DashTimeCount = -2; //��������Ȃ��_�b�V����ԂɂȂ�
			}
			else if (SoulFlareTimer == SoulFlareLimit + 1) { //�\�E���t���A�I���Ȃ̂ł��ɂ܁[��
				DashFlag = false;
				SoulFlareFlag = false;
				SoulFlareTimer = 0;
				m_Life = 0;
			}

		}break;
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
			if (NowSkillNo == 7 && m_Life < 1) {
				m_Life = 1; //1��菬�������Ȃ�
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
		SkillUpdate();

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

	//���݃��[�h��0��1�Ȃ�Q�[�W�㏸
	if (mode == GameData::Battle2D_Mode || mode == GameData::Battle3D_Mode) {
		StarPointTimer++;
		if (StarPointTimer >= StarPointLimit && NowSkillNo== -1 ) { //�X�L���������͑����܂���
			if (savedata->GetSkill(false) != 20 && savedata->GetSkill(true) != 20) { //�L���E�t�X�L���������͑����Ȃ�
				gameData->Star_PowerChange(1);
			}
			StarPointTimer = 0;
		}
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
		if (GameData::GetInstance()->GetStageNo() == 5) {
			GraphicsEngine().GetTonemap().SetLuminance(0.05f);
		}
		else if (GameData::GetInstance()->GetStageNo() == 2) {
			GraphicsEngine().GetTonemap().SetLuminance(0.1f);
		}
		else {
			GraphicsEngine().GetTonemap().SetLuminance(DEFAULT_LUMINANCE);
		}
	}
	else if (mode == 1) {
		CVector3 pos = position;
		pos.z += LightPosHoseiZ;
		m_pointLig->SetPosition(pos);
		m_pointLig->SetColor(PlayerLight * LightHosei);
		m_pointLig->SetAttn(PlayerLightAttn);
		m_skinModelRender->SetEmissionColor(EmissionColorDEF);
		if (GameData::GetInstance()->GetStageNo() == 5) {
			GraphicsEngine().GetTonemap().SetLuminance(0.1f, 0.5f);
		}
		else if (GameData::GetInstance()->GetStageNo() == 2) {
			GraphicsEngine().GetTonemap().SetLuminance(0.1f, 0.5f);
		}
		else {
			GraphicsEngine().GetTonemap().SetLuminance(DEFAULT_LUMINANCE, 0.5f);
		}
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

	SoundEngine().SetListenerPosition(position * 0.01f);

}

//�����F�X
void Player::PlayerJudge() {

	SaveData * savedata = SaveData::GetInstance();

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
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�M���M���{�[�i�X���������邩�m�F
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//�������[����
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					int EState = bunbogu->GetEState();
					if ((EState != Bunbogu::Estete_Attack && DashFlag == true )|| player_state==Estate_Dash || player_state == Estate_Frea) {//�G���U�����̎��łȂ����_�b�V����ԂȂ�c

						bunbogu->SetDeath();//���O������

						if (Hantei == true) {
							//�M���M���{�[�i�X�J�E���g��+1
							gamedata->GiriCounter();
							//�{�[�i�X�����̃G�t�F�N�g��\��
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { enemy_position.x,enemy_position.y + SpawnEffectY,enemy_position.z }, SpawnEffectScale);
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
				if (MutekiTimer == -1 && player_state != Estate_Dash) {

					//�������[����
					if (player_state != Estate_Dash) {
						if (savedata->GetSkill(false) == 17 || savedata->GetSkill(true) == 17) { //�n�K�l�m�J���_
							m_Life -= 20;
							if (m_Life < 0) {
								m_Life = 0;
							}
						}
						else {
							m_Life = 0;
						}
					}

					bullet->SetDeath();//���O������

				}
			}
		}
		return true;
		});
	QueryGOs<Bullet2>("bullet2", [&](Bullet2* bullet2) {
		CVector3 bullet_position = bullet2->Getm_Position();
		CVector3 diff = bullet_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = bullet2->GetDamageLength();
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1 && player_state != Estate_Dash) {

					//�������[����
					if (player_state != Estate_Dash) {
						if (savedata->GetSkill(false) == 17 || savedata->GetSkill(true) == 17) { //�n�K�l�m�J���_
							m_Life -= 20;
							if (m_Life < 0) {
								m_Life = 0;
							}
						}
						else {
							m_Life = 0;
						}
					}

					bullet2->SetDeath();//���O������

				}
			}
		}
		return true;
		});
	QueryGOs<Bullet3>("bullet3", [&](Bullet3* bullet3) {
		CVector3 bullet_position = bullet3->Getm_Position();
		CVector3 diff = bullet_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = bullet3->GetDamageLength();
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1 && player_state != Estate_Dash) {

					//�������[����
					if (player_state != Estate_Dash) {
						if (savedata->GetSkill(false) == 17 || savedata->GetSkill(true) == 17) { //�n�K�l�m�J���_
							m_Life -= 20;
							if (m_Life < 0) {
								m_Life = 0;
							}
						}
						else {
							m_Life = 0;
						}
					}

					bullet3->SetDeath();//���O������

				}
			}
		}
		return true;
		});
	QueryGOs<Bullet4>("bullet4", [&](Bullet4* bullet4) {
		CVector3 bullet_position = bullet4->Getm_Position();
		CVector3 diff = bullet_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = bullet4->GetDamageLength();
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1 && player_state != Estate_Dash) {

					//�������[����
					if (player_state != Estate_Dash) {
						if (savedata->GetSkill(false) == 17 || savedata->GetSkill(true) == 17) { //�n�K�l�m�J���_
							m_Life -= 20;
							if (m_Life < 0) {
								m_Life = 0;
							}
						}
						else {
							m_Life = 0;
						}
					}

					bullet4->SetDeath();//���O������

				}
			}
		}
		return true;
		});
	QueryGOs<Bullet5>("bullet5", [&](Bullet5* bullet5) {
		CVector3 bullet_position = bullet5->Getm_Position();
		CVector3 diff = bullet_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = bullet5->GetDamageLength();
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1 && player_state != Estate_Dash) {

					//�������[����
					if (player_state != Estate_Dash) {
						if (savedata->GetSkill(false) == 17 || savedata->GetSkill(true) == 17) { //�n�K�l�m�J���_
							m_Life -= 20;
							if (m_Life < 0) {
								m_Life = 0;
							}
						}
						else {
							m_Life = 0;
						}
					}

					bullet5->SetDeath();//���O������

				}
			}
		}
		return true;
		});
	QueryGOs<Bullet6>("bullet6", [&](Bullet6* bullet6) {
		CVector3 bullet_position = bullet6->Getm_Position();
		CVector3 diff = bullet_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = bullet6->GetDamageLength();
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1 && player_state != Estate_Dash) {

					//�������[����
					if (player_state != Estate_Dash) {
						if (savedata->GetSkill(false) == 17 || savedata->GetSkill(true) == 17) { //�n�K�l�m�J���_
							m_Life -= 20;
							if (m_Life < 0) {
								m_Life = 0;
							}
						}
						else {
							m_Life = 0;
						}
					}

					bullet6->SetDeath();//���O������

				}
			}
		}
		return true;
		});

	//�~�T�C���Ƃ̋������v�Z
	QueryGOs<Misairu>("Misairu", [&](Misairu* misairu) {
		CVector3 bullet_position = misairu->Getm_Position();
		CVector3 diff = bullet_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = misairu->GetDamageLength();
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�������[����
					if (player_state != Estate_Dash) {
						if (savedata->GetSkill(false) == 17 || savedata->GetSkill(true) == 17) { //�n�K�l�m�J���_
							m_Life -= 20;
							if (m_Life < 0) {
								m_Life = 0;
							}
						}
						else {
							m_Life = 0;
						}
					}

					misairu->SetDeath();//���O������

				}
			}
		}
		return true;
		});

	//�����S�{���Ƃ̋������v�Z
	QueryGOs<AppleBomb>("AppleBomb", [&](AppleBomb* appleBomb) {
		if (appleBomb->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 bullet_position = appleBomb->Getm_Position();
		CVector3 diff = bullet_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = appleBomb->GetDamageLength();
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�������[����
					if (player_state != Estate_Dash) {
						m_Life = 0;
						GameData * gamedata = GameData::GetInstance();
						gamedata->SetBombFlag();
					}

					appleBomb->SetDeath();//���O������

				}
			}
		}
		return true;
		});

	//�d�ԂƂ̋������v�Z
	QueryGOs<Train1>("Train1", [&](Train1* train1) {
		if (train1->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 bullet_position = train1->Getm_Position();
		CVector3 diff = bullet_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = train1->GetDamageLength();
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�������[����
					if (player_state != Estate_Dash) {
						m_Life = 0;
						GameData * gamedata = GameData::GetInstance();
						gamedata->SetDensyaFlag();
					}

				}
			}
		}
		return true;
		});
	QueryGOs<Train2>("Train2", [&](Train2* train2) {
		if (train2->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 bullet_position = train2->Getm_Position();
		CVector3 diff = bullet_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = train2->GetDamageLength();
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�������[����
					if (player_state != Estate_Dash) {
						m_Life = 0;
						GameData * gamedata = GameData::GetInstance();
						gamedata->SetDensyaFlag();
					}

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
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�M���M���{�[�i�X���������邩�m�F
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//�������[����
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
							m_moveSpeed.x *= -1.0f;
							m_moveSpeed.y *= -1.0f;
							m_moveSpeed.z *= -1.0f;
						}
						else {
							m_Life = 0;
						}
					}

					if (DashFlag == true) {//�_�b�V����ԂȂ�c

						neoriku->SetDeath();//���O������

						if (Hantei == true) {
							//�M���M���{�[�i�X�J�E���g��+1
							gamedata->GiriCounter();
							//�{�[�i�X�����̃G�t�F�N�g��\��
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { neoriku_position.x,neoriku_position.y + SpawnEffectY,neoriku_position.z }, SpawnEffectScale);
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
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
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
					if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
						m_moveSpeed.x *= -Zonbi_Handou_Boss;
						m_moveSpeed.y *= -Zonbi_Handou_Boss;
						m_moveSpeed.z *= -Zonbi_Handou_Boss;
					}
					else {
						if (player_state != Estate_Frea) {
							m_Life = 0;
						}
					}

					int EState = Shisok->GetEState();
					if (EState != shisokus::Estete_Attack1 && (DashFlag == true || player_state == Estate_Dash || player_state == Estate_Frea)) {//�G���U�����̎��łȂ����_�b�V����ԂȂ�c

						prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
						ss->Init(L"sound/damage.wav");
						ss->SetVolume(0.5f);
						ss->Play(false);

						//�I���@�I
						Shisok->Damage(Damage);
						gamedata->PlusBossDamage();

					}


				}
			}
		}
		return true;
		});

	//�l���N�Ƃ̋������v�Z
	QueryGOs<Neruk>("neru", [&](Neruk* neruk) {
		if (neruk->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 neruk_position = neruk->Getm_Position();
		CVector3 diff = neruk_position - position;

		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = neruk->GetDamageLength();
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�������[����
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					neruk->SetDeath();//���O������

				}
				if (player_state == Estate_Dash) {
					neruk->SetDeath();//���O������
				}
			}
		}
		return true;
		});

	//�\�E�J�u�g�Ƃ̋������v�Z
	QueryGOs<soukabuto>("sou", [&](soukabuto* souka) {
		if (souka->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 souka_position = souka->Getm_Position();
		CVector3 diff = souka_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = souka->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}			
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�M���M���{�[�i�X���������邩�m�F
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//�������[����
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					if (DashFlag == true) {//�_�b�V����ԂȂ�c

						souka->SetDeath();//���O������

						if (Hantei == true) {
							//�M���M���{�[�i�X�J�E���g��+1
							gamedata->GiriCounter();
							//�{�[�i�X�����̃G�t�F�N�g��\��
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { souka_position.x,souka_position.y + SpawnEffectY,souka_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//�L�R�E�`���E�Ƃ̋������v�Z
	QueryGOs<Kikochu>("Kikochu", [&](Kikochu* kikochu) {
		if (kikochu->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 souka_position = kikochu->Getm_Position();
		CVector3 diff = souka_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = kikochu->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�M���M���{�[�i�X���������邩�m�F
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//�������[����
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					if (DashFlag == true) {//�_�b�V����ԂȂ�c

						kikochu->SetDeath();//���O������

						if (Hantei == true) {
							//�M���M���{�[�i�X�J�E���g��+1
							gamedata->GiriCounter();
							//�{�[�i�X�����̃G�t�F�N�g��\��
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { souka_position.x,souka_position.y + SpawnEffectY,souka_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//�E�~�m�E�V�Ƃ̋������v�Z
	QueryGOs<Uminoushi>("Uminoushi", [&](Uminoushi* uminoushi) {
		if (uminoushi->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 souka_position = uminoushi->Getm_Position();
		CVector3 diff = souka_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = uminoushi->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�M���M���{�[�i�X���������邩�m�F
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//�������[����
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					if (DashFlag == true) {//�_�b�V����ԂȂ�c

						uminoushi->SetDeath();//���O������

						if (Hantei == true) {
							//�M���M���{�[�i�X�J�E���g��+1
							gamedata->GiriCounter();
							//�{�[�i�X�����̃G�t�F�N�g��\��
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { souka_position.x,souka_position.y + SpawnEffectY,souka_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//�A�R���h�J���Ƃ̋������v�Z
	QueryGOs<Akoyadokari>("Akoyadokari", [&](Akoyadokari* akoyadokari) {
		if (akoyadokari->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 enemy_position = akoyadokari->Getm_Position();
		CVector3 diff = enemy_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = akoyadokari->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�M���M���{�[�i�X���������邩�m�F
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//�������[����
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					int EState = akoyadokari->GetEState();
					if (EState != 0 && DashFlag == true || player_state == Estate_Dash || player_state == Estate_Frea) {//�G���U�����̎��łȂ����_�b�V����ԂȂ�c

						akoyadokari->SetDeath();//���O������

						if (Hantei == true) {
							//�M���M���{�[�i�X�J�E���g��+1
							gamedata->GiriCounter();
							//�{�[�i�X�����̃G�t�F�N�g��\��
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { enemy_position.x,enemy_position.y + SpawnEffectY,enemy_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}
				}
			}
		}
		return true;
		});

	//�x�j�e�[�Ƃ̋������v�Z
	QueryGOs<Benite>("Benite", [&](Benite* benite) {
		if (benite->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 enemy_position = benite->Getm_Position();
		CVector3 diff = enemy_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = benite->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�M���M���{�[�i�X���������邩�m�F
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//�������[����
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					int EState = benite->GetEState();
					if (EState != Benite::Estete_Attack && DashFlag == true || player_state == Estate_Dash || player_state == Estate_Frea) {//�G���U�����̎��łȂ����_�b�V����ԂȂ�c

						benite->SetDeath();//���O������

						if (Hantei == true) {
							//�M���M���{�[�i�X�J�E���g��+1
							gamedata->GiriCounter();
							//�{�[�i�X�����̃G�t�F�N�g��\��
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { enemy_position.x,enemy_position.y + SpawnEffectY,enemy_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}
				}
			}
		}
		return true;
		});

	//�j�[�{�[�Ƃ̋������v�Z
	QueryGOs<Nibo>("Nibo", [&](Nibo* nibo) {
		if (nibo->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 enemy_position = nibo->Getm_Position();
		CVector3 diff = enemy_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = nibo->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�M���M���{�[�i�X���������邩�m�F
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//�������[����
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					int EState = nibo->GetEState();
					if ((EState != Benite::Estete_Attack && DashFlag == true) || player_state == Estate_Dash || player_state == Estate_Frea) {//�G���U�����̎��łȂ����_�b�V����ԂȂ�c

						nibo->SetDeath();//���O������

						if (Hantei == true) {
							//�M���M���{�[�i�X�J�E���g��+1
							gamedata->GiriCounter();
							//�{�[�i�X�����̃G�t�F�N�g��\��
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { enemy_position.x,enemy_position.y + SpawnEffectY,enemy_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}
				}
			}
		}
		return true;
		});

	//�Z�N�e�B���Ƃ̋������v�Z
	QueryGOs<Sekuteimu>("Sekuteimu", [&](Sekuteimu* sekuteimu) {
		if (sekuteimu->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 souka_position = sekuteimu->Getm_Position();
		CVector3 diff = souka_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = sekuteimu->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�M���M���{�[�i�X���������邩�m�F
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//�������[����
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					if (DashFlag == true) {//�_�b�V����ԂȂ�c

						sekuteimu->SetDeath();//���O������

						if (Hantei == true) {
							//�M���M���{�[�i�X�J�E���g��+1
							gamedata->GiriCounter();
							//�{�[�i�X�����̃G�t�F�N�g��\��
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { souka_position.x,souka_position.y + SpawnEffectY,souka_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//�L���r���Ƃ̋������v�Z
	QueryGOs<Kirabi>("Kirabi", [&](Kirabi* kirabi) {
		if (kirabi->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 enemy_position = kirabi->Getm_Position();
		CVector3 diff = enemy_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = kirabi->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�M���M���{�[�i�X���������邩�m�F
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//�������[����
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					int EState = kirabi->GetEState();
					if ( (EState != Benite::Estete_Attack && DashFlag == true ) || player_state == Estate_Dash || player_state == Estate_Frea) {//�G���U�����̎��łȂ����_�b�V����ԂȂ�c

						kirabi->SetDeath();//���O������

						if (Hantei == true) {
							//�M���M���{�[�i�X�J�E���g��+1
							gamedata->GiriCounter();
							//�{�[�i�X�����̃G�t�F�N�g��\��
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { enemy_position.x,enemy_position.y + SpawnEffectY,enemy_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}
				}
			}
		}
		return true;
		});

	//�X�e�B���Ƃ̋������v�Z
	QueryGOs<Suteira>("Suteira", [&](Suteira* suteira) {
		if (suteira->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 souka_position = suteira->Getm_Position();
		CVector3 diff = souka_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = suteira->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�M���M���{�[�i�X���������邩�m�F
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//�������[����
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					if (DashFlag == true) {//�_�b�V����ԂȂ�c

						suteira->SetDeath();//���O������

						if (Hantei == true) {
							//�M���M���{�[�i�X�J�E���g��+1
							gamedata->GiriCounter();
							//�{�[�i�X�����̃G�t�F�N�g��\��
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { souka_position.x,souka_position.y + SpawnEffectY,souka_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//�������`���Ƃ̋������v�Z
	QueryGOs<Morinchu>("Morinchu", [&](Morinchu* morinchu) {
		if (morinchu->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 Shisok_position = morinchu->Getm_Position();
		Shisok_position.y += 2000.0f;
		Shisok_position.z += 500.0f;
		CVector3 diff = Shisok_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = morinchu->GetDamageLength();
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
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
					if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
						m_moveSpeed.x *= -Zonbi_Handou_Boss;
						m_moveSpeed.y *= -Zonbi_Handou_Boss;
						m_moveSpeed.z *= -Zonbi_Handou_Boss;
					}
					else {
						if (player_state != Estate_Frea) {
							m_Life = 0;
						}
					}

					int EState = morinchu->GetEState();
					if ((EState != Morinchu::Estete_Attack1 && DashFlag == true )|| player_state == Estate_Dash || player_state == Estate_Frea) {//�G���U�����̎��łȂ����_�b�V����ԂȂ�c

						prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
						ss->Init(L"sound/damage.wav");
						ss->SetVolume(0.5f);
						ss->Play(false);

						//�I���@�I
						morinchu->Damage(Damage);
						gamedata->PlusBossDamage();

					}


				}
			}
		}
		return true;
		});

	//�`�Y�`���E�Ƃ̋������v�Z
	QueryGOs<Tizutyo>("Tizutyo", [&](Tizutyo* tizutyo) {
		if (tizutyo->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 souka_position = tizutyo->Getm_Position();
		CVector3 diff = souka_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = tizutyo->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�M���M���{�[�i�X���������邩�m�F
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//�������[����
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					if (DashFlag == true) {//�_�b�V����ԂȂ�c

						tizutyo->SetDeath();//���O������

						if (Hantei == true) {
							//�M���M���{�[�i�X�J�E���g��+1
							gamedata->GiriCounter();
							//�{�[�i�X�����̃G�t�F�N�g��\��
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { souka_position.x,souka_position.y + SpawnEffectY,souka_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//�N�[�{�Ƃ̋������v�Z
	QueryGOs<Kuubo>("Kuubo", [&](Kuubo* kuubo) {
		if (kuubo->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 enemy_position = kuubo->Getm_Position();
		CVector3 diff = enemy_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = kuubo->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�M���M���{�[�i�X���������邩�m�F
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//�������[����
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					int EState = kuubo->GetEState();
					if ((EState != Kuubo::Estete_Attack && DashFlag == true) || player_state == Estate_Dash || player_state == Estate_Frea) {//�G���U�����̎��łȂ����_�b�V����ԂȂ�c

						kuubo->SetDeath();//���O������

						if (Hantei == true) {
							//�M���M���{�[�i�X�J�E���g��+1
							gamedata->GiriCounter();
							//�{�[�i�X�����̃G�t�F�N�g��\��
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { enemy_position.x,enemy_position.y + SpawnEffectY,enemy_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}
				}
			}
		}
		return true;
		});

	//�g���s�s�Ƃ̋������v�Z
	QueryGOs<Toripipi>("Toripipi", [&](Toripipi* toripipi) {
		if (toripipi->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 enemy_position = toripipi->Getm_Position();
		CVector3 diff = enemy_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = toripipi->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�M���M���{�[�i�X���������邩�m�F
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//�������[����
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					if (DashFlag == true) {//�_�b�V����ԂȂ�c

						toripipi->SetDeath();//���O������

						if (Hantei == true) {
							//�M���M���{�[�i�X�J�E���g��+1
							gamedata->GiriCounter();
							//�{�[�i�X�����̃G�t�F�N�g��\��
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { enemy_position.x,enemy_position.y + SpawnEffectY,enemy_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}
				}
			}
		}
		return true;
		});

	//�e�B���I�X�J�Ƃ̋������v�Z
	QueryGOs<Teruosuka>("Teruosuka", [&](Teruosuka* teruosuka) {
		if (teruosuka->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 Shisok_position = teruosuka->Getm_Position();

		if (teruosuka->GetTeruMode() == Teruosuka::Tank) {

		}else if (teruosuka->GetTeruMode() == Teruosuka::Plane) {
			Shisok_position.z -= 1700.0f;
		}
		else if (teruosuka->GetTeruMode() == Teruosuka::Human) {
			Shisok_position.y += 3000.0f;
			Shisok_position.z += 200.0f;
		}

		//Shisok_position.y += 2000.0f;
		//Shisok_position.z += 500.0f;
		CVector3 diff = Shisok_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = teruosuka->GetDamageLength();
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
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

					if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
						m_moveSpeed.x *= -Zonbi_Handou_Boss;
						m_moveSpeed.y *= -Zonbi_Handou_Boss;
						m_moveSpeed.z *= -Zonbi_Handou_Boss;
					}
					else {
						if (player_state != Estate_Frea) {
							m_Life = 0;
						}
					}

					int EState = teruosuka->GetEState();
					if ((EState != Teruosuka::Estete_HumanAttack && DashFlag == true) || player_state == Estate_Dash || player_state == Estate_Frea) {//�G���U�����̎��łȂ����_�b�V����ԂȂ�c

						prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
						ss->Init(L"sound/damage.wav");
						ss->SetVolume(0.5f);
						ss->Play(false);

						//�I���@�I
						teruosuka->Damage(Damage);
						gamedata->PlusBossDamage();

					}


				}
			}
		}
		return true;
		});

	//�A�c�J���Ƃ̋������v�Z
	QueryGOs<Atsukaru>("Atsukaru", [&](Atsukaru* atsukaru) {
		if (atsukaru->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 enemy_position = atsukaru->Getm_Position();
		CVector3 diff = enemy_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = atsukaru->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�M���M���{�[�i�X���������邩�m�F
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//�������[����
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					if (DashFlag == true) {//�_�b�V����ԂȂ�c

						atsukaru->SetDeath();//���O������

						if (Hantei == true) {
							//�M���M���{�[�i�X�J�E���g��+1
							gamedata->GiriCounter();
							//�{�[�i�X�����̃G�t�F�N�g��\��
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { enemy_position.x,enemy_position.y + SpawnEffectY,enemy_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}
				}
			}
		}
		return true;
		});

	//���g�|���X�Ƃ̋������v�Z
	QueryGOs<Metoporisu>("Metoporisu", [&](Metoporisu* metoporisu) {
		if (metoporisu->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 enemy_position = metoporisu->Getm_Position();
		CVector3 diff = enemy_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = metoporisu->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�M���M���{�[�i�X���������邩�m�F
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//�������[����
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					if (DashFlag == true) {//�_�b�V����ԂȂ�c

						metoporisu->SetDeath();//���O������

						if (Hantei == true) {
							//�M���M���{�[�i�X�J�E���g��+1
							gamedata->GiriCounter();
							//�{�[�i�X�����̃G�t�F�N�g��\��
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { enemy_position.x,enemy_position.y + SpawnEffectY,enemy_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}
				}
			}
		}
		return true;
		});

	//�G�b�N�Ƃ̋������v�Z
	QueryGOs<Ekku>("Ekku", [&](Ekku* ekku) {
		if (ekku->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 souka_position = ekku->Getm_Position();
		CVector3 diff = souka_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = ekku->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�M���M���{�[�i�X���������邩�m�F
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//�������[����
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					int EState = ekku->GetEState();
					if ((EState != Ekku::Estete_Attack && DashFlag == true) || player_state == Estate_Dash || player_state == Estate_Frea) {//�G���U�����̎��łȂ����_�b�V����ԂȂ�c

						ekku->SetDeath();//���O������

						if (Hantei == true) {
							//�M���M���{�[�i�X�J�E���g��+1
							gamedata->GiriCounter();
							//�{�[�i�X�����̃G�t�F�N�g��\��
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { souka_position.x,souka_position.y + SpawnEffectY,souka_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//�s�[���r�Ƃ̋������v�Z
	QueryGOs<Pi_rabi>("Pi_rabi", [&](Pi_rabi* pi_rabi) {
		if (pi_rabi->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 souka_position = pi_rabi->Getm_Position();
		CVector3 diff = souka_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = pi_rabi->GetDamageLength();		
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�M���M���{�[�i�X���������邩�m�F
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//�������[����
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					int EState = pi_rabi->GetEState();
					if ((EState != Pi_rabi::Estete_Attack && DashFlag == true) || player_state == Estate_Dash || player_state == Estate_Frea) {//�G���U�����̎��łȂ����_�b�V����ԂȂ�c

						pi_rabi->SetDeath();//���O������

						if (Hantei == true) {
							//�M���M���{�[�i�X�J�E���g��+1
							gamedata->GiriCounter();
							//�{�[�i�X�����̃G�t�F�N�g��\��
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { souka_position.x,souka_position.y + SpawnEffectY,souka_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//�t�@�C���Ƃ̋������v�Z
	QueryGOs<Fairo>("Fairo", [&](Fairo* fairo) {
		if (fairo->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 souka_position = fairo->Getm_Position();
		CVector3 diff = souka_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = fairo->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�M���M���{�[�i�X���������邩�m�F
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//�������[����
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					if (DashFlag == true) {//�_�b�V����ԂȂ�c

						fairo->SetDeath();//���O������

						if (Hantei == true) {
							//�M���M���{�[�i�X�J�E���g��+1
							gamedata->GiriCounter();
							//�{�[�i�X�����̃G�t�F�N�g��\��
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { souka_position.x,souka_position.y + SpawnEffectY,souka_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//�p�C���h���S�Ƃ̋������v�Z
	QueryGOs<Pairodorago>("Pairodorago", [&](Pairodorago* pairodorago) {
		if (pairodorago->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 Shisok_position = pairodorago->Getm_Position();
		//Shisok_position.z = Shisok_position.z - 800.0f;
		Shisok_position.y = Shisok_position.y + 2000.0f;
		CVector3 diff = Shisok_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = pairodorago->GetDamageLength();
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
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
					if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
						m_moveSpeed.x *= -Zonbi_Handou_Boss;
						m_moveSpeed.y *= -Zonbi_Handou_Boss;
						m_moveSpeed.z *= -Zonbi_Handou_Boss;
					}
					else {
						if (player_state != Estate_Frea) {
							m_Life = 0;
						}
					}
					
					if (DashFlag == true || player_state == Estate_Dash || player_state == Estate_Frea) {//�G���U�����̎��łȂ����_�b�V����ԂȂ�c

						prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
						ss->Init(L"sound/damage.wav");
						ss->SetVolume(0.5f);
						ss->Play(false);

						//�I���@�I
						pairodorago->Damage(Damage);
						gamedata->PlusBossDamage();

					}


				}
			}
		}
		return true;
		});

	//�C�[�_���h�Ƃ̋������v�Z
	QueryGOs<Idando>("Idando", [&](Idando* idando) {
		if (idando->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 enemy_position = idando->Getm_Position();
		CVector3 diff = enemy_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = idando->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�M���M���{�[�i�X���������邩�m�F
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//�������[����
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					int EState = idando->GetEState();
					if ((EState != Idando::Estete_Attack && DashFlag == true) || player_state == Estate_Dash || player_state == Estate_Frea) {//�G���U�����̎��łȂ����_�b�V����ԂȂ�c

						idando->SetDeath();//���O������

						if (Hantei == true) {
							//�M���M���{�[�i�X�J�E���g��+1
							gamedata->GiriCounter();
							//�{�[�i�X�����̃G�t�F�N�g��\��
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { enemy_position.x,enemy_position.y + SpawnEffectY,enemy_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}
				}
			}
		}
		return true;
		});

	//�R�_���Ƃ̋������v�Z
	QueryGOs<Kodan>("Kodan", [&](Kodan* kodan) {
		if (kodan->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 souka_position = kodan->Getm_Position();
		CVector3 diff = souka_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = kodan->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�M���M���{�[�i�X���������邩�m�F
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//�������[����
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					if (DashFlag == true) {//�_�b�V����ԂȂ�c

						kodan->SetDeath();//���O������

						if (Hantei == true) {
							//�M���M���{�[�i�X�J�E���g��+1
							gamedata->GiriCounter();
							//�{�[�i�X�����̃G�t�F�N�g��\��
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { souka_position.x,souka_position.y + SpawnEffectY,souka_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//�^�C�h���Ƃ̋������v�Z
	QueryGOs<Taidol>("Taidol", [&](Taidol* taidol) {
		if (taidol->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 enemy_position = taidol->Getm_Position();
		CVector3 diff = enemy_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = taidol->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�M���M���{�[�i�X���������邩�m�F
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//�������[����
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					int EState = taidol->GetEState();
					if ((EState != Taidol::Estete_Attack && DashFlag == true) || player_state == Estate_Dash || player_state == Estate_Frea) {//�G���U�����̎��łȂ����_�b�V����ԂȂ�c

						taidol->SetDeath();//���O������

						if (Hantei == true) {
							//�M���M���{�[�i�X�J�E���g��+1
							gamedata->GiriCounter();
							//�{�[�i�X�����̃G�t�F�N�g��\��
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { enemy_position.x,enemy_position.y + SpawnEffectY,enemy_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}
				}
			}
		}
		return true;
		});

	//�����R���Ƃ̋������v�Z
	QueryGOs<Morikon>("Morikon", [&](Morikon* morikon) {
		if (morikon->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 souka_position = morikon->Getm_Position();
		CVector3 diff = souka_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = morikon->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�M���M���{�[�i�X���������邩�m�F
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//�������[����
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					int EState = morikon->GetEState();
					if ((EState != Morikon::Estete_Attack && DashFlag == true) || player_state == Estate_Dash || player_state == Estate_Frea) {//�G���U�����̎��łȂ����_�b�V����ԂȂ�c

						morikon->SetDeath();//���O������

						if (Hantei == true) {
							//�M���M���{�[�i�X�J�E���g��+1
							gamedata->GiriCounter();
							//�{�[�i�X�����̃G�t�F�N�g��\��
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { souka_position.x,souka_position.y + SpawnEffectY,souka_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//�����b�g�Ƃ̋������v�Z
	QueryGOs<Riritto>("Riritto", [&](Riritto* riritto) {
		if (riritto->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 souka_position = riritto->Getm_Position();
		CVector3 diff = souka_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = riritto->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�M���M���{�[�i�X���������邩�m�F
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//�������[����
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					if (DashFlag == true) {//�_�b�V����ԂȂ�c

						riritto->SetDeath();//���O������

						if (Hantei == true) {
							//�M���M���{�[�i�X�J�E���g��+1
							gamedata->GiriCounter();
							//�{�[�i�X�����̃G�t�F�N�g��\��
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { souka_position.x,souka_position.y + SpawnEffectY,souka_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//�A���J�V���Ƃ̋������v�Z
	QueryGOs<Arukasya>("Arukasya", [&](Arukasya* arukasya) {
		if (arukasya->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 souka_position = arukasya->Getm_Position();
		CVector3 diff = souka_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = arukasya->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�M���M���{�[�i�X���������邩�m�F
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//�������[����
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					if (DashFlag == true) {//�_�b�V����ԂȂ�c

						arukasya->SetDeath();//���O������

						if (Hantei == true) {
							//�M���M���{�[�i�X�J�E���g��+1
							gamedata->GiriCounter();
							//�{�[�i�X�����̃G�t�F�N�g��\��
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { souka_position.x,souka_position.y + SpawnEffectY,souka_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//�X���[�N�Ƃ̋������v�Z
	QueryGOs<Suroku>("Suroku", [&](Suroku* suroku) {
		if (suroku->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 souka_position = suroku->Getm_Position();
		CVector3 diff = souka_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = suroku->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�M���M���{�[�i�X���������邩�m�F
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//�������[����
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					if (DashFlag == true) {//�_�b�V����ԂȂ�c

						suroku->SetDeath();//���O������

						if (Hantei == true) {
							//�M���M���{�[�i�X�J�E���g��+1
							gamedata->GiriCounter();
							//�{�[�i�X�����̃G�t�F�N�g��\��
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { souka_position.x,souka_position.y + SpawnEffectY,souka_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//�~�~�b�g�Ƃ̋������v�Z
	QueryGOs<Mimitto>("Mimitto", [&](Mimitto* mimitto) {
		if (mimitto->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 souka_position = mimitto->Getm_Position();
		CVector3 diff = souka_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = mimitto->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//��������
			if (diff.Length() < Langth_hoge) {
				//�������G���Ԓ��łȂ��Ȃ�
				if (MutekiTimer == -1) {

					//�M���M���{�[�i�X���������邩�m�F
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//�������[����
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					if (DashFlag == true) {//�_�b�V����ԂȂ�c

						mimitto->SetDeath();//���O������

						if (Hantei == true) {
							//�M���M���{�[�i�X�J�E���g��+1
							gamedata->GiriCounter();
							//�{�[�i�X�����̃G�t�F�N�g��\��
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { souka_position.x,souka_position.y + SpawnEffectY,souka_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//SS-001�Ƃ̋������v�Z
	QueryGOs<SS_001>("SS_001", [&](SS_001* ss_001) {
		if (ss_001->IsActive() == false) {
			//Active����Ȃ��B
			return true;
		}
		CVector3 Shisok_position = ss_001->Getm_Position();
		CVector3 diff = Shisok_position - position;
		playerVec = diff;
		//����ł��Ȃ���ΐڐG����
		if (player_state != Estate_Death) {
			//���_���[�W�����W�� �ǂ����B
			float Langth_hoge = ss_001->GetDamageLength();
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
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
					if (NowSkillNo == 7) { //�]���r�^�C�����͎��Ȃ��ɔ����łԂ��Ƃ�
						m_moveSpeed.x *= -Zonbi_Handou_Boss;
						m_moveSpeed.y *= -Zonbi_Handou_Boss;
						m_moveSpeed.z *= -Zonbi_Handou_Boss;
						}
					else {
						if (player_state != Estate_Frea) {
							m_Life = 0;
						}
					}

					if (DashFlag == true || player_state == Estate_Dash || player_state == Estate_Frea) {//�G���U�����̎��łȂ����_�b�V����ԂȂ�c

						prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
						ss->Init(L"sound/damage.wav");
						ss->SetVolume(0.5f);
						ss->Play(false);

						//�I���@�I
						ss_001->Damage(Damage);
						gamedata->PlusBossDamage();

					}


				}
			}

			//�r�[������I
			int EState = ss_001->GetEState();
			if (EState == SS_001::Estete_Attack2) {//�r�[���Ȃ�
				float X_MAX = Shisok_position.x + ss_001->GetBeamRange();
				float X_MIN = Shisok_position.x - ss_001->GetBeamRange();
				float Y_MAX = Shisok_position.y + ss_001->GetBeamRange();
				float Y_MIN = Shisok_position.y - ss_001->GetBeamRange();
				//���A�R���̎�
				if (X_MAX > position.x && X_MIN < position.x && Y_MAX > position.y && Y_MIN < position.y) {
					//�������[����
					m_Life = 0;
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

	GameData * gamedata = GameData::GetInstance();
	SaveData * savedata = SaveData::GetInstance();

	if (ResetTimer == 0) {

		prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
		//SE�Đ�
		ss->Init(L"sound/P_death.wav");
		ss->SetVolume(0.5f);
		ss->Play(false);

		//����ł��܂����I
		player_state = Estate_Death;
		
		DashTimeCount = -1;
		DashFlag = false;
		A_DashFlag = false;
		DashTimeCount = -1;
		NowSkillReset();

		if (savedata->GetSkill(false) == 18) { //�J�~�J�[�o�g��
			m_LifeSpeed = m_LifeSpeedDEF / 2;
		}
		else {
			m_LifeSpeed = m_LifeSpeedDEF;
		}

		//�ړ���~
		m_moveSpeed = CVector3::Zero;

		//���G���Ԃ̏����I
		MutekiTimer = 0;
	}

	if (GameData::GetInstance()->GetGameMode() == GameData::Battle2D_Mode && ResetTimer == 5) {
		//����������̂�2D���[�h�����B
		if (savedata->GetSkill(false) != 21 && savedata->GetSkill(true) != 21) { //�i�~�_�X�L���������͑����Ȃ�
			NakamaLight * nakamaLight = NewGO<NakamaLight>(0);
			//NakamaLight * nakamaLight = NakamaLight::GetInstance();
			nakamaLight->NakamaPlus(false, false);
		}
	}
	if (GameData::GetInstance()->GetGameMode() == GameData::Battle3D_Mode && ResetTimer == 5) {
		//3D���[�h�Ȃ痬���Q�[�W�㏸
		if (savedata->GetSkill(false) != 21 && savedata->GetSkill(true) != 21) { //�i�~�_�X�L���������͑����Ȃ�
			NakamaLight * nakamaLight = NewGO<NakamaLight>(0);
			//NakamaLight * nakamaLight = NakamaLight::GetInstance();
			nakamaLight->NakamaPlus(false, false);
		}
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

	//�����c�@���P�Ȃ炨���܂��ł���
	int zanki = gamedata->GetZanki();
	if (zanki == 1 && ResetTimer == DeathLightTime) {
		gamedata->SetZanki(-1);//�c�@����
		gamedata->SetGameMode(GameData::GameOver);
		MutekiTimer = -1;
		m_skinModelRender->SetActiveFlag(false);
		DeleteGOs("Radar");
		LaderFlag = true;
	}
	else if (zanki == 0) {
		ResetTimer = 0;
	}

	//
	//�C���^�[�o���I��
	//
	if (ResetTimer == ResetAverage) {
		//�Q�[���f�[�^����ő���������������Ă���
		m_Life = gamedata->GetDEF_Life();
		//���`�`�`�`�`�`
			ResetTimer = -1;
			gamedata->SetZanki(-1);//�c�@����
			 //��Ԃ�߂�
			player_state = Estate_Stay;
			//�����������x���߂�
			LifeSpeedReset();
			//�����������߂�
			if (GameData::GetInstance()->GetStageNo() == 3 && GameData::GetInstance()->GetGameMode() == GameData::Battle3D_Mode) {
				position = P_Pos_Metoro3D;
			}
			else {
				position = CVector3::Zero;
			}
			m_charaCon.SetPosition(position); //�L�����R�����߂���
			rotation = CQuaternion::Identity;
			m_scale = CVector3::One;
			LightStatus = LightStatusDEF;
			m_moveSpeed = DeathMove;
			//�͂��B
			m_skinModelRender->SetPosition(position);
			m_skinModelRender->SetRotation(rotation);
			m_skinModelRender->SetScale(m_scale);
			/*
			if (GameData::GetInstance()->GetGameMode() == GameData::Battle2D_Mode) {
				//����������̂�2D���[�h�����B
				GraphicsEngine().GetPostEffect().GetDithering().AddPointLig();
			}
			*/
			//�ړ����I������̂ŃG�t�F�N�g���Đ��i�ړ���ɂ��Ȃ��Ǝ��񂾏ꏊ�ōĐ�����Ă��܂��̂Łj
			EffectManager * effectmanager = EffectManager::GetInstance();
			int mode = gamedata->GetGameMode();
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

	//���݃��[�h
	GameData * gameData = GameData::GetInstance();
	SaveData * savedata = SaveData::GetInstance();
	int mode = gameData->GetGameMode();

	//�^�C�}�[���Z
	if (mode != GameData::Pause && player_state != Estate_Frea) { //�|�[�Y���ƃ\�E���t���A���͎��s���Ȃ��I
		MutekiTimer++;
	}

	if (MutekiTimer >= ResetAverage && mode != 2) {
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

	int Hosei = 0;
	
	if (savedata->GetSkill(false) == 13 || savedata->GetSkill(true) == 13) { //���e�L�m�o�V
		Hosei = 60;
	}

	//���Ԑ؂�

	if (MutekiTimer >= MutekiAverage + Hosei) {
		MutekiTimer = -1; //���G��߂�
		m_skinModelRender->SetActiveFlag(true);
	}
}

void Player::LightStatusSupporter() {

	//�Ăяo��
	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();
	float RightHosei = 1.0f - gamedata->ZankiWariai(); //�t���c
	float range;
	if (GameData::GetInstance()->GetGameMode() == GameData::Battle2D_Mode) {
		//2D���[�h�ł͒��Ԃ̓|�C���g���C�g�ɂȂ�B
		range = minRange;
	}
	else {
		//����ȊO(3D���[�h�Ȃ�)�ł́A���E�S�̂��Ƃ炷�B
		range = minRange * (1.0f - RightHosei) + maxRange * RightHosei;
	}
	
	//LightStatus�̒l��ݒ�
	float LightX = gamedata->GetLifePercent(0);
	LightX = 1.0f - LightX; //����Ŋ������킩��܂��I�I�I�I
	LightStatus = LightStatusMAX * LightX;
	range += LightStatus;

	//�ӂ͂͂�
	if (mode == GameData::Battle3D_Mode) {
		LightStatus *= LightHosei3D;
	}

	if (NowSkillNo == 4) { //�J�K���L�m�E�~
		range *= 4.0f;
	}

	//�Z�b�g(^_-)-��
	SetSpecialLigRange(range, 0.2f);

}

void Player::SkillYobidashi(int SkillNo) {

	//�������X�L��No��ݒ�
	NowSkillNo = SkillNo;
	GameData * gameData = GameData::GetInstance();
	EffectManager * effectmanager = EffectManager::GetInstance();

	if (SkillNo == 0) {//�����_�b�V��
		prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/stardash.wav");
		ss->SetVolume(1.0f);
		ss->Play(false);

		//�_�b�V����ԂɂȂ邼�I�I�I�I�I�I
		m_LifeSpeed = 1;
		player_state = Estate_Dash;
		DashFlag = true;
		DashTimeCount = -2; //��������Ȃ��_�b�V����ԂɂȂ�
	}
	else if (SkillNo == 1) { //����؂��Ƃ��_�b�V��
		prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/stardash.wav");
		ss->SetVolume(1.0f);
		ss->Play(false);

		//�_�b�V����ԂɂȂ邼�I�I�I�I�I�I
		m_LifeSpeed = 1;
		player_state = Estate_Dash;
		DashFlag = true;
		DashTimeCount = -2; //��������Ȃ��_�b�V����ԂɂȂ�
	}
	else if (SkillNo == 2) { //���������_�b�V��
		prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/stardash.wav");
		ss->SetVolume(1.0f);
		ss->Play(false);

		//�_�b�V����ԂɂȂ邼�I�I�I�I�I�I
		m_LifeSpeed = 1;
		player_state = Estate_Dash;
		DashFlag = true;
		DashTimeCount = -2; //��������Ȃ��_�b�V����ԂɂȂ�
	}
	else if (SkillNo == 3) { //�X�^�[�h���b�v
		NakamaLight * stardrop = NewGO<NakamaLight>(0);
		stardrop->NakamaPlus(true,false);

		effectmanager->EffectPlayer_Post(EffectManager::Bonus, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale);

	}
	else if (SkillNo == 4) { //�J�K���L�m�E�~
		//���ʉ�����
		prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/stardash.wav");
		ss->SetVolume(1.0f);
		ss->Play(false);

		effectmanager->EffectPlayer_Post(EffectManager::Bonus, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale);

	}
	else if (SkillNo == 5) { //�X�^�[�t�B�[�o�[
		NakamaLight * starFi1 = NewGO<NakamaLight>(0);
		starFi1->NakamaPlus(true,true);
		NakamaLight * starFi2 = NewGO<NakamaLight>(0);
		starFi2->NakamaPlus(true,true);
		NakamaLight * starFi3 = NewGO<NakamaLight>(0);
		starFi3->NakamaPlus(true,true);

		effectmanager->EffectPlayer_Post(EffectManager::Bonus, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale);

	}
	else if (SkillNo == 6) { //�~���L�[�E�F�C
		NakamaLight * starMil1 = NewGO<NakamaLight>(0);
		starMil1->NakamaPlus(true, true);
		NakamaLight * starMil2 = NewGO<NakamaLight>(0);
		starMil2->NakamaPlus(true, true);
		NakamaLight * starMil3 = NewGO<NakamaLight>(0);
		starMil3->NakamaPlus(true, true);
		NakamaLight * starMil4 = NewGO<NakamaLight>(0);
		starMil4->NakamaPlus(true, true);
		NakamaLight * starMil5 = NewGO<NakamaLight>(0);
		starMil5->NakamaPlus(true, true);
		NakamaLight * starMil6 = NewGO<NakamaLight>(0);
		starMil6->NakamaPlus(true, true);
		NakamaLight * starMil7 = NewGO<NakamaLight>(0);
		starMil7->NakamaPlus(true, true);
		NakamaLight * starMil8 = NewGO<NakamaLight>(0);
		starMil8->NakamaPlus(true, true);
		NakamaLight * starMil9 = NewGO<NakamaLight>(0);
		starMil9->NakamaPlus(true, true);
		NakamaLight * starMil10 = NewGO<NakamaLight>(0);
		starMil10->NakamaPlus(true, true);

		effectmanager->EffectPlayer_Post(EffectManager::Bonus, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale);

	}
	else if (SkillNo == 7) { //�]���r�^�C��
		//���ʉ�����
		prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/ZonbiTime.wav");
		ss->SetVolume(0.5f);
		ss->Play(false);

		effectmanager->EffectPlayer_Post(EffectManager::Bonus, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale);

	}
	else if (SkillNo == 8) { //�i�K���{�V
		//���ʉ�����
		prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/Nagareboshi.wav");
		ss->SetVolume(0.5f);
		ss->Play(false);

		effectmanager->EffectPlayer_Post(EffectManager::Bonus, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale);

	}
	else if (SkillNo == 9) { //�\�E���t���A
		prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/beamcharge.wav");
		ss->SetVolume(0.8f);
		ss->SetFrequencyRatio(1.5f);
		ss->Play(false);

		//Effect�Đ�
		effectmanager->EffectPlayer_Post(EffectManager::Beam, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale, true);

		MutekiTimer = 0; //���G�ɂȂ�i�������\�E���t���A�������͉i�����I�j
		m_LifeSpeed = 99999; //����Ɏ����������������Ȃ��̂��I
		player_state = Estate_Frea;
	}
	else if (SkillNo == 10) { //��������
		prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/Stacco.wav");
		ss->SetVolume(1.0f);
		ss->Play(false);

		effectmanager->EffectPlayer_Post(EffectManager::Bonus, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale);

	}
	else if (SkillNo == 11) { //�����͂��c�ł����˂�
		prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/ZankiKaihuku.wav");
		ss->SetVolume(1.0f);
		ss->Play(false);

		//�c�@���Z
		int MAX_Zanki = gameData->GetDEF_Zanki();
		float PlusZanki = (float)MAX_Zanki * 0.1f;
		gameData->SetZanki((int)PlusZanki);

		effectmanager->EffectPlayer_Post(EffectManager::Bonus, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale);

	}
	else if (SkillNo == 22) { //�L�R�T�[�`
		prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/ZankiKaihuku.wav");
		ss->SetVolume(1.0f);
		ss->Play(false);

		effectmanager->EffectPlayer_Post(EffectManager::Bonus, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale);

	}

}

void Player::NowSkillReset() { //���񂾂甭���I������X�L���͂�����

	if (NowSkillNo == 0) {//�����_�b�V��
		NowSkillNo = -1;
	}else if (NowSkillNo == 1) {//����؂��Ƃ��_�b�V��
		NowSkillNo = -1;
	}
	else if (NowSkillNo == 2) {//���������_�b�V��
		NowSkillNo = -1;
	}
	else if (NowSkillNo == 7) {//�]���r�^�C��
		NowSkillNo = -1; //�G�ɓ������Ă����ȂȂ����ǒe��d�Ԃɓ��������炱���ɍs����
	}
	else if (NowSkillNo == 9) {//�\�E���t���A
		NowSkillNo = -1;
	}
	else if (NowSkillNo == 10) {//�X�^�[�R���b�g
		NowSkillNo = -1;
	}


}

void Player::SkillUpdate() { //���Ԃ��o�ĂΏI������X�L���͂�����

	if (NowSkillNo == -1) {
		SkillTimer = 0;
		SkillTimer2 = 0;
		SoulStarFlag = false;

	}

	if (NowSkillNo == 3) {//�X�^�[�h���b�v��
		GameData * gamedata = GameData::GetInstance();
		gamedata->Star_PowerChange(-5);		//�����Q�[�W����
		SkillTimer += 5;
		if (SkillTimer >= Skill_Data[3].StarPower) { //�͂��I��
			NowSkillNo = -1;
			SkillTimer = 0;
		}
	}
	else if (NowSkillNo == 4) { //�J�K���L�m�E�~
		GameData * gamedata = GameData::GetInstance();
		SkillTimer2++;
		if (SkillTimer2 == 5) {
			gamedata->Star_PowerChange(-1);
			SkillTimer += 1;
			SkillTimer2 = 0;
		}
		if (SkillTimer >= Skill_Data[4].StarPower) { //�͂��I��
			NowSkillNo = -1;
			SkillTimer = 0;
		}
	}
	else if (NowSkillNo == 5) {//�X�^�[�t�B�[�o�[��
		GameData * gamedata = GameData::GetInstance();
		gamedata->Star_PowerChange(-10);		//�����Q�[�W����
		SkillTimer += 10;
		if (SkillTimer >= Skill_Data[5].StarPower) { //�͂��I��
			NowSkillNo = -1;
			SkillTimer = 0;
		}
	}
	else if (NowSkillNo == 6) {//�~���L�[�E�F�C��
		GameData * gamedata = GameData::GetInstance();
		gamedata->Star_PowerChange(-10);		//�����Q�[�W����
		SkillTimer += 10;
		if (SkillTimer >= Skill_Data[6].StarPower) { //�͂��I��
			NowSkillNo = -1;
			SkillTimer = 0;
		}
	}
	else if (NowSkillNo == 7) {//�]���r�^�C����
		GameData * gamedata = GameData::GetInstance();
		SkillTimer2++;
		if (SkillTimer2 == Zonbi_Gensyo_Limit) {
			gamedata->Star_PowerChange(-1);
			SkillTimer += 1;
			SkillTimer2 = 0;
		}
		if (SkillTimer >= Skill_Data[7].StarPower) { //�͂��I��
			NowSkillNo = -1;
			SkillTimer = 0;
			m_Life = 0;
		}
	}
	else if (NowSkillNo == 8) {//�i�K���{�V��
		GameData * gamedata = GameData::GetInstance();
		SkillTimer2++;
		if (SkillTimer2 == 5) {
			gamedata->Star_PowerChange(-1);
			SkillTimer += 1;
			SkillTimer2 = 0;
		}
		if (SkillTimer >= Skill_Data[7].StarPower) { //�͂��I��
			NowSkillNo = -1;
			SkillTimer = 0;
		}
	}
	else if (NowSkillNo == 9) {//�\�E���t���A
		GameData * gamedata = GameData::GetInstance();
		if (SoulStarFlag == false) {
			gamedata->Star_PowerChange(-10);		//�����Q�[�W����
			SkillTimer += 10;
		}
		if (SkillTimer >= Skill_Data[9].StarPower) { //�͂��I��
			SoulStarFlag = true;
			SkillTimer = 0;
		}
	}
	else if (NowSkillNo == 10) {//�X�^�[�R���b�g
		GameData * gamedata = GameData::GetInstance();
		SkillTimer2++;
		if (SkillTimer2 == 5) {
			gamedata->Star_PowerChange(-1);
			SkillTimer += 1;
			SkillTimer2 = 0;
		}
		if (SkillTimer >= Skill_Data[10].StarPower) { //�͂��I��
			NowSkillNo = -1;
			SkillTimer = 0;
		}
	}
	else if (NowSkillNo == 11) {//������
		GameData * gamedata = GameData::GetInstance();
		gamedata->Star_PowerChange(-10);		//�����Q�[�W����
		SkillTimer += 10;
		if (SkillTimer >= Skill_Data[11].StarPower) { //�͂��I��
			NowSkillNo = -1;
			SkillTimer = 0;
		}
	}
	else if (NowSkillNo == 22) {//�L�R�T�[�`
		GameData * gamedata = GameData::GetInstance();
		SkillTimer2++;
		if (SkillTimer2 == 5) {
			gamedata->Star_PowerChange(-1);
			SkillTimer += 1;
			SkillTimer2 = 0;
		}
		if (SkillTimer >= Skill_Data[22].StarPower) { //�͂��I��
			NowSkillNo = -1;
			SkillTimer = 0;
		}
	}



}
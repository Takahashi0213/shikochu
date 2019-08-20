#include "stdafx.h"
#include "GameData.h"
#include "Player_Status.h"
#include "Player.h"
#include "SaveData.h"
#include "SkillData.h"

Player_Status* Player_Status::m_instance = nullptr;

Player_Status::Player_Status()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɃv���C���[���o�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;

}


Player_Status::~Player_Status()
{
	for (int i = 0; i < m_spriteRender.size(); i++) {
		DeleteGO(m_spriteRender[i]);
	}
	for (int i = 0; i < m_spriteRenderBar.size(); i++) {
		DeleteGO(m_spriteRenderBar[i]);
	}
	DeleteGO(m_fontRender);

	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;

}

bool Player_Status::Start() {

	GameData * gamedata = GameData::GetInstance();
	BeforeZanki = gamedata->GetZanki();

	//�����Q�[�W�y�� 0
	prefab::CSpriteRender* r = NewGO<prefab::CSpriteRender>(7);
	r->Init(L"sprite/StarBar_base.dds", 20.0f, 300.0f);
	CVector3 Position = { -550.0f, -10.0f, 1.0f };//���W
	r->SetPosition(Position);//���W�𔽉f
	m_spriteRender.push_back(r);
	//�����Q�[�W 1
	r = NewGO<prefab::CSpriteRender>(7);
	r->Init(L"sprite/StarBar.dds", 20.0f, 300.0f);
	Position = { -550.0f, -160.0f, 1.0f };//���W
	r->SetPosition(Position);//���W�𔽉f
	m_spriteRender.push_back(r);
	//�����Q�[�W�㕔�� 2
	r = NewGO<prefab::CSpriteRender>(8);
	r->Init(L"sprite/StarBarUe.dds", 30.0f, 330.0f);
	Position = { -550.0f, -28.0f, 1.0f };//���W
	r->SetPosition(Position);//���W�𔽉f
	m_spriteRender.push_back(r);

	//�����y�� 3
	r = NewGO<prefab::CSpriteRender>(7);
	r->Init(L"sprite/LifeBar_base.dds", 120.0f, 480.0f);
	Position = { -600.0f, -20.0f, 1.0f };//���W
	r->SetPosition(Position);//���W�𔽉f
	m_spriteRender.push_back(r);
	//�o�[ 4
	r = NewGO<prefab::CSpriteRender>(7);
	r->Init(L"sprite/LifeBar.dds", 120.0f, 480.0f);
	Position = { -600.0f, -215.0f, 1.0f };//���W
	r->SetPosition(Position);//���W�𔽉f
	m_spriteRender.push_back(r);
	//������ 0
	prefab::CSpriteRender* rr = NewGO<prefab::CSpriteRender>(7);
	rr->Init(L"sprite/LifeBar_white.dds", 120.0f, 480.0f);
	Position = { -600.0f, 170.0f, 1.0f };//���W
	rr->SetPosition(Position);//���W�𔽉f
	m_spriteRenderBar.push_back(rr);
	//������ 1
	rr = NewGO<prefab::CSpriteRender>(7);
	rr->Init(L"sprite/LifeBar_base.dds", 120.0f, 480.0f);
	Position = { -600.0f, 170.0f, 1.0f };//���W
	rr->SetPosition(Position);//���W�𔽉f
	rr->SetScale({ 1.0f,0.0f,1.0f });//�g�嗦�𔽉f
	m_spriteRenderBar.push_back(rr);
	//�����㕔�� 5
	r = NewGO<prefab::CSpriteRender>(8);
	r->Init(L"sprite/LifeBarUe.dds", 120.0f, 480.0f);
	Position = { -600.0f, -20.0f, 1.0f };//���W
	r->SetPosition(Position);//���W�𔽉f
	m_spriteRender.push_back(r);

	//�\�E���A�C�R�� 6
	r = NewGO<prefab::CSpriteRender>(8);
	r->Init(L"sprite/soulIC.dds", 100.0f, 100.0f);
	Position = { -600.0f, -220.0f, 1.0f };//���W
	r->SetPosition(Position);//���W�𔽉f
	m_spriteRender.push_back(r);
	//�c�@�A���_�[ 7
	r = NewGO<prefab::CSpriteRender>(8);
	r->Init(L"sprite/Zanki.dds", 300.0f, 300.0f);
	Position = { -550.0f, 280.0f, 1.0f };//���W
	r->SetPosition(Position);//���W�𔽉f
	m_spriteRender.push_back(r);

	//�Q�[�W�}�b�N�X�A�C�R�� 8(����)
	r = NewGO<prefab::CSpriteRender>(8);
	r->Init(L"sprite/starMax.dds", 150.0f, 100.0f);
	Position = { -480.0f, -150.0f, 1.0f };//���W
	r->SetPosition(Position);//���W�𔽉f
	r->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
	m_spriteRender.push_back(r);

	//�{�[�i�X�A�C�R�� 9
	r = NewGO<prefab::CSpriteRender>(8);
	r->Init(L"sprite/KikoIC_Full.dds", 200.0f, 200.0f);
	Position = { 640.0f, -50.0f, 1.0f };//���W
	r->SetPosition(Position);//���W�𔽉f
	r->SetMulColor({ 1.0f,1.0f,1.0f,Kiko_Alpha });
	m_spriteRender.push_back(r);

	//Y�X�L��IC 10
	r = NewGO<prefab::CSpriteRender>(5);
	r->Init(L"sprite/skillicon_1.dds", 150.0f, 100.0f);
	r->SetPosition({ -510.0f,105.0f ,0.0f });//���W�𔽉f
	r->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	r->SetScale({ SkillScale,SkillScale, SkillScale });
	m_spriteRender.push_back(r);

	//Y�X�L���g 11
	r = NewGO<prefab::CSpriteRender>(6);
	r->Init(L"sprite/skilliconWakuY.dds", 190.0f, 100.0f);
	r->SetPosition({ -510.0f,105.0f ,0.0f });//���W�𔽉f
	r->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	r->SetScale({ SkillScale,SkillScale, SkillScale });
	m_spriteRender.push_back(r);

	//X�X�L��IC 12
	r = NewGO<prefab::CSpriteRender>(5);
	r->Init(L"sprite/skillicon_10.dds", 150.0f, 100.0f);
	r->SetPosition({ -515.0f,50.0f ,0.0f });//���W�𔽉f
	r->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	r->SetScale({ SkillScale,SkillScale, SkillScale });
	m_spriteRender.push_back(r);

	//X�X�L���g 13
	r = NewGO<prefab::CSpriteRender>(6);
	r->Init(L"sprite/skilliconWakuX.dds", 190.0f, 100.0f);
	r->SetPosition({ -515.0f,50.0f ,0.0f });//���W�𔽉f
	r->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	r->SetScale({ SkillScale,SkillScale, SkillScale });
	m_spriteRender.push_back(r);

	//���F�̃A��Y 14
	r = NewGO<prefab::CSpriteRender>(7);
	r->Init(L"sprite/Yellow.dds", 20.0f, 4.0f);
	r->SetPosition({ -550.0f, 0.0f, 1.0f });//���W�𔽉f
	r->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	r->SetScale({ 1.0f,1.0f, 1.0f });
	m_spriteRender.push_back(r);

	//�F�̃A��X 15
	r = NewGO<prefab::CSpriteRender>(7);
	r->Init(L"sprite/Blue.dds", 20.0f, 4.0f);
	r->SetPosition({ -550.0f, -156.0f, 1.0f });//���W�𔽉f
	r->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	r->SetScale({ 1.0f,1.0f, 1.0f });
	m_spriteRender.push_back(r);

	///////��������e�L�X�g//////
	//�c�@����
	m_fontRender = NewGO<prefab::CFontRender>(8);
	m_fontRender->SetPivot({ 0.5f,0.5f });

	//�{�[�i�X����
	m_fontRender_bonus = NewGO<prefab::CFontRender>(8);
	//�\��
	wchar_t text[256];
	//����
	swprintf(text, L"BONUS!");
	//�͂��B
	m_fontRender_bonus->SetText(text);
	m_fontRender_bonus->SetPosition({ 640.0f, -130.0f });
	m_fontRender_bonus->SetPivot({ 0.5f,0.5f });
	m_fontRender_bonus->SetScale(0.8f);
	m_fontRender_bonus->SetColor({ 1.0f,0.5f,0.0f,Kiko_Alpha });

	SkillSetUp();

	return true;

}

void Player_Status::Update() {

	//����
	CVector3 LifeScale = CVector3::Zero;
	CVector3 StarScale = CVector3::Zero;
	Player * player = Player::GetInstance();
	GameData * gamedata = GameData::GetInstance();

	//�����Q�[�W�𓮂���
	float DEF_Life = (float)gamedata->GetDEF_Life();
	float NOW_Life = (float)player->GetLife();

	//�����̊g�嗦���v�Z
	float LifeY = NOW_Life / DEF_Life;
	if (LifeY == 1.0f) {//�������}���^��
		m_spriteRenderBar[1]->SetPivot(LifePivot);
		m_spriteRenderBar[1]->SetScale({ 1.0f,0.0f,1.0f });
	}
	else if (LifeY == 0.0f) {//�������[��
		m_spriteRenderBar[1]->SetPivot(LifePivot);
		m_spriteRenderBar[1]->SetScale({ 1.0f,1.0f,1.0f });
	}
	LifeY = 1.0f - LifeY;
	//LifeY *= 480.0f;
	LifeScale = { 1.0f,LifeY,1.0f };
	//�����o�[�̐F���ς���́H
	float RED_Life = DEF_Life / 2.0f;
	//�����o�[�̐F�ς�
	if (NOW_Life < RED_Life) {
		LifeColor = { 255.0f,0.5f,0.5f,1.0f };
	}else {
		LifeColor = { 1.0f,1.0f,1.0f,1.0f };
	}

	m_spriteRenderBar[0]->SetPivot(LifePivot);
	m_spriteRenderBar[0]->SetScale(LifeScale);	
	m_spriteRender[4]->SetPivot(LifePivot2);
	m_spriteRender[4]->SetMulColor(LifeColor);

	CVector3 Ue_Gage = m_spriteRenderBar[1]->GetScale();
	CVector3 Sita_Gage = m_spriteRenderBar[0]->GetScale();

	if (player->GetA_DashFlag() == true) {//A�_�b�V�����Ȃ猸��������
		WhiteGage = true;

			Ue_Gage.y += 0.01f;
			if (Ue_Gage.y > Sita_Gage.y) {
				Ue_Gage.y = Sita_Gage.y;
			}

	}
	else {
		WhiteGage = false;
		Ue_Gage.y = Sita_Gage.y;
	}
	m_spriteRenderBar[1]->SetPivot(LifePivot);
	m_spriteRenderBar[1]->SetScale(Ue_Gage);

	//�����Q�[�W�𓮂���
	float NOW_StarPower = (float)gamedata->GetStar_Power();
	float DEF_StarPower = (float)gamedata->GetMAXStar_Power();
	//�F���ς��{�[�_�[��ݒ�i��ԏ���������l���{�[�_�[�j
	int Star_border = 100;
	if (Skill_Data[SkillNoY].StarPower > 0) {
		if (Skill_Data[SkillNoY].StarPower < Star_border) {
			Star_border = Skill_Data[SkillNoY].StarPower;
		}
	}
	if (Skill_Data[SkillNoX].StarPower > 0) {
		if (Skill_Data[SkillNoX].StarPower < Star_border) {
			Star_border = Skill_Data[SkillNoX].StarPower;
		}
	}

	//�Q�[�W�̊g�嗦���v�Z
	float StarY = NOW_StarPower / DEF_StarPower;
	StarScale = { 1.0f,StarY,1.0f };
	//�����o�[�̐F�ς�
	if ((int)NOW_StarPower >= Star_border) {
		StarColor = { 1.0f,1.0f,1.0f,1.0f };
	}
	else {
		StarColor = { 0.5f,0.5f,255.0f,1.0f };
	}

	m_spriteRender[1]->SetPivot(StarPivot);
	m_spriteRender[1]->SetScale(StarScale);
	m_spriteRender[1]->SetMulColor(StarColor);
	
	//�Q�[�W���B�Ō��ʉ�

	//Y�X�L��
	if (SkillNoY > -1) { //�Z�b�g����Ă��邩
		if (Skill_Data[SkillNoY].StarPower > 0) { //�p�b�V�u�X�L���łȂ���
			if (NOW_StarPower >= Skill_Data[SkillNoY].StarPower) {
				if (StarMaxSE == false) { //SE�t���O�`�F�b�N
					prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
					ss->Init(L"sound/StarGageMAX.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);

					StarMaxSE = true;
				}
			}
			else {
				StarMaxSE = false;
			}
		}
	}

	//X�X�L��
	if (SkillNoX > -1) { //�Z�b�g����Ă��邩
		if (Skill_Data[SkillNoX].StarPower > 0) { //�p�b�V�u�X�L���łȂ���
			if (NOW_StarPower >= Skill_Data[SkillNoX].StarPower) {
				if (StarMaxSE2 == false) { //SE�t���O�`�F�b�N
					prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
					ss->Init(L"sound/StarGageMAX.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);

					StarMaxSE2 = true;
				}
			}
			else {
				StarMaxSE2 = false;
			}
		}
	}

	//�����Q�[�W�ɉ����Č������茩���Ȃ������肵��
	/*
	if (StarMaxFlag == true) {
		//�����違�_�ł���
		if (StarMaxColorFlag == false) {
			StarMaxColor += 0.05f;
			StarMaxScale += 0.01f;
			if (StarMaxColor > 2.0f) {
				StarMaxColor = 2.0f;
				StarMaxColorFlag = true;
			}
		}
		else if (StarMaxColorFlag == true) {
			StarMaxColor -= 0.05f;
			StarMaxScale -= 0.01f;
			if (StarMaxColor < 1.0f) {
				StarMaxColor = 1.0f;
				StarMaxColorFlag = false;
			}
			m_spriteRender[8]->SetMulColor({ StarMaxColor,StarMaxColor,StarMaxColor,0.8f });
			m_spriteRender[8]->SetScale({ StarMaxScale ,StarMaxScale ,StarMaxScale });
		}
	}
	else {
		//��\��
		m_spriteRender[8]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
	}
	*/

	//�c�@���X�V
	wchar_t text[256];
	//����
	swprintf(text, L"%d", gamedata->GetZanki());
	//�͂��B
	m_fontRender->SetText(text);
	if (gamedata->GetZanki() <= 9) { //�c�@��1���ł��I
		m_fontRender->SetPosition({ ZankiPos.x + ZankiPosXHosei ,ZankiPos.y});
	}
	else {
		m_fontRender->SetPosition(ZankiPos);
	}
	m_fontRender->SetScale(ZankiScaleNow);
	
	//�������ݎc�@�ƑO�c�@���Ⴄ�Ȃ�A�j���t���O�I��
	if (gamedata->GetZanki() != BeforeZanki) {
		ZankiAnimeFlag = true;
		BeforeZanki = gamedata->GetZanki();
		ZankiAnimeTimer = 0;
	}

	//�c�@�A�j���[�V����
	if (ZankiAnimeFlag == true) {

		if (ZankiAnimeTimer < ZankiAnimeLimit/2) {//�g��
			ZankiScaleNow += 0.1f;
		}
		else {//�߂�
			ZankiScaleNow -= 0.1f;
			if (ZankiScaleNow < ZankiScale) {
				ZankiScaleNow = ZankiScale;
			}
		}

		if (ZankiAnimeTimer == ZankiAnimeLimit) { //�c�@�A�j���[�V�����I��
			ZankiAnimeFlag = false;
		}
		ZankiAnimeTimer++;
	}

	//�L�R�E�`���E���o
	if (gamedata->GetKikoFlag() == true && KikoFlag == false) { //�L�R�E�`���E�����j���Ă���̂ɉ��o���܂����\���Ȃ���s
		CVector3 pos = m_spriteRender[9]->GetPosition();
		CVector2 pos_2 = m_fontRender_bonus->GetPosition();
		if (KikoTimer < KikoLimit / 2) { //���ֈړ�
			pos.x -= KikoMoveX;
			pos_2.x -= KikoMoveX;
			Kiko_Alpha += Kiko_AlphaSpeed;
			if (Kiko_Alpha > 1.0f) {
				Kiko_Alpha = 1.0f;
			}
		}
		else if (KikoTimer > (KikoLimit / 2) + KikoWait) { //�E�ֈړ�
			pos.x += KikoMoveX;
			pos_2.x += KikoMoveX;
			Kiko_Alpha -= Kiko_AlphaSpeed;
			if (Kiko_Alpha < 0.0f) {
				Kiko_Alpha = 0.0f;
			}
		}
		m_spriteRender[9]->SetPosition(pos);
		m_spriteRender[9]->SetMulColor({ 1.0f,1.0f,1.0f,Kiko_Alpha });
		m_fontRender_bonus->SetPosition(pos_2);
		m_fontRender_bonus->SetColor({ 1.0f,0.5f,0.0f,Kiko_Alpha });

		//�I������
		if (KikoTimer == KikoLimit + KikoWait) {
			KikoFlag = true;
		}

		KikoTimer++;
	}

	SkillUpdate(); //���Ղ�

}

void Player_Status::SkillSetUp(){

	//�v���C���[���Z�b�g���Ă�X�L�������������Ă���
	SaveData * savedata = SaveData::GetInstance();

	SkillNoY = savedata->GetSkill(false);
	SkillNoX = savedata->GetSkill(true);

}

void Player_Status::SkillUpdate() {

	//�X�L���f�[�^����₻���
	GameData * gamedata = GameData::GetInstance();
	Player * player = Player::GetInstance();
	//SaveData * savedata = SaveData::GetInstance();
	wchar_t text[256];

	//Y�X�L����//

	//�Z�b�g�ςݔ���
	if (SkillNoY != -1) {

		//�p�b�V�u�X�L������
		if (Skill_Data[SkillNoY].StarPower == 0) {
			//�A�C�R����\�����Ėڈ�͕\�����Ȃ�
			int len = (int)wcslen(Skill_Data[SkillNoY].SkillIcon);
			for (int z = 0; z < len + 1; z++) { //���O�̎擾
				text[z] = Skill_Data[SkillNoY].SkillIcon[z];
			}
			m_spriteRender[10]->Init(text, 150.0f, 100.0f);

			m_spriteRender[14]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });

		}
		else { //�����^
			if (Skill_Data[SkillNoY].StarPower <= gamedata->GetStar_Power() && player->GetNowSkill() == -1) { //�����\
				if (SkillIconMAX_Timer < 15) {
					m_spriteRender[10]->Init(L"sprite/skillicon_Y.dds", 150.0f, 100.0f);
				}
				else {
					m_spriteRender[10]->Init(L"sprite/skillicon_Y2.dds", 150.0f, 100.0f);
				}
			}
			else {
				//�A�C�R����\�����Ėڈ�͕\�����Ȃ�
				int len = (int)wcslen(Skill_Data[SkillNoY].SkillIcon);
				for (int z = 0; z < len + 1; z++) { //���O�̎擾
					text[z] = Skill_Data[SkillNoY].SkillIcon[z];
				}
				m_spriteRender[10]->Init(text, 150.0f, 100.0f);
			}

			//�o�[�\��
			float SkillY = (float)Skill_Data[SkillNoY].StarPower / gamedata->GetMAXStar_Power();
			SkillY = StarPOS + (StarMAX * SkillY);

			m_spriteRender[14]->SetPosition({ -550.0f, SkillY, 1.0f });

			m_spriteRender[14]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		}
	}
	else {//�����ݒ肳��Ă��Ȃ�

		m_spriteRender[10]->Init(L"sprite/skillicon_0.dds", 150.0f, 100.0f);

		m_spriteRender[14]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });

	}

	//X�X�L����//

	//�Z�b�g�ςݔ���
	if (SkillNoX != -1) {

		//�p�b�V�u�X�L������
		if (Skill_Data[SkillNoX].StarPower == 0) {
			//�A�C�R����\�����Ėڈ�͕\�����Ȃ�
			int len = (int)wcslen(Skill_Data[SkillNoX].SkillIcon);
			for (int z = 0; z < len + 1; z++) { //���O�̎擾
				text[z] = Skill_Data[SkillNoX].SkillIcon[z];
			}
			m_spriteRender[12]->Init(text, 150.0f, 100.0f);

			m_spriteRender[15]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });

		}
		else { //�����^
			if (Skill_Data[SkillNoX].StarPower <= gamedata->GetStar_Power() && player->GetNowSkill() == -1) { //�����\
				if (SkillIconMAX_Timer < 15) {
					m_spriteRender[12]->Init(L"sprite/skillicon_X.dds", 150.0f, 100.0f);
				}
				else {
					m_spriteRender[12]->Init(L"sprite/skillicon_X2.dds", 150.0f, 100.0f);
				}
			}
			else {
				//�A�C�R����\�����Ėڈ�͕\�����Ȃ�
				int len = (int)wcslen(Skill_Data[SkillNoX].SkillIcon);
				for (int z = 0; z < len + 1; z++) { //���O�̎擾
					text[z] = Skill_Data[SkillNoX].SkillIcon[z];
				}
				m_spriteRender[12]->Init(text, 150.0f, 100.0f);
			}

			//�o�[�\��
			float SkillY = (float)Skill_Data[SkillNoX].StarPower / gamedata->GetMAXStar_Power();
			SkillY = StarPOS + (StarMAX * SkillY);

			m_spriteRender[15]->SetPosition({ -550.0f, SkillY, 1.0f });

			m_spriteRender[15]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		}
	}
	else {//�����ݒ肳��Ă��Ȃ�

		m_spriteRender[12]->Init(L"sprite/skillicon_0.dds", 150.0f, 100.0f);

		m_spriteRender[15]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });

	}

	//�X�L���������Ȃ炻�̃X�L���A�C�R���̐F��ς���I�I
	int skill = player->GetNowSkill();
	if (skill > -1) {
		if (skill == SkillNoY) {
			m_spriteRender[12]->SetMulColor({ 0.2f,0.2f,0.2f,1.0f });

			if (SkillIconMAX_Timer < 15) {
				m_spriteRender[10]->SetMulColor({ 1.0f,1.0f,0.0f,1.0f });
			}
			else {
				m_spriteRender[10]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
			}
		}
		else if (skill == SkillNoX) {
			m_spriteRender[10]->SetMulColor({ 0.2f,0.2f,0.2f,1.0f });

			if (SkillIconMAX_Timer < 15) {
				m_spriteRender[12]->SetMulColor({ 1.0f,1.0f,0.0f,1.0f });
			}
			else {
				m_spriteRender[12]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
			}
		}
	}
	else {
		m_spriteRender[10]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		m_spriteRender[12]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	}

	//�^�C�}�[
	SkillIconMAX_Timer++;
	if (SkillIconMAX_Timer >= 30) {
		SkillIconMAX_Timer = 0;
	}

}

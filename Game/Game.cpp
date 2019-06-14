#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "Player_Status.h"
#include "GameData.h"
#include "StarItem.h"
#include "EffectManager.h"
#include "BackGround.h"
#include "WaveManager.h"
#include "UICamera.h"
#include "LevelSet.h"
#include "GameResult.h"
#include "WaveEffect.h"
#include "StageSelect.h"
#include "GameOver.h"
#include "GamePause.h"

#include "Akoyadokari.h"

Game* Game::m_instance = nullptr;

Game::Game()
{

	if (m_instance != nullptr) {
		std::abort();
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;

}


Game::~Game()
{
	GameData * gamedata = GameData::GetInstance();
	bool F_mode = gamedata->GetFinalMode();

	if (F_mode == true) {
		DeleteGOs("BossHPGage");
	}

	//�F�X����
	DeleteGOs("Gamecamera");
	DeleteGOs("Status");
	DeleteGOs("WaveManager");
	DeleteGOs("BackGround");
	DeleteGOs("Player_Status");
	DeleteGOs("LevelSet");
	DeleteGOs("Sky");
	DeleteGOs("L_Light");

	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;

	gamedata->SetGameMode(GameData::NotGame);

	WaveManager * wavemanager = WaveManager::GetInstance();
	wavemanager->DeleteAll();
	DeleteGOs("Bug");

	NewGO<UICamera>(0, "UICamera");
	NewGO<StageSelect>(0);
	//�P�x��߂��B
	postEffect::Tonemap().SetLuminance(0.4);
}
bool Game::Start()
{
	//EnableSpecialLigRange();
	DisableSpecialLigRange();

	NewGO<Player>(0,"Bug");

	NewGO<GameCamera>(0,"Gamecamera");
	NewGO<Player_Status>(0, "Status");
	NewGO<BackGround>(0, "BackGround");
	NewGO<WaveManager>(0, "WaveManager");
	NewGO<LevelSet>(0, "LevelSet");

	GameData * gamedata = GameData::GetInstance();
	gamedata->SetGameMode(GameData::Battle2D_Mode);
	gamedata->GameDataReset();
	int stageNo = gamedata->GetStageNo();
	stageNo--;

	//�w�i��\��
	BackGround * background = BackGround::GetInstance();
	background->StageMaker(stageNo);

	prefab::CSky* sky = NewGO<prefab::CSky>(0, "Sky");
	sky->SetScale({ 20000.0f, 20000.0f, 20000.0f });
	sky->SetEmissionColor({6.1f, 6.1f, 8.1f});
	LightManager().SetAmbientLight({ 100.1f,100.1f, 100.1f });

	m_directionLig = NewGO<prefab::CDirectionLight>(0,"L_Light");
	m_directionLig->SetColor({ 900.0f, 900.0f, 1000.0f, 1.0f });
	CVector3 ligDir = { 1, -1, 1 };
	ligDir.Normalize();
	m_directionLig->SetDirection(ligDir);
	GraphicsEngine().GetShadowMap().SetLightDirection(ligDir);

	//�z�u
	WaveManager * wavemanager = WaveManager::GetInstance();
	wavemanager->AllStage(stageNo);

	NewGO<WaveEffect>(0);

	return true;
}

void Game::Update()
{

	m_tonemapDisableTimer -= GameTime().GetFrameDeltaTime();
	if (m_tonemapDisableTimer <= 0.0f) {
		m_tonemapDisableTimer = 0.0f;
	}
	if (m_tonemapDisableTimer > 0.0f) {
		GraphicsEngine().GetTonemap().Reset();
	}

	GameData * gamedata = GameData::GetInstance();

	//���U���g�ɑJ��
	bool resultflag = gamedata->GetResultFlag();
	if (resultflag==true) {
		NewGO<GameResult>(0);
		gamedata->ResultFlagSet(false);
	}
	//���悤�Ȃ�c
	int mode=gamedata->GetGameMode();
	if (mode == GameData::GameEnd) {
		DeleteGO(this);
	}
	//����ł��܂��Ƃ͂Ȃ����Ȃ��I
	if (mode == GameData::GameOver && GameOverFlag == false) {
		NewGO<GameOver>(0);
		GameOverFlag = true;
	}

	//�|�`�`�`�`�`�`�Y�b�I�I�I
	if (mode == GameData::Battle2D_Mode || mode == GameData::Battle3D_Mode) {
		if (Pad(0).IsPress(enButtonSelect)) {
			NewGO<GamePause>(0);
		}
	}

}
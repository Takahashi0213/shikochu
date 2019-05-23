#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "Player_Status.h"
#include "GameData.h"
#include "Bunbogu.h"
#include "Title.h"
#include "StarItem.h"
#include "EffectManager.h"
#include "BackGround.h"
#include "Neoriku.h"
#include "shisokus.h"
#include "WaveManager.h"

#include "LevelSet.h"
#include "GameResult.h"
#include "WaveEffect.h"
#include "StageSelect.h"

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
	//�F�X����
	DeleteGOs("Bug");
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

	NewGO<StageSelect>(0);
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

	//�w�i��\��
	BackGround * background = BackGround::GetInstance();
	background->StageMaker(BackGround::Stage_1);

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
	wavemanager->AllStage(0);

	//NewGO<GameResult>(0);

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
}
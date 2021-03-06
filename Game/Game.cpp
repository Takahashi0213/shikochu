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
#include "StageGimmick.h"
#include "GameSupport.h"

#include "Metoporisu.h"

Game* Game::m_instance = nullptr;

Game::Game()
{

	if (m_instance != nullptr) {
		std::abort();
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

}


Game::~Game()
{
	GameData * gamedata = GameData::GetInstance();
	bool F_mode = gamedata->GetFinalMode();

	//もし最後のモードが3Dだったらゲージを消しておく
	if (F_mode == true) {
		DeleteGOs("BossHPGage");
	}

	//色々消す
	DeleteGOs("Gamecamera");
	DeleteGOs("Status");
	DeleteGOs("WaveManager");
	DeleteGOs("BackGround");
	DeleteGOs("Player_Status");
	DeleteGOs("LevelSet");
	DeleteGOs("StageGimmick");
	DeleteGOs("GameSupport");
	DeleteGOs("Sky");
	DeleteGOs("L_Light");

	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;

	gamedata->SetGameMode(GameData::NotGame);

	WaveManager * wavemanager = WaveManager::GetInstance();
	wavemanager->DeleteAll();
	DeleteGOs("Bug");

	NewGO<UICamera>(0, "UICamera");
	NewGO<StageSelect>(0);
	//輝度を戻す。
	postEffect::Tonemap().SetLuminance(0.4);
}
bool Game::Start()
{
	EnableSpecialLigRange();
	//DisableSpecialLigRange();

	NewGO<Player>(0,"Bug");
	//NewGO<Metoporisu>(0, "Metoporisu");

	NewGO<GameCamera>(0,"Gamecamera");
	NewGO<Player_Status>(0, "Status");
	NewGO<BackGround>(0, "BackGround");
	NewGO<WaveManager>(0, "WaveManager");
	NewGO<LevelSet>(0, "LevelSet");
	NewGO<StageGimmick>(0, "StageGimmick");
	NewGO<GameSupport>(0, "GameSupport");

	//ゲームモードの設定
	GameData * gamedata = GameData::GetInstance();
	gamedata->SetGameMode(GameData::Battle2D_Mode);
	//記録用変数のリセット
	gamedata->GameDataReset();
	//ステージ番号の取得
	int stageNo = gamedata->GetStageNo();
	stageNo--; //1減らさないとずれます

	//背景を表示
	BackGround * background = BackGround::GetInstance();
	background->StageMaker(stageNo);

	//空を表示
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

	//配置
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

	//リザルトに遷移
	bool resultflag = gamedata->GetResultFlag();
	if (resultflag==true) {
		NewGO<GameResult>(0);
		gamedata->ResultFlagSet(false);
	}
	//さようなら…
	int mode=gamedata->GetGameMode();
	if (mode == GameData::GameEnd) {
		DeleteGO(this);
	}
	//しんでしまうとはなさけない！
	if (mode == GameData::GameOver && GameOverFlag == false) {
		NewGO<GameOver>(0);
		GameOverFlag = true;
	}

	//ポ〜〜〜〜〜〜ズッ！！！
	if (mode == GameData::Battle2D_Mode || mode == GameData::Battle3D_Mode) {
		if (Pad(0).IsPress(enButtonSelect)) {
			NewGO<GamePause>(0);
		}
	}

}
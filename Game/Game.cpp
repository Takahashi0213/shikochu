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
	//色々消す
	DeleteGOs("GameData");
	DeleteGOs("Bug");
	DeleteGOs("Enemy");
	DeleteGOs("Gamecamera");
	DeleteGOs("Status");
	DeleteGOs("item");
	DeleteGOs("Sky");

	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;

}
bool Game::Start()
{
	//EnableSpecialLigRange();
	DisableSpecialLigRange();
	NewGO<GameData>(0,"GameData");
	NewGO<Player>(0,"Bug");
	
	m_level.Init(L"level/level_01.tkl", [&](LevelObjectData& objData) {
		if (objData.EqualObjectName(L"bunbo-gu0")) {
			Bunbogu* bun = NewGO<Bunbogu>(0, "Enemy");
			bun->SetPosition(objData.position);
			bun->SetRotation(objData.rotation);
			return true;
		}
		if (objData.EqualObjectName(L"neoriku_0")) {
			Neoriku* neo = NewGO<Neoriku>(0, "neo");
			neo->SetPosition(objData.position);
			neo->SetRotation(objData.rotation);
			return true;
		}
		return false;
	});
	NewGO<GameCamera>(0,"Gamecamera");
	NewGO<Player_Status>(0, "Status");
	NewGO<EffectManager>(0, "EffectManager");
	NewGO<BackGround>(0, "BackGround");

	NewGO<StarItem>(0, "item");

	GameData * gamedata = GameData::GetInstance();
	gamedata->SetGameMode(GameData::Battle2D_Mode);

	BackGround * background = BackGround::GetInstance();
	background->StageMaker(BackGround::Stage_1);

	prefab::CSky* sky = NewGO<prefab::CSky>(0, "Sky");
	sky->SetScale({ 20000.0f, 20000.0f, 20000.0f });
	sky->SetEmissionColor({6.1f, 6.1f, 8.1f});
	LightManager().SetAmbientLight({ 100.1f,100.1f, 100.1f });

	m_directionLig = NewGO<prefab::CDirectionLight>(0);
	m_directionLig->SetColor({ 900.0f, 900.0f, 1000.0f, 1.0f });
	CVector3 ligDir = { 1, -1, 1 };
	ligDir.Normalize();
	m_directionLig->SetDirection(ligDir);
	GraphicsEngine().GetShadowMap().SetLightDirection(ligDir);
	
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
	if (Pad(0).IsPress(enButtonSelect)) {
		NewGO<Title>(0, "title");
		DeleteGO(this);
	}
}
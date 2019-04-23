#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "Player_Status.h"
#include "GameData.h"
#include "Enemy.h"
#include "Title.h"
#include "StarItem.h"
#include "EffectManager.h"

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
	NewGO<GameData>(0,"GameData");
	NewGO<Player>(0,"Bug");
	NewGO<Enemy>(0, "Enemy");
	NewGO<GameCamera>(0,"Gamecamera");
	NewGO<Player_Status>(0, "Status");
	NewGO<EffectManager>(0, "EffectManager");

	NewGO<StarItem>(0, "item");

	GameData * gamedata = GameData::GetInstance();
	gamedata->SetGameMode(GameData::Battle2D_Mode);

	prefab::CSky* sky = NewGO<prefab::CSky>(0, "Sky");
	sky->SetScale({ 2000.0f, 2000.0f, 2000.0f });
	sky->SetEmissionColor({0.1f, 0.1f, 0.1f});
	LightManager().SetAmbientLight({ 0.1f,0.1f, 0.1f });

	return true;
}

void Game::Update()
{
	if (Pad(0).IsPress(enButtonSelect)) {
		NewGO<Title>(0, "title");
		DeleteGO(this);
	}
}
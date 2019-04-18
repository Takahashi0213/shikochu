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

Game::Game()
{
}


Game::~Game()
{
	DeleteGOs("GameData");
	DeleteGOs("Bug");
	DeleteGOs("Enemy");
	DeleteGOs("Gamecamera");
	DeleteGOs("Status");
	DeleteGOs("item");
	DeleteGOs("Sky");

}
bool Game::Start()
{
	NewGO<GameData>(0,"GameData");
	NewGO<Player>(0,"Bug");
	NewGO<Enemy>(0, "Enemy");
	NewGO<GameCamera>(0,"Gamecamera");
	NewGO<Player_Status>(0, "Status");

	NewGO<StarItem>(0, "item");

	GameData * gameData = FindGO<GameData>("GameData");
	gameData->SetGameMode(GameData::Battle2D_Mode);
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
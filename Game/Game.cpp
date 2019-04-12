#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "Player_Status.h"
#include "GameData.h"
#include "Enemy.h"
#include "Title.h"

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

}
bool Game::Start()
{
	NewGO<GameData>(0,"GameData");
	NewGO<Player>(0,"Bug");
	NewGO<Enemy>(0, "Enemy");
	NewGO<GameCamera>(0,"Gamecamera");
	NewGO<Player_Status>(0, "Status");

	GameData * gameData = FindGO<GameData>("GameData");
	gameData->SetGameMode(GameData::Battle2D_Mode);

	return true;
}

void Game::Update()
{
	if (Pad(0).IsPress(enButtonSelect)) {
		NewGO<Title>(0, "title");
		DeleteGO(this);
	}
}
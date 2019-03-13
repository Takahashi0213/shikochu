#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "Player_Status.h"
#include "GameData.h"
#include "Enemy.h"

Game::Game()
{
}


Game::~Game()
{
}
bool Game::Start()
{

	NewGO<GameData>(0,"GameData");

	NewGO<Player>(0,"Bug");
	NewGO<Enemy>(0, "Enemy");
	NewGO<GameCamera>(0);
	NewGO<Player_Status>(0, "Status");

	return true;
}

void Game::Update()
{

}
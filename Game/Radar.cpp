#include "stdafx.h"
#include "Radar.h"
#include "GameData.h"

#include "Player.h"

//エネミー
#include "Bunbogu.h"
#include "Neoriku.h"
#include "shisokus.h"

Radar::Radar()
{
}


Radar::~Radar()
{
	DeleteGO(m_skinModelRender);
}

bool Radar::Start() {

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0, "pointa");
	m_skinModelRender->Init(L"modelData/pointa.cmo", nullptr, 0, enFbxUpAxisZ, 1000);
	m_skinModelRender->SetEmissionColor({ 100.0f, 100.0f, 100.0f });
	return true;
}



void Radar::Update() {

	Player * player = Player::GetInstance();
	//GameData * gamedata = GameData::GetInstance();

	//ブンボーグとの距離を計算
	QueryGOs<Bunbogu>("bun", [&](Bunbogu* bunbogu) {
		if (bunbogu->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position= player->Getm_Position();
		CVector3 enemy_position = bunbogu->Getm_Position();
		CVector3 diff = enemy_position - player_position;
		
		diff.Normalize();
		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, CQuaternion::Identity, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	//クリオネとの距離を計算
	QueryGOs<Neoriku>("neo", [&](Neoriku* neoriku) {
		if (neoriku->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = neoriku->Getm_Position();
		CVector3 diff = enemy_position - player_position;

		diff.Normalize();
		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, CQuaternion::Identity, { 0.2f, 0.2f, 0.2f });
		return true;
		});

}

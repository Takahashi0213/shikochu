#include "stdafx.h"
#include "Radar.h"
#include "GameData.h"

#include "Player.h"

//エネミー
#include "Bunbogu.h"
#include "Neoriku.h"
#include "soukabuto.h"
#include "Ekku.h"
#include "Pi_rabi.h"
#include "Fairo.h"
#include "Morikon.h"
#include "Riritto.h"
#include "Arukasya.h"

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

	//ソウカブトとの距離を計算
	QueryGOs<soukabuto>("sou", [&](soukabuto* souka) {
		if (souka->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = souka->Getm_Position();
		CVector3 diff = enemy_position - player_position;

		diff.Normalize();
		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, CQuaternion::Identity, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	//エックとの距離を計算
	QueryGOs<Ekku>("Ekku", [&](Ekku* ekku) {
		if (ekku->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = ekku->Getm_Position();
		CVector3 diff = enemy_position - player_position;

		diff.Normalize();
		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, CQuaternion::Identity, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	//ピーラビとの距離を計算
	QueryGOs<Pi_rabi>("Pi_rabi", [&](Pi_rabi* pi_rabi) {
		if (pi_rabi->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = pi_rabi->Getm_Position();
		CVector3 diff = enemy_position - player_position;

		diff.Normalize();
		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, CQuaternion::Identity, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	//ファイロとの距離を計算
	QueryGOs<Fairo>("Fairo", [&](Fairo* fairo) {
		if (fairo->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = fairo->Getm_Position();
		CVector3 diff = enemy_position - player_position;

		diff.Normalize();
		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, CQuaternion::Identity, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	//モリコンとの距離を計算
	QueryGOs<Morikon>("Morikon", [&](Morikon* morikon) {
		if (morikon->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = morikon->Getm_Position();
		CVector3 diff = enemy_position - player_position;

		diff.Normalize();
		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, CQuaternion::Identity, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	//リリットとの距離を計算
	QueryGOs<Riritto>("Riritto", [&](Riritto* riritto) {
		if (riritto->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = riritto->Getm_Position();
		CVector3 diff = enemy_position - player_position;

		diff.Normalize();
		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, CQuaternion::Identity, { 0.2f, 0.2f, 0.2f });
		return true;
		});

	//アルカシャとの距離を計算
	QueryGOs<Arukasya>("Arukasya", [&](Arukasya* arukasya) {
		if (arukasya->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 player_position = player->Getm_Position();
		CVector3 enemy_position = arukasya->Getm_Position();
		CVector3 diff = enemy_position - player_position;

		diff.Normalize();
		diff *= 40.0f;

		CVector3 pointPos = player_position + diff;

		m_skinModelRender->UpdateInstancingData(pointPos, CQuaternion::Identity, { 0.2f, 0.2f, 0.2f });
		return true;
		});


}

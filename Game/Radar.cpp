#include "stdafx.h"
#include "Radar.h"
#include "GameData.h"

#include "Player.h"

//�G�l�~�[
#include "Bunbogu.h"
#include "Neoriku.h"
#include "soukabuto.h"
#include "Ekku.h"
#include "Pi_rabi.h"
#include "Fairo.h"
#include "Morikon.h"
#include "Riritto.h"
#include "Arukasya.h"

#include "Kikochu.h"

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

	//�u���{�[�O�Ƃ̋������v�Z
	QueryGOs<Bunbogu>("bun", [&](Bunbogu* bunbogu) {
		if (bunbogu->IsActive() == false) {
			//Active����Ȃ��B
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

	//�N���I�l�Ƃ̋������v�Z
	QueryGOs<Neoriku>("neo", [&](Neoriku* neoriku) {
		if (neoriku->IsActive() == false) {
			//Active����Ȃ��B
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

	//�\�E�J�u�g�Ƃ̋������v�Z
	QueryGOs<soukabuto>("sou", [&](soukabuto* souka) {
		if (souka->IsActive() == false) {
			//Active����Ȃ��B
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

	//�G�b�N�Ƃ̋������v�Z
	QueryGOs<Ekku>("Ekku", [&](Ekku* ekku) {
		if (ekku->IsActive() == false) {
			//Active����Ȃ��B
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

	//�s�[���r�Ƃ̋������v�Z
	QueryGOs<Pi_rabi>("Pi_rabi", [&](Pi_rabi* pi_rabi) {
		if (pi_rabi->IsActive() == false) {
			//Active����Ȃ��B
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

	//�t�@�C���Ƃ̋������v�Z
	QueryGOs<Fairo>("Fairo", [&](Fairo* fairo) {
		if (fairo->IsActive() == false) {
			//Active����Ȃ��B
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

	//�����R���Ƃ̋������v�Z
	QueryGOs<Morikon>("Morikon", [&](Morikon* morikon) {
		if (morikon->IsActive() == false) {
			//Active����Ȃ��B
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

	//�����b�g�Ƃ̋������v�Z
	QueryGOs<Riritto>("Riritto", [&](Riritto* riritto) {
		if (riritto->IsActive() == false) {
			//Active����Ȃ��B
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

	//�A���J�V���Ƃ̋������v�Z
	QueryGOs<Arukasya>("Arukasya", [&](Arukasya* arukasya) {
		if (arukasya->IsActive() == false) {
			//Active����Ȃ��B
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



	//QueryGOs<Kikochu>("Kikochu", [&](Kikochu* kikochu) {
	//	if (kikochu->IsActive() == false) {
	//		//Active����Ȃ��B
	//		return true;
	//	}
	//	CVector3 player_position = player->Getm_Position();
	//	CVector3 enemy_position = kikochu->Getm_Position();
	//	CVector3 diff = enemy_position - player_position;
	//	diff.Normalize();
	//	diff *= 40.0f;
	//	CVector3 pointPos = player_position + diff;
	//	m_skinModelRender->UpdateInstancingData(pointPos, CQuaternion::Identity, { 0.2f, 0.2f, 0.2f });
	//	return true;
	//	});

}

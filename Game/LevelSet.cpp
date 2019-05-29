#include "stdafx.h"
#include "LevelSet.h"
#include "GameData.h"

//エネミー
#include "Bunbogu.h"
#include "Neoriku.h"
#include "shisokus.h"
#include "soukabuto.h"
#include "Ekku.h"
#include "Pi_rabi.h"
#include "Fairo.h"

//ギミック
#include "StarItem.h"

LevelSet* LevelSet::m_instance = nullptr;

LevelSet::LevelSet()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;
}


LevelSet::~LevelSet()
{
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

void LevelSet::LevelSetting(wchar_t LEVEL_Name[255],bool flag,int wave) {

	//Setting前の初期化
	int EnemyCount = 0;

	//セットする
	m_level.Init( LEVEL_Name , [&](LevelObjectData& objData) {

		if (objData.EqualObjectName(L"bunbo-gu0")) {
			Bunbogu* bun = NewGO<Bunbogu>(0, "bun");
			bun->SetPosition(objData.position);
			bun->SetRotation(objData.rotation);
			bun->SetActiveFlag(flag);
			bun->SetWave(wave);
			if (flag == true) {
				EnemyCount++;
			}
			return true;
		}

		if (objData.EqualObjectName(L"neoriku_0")) {
			Neoriku* neo = NewGO<Neoriku>(0, "neo");
			neo->SetPosition(objData.position);
			neo->SetRotation(objData.rotation);
			neo->SetActiveFlag(flag);
			neo->SetWave(wave);
			if (flag == true) {
				EnemyCount++;
			}		
			return true;
		}

		if (objData.EqualObjectName(L"shisokus")) {
			shisokus* shi = NewGO<shisokus>(0, "shiso");
			shi->SetPosition(objData.position);
			shi->SetRotation(objData.rotation);
			shi->SetActiveFlag(flag);
			shi->SetWave(wave);
			if (flag == true) {
				EnemyCount++;
			}		
			return true;
		}

		if (objData.EqualObjectName(L"soukabuto_0")) {
			soukabuto* sou = NewGO<soukabuto>(0, "sou");
			sou->SetPosition(objData.position);
			sou->SetRotation(objData.rotation);
			sou->SetActiveFlag(flag);
			sou->SetWave(wave);
			if (flag == true) {
				EnemyCount++;
			}		
			return true;
		}

		if (objData.EqualObjectName(L"Ekku")) {
			Ekku* ekku = NewGO<Ekku>(0, "Ekku");
			ekku->SetPosition(objData.position);
			ekku->SetRotation(objData.rotation);
			ekku->SetActiveFlag(flag);
			ekku->SetWave(wave);
			if (flag == true) {
				EnemyCount++;
			}
			return true;
		}

		if (objData.EqualObjectName(L"Rabbit_Level_1")) {
			Pi_rabi* pi_rabi = NewGO<Pi_rabi>(0, "Pi_rabi");
			pi_rabi->SetPosition(objData.position);
			pi_rabi->SetRotation(objData.rotation);
			pi_rabi->SetActiveFlag(flag);
			pi_rabi->SetWave(wave);
			if (flag == true) {
				EnemyCount++;
			}
			return true;
		}

		if (objData.EqualObjectName(L"Fairo")) {
			Fairo* fairo = NewGO<Fairo>(0, "Fairo");
			fairo->SetPosition(objData.position);
			fairo->SetRotation(objData.rotation);
			fairo->SetActiveFlag(flag);
			fairo->SetWave(wave);
			if (flag == true) {
				EnemyCount++;
			}
			return true;
		}

		/////////////////////////////////////////////////
		if (objData.EqualObjectName(L"item")) {
			StarItem* ITEM = NewGO<StarItem>(0, "Item");
			ITEM->SetPosition(objData.position);
			ITEM->SetActiveFlag(flag);
			ITEM->SetWave(wave);
			return true;
		}
		return false;
		});

	if (flag == true) {
		//敵の数をGameDataに教える
		GameData * gamedata = GameData::GetInstance();
		gamedata->EnemyCounterSet(EnemyCount);
	}

}
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
#include "Pairodorago.h"
#include "Morikon.h"
#include "Riritto.h"
#include "Arukasya.h"
#include "SS_001.h"
#include "Kikochu.h"
#include "Uminoushi.h"
#include "Akoyadokari.h"
#include "Benite.h"
#include "Nibo.h"
#include "Sekuteimu.h"
#include "Morinchu.h"
#include "Kirabi.h"
#include "Suteira.h"
#include "Idando.h"
#include "Kodan.h"
#include "Taidol.h"
#include "Suroku.h"
#include "Mimitto.h"
#include "Tizutyo.h"
#include "Kuubo.h"
#include "Toripipi.h"
#include "Teruosuka.h"
#include "Atsukaru.h"
#include "Metoporisu.h"

//ギミック
#include "StarItem.h"
#include "AppleBomb.h"

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

		if (objData.EqualObjectName(L"Benite")) {
			Benite* benite = NewGO<Benite>(0, "Benite");
			benite->SetPosition(objData.position);
			benite->SetRotation(objData.rotation);
			benite->SetActiveFlag(flag);
			benite->SetWave(wave);
			if (flag == true) {
				EnemyCount++;
			}
			return true;
		}

		if (objData.EqualObjectName(L"Nibo")) {
			Nibo* nibo = NewGO<Nibo>(0, "Nibo");
			nibo->SetPosition(objData.position);
			nibo->SetRotation(objData.rotation);
			nibo->SetActiveFlag(flag);
			nibo->SetWave(wave);
			if (flag == true) {
				EnemyCount++;
			}
			return true;
		}

		if (objData.EqualObjectName(L"Sekuteia")) {
			Sekuteimu* sekuteimu = NewGO<Sekuteimu>(0, "Sekuteimu");
			sekuteimu->SetPosition(objData.position);
			sekuteimu->SetRotation(objData.rotation);
			sekuteimu->SetActiveFlag(flag);
			sekuteimu->SetWave(wave);
			if (flag == true) {
				EnemyCount++;
			}
			return true;
		}

		if (objData.EqualObjectName(L"Suteira")) {
			Suteira* suteira = NewGO<Suteira>(0, "Suteira");
			suteira->SetPosition(objData.position);
			suteira->SetRotation(objData.rotation);
			suteira->SetActiveFlag(flag);
			suteira->SetWave(wave);
			if (flag == true) {
				EnemyCount++;
			}
			return true;
		}

		if (objData.EqualObjectName(L"kyozin")) {
			Morinchu* morinchu = NewGO<Morinchu>(0, "Morinchu");
			morinchu->SetPosition(objData.position);
			morinchu->SetRotation(objData.rotation);
			morinchu->SetActiveFlag(flag);
			morinchu->SetWave(wave);
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

		if (objData.EqualObjectName(L"DragonTerrorBringerMesh")) {
			Pairodorago* pairodorago = NewGO<Pairodorago>(0, "Pairodorago");
			pairodorago->SetPosition(objData.position);
			pairodorago->SetRotation(objData.rotation);
			pairodorago->SetActiveFlag(flag);
			pairodorago->SetWave(wave);
			if (flag == true) {
				EnemyCount++;
			}
			return true;
		}

		if (objData.EqualObjectName(L"Idando")) {
			Idando* idando = NewGO<Idando>(0, "Idando");
			idando->SetPosition(objData.position);
			idando->SetRotation(objData.rotation);
			idando->SetActiveFlag(flag);
			idando->SetWave(wave);
			if (flag == true) {
				EnemyCount++;
			}
			return true;
		}

		if (objData.EqualObjectName(L"Kodan")) {
			Kodan* kodan = NewGO<Kodan>(0, "Kodan");
			kodan->SetPosition(objData.position);
			kodan->SetRotation(objData.rotation);
			kodan->SetActiveFlag(flag);
			kodan->SetWave(wave);
			if (flag == true) {
				EnemyCount++;
			}
			return true;
		}

		if (objData.EqualObjectName(L"Taidol")) {
			Taidol* taidol = NewGO<Taidol>(0, "Taidol");
			taidol->SetPosition(objData.position);
			taidol->SetRotation(objData.rotation);
			taidol->SetActiveFlag(flag);
			taidol->SetWave(wave);
			if (flag == true) {
				EnemyCount++;
			}
			return true;
		}

		if (objData.EqualObjectName(L"Bat_Level_1")) {
			Morikon* morikon = NewGO<Morikon>(0, "Morikon");
			morikon->SetPosition(objData.position);
			morikon->SetRotation(objData.rotation);
			morikon->SetActiveFlag(flag);
			morikon->SetWave(wave);
			if (flag == true) {
				EnemyCount++;
			}
			return true;
		}

		if (objData.EqualObjectName(L"Riritto")) {
			Riritto* riritto = NewGO<Riritto>(0, "Riritto");
			riritto->SetPosition(objData.position);
			riritto->SetRotation(objData.rotation);
			riritto->SetActiveFlag(flag);
			riritto->SetWave(wave);
			if (flag == true) {
				EnemyCount++;
			}
			return true;
		}

		if (objData.EqualObjectName(L"Arukasya")) {
			Arukasya* arukasya = NewGO<Arukasya>(0, "Arukasya");
			arukasya->SetPosition(objData.position);
			arukasya->SetRotation(objData.rotation);
			arukasya->SetActiveFlag(flag);
			arukasya->SetWave(wave);
			if (flag == true) {
				EnemyCount++;
			}
			return true;
		}

		if (objData.EqualObjectName(L"SS_001")) {
			SS_001* ss_001 = NewGO<SS_001>(0, "SS_001");
			ss_001->SetPosition(objData.position);
			ss_001->SetRotation(objData.rotation);
			ss_001->SetActiveFlag(flag);
			ss_001->SetWave(wave);
			if (flag == true) {
				EnemyCount++;
			}
			return true;
		}

		if (objData.EqualObjectName(L"Kikochu")) {
			Kikochu* kikochu = NewGO<Kikochu>(0, "Kikochu");
			kikochu->SetPosition(objData.position);
			kikochu->SetRotation(objData.rotation);
			kikochu->SetActiveFlag(flag);
			kikochu->SetWave(wave);
			return true;
		}

		if (objData.EqualObjectName(L"umino")) {
			Uminoushi* uminoushi = NewGO<Uminoushi>(0, "Uminoushi");
			uminoushi->SetPosition(objData.position);
			uminoushi->SetRotation(objData.rotation);
			uminoushi->SetActiveFlag(flag);
			uminoushi->SetWave(wave);
			if (flag == true) {
				EnemyCount++;
			}
			return true;
		}

		if (objData.EqualObjectName(L"Akoyadokari")) {
			Akoyadokari* akoyadokari = NewGO<Akoyadokari>(0, "Akoyadokari");
			akoyadokari->SetPosition(objData.position);
			akoyadokari->SetRotation(objData.rotation);
			akoyadokari->SetActiveFlag(flag);
			akoyadokari->SetWave(wave);
			if (flag == true) {
				EnemyCount++;
			}
			return true;
		}

		if (objData.EqualObjectName(L"Kirabin")) {
			Kirabi* kirabi = NewGO<Kirabi>(0, "Kirabi");
			kirabi->SetPosition(objData.position);
			kirabi->SetRotation(objData.rotation);
			kirabi->SetActiveFlag(flag);
			kirabi->SetWave(wave);
			if (flag == true) {
				EnemyCount++;
			}
			return true;
		}

		if (objData.EqualObjectName(L"Suroku")) {
			Suroku* suroku = NewGO<Suroku>(0, "Suroku");
			suroku->SetPosition(objData.position);
			suroku->SetRotation(objData.rotation);
			suroku->SetActiveFlag(flag);
			suroku->SetWave(wave);
			if (flag == true) {
				EnemyCount++;
			}
			return true;
		}

		if (objData.EqualObjectName(L"Mimitto")) {
			Mimitto* mimitto = NewGO<Mimitto>(0, "Mimitto");
			mimitto->SetPosition(objData.position);
			mimitto->SetRotation(objData.rotation);
			mimitto->SetActiveFlag(flag);
			mimitto->SetWave(wave);
			if (flag == true) {
				EnemyCount++;
			}
			return true;
		}

		if (objData.EqualObjectName(L"Tizutyo")) {
			Tizutyo* tizutyo = NewGO<Tizutyo>(0, "Tizutyo");
			tizutyo->SetPosition(objData.position);
			tizutyo->SetRotation(objData.rotation);
			tizutyo->SetActiveFlag(flag);
			tizutyo->SetWave(wave);
			if (flag == true) {
				EnemyCount++;
			}
			return true;
		}
		
		if (objData.EqualObjectName(L"Kuubo")) {
			Kuubo* kuubo = NewGO<Kuubo>(0, "Kuubo");
			kuubo->SetPosition(objData.position);
			kuubo->SetRotation(objData.rotation);
			kuubo->SetActiveFlag(flag);
			kuubo->SetWave(wave);
			if (flag == true) {
				EnemyCount++;
			}
			return true;
		}

		if (objData.EqualObjectName(L"toripp")) {
			Toripipi* toripipi = NewGO<Toripipi>(0, "Toripipi");
			toripipi->SetPosition(objData.position);
			toripipi->SetRotation(objData.rotation);
			toripipi->SetActiveFlag(flag);
			toripipi->SetWave(wave);
			if (flag == true) {
				EnemyCount++;
			}
			return true;
		}

		if (objData.EqualObjectName(L"Teruosuka")) {
			Teruosuka* teruosuka = NewGO<Teruosuka>(0, "Teruosuka");
			teruosuka->SetPosition(objData.position);
			teruosuka->SetRotation(objData.rotation);
			teruosuka->SetActiveFlag(flag);
			teruosuka->SetWave(wave);
			if (flag == true) {
				EnemyCount++;
			}
			return true;
		}

		if (objData.EqualObjectName(L"Atsukaru")) {
			Atsukaru* atsukaru = NewGO<Atsukaru>(0, "Atsukaru");
			atsukaru->SetPosition(objData.position);
			atsukaru->SetRotation(objData.rotation);
			atsukaru->SetActiveFlag(flag);
			atsukaru->SetWave(wave);
			if (flag == true) {
				EnemyCount++;
			}
			return true;
		}

		if (objData.EqualObjectName(L"Metoporisu")) {
			Metoporisu* metoporisu = NewGO<Metoporisu>(0, "Metoporisu");
			metoporisu->SetPosition(objData.position);
			metoporisu->SetRotation(objData.rotation);
			metoporisu->SetActiveFlag(flag);
			metoporisu->SetWave(wave);
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

		////////////////////////////////////////////////

		if (objData.EqualObjectName(L"Apple")) {
			AppleBomb* appleBomb = NewGO<AppleBomb>(0, "AppleBomb");
			appleBomb->SetPosition(objData.position);
			appleBomb->SetActiveFlag(flag);
			appleBomb->SetWave(wave);
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
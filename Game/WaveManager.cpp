#include "stdafx.h"
#include "WaveManager.h"
#include "EffectManager.h"

#include "GameData.h"
#include "LevelData.h"
#include "LevelSet.h"

#include "GameResult.h"
#include "BossHPGage.h"

//エネミー
#include "Bunbogu.h"
#include "Neoriku.h"
#include "shisokus.h"
#include "soukabuto.h"
//ギミック
#include "StarItem.h"

#include "WaveEffect.h"

WaveManager* WaveManager::m_instance = nullptr;

WaveManager::WaveManager()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;
}


WaveManager::~WaveManager()
{
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

void WaveManager::Update() {

	//敵が0になったら実行される
	GameData * gamedata = GameData::GetInstance();
	int enemy = gamedata->GetEnemyCounter();
	bool flag = gamedata->GetLevelSet();
	int stage = gamedata->GetStageNo() - 1;
	int LastWave = Stage_Wave[stage];

	if (enemy == 0 && flag == true) {

		//現在Waveの敵をアクティブにする！
		gamedata->WavePlus();
		int NowWave = gamedata->GetWave();
		int Enemy = 0;

		if (NowWave == LastWave) {
			//リザルトへ移行
			gamedata->ResultFlagSet(true);
			gamedata->EnemyCounterSet(-1);
		}
		else {
			//探せ〜〜〜！！！！
			QueryGOs<Bunbogu>("bun", [&](Bunbogu* bunbogu) {
				//対象の所属Waveを取得
				int wave = bunbogu->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					Enemy++;
					bunbogu->SetActiveFlag(true);
					EffectManager * effectmanager = EffectManager::GetInstance();
					CVector3 EF_Position = bunbogu->Getm_Position();
					EF_Position.x += 50.0f;
					EF_Position.y += 50.0f;
					effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });
				}
				return true;
				});

			QueryGOs<Neoriku>("neo", [&](Neoriku* neoriku) {
				//対象の所属Waveを取得
				int wave = neoriku->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					Enemy++;
					neoriku->SetActiveFlag(true);
					EffectManager * effectmanager = EffectManager::GetInstance();
					CVector3 EF_Position = neoriku->Getm_Position();
					EF_Position.y += 50.0f;
					effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });
				}
				return true;
				});

			QueryGOs<shisokus>("shiso", [&](shisokus* Shisokus) {
				//対象の所属Waveを取得
				int wave = Shisokus->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					Enemy++;
					Shisokus->SetActiveFlag(true);
				}
				return true;
				});

			QueryGOs<soukabuto>("sou", [&](soukabuto* souka) {
				//対象の所属Waveを取得
				int wave = souka->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					Enemy++;
					souka->SetActiveFlag(true);
					EffectManager * effectmanager = EffectManager::GetInstance();
					CVector3 EF_Position = souka->Getm_Position();
					EF_Position.y += 50.0f;
					effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });
				}
				return true;
				});

			//アイテム
			QueryGOs<StarItem>("Item", [&](StarItem* staritem) {
				//対象の所属Waveを取得
				int wave = staritem->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					staritem->SetActiveFlag(true);
				}
				else if (NowWave-1 == wave) {
					staritem->DeleteItem();
				}
				return true;
				});

			//敵の数をセット
			gamedata->EnemyCounterSet(Enemy);
			//エフェクト再生
			NewGO<WaveEffect>(0);
			//もしボスバトルなら3Dへの移行を行う
			if (NowWave+1 == LastWave) {
				ss->SetVolume(0.0f);
				NewGO<BossHPGage>(0);
				int len = (int)wcslen(BossName[stage]);
				for (int z = 0; z < len + 1; z++) {
					BOSS_Name[z] = BossName[stage][z];
				}
				BossHPGage * bossHPgage = BossHPGage::GetInstance();
				bossHPgage->SetBossName(BOSS_Name);
				gamedata->SwapGameMode();
			}

		}

	}
}

//ステージの最初に実行する
void WaveManager::AllStage(int x) {

	//BGM再生
	ss = NewGO<prefab::CSoundSource>(0);
	//SE再生
	ss->Init(BGMName[x]);
	ss->SetVolume(BMG_V);
	ss->Play(true);

	LevelSet * levelset = LevelSet::GetInstance();
	GameData * gamedata = GameData::GetInstance();
	int NowWave = gamedata->GetWave();
	bool flag = false;

	//基点となる変数を設定しましょい
	//これがないとステージによって実行するWaveを切り替えられません！
	int Hoge = 0;
	int SettingCount = 0;
	//始点となる箱座標を決める
	while (SettingCount < x)
	{
		Hoge += Stage_Wave[SettingCount];

		SettingCount++;
	}

	//このステージのWave数を取得
	int y = Stage_Wave[x];
	//GameDataにメモしておく（便利なので）
	gamedata->SetMAX_WaveNo(y);

	for (int i = 0; i < y; i++) {

		if (NowWave == i) {
			flag = true;
		}
		else {
			flag = false;
		}

		int len = (int)wcslen(LevelName[Hoge]);
		for (int z = 0; z < len + 1; z++) {
			LEVEL_Name[z] = LevelName[Hoge][z];
		}

		levelset->LevelSetting(LEVEL_Name, flag, i);
		Hoge++;
	}

	gamedata->LevelSetComplete();

}

//全てを無に還す
void WaveManager::DeleteAll() {

	QueryGOs<Bunbogu>("bun", [&](Bunbogu* bunbogu) {
		bunbogu->SetDeath();
		return true;
		});

	QueryGOs<Neoriku>("neo", [&](Neoriku* neoriku) {
		neoriku->SetDeath();
		return true;
		});

	QueryGOs<shisokus>("shiso", [&](shisokus* Shisokus) {
		Shisokus->SetDeath();
		return true;
		});

	QueryGOs<soukabuto>("sou", [&](soukabuto* souka) {
		souka->SetDeath();
		return true;
		});

	QueryGOs<StarItem>("Item", [&](StarItem* staritem) {
		staritem->DeleteItem();
		return true;
		});

}
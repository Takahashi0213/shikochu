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
#include "Ekku.h"
#include "Pi_rabi.h"
#include "Fairo.h"
#include "Pairodorago.h"
#include "Morikon.h"
#include "Riritto.h"
#include "Arukasya.h"
#include "SS_001.h"

//ギミック
#include "StarItem.h"

#include "WaveEffect.h"
#include "Nerubikkuri.h"

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
			//探せ～～～！！！！
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

			QueryGOs<Ekku>("Ekku", [&](Ekku* ekku) {
				//対象の所属Waveを取得
				int wave = ekku->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					Enemy++;
					ekku->SetActiveFlag(true);
					EffectManager * effectmanager = EffectManager::GetInstance();
					CVector3 EF_Position = ekku->Getm_Position();
					EF_Position.y += 50.0f;
					effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });
				}
				return true;
				});
			
			QueryGOs<Pi_rabi>("Pi_rabi", [&](Pi_rabi* pi_rabi) {
				//対象の所属Waveを取得
				int wave = pi_rabi->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					Enemy++;
					pi_rabi->SetActiveFlag(true);
					EffectManager * effectmanager = EffectManager::GetInstance();
					CVector3 EF_Position = pi_rabi->Getm_Position();
					EF_Position.y += 50.0f;
					effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });
				}
				return true;
				});
			
			QueryGOs<Fairo>("Fairo", [&](Fairo* fairo) {
				//対象の所属Waveを取得
				int wave = fairo->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					Enemy++;
					fairo->SetActiveFlag(true);
					EffectManager * effectmanager = EffectManager::GetInstance();
					CVector3 EF_Position = fairo->Getm_Position();
					EF_Position.y += 50.0f;
					effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });
				}
				return true;
				});

			QueryGOs<Pairodorago>("Pairodorago", [&](Pairodorago* pairodorago) {
				//対象の所属Waveを取得
				int wave = pairodorago->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					Enemy++;
					pairodorago->SetActiveFlag(true);
				}
				return true;
				});

			QueryGOs<Morikon>("Morikon", [&](Morikon* morikon) {
				//対象の所属Waveを取得
				int wave = morikon->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					Enemy++;
					morikon->SetActiveFlag(true);
					EffectManager * effectmanager = EffectManager::GetInstance();
					CVector3 EF_Position = morikon->Getm_Position();
					EF_Position.y += 50.0f;
					effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });
				}
				return true;
				});

			QueryGOs<Riritto>("Riritto", [&](Riritto* riritto) {
				//対象の所属Waveを取得
				int wave = riritto->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					Enemy++;
					riritto->SetActiveFlag(true);
					EffectManager * effectmanager = EffectManager::GetInstance();
					CVector3 EF_Position = riritto->Getm_Position();
					EF_Position.y += 50.0f;
					effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });
				}
				return true;
				});

			QueryGOs<Arukasya>("Arukasya", [&](Arukasya* arukasya) {
				//対象の所属Waveを取得
				int wave = arukasya->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					Enemy++;
					arukasya->SetActiveFlag(true);
					EffectManager * effectmanager = EffectManager::GetInstance();
					CVector3 EF_Position = arukasya->Getm_Position();
					EF_Position.y += 50.0f;
					effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });
				}
				return true;
				});

			QueryGOs<SS_001>("SS_001", [&](SS_001* ss_001) {
				//対象の所属Waveを取得
				int wave = ss_001->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					Enemy++;
					ss_001->SetActiveFlag(true);
					EffectManager * effectmanager = EffectManager::GetInstance();
					CVector3 EF_Position = ss_001->Getm_Position();
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
				//ポイントライトを消す。
				GraphicsEngine().GetPostEffect().GetDithering().DisablePointLig(0.5f);
				NewGO<Nerubikkuri>(0, "びっくり");
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

	QueryGOs<Ekku>("Ekku", [&](Ekku* ekku) {
		ekku->SetDeath();
		return true;
		});

	QueryGOs<Pi_rabi>("Pi_rabi", [&](Pi_rabi* pi_rabi) {
		pi_rabi->SetDeath();
		return true;
		});

	QueryGOs<Fairo>("Fairo", [&](Fairo* fairo) {
		fairo->SetDeath();
		return true;
		});

	QueryGOs<Pairodorago>("Pairodorago", [&](Pairodorago* pairodorago) {
		pairodorago->SetDeath();
		return true;
		});

	QueryGOs<Morikon>("Morikon", [&](Morikon* morikon) {
		morikon->SetDeath();
		return true;
		});

	QueryGOs<Riritto>("Riritto", [&](Riritto* riritto) {
		riritto->SetDeath();
		return true;
		});

	QueryGOs<Arukasya>("Arukasya", [&](Arukasya* arukasya) {
		arukasya->SetDeath();
		return true;
		});

	QueryGOs<SS_001>("SS_001", [&](SS_001* ss_001) {
		ss_001->SetDeath();
		return true;
		});

	QueryGOs<StarItem>("Item", [&](StarItem* staritem) {
		staritem->DeleteItem();
		return true;
		});

	DeleteGOs("びっくり");

}
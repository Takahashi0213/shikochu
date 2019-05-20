#include "stdafx.h"
#include "WaveManager.h"
#include "GameData.h"
#include "LevelData.h"
#include "LevelSet.h"

#include "GameResult.h"
#include "BossHPGage.h"

//エネミー
#include "Bunbogu.h"
#include "Neoriku.h"
#include "shisokus.h"
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
			//探せ～～～！！！！
			QueryGOs<Bunbogu>("bun", [&](Bunbogu* bunbogu) {
				//対象の所属Waveを取得
				int wave = bunbogu->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					Enemy++;
					bunbogu->SetActiveFlag(true);
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

			//敵の数をセット
			gamedata->EnemyCounterSet(Enemy);
			//エフェクト再生
			NewGO<WaveEffect>(0);
			//もしボスバトルなら3Dへの移行を行う
			if (NowWave+1 == LastWave) {
				NewGO<BossHPGage>(0);
				BossHPGage * bossHPgage = BossHPGage::GetInstance();
				bossHPgage->SetBossName(BossName[stage]);
				gamedata->SwapGameMode();
			}

		}

	}
}

//ステージの最初に実行する
void WaveManager::AllStage(int x) {

	LevelSet * levelset = LevelSet::GetInstance();
	GameData * gamedata = GameData::GetInstance();
	int NowWave = gamedata->GetWave();
	bool flag = false;

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

		int len = (int)wcslen(LevelName[i]);
		for (int z = 0; z < len + 1; z++) {
			LEVEL_Name[z] = LevelName[i][z];
		}

		levelset->LevelSetting(LEVEL_Name, flag, i);

	}

	gamedata->LevelSetComplete();

}
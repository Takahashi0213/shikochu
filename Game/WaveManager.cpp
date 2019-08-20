#include "stdafx.h"
#include "WaveManager.h"
#include "EffectManager.h"
#include "BackGround.h"

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
#include "Neruk.h"
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
#include "Train1.h"
#include "Train2.h"

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

			QueryGOs<Benite>("Benite", [&](Benite* benite) {
				//対象の所属Waveを取得
				int wave = benite->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					Enemy++;
					benite->SetActiveFlag(true);
					EffectManager * effectmanager = EffectManager::GetInstance();
					CVector3 EF_Position = benite->Getm_Position();
					EF_Position.y += 50.0f;
					effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });
				}
				return true;
				});
			
			QueryGOs<Nibo>("Nibo", [&](Nibo* nibo) {
				//対象の所属Waveを取得
				int wave = nibo->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					Enemy++;
					nibo->SetActiveFlag(true);
					EffectManager * effectmanager = EffectManager::GetInstance();
					CVector3 EF_Position = nibo->Getm_Position();
					EF_Position.y += 50.0f;
					effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });
				}
				return true;
				});

			QueryGOs<Sekuteimu>("Sekuteimu", [&](Sekuteimu* sekuteimu) {
				//対象の所属Waveを取得
				int wave = sekuteimu->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					Enemy++;
					sekuteimu->SetActiveFlag(true);
					EffectManager * effectmanager = EffectManager::GetInstance();
					CVector3 EF_Position = sekuteimu->Getm_Position();
					EF_Position.y += 50.0f;
					effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });
				}
				return true;
				});

			QueryGOs<Morinchu>("Morinchu", [&](Morinchu* morinchu) {
				//対象の所属Waveを取得
				int wave = morinchu->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					Enemy++;
					morinchu->SetActiveFlag(true);
					EffectManager * effectmanager = EffectManager::GetInstance();
					CVector3 EF_Position = morinchu->Getm_Position();
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

			QueryGOs<Idando>("Idando", [&](Idando* idando) {
				//対象の所属Waveを取得
				int wave = idando->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					Enemy++;
					idando->SetActiveFlag(true);
					EffectManager * effectmanager = EffectManager::GetInstance();
					CVector3 EF_Position = idando->Getm_Position();
					EF_Position.y += 50.0f;
					effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });
				}
				return true;
				});

			QueryGOs<Kodan>("Kodan", [&](Kodan* kodan) {
				//対象の所属Waveを取得
				int wave = kodan->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					Enemy++;
					kodan->SetActiveFlag(true);
					EffectManager * effectmanager = EffectManager::GetInstance();
					CVector3 EF_Position = kodan->Getm_Position();
					EF_Position.y += 50.0f;
					effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });
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

			QueryGOs<Suroku>("Suroku", [&](Suroku* suroku) {
				//対象の所属Waveを取得
				int wave = suroku->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					Enemy++;
					suroku->SetActiveFlag(true);
					EffectManager * effectmanager = EffectManager::GetInstance();
					CVector3 EF_Position = suroku->Getm_Position();
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

			QueryGOs<Kikochu>("Kikochu", [&](Kikochu* kikochu) {
				//対象の所属Waveを取得
				int wave = kikochu->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					kikochu->SetActiveFlag(true);
					EffectManager * effectmanager = EffectManager::GetInstance();
					CVector3 EF_Position = kikochu->Getm_Position();
					EF_Position.y += 50.0f;
					effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });
				}
				else if (NowWave - 1 == wave) {
					kikochu->SetDeath2();
				}
				return true;
				});

			QueryGOs<Uminoushi>("Uminoushi", [&](Uminoushi* uminoushi) {
				//対象の所属Waveを取得
				int wave = uminoushi->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					Enemy++;
					uminoushi->SetActiveFlag(true);
					EffectManager * effectmanager = EffectManager::GetInstance();
					CVector3 EF_Position = uminoushi->Getm_Position();
					EF_Position.y += 50.0f;
					effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });
				}
				return true;
				});

			QueryGOs<Akoyadokari>("Akoyadokari", [&](Akoyadokari* akoyadokari) {
				//対象の所属Waveを取得
				int wave = akoyadokari->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					Enemy++;
					akoyadokari->SetActiveFlag(true);
					EffectManager * effectmanager = EffectManager::GetInstance();
					CVector3 EF_Position = akoyadokari->Getm_Position();
					EF_Position.y += 50.0f;
					effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });
				}
				return true;
				});

			QueryGOs<Kirabi>("Kirabi", [&](Kirabi* kirabi) {
				//対象の所属Waveを取得
				int wave = kirabi->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					Enemy++;
					kirabi->SetActiveFlag(true);
					EffectManager * effectmanager = EffectManager::GetInstance();
					CVector3 EF_Position = kirabi->Getm_Position();
					EF_Position.y += 50.0f;
					effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });
				}
				return true;
				});

			QueryGOs<Suteira>("Suteira", [&](Suteira* suteira) {
				//対象の所属Waveを取得
				int wave = suteira->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					Enemy++;
					suteira->SetActiveFlag(true);
					EffectManager * effectmanager = EffectManager::GetInstance();
					CVector3 EF_Position = suteira->Getm_Position();
					EF_Position.y += 50.0f;
					effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });
				}
				return true;
				});

			QueryGOs<Taidol>("Taidol", [&](Taidol* taidol) {
				//対象の所属Waveを取得
				int wave = taidol->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					Enemy++;
					taidol->SetActiveFlag(true);
					EffectManager * effectmanager = EffectManager::GetInstance();
					CVector3 EF_Position = taidol->Getm_Position();
					EF_Position.y += 50.0f;
					effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });
				}
				return true;
				});

			QueryGOs<Mimitto>("Mimitto", [&](Mimitto* mimitto) {
				//対象の所属Waveを取得
				int wave = mimitto->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					Enemy++;
					mimitto->SetActiveFlag(true);
					EffectManager * effectmanager = EffectManager::GetInstance();
					CVector3 EF_Position = mimitto->Getm_Position();
					EF_Position.y += 50.0f;
					effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });
				}
				return true;
				});

			QueryGOs<Tizutyo>("Tizutyo", [&](Tizutyo* tizutyo) {
				//対象の所属Waveを取得
				int wave = tizutyo->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					Enemy++;
					tizutyo->SetActiveFlag(true);
					EffectManager * effectmanager = EffectManager::GetInstance();
					CVector3 EF_Position = tizutyo->Getm_Position();
					EF_Position.y += 50.0f;
					effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });
				}
				return true;
				});

			QueryGOs<Kuubo>("Kuubo", [&](Kuubo* kuubo) {
				//対象の所属Waveを取得
				int wave = kuubo->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					Enemy++;
					kuubo->SetActiveFlag(true);
					EffectManager * effectmanager = EffectManager::GetInstance();
					CVector3 EF_Position = kuubo->Getm_Position();
					EF_Position.y += 50.0f;
					effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });
				}
				return true;
				});

			QueryGOs<Toripipi>("Toripipi", [&](Toripipi* toripipi) {
				//対象の所属Waveを取得
				int wave = toripipi->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					Enemy++;
					toripipi->SetActiveFlag(true);
					EffectManager * effectmanager = EffectManager::GetInstance();
					CVector3 EF_Position = toripipi->Getm_Position();
					EF_Position.y += 50.0f;
					effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });
				}
				return true;
				});

			QueryGOs<Teruosuka>("Teruosuka", [&](Teruosuka* teruosuka) {
				//対象の所属Waveを取得
				int wave = teruosuka->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					Enemy++;
					teruosuka->SetActiveFlag(true);
					EffectManager * effectmanager = EffectManager::GetInstance();
					CVector3 EF_Position = teruosuka->Getm_Position();
					EF_Position.y += 50.0f;
					effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });
				}
				return true;
				});

			QueryGOs<Atsukaru>("Atsukaru", [&](Atsukaru* atsukaru) {
				//対象の所属Waveを取得
				int wave = atsukaru->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					Enemy++;
					atsukaru->SetActiveFlag(true);
					EffectManager * effectmanager = EffectManager::GetInstance();
					CVector3 EF_Position = atsukaru->Getm_Position();
					EF_Position.y += 50.0f;
					effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });
				}
				return true;
				});

			QueryGOs<Metoporisu>("Metoporisu", [&](Metoporisu* metoporisu) {
				//対象の所属Waveを取得
				int wave = metoporisu->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					Enemy++;
					metoporisu->SetActiveFlag(true);
					EffectManager * effectmanager = EffectManager::GetInstance();
					CVector3 EF_Position = metoporisu->Getm_Position();
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

			//ギミック
			QueryGOs<AppleBomb>("AppleBomb", [&](AppleBomb* apleBomb) {
				//対象の所属Waveを取得
				int wave = apleBomb->GetWave();
				if (NowWave == wave) {
					//アクティブ化
					apleBomb->SetActiveFlag(true);
				}
				else if (NowWave - 1 == wave) {
					apleBomb->SetDeath();
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
				NewGO<BossHPGage>(0,"BossHPGage");
				int len = (int)wcslen(BossName[stage]);
				for (int z = 0; z < len + 1; z++) {
					BOSS_Name[z] = BossName[stage][z];
				}
				//もしステージ2なら当たり判定をあの世行き
				if (stage == 1) {
					BackGround * background = BackGround::GetInstance();
					background->PhysicsRelease();
				}
				//ポイントライトを消す。
				GraphicsEngine().GetPostEffect().GetDithering().DisablePointLig(0.5f);
				NewGO<Nerubikkuri>(0, "びっくり");
				BossHPGage * bossHPgage = BossHPGage::GetInstance();
				bossHPgage->SetBossName(BOSS_Name);
				gamedata->SwapGameMode();
				gamedata->SetFinalMode(true);
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
	bool HardFlag = gamedata->GetHardModeFlag();

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

		//ノーマルモードとハードモードで見る場所が違う
		if (HardFlag == false) {
			int len = (int)wcslen(LevelName[Hoge]);
			for (int z = 0; z < len + 1; z++) {
				LEVEL_Name[z] = LevelName[Hoge][z];
			}
		}
		else if (HardFlag == true) {
			int len = (int)wcslen(LevelName_Hard[Hoge]);
			for (int z = 0; z < len + 1; z++) {
				LEVEL_Name[z] = LevelName_Hard[Hoge][z];
			}

		}

		//レベル読み込み
		levelset->LevelSetting(LEVEL_Name, flag, i);
		Hoge++;
	}

	gamedata->LevelSetComplete();

}

//全てを無に還す
void WaveManager::DeleteAll() {

	ss->SetVolume(0.0f);

	QueryGOs<Bunbogu>("bun", [&](Bunbogu* bunbogu) {
		bunbogu->SetActiveFlag(true); 
		bunbogu->SetDeath2();
		return true;
		});

	QueryGOs<Neoriku>("neo", [&](Neoriku* neoriku) {
		neoriku->SetActiveFlag(true);
		neoriku->SetDeath2();
		return true;
		});

	QueryGOs<shisokus>("shiso", [&](shisokus* Shisokus) {
		Shisokus->SetActiveFlag(true);
		Shisokus->SetDeath();
		return true;
		});

	QueryGOs<Neruk>("neru", [&](Neruk* neruk) {
		neruk->SetActiveFlag(true);
		neruk->SetDeath2();
		return true;
		});

	QueryGOs<soukabuto>("sou", [&](soukabuto* souka) {
		souka->SetActiveFlag(true);
		souka->SetDeath2();
		return true;
		});

	QueryGOs<Benite>("Benite", [&](Benite* benite) {
		benite->SetActiveFlag(true);
		benite->SetDeath2();
		return true;
		});

	QueryGOs<Nibo>("Nibo", [&](Nibo* nibo) {
		nibo->SetActiveFlag(true);
		nibo->SetDeath2();
		return true;
		});

	QueryGOs<Sekuteimu>("Sekuteimu", [&](Sekuteimu* sekuteimu) {
		sekuteimu->SetActiveFlag(true);
		sekuteimu->SetDeath2();
		return true;
		});

	QueryGOs<Morinchu>("Morinchu", [&](Morinchu* morinchu) {
		morinchu->SetActiveFlag(true);
		morinchu->SetDeath();
		return true;
		});

	QueryGOs<Ekku>("Ekku", [&](Ekku* ekku) {
		ekku->SetActiveFlag(true);
		ekku->SetDeath2();
		return true;
		});

	QueryGOs<Pi_rabi>("Pi_rabi", [&](Pi_rabi* pi_rabi) {
		pi_rabi->SetActiveFlag(true);
		pi_rabi->SetDeath2();
		return true;
		});

	QueryGOs<Fairo>("Fairo", [&](Fairo* fairo) {
		fairo->SetActiveFlag(true);
		fairo->SetDeath2();
		return true;
		});

	QueryGOs<Pairodorago>("Pairodorago", [&](Pairodorago* pairodorago) {
		pairodorago->SetActiveFlag(true);
		pairodorago->SetDeath();
		return true;
		});

	QueryGOs<Morikon>("Morikon", [&](Morikon* morikon) {
		morikon->SetActiveFlag(true);
		morikon->SetDeath2();
		return true;
		});

	QueryGOs<Riritto>("Riritto", [&](Riritto* riritto) {
		riritto->SetActiveFlag(true);
		riritto->SetDeath2();
		return true;
		});

	QueryGOs<Arukasya>("Arukasya", [&](Arukasya* arukasya) {
		arukasya->SetActiveFlag(true);
		arukasya->SetDeath2();
		return true;
		});

	QueryGOs<SS_001>("SS_001", [&](SS_001* ss_001) {
		ss_001->SetActiveFlag(true);
		ss_001->SetDeath();
		return true;
		});

	QueryGOs<StarItem>("Item", [&](StarItem* staritem) {
		staritem->SetActiveFlag(true);
		staritem->DeleteItem2();
		return true;
		});
	QueryGOs<AppleBomb>("AppleBomb", [&](AppleBomb* appleBomb) {
		appleBomb->SetActiveFlag(true);
		appleBomb->SetDeath2();
		return true;
		});

	QueryGOs<Kikochu>("Kikochu", [&](Kikochu* kikochu) {
		kikochu->SetActiveFlag(true);
		kikochu->SetDeath2();
		return true;
		});

	QueryGOs<Uminoushi>("Uminoushi", [&](Uminoushi* uminoushi) {
		uminoushi->SetActiveFlag(true);
		uminoushi->SetDeath2();
		return true;
		});

	QueryGOs<Akoyadokari>("Akoyadokari", [&](Akoyadokari* akoyadokari) {
		akoyadokari->SetActiveFlag(true);
		akoyadokari->SetDeath2();
		return true;
		});
	
	QueryGOs<Kirabi>("Kirabi", [&](Kirabi* kirabi) {
		kirabi->SetActiveFlag(true);
		kirabi->SetDeath2();
		return true;
		});

	QueryGOs<Suteira>("Suteira", [&](Suteira* suteira) {
		suteira->SetActiveFlag(true);
		suteira->SetDeath2();
		return true;
		});

	QueryGOs<Idando>("Idando", [&](Idando* idando) {
		idando->SetActiveFlag(true);
		idando->SetDeath2();
		return true;
		});

	QueryGOs<Kodan>("Kodan", [&](Kodan* kodan) {
		kodan->SetActiveFlag(true);
		kodan->SetDeath2();
		return true;
		});

	QueryGOs<Taidol>("Taidol", [&](Taidol* taidol) {
		taidol->SetActiveFlag(true);
		taidol->SetDeath2();
		return true;
		});

	QueryGOs<Suroku>("Suroku", [&](Suroku* suroku) {
		suroku->SetActiveFlag(true);
		suroku->SetDeath2();
		return true;
		});

	QueryGOs<Mimitto>("Mimitto", [&](Mimitto* mimitto) {
		mimitto->SetActiveFlag(true);
		mimitto->SetDeath2();
		return true;
		});

	QueryGOs<Tizutyo>("Tizutyo", [&](Tizutyo* tizutyo) {
		tizutyo->SetActiveFlag(true);
		tizutyo->SetDeath2();
		return true;
		});

	QueryGOs<Kuubo>("Kuubo", [&](Kuubo* kuubo) {
		kuubo->SetActiveFlag(true);
		kuubo->SetDeath2();
		return true;
		});

	QueryGOs<Teruosuka>("Teruosuka", [&](Teruosuka* teruosuka) {
		teruosuka->SetActiveFlag(true);
		teruosuka->SetDeath();
		return true;
		});

	QueryGOs<Toripipi>("Toripipi", [&](Toripipi* toripipi) {
		toripipi->SetActiveFlag(true);
		toripipi->SetDeath2();
		return true;
		});

	QueryGOs<Atsukaru>("Atsukaru", [&](Atsukaru* atsukaru) {
		atsukaru->SetActiveFlag(true);
		atsukaru->SetDeath2();
		return true;
		});

	QueryGOs<Metoporisu>("Metoporisu", [&](Metoporisu* metoporisu) {
		metoporisu->SetActiveFlag(true);
		metoporisu->SetDeath2();
		return true;
		});

	QueryGOs<Train1>("Train1", [&](Train1* train1) {
		train1->SetActiveFlag(true);
		train1->DeleteNow();
		return true;
		});
	QueryGOs<Train2>("Train2", [&](Train2* train2) {
		train2->SetActiveFlag(true);
		train2->DeleteNow();
		return true;
		});

	DeleteGOs("びっくり");

}
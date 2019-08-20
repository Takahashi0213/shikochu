#include "stdafx.h"
#include "WaveManager.h"
#include "EffectManager.h"
#include "BackGround.h"

#include "GameData.h"
#include "LevelData.h"
#include "LevelSet.h"

#include "GameResult.h"
#include "BossHPGage.h"

//�G�l�~�[
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

//�M�~�b�N
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
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;
}


WaveManager::~WaveManager()
{
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
}

void WaveManager::Update() {

	//�G��0�ɂȂ�������s�����
	GameData * gamedata = GameData::GetInstance();
	int enemy = gamedata->GetEnemyCounter();
	bool flag = gamedata->GetLevelSet();
	int stage = gamedata->GetStageNo() - 1;
	int LastWave = Stage_Wave[stage];

	if (enemy == 0 && flag == true) {

		//����Wave�̓G���A�N�e�B�u�ɂ���I
		gamedata->WavePlus();
		int NowWave = gamedata->GetWave();
		int Enemy = 0;

		if (NowWave == LastWave) {
			//���U���g�ֈڍs
			gamedata->ResultFlagSet(true);
			gamedata->EnemyCounterSet(-1);
		}
		else {
			//�T���`�`�`�I�I�I�I
			QueryGOs<Bunbogu>("bun", [&](Bunbogu* bunbogu) {
				//�Ώۂ̏���Wave���擾
				int wave = bunbogu->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
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
				//�Ώۂ̏���Wave���擾
				int wave = neoriku->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
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
				//�Ώۂ̏���Wave���擾
				int wave = Shisokus->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
					Enemy++;
					Shisokus->SetActiveFlag(true);
				}
				return true;
				});

			QueryGOs<soukabuto>("sou", [&](soukabuto* souka) {
				//�Ώۂ̏���Wave���擾
				int wave = souka->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
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
				//�Ώۂ̏���Wave���擾
				int wave = benite->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
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
				//�Ώۂ̏���Wave���擾
				int wave = nibo->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
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
				//�Ώۂ̏���Wave���擾
				int wave = sekuteimu->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
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
				//�Ώۂ̏���Wave���擾
				int wave = morinchu->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
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
				//�Ώۂ̏���Wave���擾
				int wave = ekku->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
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
				//�Ώۂ̏���Wave���擾
				int wave = pi_rabi->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
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
				//�Ώۂ̏���Wave���擾
				int wave = fairo->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
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
				//�Ώۂ̏���Wave���擾
				int wave = pairodorago->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
					Enemy++;
					pairodorago->SetActiveFlag(true);
				}
				return true;
				});

			QueryGOs<Idando>("Idando", [&](Idando* idando) {
				//�Ώۂ̏���Wave���擾
				int wave = idando->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
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
				//�Ώۂ̏���Wave���擾
				int wave = kodan->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
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
				//�Ώۂ̏���Wave���擾
				int wave = morikon->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
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
				//�Ώۂ̏���Wave���擾
				int wave = riritto->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
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
				//�Ώۂ̏���Wave���擾
				int wave = arukasya->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
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
				//�Ώۂ̏���Wave���擾
				int wave = suroku->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
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
				//�Ώۂ̏���Wave���擾
				int wave = ss_001->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
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
				//�Ώۂ̏���Wave���擾
				int wave = kikochu->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
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
				//�Ώۂ̏���Wave���擾
				int wave = uminoushi->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
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
				//�Ώۂ̏���Wave���擾
				int wave = akoyadokari->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
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
				//�Ώۂ̏���Wave���擾
				int wave = kirabi->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
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
				//�Ώۂ̏���Wave���擾
				int wave = suteira->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
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
				//�Ώۂ̏���Wave���擾
				int wave = taidol->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
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
				//�Ώۂ̏���Wave���擾
				int wave = mimitto->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
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
				//�Ώۂ̏���Wave���擾
				int wave = tizutyo->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
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
				//�Ώۂ̏���Wave���擾
				int wave = kuubo->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
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
				//�Ώۂ̏���Wave���擾
				int wave = toripipi->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
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
				//�Ώۂ̏���Wave���擾
				int wave = teruosuka->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
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
				//�Ώۂ̏���Wave���擾
				int wave = atsukaru->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
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
				//�Ώۂ̏���Wave���擾
				int wave = metoporisu->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
					Enemy++;
					metoporisu->SetActiveFlag(true);
					EffectManager * effectmanager = EffectManager::GetInstance();
					CVector3 EF_Position = metoporisu->Getm_Position();
					EF_Position.y += 50.0f;
					effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });
				}
				return true;
				});

			//�A�C�e��
			QueryGOs<StarItem>("Item", [&](StarItem* staritem) {
				//�Ώۂ̏���Wave���擾
				int wave = staritem->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
					staritem->SetActiveFlag(true);
				}
				else if (NowWave-1 == wave) {
					staritem->DeleteItem();
				}
				return true;
				});

			//�M�~�b�N
			QueryGOs<AppleBomb>("AppleBomb", [&](AppleBomb* apleBomb) {
				//�Ώۂ̏���Wave���擾
				int wave = apleBomb->GetWave();
				if (NowWave == wave) {
					//�A�N�e�B�u��
					apleBomb->SetActiveFlag(true);
				}
				else if (NowWave - 1 == wave) {
					apleBomb->SetDeath();
				}
				return true;
				});

			//�G�̐����Z�b�g
			gamedata->EnemyCounterSet(Enemy);
			//�G�t�F�N�g�Đ�
			NewGO<WaveEffect>(0);
			//�����{�X�o�g���Ȃ�3D�ւ̈ڍs���s��
			if (NowWave+1 == LastWave) {
				ss->SetVolume(0.0f);
				NewGO<BossHPGage>(0,"BossHPGage");
				int len = (int)wcslen(BossName[stage]);
				for (int z = 0; z < len + 1; z++) {
					BOSS_Name[z] = BossName[stage][z];
				}
				//�����X�e�[�W2�Ȃ瓖���蔻������̐��s��
				if (stage == 1) {
					BackGround * background = BackGround::GetInstance();
					background->PhysicsRelease();
				}
				//�|�C���g���C�g�������B
				GraphicsEngine().GetPostEffect().GetDithering().DisablePointLig(0.5f);
				NewGO<Nerubikkuri>(0, "�т�����");
				BossHPGage * bossHPgage = BossHPGage::GetInstance();
				bossHPgage->SetBossName(BOSS_Name);
				gamedata->SwapGameMode();
				gamedata->SetFinalMode(true);
			}

		}

	}
}

//�X�e�[�W�̍ŏ��Ɏ��s����
void WaveManager::AllStage(int x) {

	//BGM�Đ�
	ss = NewGO<prefab::CSoundSource>(0);
	//SE�Đ�
	ss->Init(BGMName[x]);
	ss->SetVolume(BMG_V);
	ss->Play(true);

	LevelSet * levelset = LevelSet::GetInstance();
	GameData * gamedata = GameData::GetInstance();
	int NowWave = gamedata->GetWave();
	bool flag = false;
	bool HardFlag = gamedata->GetHardModeFlag();

	//��_�ƂȂ�ϐ���ݒ肵�܂��傢
	//���ꂪ�Ȃ��ƃX�e�[�W�ɂ���Ď��s����Wave��؂�ւ����܂���I
	int Hoge = 0;
	int SettingCount = 0;
	//�n�_�ƂȂ锠���W�����߂�
	while (SettingCount < x)
	{
		Hoge += Stage_Wave[SettingCount];

		SettingCount++;
	}

	//���̃X�e�[�W��Wave�����擾
	int y = Stage_Wave[x];
	//GameData�Ƀ������Ă����i�֗��Ȃ̂Łj
	gamedata->SetMAX_WaveNo(y);

	for (int i = 0; i < y; i++) {

		if (NowWave == i) {
			flag = true;
		}
		else {
			flag = false;
		}

		//�m�[�}�����[�h�ƃn�[�h���[�h�Ō���ꏊ���Ⴄ
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

		//���x���ǂݍ���
		levelset->LevelSetting(LEVEL_Name, flag, i);
		Hoge++;
	}

	gamedata->LevelSetComplete();

}

//�S�Ă𖳂Ɋ҂�
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

	DeleteGOs("�т�����");

}
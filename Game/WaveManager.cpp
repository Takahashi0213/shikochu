#include "stdafx.h"
#include "WaveManager.h"
#include "EffectManager.h"

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

//�M�~�b�N
#include "StarItem.h"

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

			//�G�̐����Z�b�g
			gamedata->EnemyCounterSet(Enemy);
			//�G�t�F�N�g�Đ�
			NewGO<WaveEffect>(0);
			//�����{�X�o�g���Ȃ�3D�ւ̈ڍs���s��
			if (NowWave+1 == LastWave) {
				ss->SetVolume(0.0f);
				NewGO<BossHPGage>(0);
				int len = (int)wcslen(BossName[stage]);
				for (int z = 0; z < len + 1; z++) {
					BOSS_Name[z] = BossName[stage][z];
				}
				NewGO<Nerubikkuri>(0, "�т�����");
				BossHPGage * bossHPgage = BossHPGage::GetInstance();
				bossHPgage->SetBossName(BOSS_Name);
				gamedata->SwapGameMode();
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

		int len = (int)wcslen(LevelName[Hoge]);
		for (int z = 0; z < len + 1; z++) {
			LEVEL_Name[z] = LevelName[Hoge][z];
		}

		levelset->LevelSetting(LEVEL_Name, flag, i);
		Hoge++;
	}

	gamedata->LevelSetComplete();

}

//�S�Ă𖳂Ɋ҂�
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

	DeleteGOs("�т�����");

}
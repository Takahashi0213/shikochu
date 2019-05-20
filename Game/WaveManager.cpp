#include "stdafx.h"
#include "WaveManager.h"
#include "GameData.h"
#include "LevelData.h"
#include "LevelSet.h"

#include "GameResult.h"

#include "Bunbogu.h"
#include "Neoriku.h"
#include "StarItem.h"

#include "WaveEffect.h"

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
				}
				return true;
				});

			//�G�̐����Z�b�g
			gamedata->EnemyCounterSet(Enemy);
			NewGO<WaveEffect>(0);

		}

	}
}

//�X�e�[�W�̍ŏ��Ɏ��s����
void WaveManager::AllStage(int x) {

	LevelSet * levelset = LevelSet::GetInstance();
	GameData * gamedata = GameData::GetInstance();
	int NowWave = gamedata->GetWave();
	bool flag = false;

	int y = Stage_Wave[x];

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
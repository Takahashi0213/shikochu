#include "stdafx.h"
#include "LevelSet.h"
#include "GameData.h"

//�G�l�~�[
#include "Bunbogu.h"
#include "Neoriku.h"
#include "shisokus.h"
//�M�~�b�N
#include "StarItem.h"

LevelSet* LevelSet::m_instance = nullptr;

LevelSet::LevelSet()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;
}


LevelSet::~LevelSet()
{
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
}

void LevelSet::LevelSetting(wchar_t LEVEL_Name[255],bool flag,int wave) {

	//Setting�O�̏�����
	int EnemyCount = 0;

	//�Z�b�g����
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
			}			return true;
		}
		if (objData.EqualObjectName(L"StarItem")) {
			StarItem* item = NewGO<StarItem>(0, "Item");
			item->SetPosition(objData.position);
			item->SetActiveFlag(flag);
			item->SetWave(wave);
			return true;
		}
		return false;
		});

	if (flag == true) {
		//�G�̐���GameData�ɋ�����
		GameData * gamedata = GameData::GetInstance();
		gamedata->EnemyCounterSet(EnemyCount);
	}

}
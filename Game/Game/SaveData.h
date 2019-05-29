#pragma once
#include "LevelData.h"
#include "ZukanData.h"

class SaveData : public IGameObject
{
	static SaveData* m_instance;

public:

	/////////////// Singleton //////////////////////////////

	SaveData::SaveData()
	{

		if (m_instance != nullptr) {
			std::abort(); //���łɃJ�������o�Ă��邽�߃N���b�V��
		}

		//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
		m_instance = this;
	}

	SaveData::~SaveData()
	{
		//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
		m_instance = nullptr;
	}

	//�C���X�^���X�̎擾
	static SaveData* SaveData::GetInstance() {
		return m_instance;
	}

	//////////////////////////////////////////////////////

	//�n�C�X�R�A��ݒ� (�ݒ�ꏊ,���l)
	void SaveData::SetHighScore(int x, int y) {
	HighScore[x] = y;
	}

	//�����ɐݒ肵���ꏊ�̃n�C�X�R�A���擾
	int SaveData::GetHighScore(int x) {
	return HighScore[x];
	}

	//�����ɐݒ肵���ꏊ�̃����X�^�[�t���O��true�ɂ���
	void SaveData::SetMonFlag(int x) {
		MonstarFlag[x] = true;
	}

	//�����ɐݒ肵���ꏊ�̃����X�^�[�t���O���擾
	bool SaveData::GetMonFlag(int x) {
		return MonstarFlag[x];
	}


	//�N���A�����X�e�[�W�𑝂₷
	void SaveData::PlusClearedStage() {
		ClearedStage++;
	}

	//�N���A�����X�e�[�W���擾
	int SaveData::GetClearedStage() {
		return ClearedStage;
	}

	//�c�@�����񐔎擾
	int SaveData::GetZanki_Upgrade() {
		return Zanki_Upgrade;
	}
	//�U�������񐔎擾
	int SaveData::GetAttack_Upgrade() {
		return Attack_Upgrade;
	}
	//���������񐔎擾
	int SaveData::GetLife_Upgrade() {
		return Life_Upgrade;
	}

	//�c�@�����񐔉��Z
	void SaveData::PlusZanki_Upgrade() {
		Zanki_Upgrade++;
	}
	//�U�������񐔉��Z
	void SaveData::PlusAttack_Upgrade() {
		Attack_Upgrade++;
	}
	//���������񐔉��Z
	void SaveData::PlusLife_Upgrade() {
		Life_Upgrade++;
	}

private:
	//�n�C�X�R�A
	int HighScore[Stage]{
		0,
		0,
	};

	//�����X�^�[�̐}�ӓo�^�ς݃t���O
	bool MonstarFlag[Monster]{
		false,
		false,
		false,
		false,
		false,
	};

	int Zanki_Upgrade = 0; //�c�@������
	int Attack_Upgrade = 0; //�U��������
	int Life_Upgrade = 0; //����������

	//�N���A�����X�e�[�W
	int ClearedStage = 0;
};


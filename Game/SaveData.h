#pragma once
#include "LevelData.h"
#include "ZukanData.h"

class SaveData 
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

	//�n�[�h�Ńn�C�X�R�A��ݒ� (�ݒ�ꏊ,���l)
	void SaveData::SetHighScore_Hard(int x, int y) {
		HighScore_Hard[x] = y;
	}

	//�����ɐݒ肵���ꏊ�̃n�[�h�Ńn�C�X�R�A���擾
	int SaveData::GetHighScore_Hard(int x) {
		return HighScore_Hard[x];
	}

	//�����ɐݒ肵���ꏊ�̃����X�^�[�t���O��true�ɂ���
	void SaveData::SetMonFlag(int x) {
		MonstarFlag[x] = true;
	}

	//�����ɐݒ肵���ꏊ�̃����X�^�[�t���O���擾
	bool SaveData::GetMonFlag(int x) {
		return MonstarFlag[x];
	}

	//�����ɐݒ肵���ꏊ�̃L�R�E�`���E�t���O��true�ɂ���
	void SaveData::SetKikoFlag(int x) {
		KikoFlag[x] = true;
	}
	//�����ɐݒ肵���ꏊ�̃L�R�E�`���E�t���O���擾
	bool SaveData::GetKikoFlag(int x) {
		return KikoFlag[x];
	}

	//�����ɐݒ肵���ꏊ�̃L�R�E�`���E�t���O �n�[�h��true�ɂ���
	void SaveData::SetKikoFlag_Hard(int x) {
		KikoFlag_Hard[x] = true;
	}

	//�����ɐݒ肵���ꏊ�̃L�R�E�`���E�t���O�i�n�[�h�j���擾
	bool SaveData::GetKikoFlag_Hard(int x) {
		return KikoFlag_Hard[x];
	}

	//�����ɐݒ肵���ꏊ�̃T�|�[�g�`���[�g���A���t���O��true�ɂ���
	void SaveData::SetSupportFlag(int x) {
		SupportFlag[x] = true;
	}
	//�����ɐݒ肵���ꏊ�̃T�|�[�g�`���[�g���A���t���O���擾
	bool SaveData::GetSupportFlag(int x) {
		return SupportFlag[x];
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

	//�����ʒu�̃X�L���擾�t���O��true�ɂ���
	void SaveData::SkillGetFlag_Set(int x) {
		SkillGetFlag[x] = true;
	}
	//�����ʒu�̃X�L���擾�t���O���擾����
	bool SaveData::SkillGetFlag_Get(int x) {
		return SkillGetFlag[x];
	}

	//���������ύX����X�L���ꏊ(false��Y�Atrue��X�j
	//���������Z�b�g����X�L��No�i-1�Ȃ疳�j
	//�X�L����ݒ肷��
	void SaveData::SkillSetting(bool YorX, int skill) {
		if (YorX == false) { //Y�{�^���ɃZ�b�g
			SkillSet[0] = skill;
		}
		else { //X�{�^���ɃZ�b�g
			SkillSet[1] = skill;
		}
	}
	//���������ύX����X�L���ꏊ(false��Y�Atrue��X�j
	//�ݒ肳��Ă���X�L��No��Ԃ�
	int SaveData::GetSkill(bool YorX) {
		if (YorX == false) { //Y�{�^��
			return SkillSet[0];
		}
		else { //X�{�^��
			return SkillSet[1];
		}
	}
	
private:
	//�n�C�X�R�A
	int HighScore[Stage]{
		0,
		0,
		0,
		0,
		0,
	};

	//�n�C�X�R�A�i�n�[�h�j
	int HighScore_Hard[Stage]{
		0,
		0,
		0,
		0,
		0,
	};

	//�L�R�E�`���E�t���O
	bool KikoFlag[Stage]{
		false,
	};

	//�L�R�E�`���E�t���O �n�[�h
	bool KikoFlag_Hard[Stage]{
		false,
	};

	//�����X�^�[�̐}�ӓo�^�ς݃t���O
	bool MonstarFlag[Monster]{
		false,
	};

	int Zanki_Upgrade = 0; //�c�@������
	int Attack_Upgrade = 0; //�U��������
	int Life_Upgrade = 0; //����������

	//�N���A�����X�e�[�W
	int ClearedStage = 0;

	//�T�|�[�g�`���[�g���A���t���O
	bool SupportFlag[4]{
		false, //�G��4�̓|������폜
		false, //��イ�����_�b�V�����g�p������폜
		false, //�{�X�Ƀ_���[�W��^������폜
		false, //�{�X��3��_���[�W��^������폜
	};

	int SkillSet[2]{//�Z�b�g���̃X�L���f�[�^�i-1�Ȃ疳���j
		0, //Y�{�^��
		-1, //X�{�^��
	};

	//�X�L������t���O
	bool SkillGetFlag[24]{
		true,
		false,
	};

};


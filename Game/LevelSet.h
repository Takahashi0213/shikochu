#pragma once

class LevelSet : public IGameObject
{
	static LevelSet* m_instance;
public:
	LevelSet();
	~LevelSet();
	void LevelSetting(wchar_t LEVEL_Name[255], bool flag, int waveNo);

	//�C���X�^���X�̎擾
	static LevelSet* LevelSet::GetInstance() {
		return m_instance;
	}

private:
	CLevel m_level;	//���x���f�[�^�B
};


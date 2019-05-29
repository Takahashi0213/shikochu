#pragma once

class LevelSet : public IGameObject
{
	static LevelSet* m_instance;
public:
	LevelSet();
	~LevelSet();
	void LevelSetting(wchar_t LEVEL_Name[255], bool flag, int waveNo);

	//インスタンスの取得
	static LevelSet* LevelSet::GetInstance() {
		return m_instance;
	}

private:
	CLevel m_level;	//レベルデータ。

};


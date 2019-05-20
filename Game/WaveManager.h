#pragma once
class WaveManager : public IGameObject
{
	static WaveManager* m_instance;
public:
	WaveManager();
	~WaveManager();
	void Update();
	void AllStage(int x);

	//インスタンスの取得
	static WaveManager* WaveManager::GetInstance() {
		return m_instance;
	}

private:
	enum {
		WAVE_1,
		WAVE_2,
		WAVE_3,
	};
	int m_currentWaveNo = WAVE_1;

	wchar_t LEVEL_Name[255] = { L"" };	//レベル名保管用

};


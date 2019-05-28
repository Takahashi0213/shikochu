#pragma once
class WaveManager : public IGameObject
{
	static WaveManager* m_instance;
public:

	WaveManager();
	~WaveManager();
	void Update();
	void AllStage(int x);
	void DeleteAll();

	//インスタンスの取得
	static WaveManager* WaveManager::GetInstance() {
		return m_instance;
	}

private:
	prefab::CSoundSource* ss;
	float BMG_V = 1.0f;

	wchar_t LEVEL_Name[255] = { L"" };	//レベル名保管用
	wchar_t BOSS_Name[128] = { L"" };	//ボス名保管用

};


#pragma once
class WaveManager : public IGameObject
{
	static WaveManager* m_instance;
public:

	WaveManager();
	~WaveManager();
	void Update();
	void AllStage(int x);

	//�C���X�^���X�̎擾
	static WaveManager* WaveManager::GetInstance() {
		return m_instance;
	}

private:

	wchar_t LEVEL_Name[255] = { L"" };	//���x�����ۊǗp
	wchar_t BOSS_Name[128] = { L"" };	//�{�X���ۊǗp

};


#pragma once
class RockGenerator : public IGameObject
{
	static RockGenerator* m_instance;
public:
	RockGenerator();
	~RockGenerator();
	bool Start();
	void Update();

	//インスタンスの取得
	static RockGenerator* RockGenerator::GetInstance() {
		return m_instance;
	}

private:

	void RockSeisei(bool Flag);

	int Timer = 0;
	int RockLimit = 0;
	int random = 0;
};


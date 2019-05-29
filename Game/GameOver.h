#pragma once
class GameOver : public IGameObject
{
	static GameOver* m_instance;
public:
	GameOver();
	~GameOver();
	bool Start();
	void Update();

	//インスタンスの取得
	static GameOver* GameOver::GetInstance() {
		return m_instance;
	}

private:
	std::vector<prefab::CSpriteRender*> m_spriteRender;
	prefab::CSpriteRender* r;

	int DeleteTimer = 0;
	bool DeleteFlag = false;
};


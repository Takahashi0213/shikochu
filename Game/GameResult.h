#pragma once
class GameResult : public IGameObject
{
	static GameResult* m_instance;
public:
	GameResult();
	~GameResult();
	bool Start();
	void Update();
private:

	std::vector<prefab::CSpriteRender*> m_spriteRender;

	int Score = 0; //結果スコア
	int Score_Count = 0; //表示用スコア

	bool OK_Flag = false; //決定キーを押すまで待ちなさい
};


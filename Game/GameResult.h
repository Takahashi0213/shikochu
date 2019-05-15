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

	int Score = 0; //���ʃX�R�A
	int Score_Count = 0; //�\���p�X�R�A

	bool OK_Flag = false; //����L�[�������܂ő҂��Ȃ���
};


#pragma once
class GameSupport : public IGameObject
{
	static GameSupport* m_instance;
public:
	GameSupport();
	~GameSupport();
	bool Start();
	void Update();

private:

	std::vector<prefab::CFontRender*> m_fontRender;
	prefab::CFontRender* f;

	wchar_t text[256];

	bool StarDashSupportFlag = false; //�����Q�[�W���}���^���ɂȂ�����true

	//�萔
	const CVector2 Def_MePos = { 0.0f,-250.0f };
	const float Me_Size = 1.0f;

};


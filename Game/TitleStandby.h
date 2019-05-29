#pragma once
class TitleStandby : public IGameObject
{
	static TitleStandby* m_instance;
public:
	TitleStandby();
	~TitleStandby();
	bool Start();
	void Update();

	//インスタンスの取得
	static TitleStandby* TitleStandby::GetInstance() {
		return m_instance;
	}

private:
	std::vector<prefab::CSpriteRender*> m_spriteRender;
	prefab::CSoundSource* ss;
	prefab::CSpriteRender* r;

	CVector4 color = { 1.0f,1.0f,1.0f,0.0f };

	int Timer = 0;
};


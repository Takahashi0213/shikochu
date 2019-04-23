#pragma once
class Title : public IGameObject
{
public:
	Title();
	~Title();
	bool Start();
	void Update();

private:

	std::vector<prefab::CSpriteRender*> m_spriteRender;

};


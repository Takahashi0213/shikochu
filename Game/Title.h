#pragma once
class Title : public IGameObject
{
	static Title* m_instance;
public:
	Title();
	~Title();
	bool Start();
	void Update();

private:

	std::vector<prefab::CSpriteRender*> m_spriteRender;

};


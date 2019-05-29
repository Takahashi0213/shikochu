#pragma once
class NakamaLight : public IGameObject
{
	static NakamaLight* m_instance;
public:
	NakamaLight();
	~NakamaLight();
	bool Start();
	void Update();
private:
};


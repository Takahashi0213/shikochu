#pragma once
class Radar: public IGameObject
{
public:
	Radar();
	~Radar();
	bool Start();
	void Update();

private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。


};


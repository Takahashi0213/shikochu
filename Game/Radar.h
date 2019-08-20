#pragma once
class Radar: public IGameObject
{
	static Radar* m_instance;
public:
	Radar();
	~Radar();
	bool Start();
	void Update();

	//インスタンスの取得
	static Radar* Radar::GetInstance() {
		return m_instance;
	}

private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。


};


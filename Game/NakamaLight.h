#pragma once
class NakamaLight : public IGameObject
{
	static NakamaLight* m_instance;
public:
	NakamaLight();
	~NakamaLight();
	bool Start();
	void Update();

	//インスタンスの取得
	static NakamaLight* NakamaLight::GetInstance() {
		return m_instance;
	}

private:
};


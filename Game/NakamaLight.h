#pragma once
class NakamaLight : public IGameObject
{
	static NakamaLight* m_instance;
public:
	NakamaLight();
	~NakamaLight();
	bool Start();
	void Update();

	//�C���X�^���X�̎擾
	static NakamaLight* NakamaLight::GetInstance() {
		return m_instance;
	}

private:
};


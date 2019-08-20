#pragma once
class Radar: public IGameObject
{
	static Radar* m_instance;
public:
	Radar();
	~Radar();
	bool Start();
	void Update();

	//�C���X�^���X�̎擾
	static Radar* Radar::GetInstance() {
		return m_instance;
	}

private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B


};


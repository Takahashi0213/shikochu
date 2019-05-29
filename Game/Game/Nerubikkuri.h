#pragma once
class Nerubikkuri : public IGameObject
{
	static Nerubikkuri* m_instance;

public:
	Nerubikkuri();
	~Nerubikkuri();
	bool Start();
	//�C���X�^���X�̎擾
	static Nerubikkuri* Nerubikkuri::GetInstance() {
		return m_instance;
	}

	void NeruDelete() {
		DeleteGO(this);
	}
	void Update();
private:
	prefab::CSpriteRender* bikkuri;

	CVector3 Position = CVector3::Zero;
	CQuaternion Rotation = CQuaternion::Identity;
	CVector3 m_scale = CVector3::One; // �g�嗦�B
};


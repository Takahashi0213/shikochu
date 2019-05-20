#pragma once
class BossHPGage : public IGameObject
{
	static BossHPGage* m_instance;
public:
	BossHPGage();
	~BossHPGage();
	bool Start();
	void Update();

	//�{�X�̖��O��ݒ�
	void SetBossName(wchar_t Name[128]) {
		int len = (int)wcslen(Name);
		for (int z = 0; z < len + 1; z++) {
			bossname[z] = Name[z];
		}
	}

	//�C���X�^���X�̎擾
	static BossHPGage* BossHPGage::GetInstance() {
		return m_instance;
	}

private:
	std::vector<prefab::CSpriteRender*> m_spriteRender;
	std::vector<prefab::CFontRender*> m_fontRender;

	prefab::CSpriteRender* r;
	prefab::CFontRender* f;

	float MulAlpha = 0.0f;
	CVector4 MulColor{ 1.0f,1.0f,1.0f,1.0f };
	CVector3 Position = CVector3::Zero;

	int Timer = 0;
	wchar_t bossname[128];
	int stage = 0;
	CVector3 BarScale = CVector3::One;
	int HogeHP = 0; //�\���pHP

	//�萔
	const float HPBarY = 326.0f; //HP�o�[�̍���
};


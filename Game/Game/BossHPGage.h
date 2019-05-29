#pragma once
class BossHPGage : public IGameObject
{
	static BossHPGage* m_instance;
public:
	BossHPGage();
	~BossHPGage();
	bool Start();
	void Update();

	//ボスの名前を設定
	void SetBossName(wchar_t Name[128]) {
		int len = (int)wcslen(Name);
		for (int z = 0; z < len + 1; z++) {
			bossname[z] = Name[z];
		}
	}

	//フェードしながら消えます
	void DeleteGage() {
		DeleteTimer = 0;
	}

	//インスタンスの取得
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
	int HogeHP = 0; //表示用HP

	bool HPMAX_Flag = false;
	float MulAlphaYobi = 0;
	bool HPMAX_FlagYobi = false;
	float HPMAX_Scale = 1.0f;

	//消去関連
	int DeleteTimer = -1;
	float DeleteMulAlpha = 1.0f;

	//定数
	const float HPBarY = 326.0f; //HPバーの高さ
	const float HPBarX = 20.0f; //HPバーのXざひょ～
	const int DeleteLimit = 180; //消去制限時間
};


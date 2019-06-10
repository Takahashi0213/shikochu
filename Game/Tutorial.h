#pragma once
class Tutorial : public IGameObject
{
	static Tutorial* m_instance;
public:
	Tutorial();
	~Tutorial();
	bool Start();
	void Update();

private:

	enum TutorialScene {
		scene1,//最初に
		scene1_Play,//移動してみる
		scene2,//寿命と敵
		scene2_Play,//敵を倒してみる
		scene3,//流星ダッシュ
		scene3_Play,//アイテムを集めて流星ダッシュを使ってみよう
		scene4,//おしまい
		END,//マジで終了
	};

	std::vector<prefab::CSpriteRender*> m_spriteRender;
	std::vector<prefab::CFontRender*> m_fontRender;
	std::vector<prefab::CSkinModelRender*> m_skinModelRender;

	TutorialScene Tutorialscene = scene1;		 //状態

	prefab::CSpriteRender* r;
	prefab::CFontRender* f;
	prefab::CSkinModelRender* e;
	prefab::CSoundSource* ss;

	int Timer = 0;
	float MulAlpha = 0.0f;
	CVector4 MulColor{ 1.0f,1.0f,1.0f,1.0f };
	prefab::CDirectionLight* m_directionLig = nullptr;
	float m_tonemapDisableTimer = 1.0f;

	int PushCount = 0; //カウント用
	wchar_t text[256];
	int A_Timer = 0;

	int YazirusiTimer = 0;
	bool YazirusiFlag = false;

	bool StarFlag = false; //スターゲージマックスフラグ
	bool GameOverFlag = false; //ゲームオーバーになってしまった…

	//定数
	const float M_PosY = 800.0f;
	const float M_PosY2 = 880.0f;
	const float M_YHosei = 30.0f;

};


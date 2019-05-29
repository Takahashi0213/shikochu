#pragma once
class Title : public IGameObject
{
	static Title* m_instance;
public:
	Title();
	~Title();
	enum Estete {
		NewGame,	//初めから
		LoadGame,	//続きから
		Exit,		//終了
	};
	enum Newmove {
		NewUp,
		Newloop,
		NewDisappear,
	};
	enum Loadmove {
		LoadDown,
		Loadloop,
		LoadUp,
	};

	enum Exitmove {
		Exitdown1,	
		Exitloop,	
		Exitdown2,		
	};


	bool Start();
	void Update();

	void GameStart();
	void GameMore();
	void GameEnd();


	void NewMove();
	void LoadMove();
	void ExitMove();

	void minimusi();
	void minimove();

private:

	std::vector<prefab::CSpriteRender*> m_spriteRender;
	prefab::CSpriteRender* r;
	prefab::CSoundSource* ss;

	CVector4 MulColor{ 1.0f,1.0f,1.0f,1.0f };

	Estete m_stete = NewGame;//状態
	Newmove m_new = NewUp;//状態
	Loadmove m_load = LoadDown;//状態
	Exitmove m_exit= Exitdown1;//状態
	//ミニ虫関連
	int timer = 0;
	CVector3 minipos = {0.0f,-70.0f,0.0f};
	bool miniflag = false;
	bool minimoveflag = false;
	int movetimer = 0;
	//共通して使用
	CVector3 musi = { 0.0f,0.0f,0.0f };
	CVector3 diff;
	CVector3 scalediff;
	const float movecount = 12;			//動く時用
	int down1timer = 0;
	int down2timer = 0;
	const float loop_1y = 100.0f;		//テクスチャの高さ固定
	const float loop_2y = 100.0f;		//テクスチャの高さ固定

	//New関連
	const float hoge1posX = 800.0f;
	const float hoge1posY = -800.0f;
	CVector3 musi1up = { -150.0f,2000.0f,0.0f };//消える座標（画面外）
	const float loop_11y = -100.0f;		//テクスチャの高さ固定
	const float loop_12y = -100.0f;		//テクスチャの高さ固定
	CVector3 misi1setscale = { 2.5f,2.5f,2.5f };
	CVector3 misi1upscale = { 3.0f,3.0f,3.0f };
	CVector3 misi1scale = { 1.0f,1.0f,1.0f };

	//Load関連
	const float hoge2posX = 200.0f;
	const float hoge2posY = 600.0f;
	CVector3 misi2setscale = { 0.0f,0.0f,0.0f };
	CVector3 misi2scale = { 1.0f,1.0f,1.0f };
	CVector3 misi2bigscale = { 3.0f,3.0f,3.0f };
	CVector3 musi2up = { 0.0f,1000.0f,0.0f };//消える座標（画面外）
	bool selectflag = false;
	//Exit関連
	const float hogeposY = 700.0f;		//初期座標（画面外）
	CVector3 musidown = { 0.0f,-700.0f,0.0f };//消える座標（画面外）
	float Feathertoumaina = 1.0f;		//透明度用
	bool Featherflag = false;
	//loop関連
	float setloop1_1x = 200.0f;
	float setloop1_2x = -800.0f;

	float setloop2_1x = 200.0f;
	float setloop2_2x = -800.0f;

	float setloop3_1x = 200.0f;
	float setloop3_2x = -800.0f;

	float BGM_V = 1.0f;
	int Timer = 0;
};


#pragma once
class OP : public IGameObject
{
	static OP* m_instance;
public:
	OP();
	~OP();
	bool Start();
	void Update();

	//インスタンスの取得
	static OP* OP::GetInstance() {
		return m_instance;
	}

private:

	void BounderSet(int x);
	void Bounder();
	//
	void UpperSet(int x);
	void Upper();
	//
	void KamisibaiSet(int x);
	void Kamisibai();

	//OPシーン
	enum op_Scene {
		Hazimari,
		Seisitu,
		sinigami,
		ganbaru,
		END,
	};

	std::vector<prefab::CSpriteRender*> m_spriteRender;
	std::vector<prefab::CFontRender*> m_fontRender;
	prefab::CSoundSource* ss;
	prefab::CSpriteRender* r;
	prefab::CFontRender* f;
	op_Scene OP_Scene = Hazimari;		 //状態

	int Timer = 0;
	CVector3 pos = CVector3::Zero;
	CVector3 scl = CVector3::One;

	//バウンダー
	int BoundSet[5]{
	{ -1 },
	{ -1 },
	{ -1 },
	{ -1 },
	{ -1 },
	};
	int BoundTimer[5]{
	{ -1 },
	{ -1 },
	{ -1 },
	{ -1 },
	{ -1 },
	};

	//アッパー
	int UppSet[5]{
	{ -1 },
	{ -1 },
	{ -1 },
	{ -1 },
	{ -1 },
	};
	int UpperTimer[5]{
	{ -1 },
	{ -1 },
	{ -1 },
	{ -1 },
	{ -1 },
	};

	float BMG_V = 0.8f;

	//紙芝居
	int KamisibaiNo = -1;
	int KamisibaiTimer = -1;

	//くるりん用
	int KuruTimer = 0;

	//実行用
	float MulAlpha = 0.0f;
	CVector4 MulColor{ 1.0f,1.0f,1.0f,1.0f };

	//定数
	const float DEF_POS = 720.0f;//デフォ用加算定数

	const float TextScale = 1.3f;

	const int Scene1_Limit = 180; //シーン1のタイムリミット
	const int Scene2_Limit = 360; //シーン2のタイムリミット
	const int Scene3_Limit = 360; //シーン3のタイムリミット
	const int Scene4_Limit = 180; //シーン4のタイムリミット
	const int Scene5_Limit = 200; //シーン5のタイムリミット


};


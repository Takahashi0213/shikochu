#pragma once
class NerukGenerator;
class Neruk : public IGameObject
{
public:
	Neruk();
	~Neruk();
	enum Estete {
		Estete_Select,
		Estete_Move,//移動
		Estete_Attack,//移動
		Estete_Death,	//死
	};
	enum EnAnimationClip {
		enAnimationClip_move, //動作
		enAnimationClip_Num,  //アニメーションクリップ
	};

	bool Start();
	void Update();

	void position1();
	void position2();
	void position3();
	void position4();
	void position5();
	void position6();


	void Movetype1();
	void Movetype2();
	void Movetype3();

	void NeruSelect();
	void NeruMove();
	void NeruAttack();
	void NeruDeath();


	//ポジションを返す関数
	CVector3 Neruk::Getm_Position() {
		return m_position;
	}
	//ステートを返す関数
	int Neruk::GetEState() {
		return m_stete;
	}
	//自分が死ぬ関数
	int Neruk::SetDeath() {
		m_stete = Estete_Death;
		return 0;
	}
	//ダメージ範囲を教える関数
	float GetDamageLength() {
		return DamageLength;
	}

	//初期化
	void Init(NerukGenerator* nerukGenerator)
	{
		m_nerukGenerator = nerukGenerator;
	}

private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = CVector3::Zero;
	CQuaternion m_rotation = CQuaternion::Identity; //回転。
	CVector3 m_scale = CVector3::One; // 拡大率。
	CAnimationClip m_animClips[enAnimationClip_Num]; //アニメーションクリップ

	Estete m_stete = Estete_Select; //状態

	CCharacterController m_charaCon; //キャラコン

	//移動関連
	int posmove = 0;
	int animove = 0;

	//pos関連
	bool moveflag = false;
	int movetimer = 0;
	CVector3 pomove;
	//position1上
	const CVector3 oldpos1 = { 0.0f,6000.0f,1800.0f };
	const CVector3 pos1 = { 0.0f, 1200.0f, 1800.0f };
	const int moveflame1 = 300;
	//position2右下
	const CVector3 oldpos2 = { 4000.0f,6000.0f,2300.0f };
	const CVector3 pos2 = { 1000.0f,500.0f,2300.0f };
	//position3左上
	const CVector3 oldpos3 = { -4000.0f,6000.0f,2300.0f };
	const CVector3 pos3 = { -1000.0f,700.0f,2300.0f };

	//position4右上
	const CVector3 oldpos4 = { 4000.0f,6000.0f,2300.0f };
	const CVector3 pos4 = { 600.0f,1200.0f,2300.0f };

	//position5左下
	const CVector3 oldpos5 = { -4000.0f,6000.0f,2300.0f };
	const CVector3 pos5 = { -800.0f,300.0f,2300.0f };

	//position6ドドド真ん中
	const CVector3 oldpos6 = { 0.0f,6000.0f,2000.0f };
	const CVector3 pos6 = { 0.0f,500.0f,2000.0f };


	//攻撃
	bool attackflag = false;
	const float attackmove = 30.0f;
	int deathtimer = 0;
	CVector3 atmove;

	//移動関連
	int waittimer = 0;
	int timer = 0;

	//movetype1
	const float up = 60.f;
	const float down = 120.f;

	//movetype2
	const float Right = 60.f;
	const float Left = 120.f;

	//movetype3
	const float Rightup = 30.f;
	const float Leftdown = 60.f;
	const float Leftup = 90.f;
	const float Rightdown = 120.f;

	//死
	const float deathMove = 420.0f;
	const float deathwait = 30.0f;
	const float deathattack = 120.f;
	CVector3 deathdiff;
	//ランダム
	int  moverandom = 0; //動く場所乱数用
	int  animesionrandom = 0; //アニメーション乱数用

	int oldmovecount = 3;

	const float DamageLength = 100.0f; //ダメメージを受けけるは範囲だだよ
	NerukGenerator* m_nerukGenerator = nullptr;

};


#pragma once
class PlayerUpgrade : public IGameObject
{
	static PlayerUpgrade* m_instance;
public:
	PlayerUpgrade();
	~PlayerUpgrade();
	bool Start();
	void Update();
private:
	
	void Setting();
	void CommandUpdate();
	void CommandJump();
	void CommandShake();
	void Transceiver(wchar_t text[256]);
	void TransceiverStandby();
	void commandTren();
	void A_ButtonUpdate();
	void KumoMove();

	void Point_keisan() { //消費ポイントを計算
		zanki_Point = 100 + (100 * zanki_X);
		attack_Point = 100 + (100 * attack_X);
		jyumyo_Point = 100 + (100 * jyumyo_X);
	}

	int CommandNow = 0;

	std::vector<prefab::CSpriteRender*> m_spriteRender;
	std::vector<prefab::CFontRender*> m_fontRender;
	prefab::CSpriteRender* r;
	prefab::CFontRender* f;
	prefab::CSoundSource* ss;

	int akariTimer = 0;
	int startTimer = 0;

	//項目Jump
	bool jumpFlag = false;
	int jumpTimer = 0;
	
	//項目震える
	bool buruFlag = false;
	int buruTimer = 0;

	//トランシーバー
	wchar_t Message[256]; //喋る内容を保存
	bool TranFlag = false;
	int TranTimer = 0;
	int T_Timer = 0;

	//ステータス
	int point = 0; //所持ポイント
	int zanki = 0; //残機
	int attack = 0; //こうげき
	int jyumyo = 0; //寿命
	int zanki_X = 0; //残機強化回数
	int attack_X = 0; //攻撃力強化回数
	int jyumyo_X = 0; //寿命強化回数
	int zanki_Point = 0; //残機強化に必要なポイント
	int attack_Point = 0;
	int jyumyo_Point = 0;

	float DEF_Mul = 0.4f; //１番の不透明度
	float DEF_Mul2 = 0.0f; //２番の不透明度
	float Move_Hoge = 300.0f; //移動する虫

	float MulAlpha = 0.0f;
	CVector4 MulColor{ 1.0f,1.0f,1.0f,1.0f };

	//ステータスUP
	int StatusUpTimer = -1;
	float StatusUpAlpha = 1.0f;

	//Exit演出
	int E_MoveTimer = 0;
	bool E_MoveFlag = false;

	int A_Timer = 0;

	//動く蜘蛛
	int KumoTimer = 0;
	int Random = 0;
	int KumoLimit = 0;

	//さようなら
	bool DeleteFlag = false;
	int DeleteTimer = 0;

	//定数
	const float Ypos_hoge = 720.0f; //Yサイズ（便利）
	const float wakuPosDefY = 140.0f; //強化枠のポジション差
	const float wakuPosDEF_X = 40.0f; //強化枠のXポジション
	const float statusPosY = 40.0f; //強化ステータスのポジション差

	const int MAX_Upgrade = 10; //最大強化回数
	const int Zanki_Plus = 5; //1回の強化で加算される残機
	const int Attack_Plus = 20; //1回の強化で加算される攻撃
	const int Life_Plus = 5; //1回の強化で加算される残機
	const int TranStart = 180; //トランシーバーの更新が始まるタイミング
	const wchar_t Reset[1] = L"";
	const CVector2 StatusUP_DefPos = { 380.0f, 70.0f };
	const float KumoY_MAX = 380.0f; //動く蜘蛛の最大位置
	const float KumoY_MIN = 300.0f; //動く蜘蛛の最小位置
	const int KumoInterval = 60; //蜘蛛がまた動くまでの時間
};


#pragma once
class TransitionMaker : public IGameObject
{
	static TransitionMaker* m_instance;
public:

	//トランジションの種類
	enum Transition {
		Fade, //フェード
		Toziru, //閉じる
	};

	TransitionMaker();
	~TransitionMaker();
	bool Start();
	void Update();

	//トランジションを置きます
	//第一引数→トランジションの種類
	//第二引数→トランジションの実行時間
	//第三引数→トランジションが始まるまでのウェイト
	//第四引数→falseなら表示、trueなら消去される
	//注意！！表示と消去のトランジションの種類は同じじゃないとバグるよ
	void TransitionSetting(Transition tran, int frame, int wait, bool flag);

	//インスタンスの取得
	static TransitionMaker* TransitionMaker::GetInstance() {
		return m_instance;
	}

private:
	std::vector<prefab::CSpriteRender*> m_spriteRender;
	prefab::CSpriteRender* r;

	int TransitionTimer = -1; //トランジション用タイマー
	int TransitionLimit = -1; //トランジション用制限時間
	int TransitionFrame = -1; //トランジションの実行フレーム
	int TransitionWait = -1; //トランジションのウェイト
	int TransitionNo = -1; //実行中のトランジション
	bool TransitionFlag = false; //falseなら表示、trueなら消去

	//実行用
	float MulAlpha = 0.0f;
	CVector4 MulColor{ 1.0f,1.0f,1.0f,1.0f };

	//定数





	/*
	
	
￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣｣
―――――――――――――‐┬┘
　　　　　　　　 　 　   　 |
　　 ＿＿＿＿.＿＿＿＿＿    |  　.＿＿　 いらないＰＣを
　　|　 　 　 | 　 　  　|  |  　|＼＿＼　　窓から
　　|　 　 　 |  ∧＿∧　|  |  　| |.◎｜　投げ捨てろ
　　|　 　 　 |（ ´∀｀）つ| ミ | |.：｜
　　|　 　 　 |/ ⊃　 ﾉ　|  |　  ＼|.≡｜
　 　￣￣￣￣'￣￣￣￣　 　 |　　　 ￣￣
	
	*/
};


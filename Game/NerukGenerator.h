#pragma once
class NerukGenerator : public  IGameObject
{
	static NerukGenerator* m_instance;

public:
	NerukGenerator();
	~NerukGenerator();
	void Update();

	
	//インスタンスの取得
	static NerukGenerator* NerukGenerator::GetInstance() {
		return m_instance;
	}
	int GetMoveRandom();
	int GetAnimesionRandom();

private:
	//生成
	int  moverandom = 0; //動く場所乱数用
	int  animesionrandom = 0; //アニメーション乱数用
	int timer = 0;	//ネルクの生成用
	int oldmovecount = 3;
	const float newtimer = 90.0f;//生成されるまでの時間

	int timer1 = 0;	//ネルクの生成用
	int oldmovecount1 = 3;
	const float newtimer1 = 90.0f;//生成されるまでの時間
	
	bool flag = false;
	
};


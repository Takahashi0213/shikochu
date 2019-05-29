#include "stdafx.h"
#include "TransitionMaker.h"

TransitionMaker* TransitionMaker::m_instance = nullptr;

TransitionMaker::TransitionMaker()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;
}


TransitionMaker::~TransitionMaker()
{
	for (int i = 0; i < m_spriteRender.size(); i++) {
		DeleteGO(m_spriteRender[i]);
	}

	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

bool TransitionMaker::Start() {

	//0番 フェード用
	r = NewGO<prefab::CSpriteRender>(15);
	r->Init(L"sprite/Black.dds", 1280.0f, 720.0f);
	r->SetPosition({ 0.0f ,0.0f,0.0f });
	MulAlpha = 0.0f;
	MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//1番 閉じる用1
	r = NewGO<prefab::CSpriteRender>(15);
	r->Init(L"sprite/Black.dds", 1280.0f, 720.0f);
	r->SetPosition({ 0.0f ,720.0f,0.0f });
	MulAlpha = 0.0f;
	MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//2番 閉じる用2
	r = NewGO<prefab::CSpriteRender>(15);
	r->Init(L"sprite/Black.dds", 1280.0f, 720.0f);
	r->SetPosition({ 0.0f ,-720.0f,0.0f });
	MulAlpha = 0.0f;
	MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);

	return true;
}

void TransitionMaker::Update() {

	if (TransitionTimer >= 0) { //タイマーが0以上なら実行
		if (TransitionTimer >= TransitionWait) { //ウェイトなら待つ
			/////////////////この中でトランジション！！！！！！！！///////////////////
			if (TransitionFlag == false) {//表示////////////////////////////////////////////////
				if (TransitionNo == 0) {
					float hoge = 1.0f / (float)TransitionFrame;
					MulAlpha += hoge;
					MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
					m_spriteRender[0]->SetMulColor(MulColor);
				}
				else if (TransitionNo == 1) {
					float hoge = 360.0f / (float)TransitionFrame;
					CVector3 pos = m_spriteRender[1]->GetPosition();
					pos.y -= hoge;
					m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
					m_spriteRender[1]->SetPosition(pos);
					hoge = 360.0f / (float)TransitionFrame;
					pos = m_spriteRender[2]->GetPosition();
					pos.y += hoge;
					m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
					m_spriteRender[2]->SetPosition(pos);
				}
			}
			else if (TransitionFlag == true) {//消去///////////////////////////////////////////
				if (TransitionNo == 0) {
					float hoge = 1.0f / (float)TransitionFrame;
					MulAlpha -= hoge;
					MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
					m_spriteRender[0]->SetMulColor(MulColor);
				}
				else if (TransitionNo == 1) {
					float hoge = 360.0f / (float)TransitionFrame;
					CVector3 pos = m_spriteRender[1]->GetPosition();
					pos.y += hoge;
					m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
					m_spriteRender[1]->SetPosition(pos);
					hoge = 360.0f / (float)TransitionFrame;
					pos = m_spriteRender[2]->GetPosition();
					pos.y -= hoge;
					m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
					m_spriteRender[2]->SetPosition(pos);
				}

			}
			//////////////////////////////////////////////////////////////////////////
			//時間切れならおしまい
			if (TransitionTimer > TransitionLimit) {
				if (TransitionFlag == true && TransitionNo == 1) {
					m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
					m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
				}
				TransitionTimer = -2;
			}
		}
		TransitionTimer++;
	}
}

//トランジションを置きます
//第一引数→トランジションの種類
//第二引数→トランジションの実行時間
//第三引数→トランジションが始まるまでのウェイト
//第四引数→falseなら表示、trueなら消去される
//注意！！表示と消去のトランジションの種類は同じじゃないとバグるよ
void TransitionMaker::TransitionSetting(Transition tran, int frame, int wait,bool flag) {

	//設定
	TransitionNo = tran;
	TransitionTimer = 0; //タイマーを0に
	TransitionFrame = frame;
	TransitionWait = wait;
	TransitionLimit = frame + wait;
	TransitionFlag = flag;

}


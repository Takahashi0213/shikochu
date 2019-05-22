#include "stdafx.h"
#include "Neruk.h"
#include "NerukGenerator.h"

NerukGenerator* NerukGenerator::m_instance = nullptr;

NerukGenerator::NerukGenerator()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

}


NerukGenerator::~NerukGenerator()
{
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;

}

void NerukGenerator::Update() {

	timer++;
	if (timer > newtimer) {
		moverandom = rand() % 6;
		if (oldmovecount == moverandom) {
			moverandom = rand() % 6;
		}
		else {
			animesionrandom = rand() % 1; //アニメーション乱数用
			oldmovecount = moverandom;
			Neruk* neruk = NewGO<Neruk>(0, "neru");
			neruk->Init(this);
			timer = 0;
		}

	}
	timer1++;
	if (timer1 > newtimer1) {
		moverandom = rand() % 6;
		if (oldmovecount == moverandom) {
			moverandom = rand() % 6;
		}
		else {
			animesionrandom = rand() % 1; //アニメーション乱数用
			oldmovecount = moverandom;
			Neruk* neruk = NewGO<Neruk>(0, "neru");
			neruk->Init(this);
			timer1 = 0;

		}

	}
}

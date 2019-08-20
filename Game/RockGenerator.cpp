#include "stdafx.h"
#include "RockGenerator.h"
#include "Rock.h"

RockGenerator* RockGenerator::m_instance = nullptr;

RockGenerator::RockGenerator()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;
}


RockGenerator::~RockGenerator()
{
	QueryGOs<Rock>("Rock", [&](Rock* rock) {
		rock->SetActiveFlag(true);
		rock->DeleteNow();
		return true;
		});

	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

bool RockGenerator::Start() {

	int RockKazu = rand() % 4;

	for (int i = 0; i < 3 + RockKazu; i++) {
		RockSeisei(true);
	}

	return true;
}

void RockGenerator::Update() {

	if (Timer >= RockLimit) {//岩を生成する

		RockSeisei(false);

		RockLimit = rand() % 300;

		Timer = 0;
	}

	Timer++;

}

//引数がtureだと初期用ダイナミック生成
void RockGenerator::RockSeisei(bool Flag) {

	//初期Y位置をランダムに決める
	float PosY = 0.0f;
	random = rand() % 500;
	PosY = (float)random;
	random = rand() % 2;
	if (random == 1) {
		PosY = -1.0f;
	}
	PosY -= 250.0f;

	if (Flag == false) {
		Rock *rock = NewGO<Rock>(0, "Rock");
		rock->SetPosition({ -2000.0f,PosY,-800.0f });
	}
	else if (Flag == true) {
		Rock *rock = NewGO<Rock>(0, "Rock");

		float PosX = -1500.0f;
		random = rand() % 2000;
		PosX += (float)random;
		PosY += 100.0f;

		rock->SetPosition({ PosX,PosY,-800.0f });

	}

}
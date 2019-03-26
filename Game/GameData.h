#pragma once
#include "stdafx.h"

class GameData : public IGameObject
{
public:
	int GameData::GetZanki() {

		return Zanki;
	}

	int GameData::GetPoint() {

		return Point;
	}

	int GameData::GetATK() {

		return ATK;
	}

	int GameData::GetDEF_Life() {

		return DEF_Life;
	}

	int GameData::GetDEF_Zanki() {

		return DEF_Zanki;
	}

private:
	int Zanki = 50; //残機

	int Point = 0; //所持ポイント

	//以下ポイントで強化できる部分
	int ATK = 100; //基本攻撃力
	int DEF_Zanki = 50; //デフォルト残機
	int DEF_Life = 100; //デフォルト寿命
};
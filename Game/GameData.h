#pragma once
#include "stdafx.h"

class GameData : public IGameObject
{
public:
	int GetZanki();
	int GetPoint();
	int GetATK();
	int GetDEF_Zanki();
	int GetDEF_Life();

private:
	int Zanki = 50; //残機

	int Point = 0; //所持ポイント

	//以下ポイントで強化できる部分
	int ATK = 100; //基本攻撃力
	int DEF_Zanki = 50; //デフォルト残機
	int DEF_Life = 100; //デフォルト寿命
};
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
	int Zanki = 50; //�c�@

	int Point = 0; //�����|�C���g

	//�ȉ��|�C���g�ŋ����ł��镔��
	int ATK = 100; //��{�U����
	int DEF_Zanki = 50; //�f�t�H���g�c�@
	int DEF_Life = 100; //�f�t�H���g����
};
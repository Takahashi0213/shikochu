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
	int Zanki = 50; //�c�@

	int Point = 0; //�����|�C���g

	//�ȉ��|�C���g�ŋ����ł��镔��
	int ATK = 100; //��{�U����
	int DEF_Zanki = 50; //�f�t�H���g�c�@
	int DEF_Life = 100; //�f�t�H���g����
};
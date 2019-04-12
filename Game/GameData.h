#pragma once
#include "stdafx.h"

class GameData : public IGameObject
{
public:

	//�Q�[�����[�h
	enum GameMode {
		Battle2D_Mode,
		Battle3D_Mode,
	};

	//�c�@����
	void GameData::SetZanki(int x) {
		Zanki += x;
		if (Zanki < 0) {
			Zanki = 0;
		}
		if (Zanki > DEF_Zanki) {
			Zanki = DEF_Zanki;
		}
	}

	//�c�@�擾
	int GameData::GetZanki() {

		return Zanki;
	}

	//�����|�C���g�擾
	int GameData::GetPoint() {

		return Point;
	}

	//��{�U���͎擾
	int GameData::GetATK() {

		return ATK;
	}

	//��{�̗͎擾
	int GameData::GetDEF_Life() {

		return DEF_Life;
	}

	//�����c�@�擾
	int GameData::GetDEF_Zanki() {

		return DEF_Zanki;
	}

	//�Q�[�����[�h�ύX
	void GameData::SetGameMode(GameMode Mode) {
		m_stete = Mode;
	}

	//�Q�[�����[�h�擾
	int GameData::GetGameMode() {
		return m_stete;
	}

	//�����Q�[�W�擾
	int GameData::GetStar_Power() {
		return Star_Power;
	}
private:
	
	int Zanki = 50; //�c�@
	int Star_Power = 0; //�����_�b�V�������܂ł̃Q�[�W

	int Point = 0; //�����|�C���g

	GameMode m_stete = Battle2D_Mode;		 //���

	//�ȉ��|�C���g�ŋ����ł��镔��
	int ATK = 100; //��{�U����
	int DEF_Zanki = 50; //�f�t�H���g�c�@
	int DEF_Life = 100; //�f�t�H���g����
};
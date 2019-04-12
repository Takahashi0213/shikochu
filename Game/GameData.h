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

	//�����Q�[�W����
	//�w�肵���l�����Z���邩�猸���������Ƃ��͕��̐������Ă�
	void GameData::Star_PowerChange(int hoge) {
		Star_Power += hoge;
		if (Star_Power > MAXStarPower) {
			Star_Power = MAXStarPower;
		}
		if (Star_Power < 0) {
			Star_Power = 0;
		}

	}

	//�����Q�[�W�擾
	int GameData::GetStar_Power() {
		return Star_Power;
	}

	//�����Q�[�W�ő�l�擾
	int GameData::GetMAXStar_Power() {
		return MAXStarPower;
	}

	//�e�X�g���b�Z�[�W
	void GameData::TestMessage() {

		prefab::CFontRender* m_fontRender;
		m_fontRender = NewGO<prefab::CFontRender>(1);

		wchar_t text[256];
		swprintf(text, L"TEST MESSAGE");

		m_fontRender->SetText(text);
		m_fontRender->SetPosition({ 0.0f,0.0f});

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

	//�萔
	const int MAXStarPower = 100;//�����Q�[�W�̍ő�l

};
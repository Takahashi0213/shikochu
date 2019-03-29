#pragma once
#include "stdafx.h"

class GameData : public IGameObject
{
public:

	//ゲームモード
	enum GameMode {
		Battle2D_Mode,
		Battle3D_Mode,
	};

	//残機増減
	void GameData::SetZanki(int x) {
		Zanki += x;
		if (Zanki < 0) {
			Zanki = 0;
		}
		if (Zanki > DEF_Zanki) {
			Zanki = DEF_Zanki;
		}
	}

	//残機取得
	int GameData::GetZanki() {

		return Zanki;
	}

	//所持ポイント取得
	int GameData::GetPoint() {

		return Point;
	}

	//基本攻撃力取得
	int GameData::GetATK() {

		return ATK;
	}

	//基本体力取得
	int GameData::GetDEF_Life() {

		return DEF_Life;
	}

	//初期残機取得
	int GameData::GetDEF_Zanki() {

		return DEF_Zanki;
	}

	//ゲームモード変更
	int GameData::SetGameMode(GameMode Mode) {
		m_stete = Mode;
	}

	//ゲームモード取得
	int GameData::GetGameMode() {
		return m_stete;
	}

	//流星ゲージ取得
	int GameData::GetStar_Power() {
		return Star_Power;
	}
private:
	
	int Zanki = 50; //残機
	int Star_Power = 0; //流星ダッシュ発動までのゲージ

	int Point = 0; //所持ポイント

	GameMode m_stete = Battle2D_Mode;		 //状態

	//以下ポイントで強化できる部分
	int ATK = 100; //基本攻撃力
	int DEF_Zanki = 50; //デフォルト残機
	int DEF_Life = 100; //デフォルト寿命
};
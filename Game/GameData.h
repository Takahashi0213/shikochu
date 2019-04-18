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
	void GameData::SetGameMode(GameMode Mode) {
		m_stete = Mode;
	}

	//ゲームモード取得
	int GameData::GetGameMode() {
		return m_stete;
	}

	//流星ゲージ加減
	//指定した値を加算するから減少したいときは負の数を入れてね
	void GameData::Star_PowerChange(int hoge) {
		Star_Power += hoge;
		if (Star_Power > MAXStarPower) {
			Star_Power = MAXStarPower;
		}
		if (Star_Power < 0) {
			Star_Power = 0;
		}

	}

	//流星ゲージを0にする
	void GameData::StarPowerZero() {
		Star_Power = 0;
	}

	//流星ゲージ取得
	int GameData::GetStar_Power() {
		return Star_Power;
	}

	//流星ゲージ最大値取得
	int GameData::GetMAXStar_Power() {
		return MAXStarPower;
	}

	//テストメッセージ
	void GameData::TestMessage() {

		prefab::CFontRender* m_fontRender;
		m_fontRender = NewGO<prefab::CFontRender>(1);

		wchar_t text[256];
		swprintf(text, L"TEST MESSAGE");

		m_fontRender->SetText(text);
		m_fontRender->SetPosition({ 0.0f,0.0f});

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

	//定数
	const int MAXStarPower = 100;//流星ゲージの最大値

};
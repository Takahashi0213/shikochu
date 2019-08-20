#include "stdafx.h"
#include "GameData.h"
#include "SaveData.h"
#include "Player.h"

GameData* GameData::m_instance = nullptr;

void GameData::GameDataReset() {
	//現在残機をデフォルト残機に設定
	Zanki = DEF_Zanki;
	//カウント系もろもろ0にする
	Star_Power = 0;
	ItemCount = 0;
	GiriCount = 0;
	EnemyCount = 0;
	WaveNow = 0;
	WaveMAX = 0;
	GekihaEnemy = 0;
	LevelSetFlag = false;
	ResultFlag = false;
	KikoFlag = false;
	BossDamage = 0;
	BomFlag = false;
	DensyaFlag = false;
	LastDamage_StarDashFlag = false;
}

//x=0で割合を、x=1で減少値を返す
float GameData::GetLifePercent(int x) {

	Player * player = Player::GetInstance();
	int m_Life = player->GetLife();

	if (x == 0) {
		float player_percent = (float)m_Life / (float)DEF_Life;
		return player_percent;
	}
	else if (x == 1) {
		int player_Gensyou = DEF_Life - m_Life;
		return (float)player_Gensyou;
	}
	else {
		return true;
	}
}

//これが実行されたとき、ギリギリボーナスが成立する寿命ならtrue、
//そうでないならfalseを返します
bool GameData::GiriBonusKeisan() {

	float m_Life = GetLifePercent(0);

	if (m_Life <= GiriBonus_Line) {
		return true;
	}
	else {
		return false;
	}

}

//残機ボーナスの値を計算して返す関数(^^)/
int GameData::ZankiBonusKeisan() {

	float hoge = ZankiWariai();
	int Bonus = (int)(MAX_ZankiBonus * hoge);

	return Bonus;
}

//現在寿命と攻撃力からダメージを計算して返す 引数には流星ダッシュ中ならtrueを、それ以外ならfalseを入れること！！！！！！！！！
int GameData::DamageKeisan(bool dashflag) {

	SaveData * savedata = SaveData::GetInstance();
	LastDamage_StarDashFlag = false;

	float m_Life = GetLifePercent(0);
	//
	m_Life = 1.0f + ((1.0f - m_Life)*5.0f); //これが攻撃倍率

	int damage = (int)(ATK * m_Life);

	bool flag = GiriBonusKeisan();
	if (flag == true) {
		damage = (int)((float)damage * 1.5f); //ギリギリボーナス圏内ならダメージアップ
	}

	if (dashflag == true) {//流星ダッシュ中ならダメージアップ！
		LastDamage_StarDashFlag = true;
		damage *= 3;
	}

	if (savedata->GetSkill(false) == 12 || savedata->GetSkill(true) == 12) { //アタックアップ！
		damage = (int)((float)damage * 1.2f);
	}

	if (savedata->GetSkill(false) == 17 || savedata->GetSkill(true) == 17) { //カミカゼバトル
		damage *= 3;
	}

	return damage;
}

//ゲームオーバー用 もらえるポイントを取得
int GameData::GetGameOverKeisan() {
	int x = GekihaEnemy * GameOverBonus;
	x += GetGiriCountKeisan();
	x += GetItemCountKeisan();

	if (KikoFlag == true) {
		x += KikoBonus;
	}

	return x;
}

void GameData::TestMessage() {

	prefab::CFontRender* m_fontRender;
	m_fontRender = NewGO<prefab::CFontRender>(1);

	wchar_t text[256];
	swprintf(text, L"TEST MESSAGE");

	m_fontRender->SetText(text);
	m_fontRender->SetPosition({ 0.0f,0.0f });

}
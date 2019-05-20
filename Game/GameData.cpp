#include "stdafx.h"
#include "GameData.h"
#include "Player.h"

GameData* GameData::m_instance = nullptr;

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

int GameData::ZankiBonusKeisan() {

	float hoge = ZankiWariai();
	int Bonus = (int)(MAX_ZankiBonus * hoge);

	return Bonus;
}
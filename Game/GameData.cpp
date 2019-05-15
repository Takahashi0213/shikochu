#include "stdafx.h"
#include "GameData.h"
#include "Player.h"

GameData* GameData::m_instance = nullptr;

//x=0�Ŋ������Ax=1�Ō����l��Ԃ�
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

}

//���ꂪ���s���ꂽ�Ƃ��A�M���M���{�[�i�X��������������Ȃ�true�A
//�����łȂ��Ȃ�false��Ԃ��܂�
bool GameData::GiriBonusKeisan() {

	float m_Life = GetLifePercent(0);

	if (m_Life <= GiriBonus_Line) {
		return true;
	}
	else {
		return false;
	}

}
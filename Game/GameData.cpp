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
	else {
		return true;
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

//�c�@�{�[�i�X�̒l���v�Z���ĕԂ��֐�(^^)/
int GameData::ZankiBonusKeisan() {

	float hoge = ZankiWariai();
	int Bonus = (int)(MAX_ZankiBonus * hoge);

	return Bonus;
}

//���ݎ����ƍU���͂���_���[�W���v�Z���ĕԂ� �����ɂ͗����_�b�V�����Ȃ�true���A����ȊO�Ȃ�false�����邱�ƁI�I�I�I�I�I�I�I�I
int GameData::DamageKeisan(bool dashflag) {

	float m_Life = GetLifePercent(0);
	//
	m_Life = 1.0f + ((1.0f - m_Life)*5.0f); //���ꂪ�U���{��

	int damage = ATK * m_Life;

	bool flag = GiriBonusKeisan();
	if (flag == true) {
		damage = (int)((float)damage * 1.5f); //�M���M���{�[�i�X�����Ȃ�_���[�W�A�b�v
	}

	if (dashflag == true) {//�����_�b�V�����Ȃ�_���[�W�A�b�v�I
		damage *= 5;
	}

	return damage;
}
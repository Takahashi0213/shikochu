#include "stdafx.h"
#include "GameData.h"
#include "SaveData.h"
#include "Player.h"

GameData* GameData::m_instance = nullptr;

void GameData::GameDataReset() {
	//���ݎc�@���f�t�H���g�c�@�ɐݒ�
	Zanki = DEF_Zanki;
	//�J�E���g�n�������0�ɂ���
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

	SaveData * savedata = SaveData::GetInstance();
	LastDamage_StarDashFlag = false;

	float m_Life = GetLifePercent(0);
	//
	m_Life = 1.0f + ((1.0f - m_Life)*5.0f); //���ꂪ�U���{��

	int damage = (int)(ATK * m_Life);

	bool flag = GiriBonusKeisan();
	if (flag == true) {
		damage = (int)((float)damage * 1.5f); //�M���M���{�[�i�X�����Ȃ�_���[�W�A�b�v
	}

	if (dashflag == true) {//�����_�b�V�����Ȃ�_���[�W�A�b�v�I
		LastDamage_StarDashFlag = true;
		damage *= 3;
	}

	if (savedata->GetSkill(false) == 12 || savedata->GetSkill(true) == 12) { //�A�^�b�N�A�b�v�I
		damage = (int)((float)damage * 1.2f);
	}

	if (savedata->GetSkill(false) == 17 || savedata->GetSkill(true) == 17) { //�J�~�J�[�o�g��
		damage *= 3;
	}

	return damage;
}

//�Q�[���I�[�o�[�p ���炦��|�C���g���擾
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
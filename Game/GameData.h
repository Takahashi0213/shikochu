#pragma once
#include "stdafx.h"

class GameData 
{
	static GameData* m_instance;
public:

	//�Q�[�����[�h
	enum GameMode {
		Battle2D_Mode,
		Battle3D_Mode,
		BattleMode_Swap,//2D���[�h��3D���[�h����ւ���
		Result,
		GameEnd,
		GameOver,
		NotGame,
	};

	/////////////// Singleton //////////////////////////////
	
	GameData::GameData()
	{

		if (m_instance != nullptr) {
			std::abort(); //���łɃJ�������o�Ă��邽�߃N���b�V��
		}

		//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
		m_instance = this;
	}

	GameData::~GameData()
	{
		//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
		m_instance = nullptr;
	}

	//�C���X�^���X�̎擾
	static GameData* GameData::GetInstance() {
		return m_instance;
	}

	//////////////////////////////////////////////////////

	//x=0�Ŋ������Ax=1�Ō����l��Ԃ�
	float GameData::GetLifePercent(int x);
	bool GameData::GiriBonusKeisan();
	int GameData::ZankiBonusKeisan();
	int GameData::DamageKeisan(bool dashflag);
	void GameData::TestMessage();

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

	//��������{�U���͂����Z
	void GameData::PlusATK(int x) {

		ATK += x;
	}

	//��{�̗͎擾
	int GameData::GetDEF_Life() {

		return DEF_Life;
	}
	//��������{�̗͂����Z
	void GameData::PlusLife(int x) {

		DEF_Life += x;
	}

	//�����c�@�擾
	int GameData::GetDEF_Zanki() {

		return DEF_Zanki;
	}
	//�����������c�@�����Z
	void GameData::PlusDEF_Zanki(int x) {

		DEF_Zanki += x;
		if (DEF_Zanki > ZankiDEF_MAX) {
			DEF_Zanki = ZankiDEF_MAX;
		}
	}

	//�Q�[�����[�h�ύX
	void GameData::SetGameMode(GameMode Mode) {
		m_stete = Mode;
	}

	//�Q�[�����[�h�擾
	int GameData::GetGameMode() {
		return m_stete;
	}

	//�ő�c�@-���ݎc�@��Ԃ�
	int GameData::ZankiKeisan() {
		int x = DEF_Zanki - Zanki;
		return x;
	}

	//���ݎc�@/�ő�c�@�������
	float GameData::ZankiWariai() {
		float x = (float)Zanki / (float)DEF_Zanki;
		return x;
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

	//�����Q�[�W��0�ɂ���
	void GameData::StarPowerZero() {
		Star_Power = 0;
	}

	//�����Q�[�W�擾
	int GameData::GetStar_Power() {
		return Star_Power;
	}

	//�����Q�[�W�ő�l�擾
	int GameData::GetMAXStar_Power() {
		return MAXStarPower;
	}

	//���s�����2D���[�h����3D���[�h�ֈڍs�i���o���j
	void GameData::SwapGameMode() {
		SetGameMode(BattleMode_Swap);
	}

	//�A�C�e���J�E���g�i�ϐ��j��1���₷����
	//�A�C�e�����E�����Ƃ��Ɏ��s����
	void GameData::ItemCounter() {
		ItemCount++;
	}

	//�A�C�e���J�E���g�擾
	int GameData::GetItemCount() {
		return ItemCount;
	}

	//�A�C�e���J�E���g���{�[�i�X�Ƃ��Čv�Z���Ď擾
	int GameData::GetItemCountKeisan() {
		int x = ItemCount * ItemBonusHosei;
		return x;
	}

	//�M���M���{�[�i�X�̃J�E���g�i�ϐ��j��1���₷����
	//���������l�ȉ��œG��|�����Ƃ��ɌĂяo���܂�
	void GameData::GiriCounter() {
		GiriCount++;
	}

	//�M���M���{�[�i�X�擾
	int GameData::GetGiriCount() {
		return GiriCount;
	}

	//�M���M���{�[�i�X���v�Z���Ď擾
	int GameData::GetGiriCountKeisan() {
		int x = GiriCount * GiriBonusHosei;
		return x;
	}

	//�|�C���g���Z�i�����������|�C���g�ɉ��Z�����j
	void GameData::PlusPoint(int x) {

		Point += x;
	}

	//�G�l�~�[�J�E���^�[������������
	void GameData::EnemyCounterGensyou() {
		EnemyCount--;
	}
	//�������G�l�~�[�J�E���^�[�ɑ��
	void GameData::EnemyCounterSet(int x) {
		EnemyCount = x;
	}

	//�G�l�~�[�J�E���^�[�擾
	int GameData::GetEnemyCounter() {
		return EnemyCount;
	}

	//����Wave�i�ϐ��j��1���₷����
	void GameData::WavePlus() {
		WaveNow++;
	}

	//����Wave�擾
	int GameData::GetWave() {
		return WaveNow;
	}

	//���݃X�e�[�W������
	void GameData::SetStageNo(int x) {
		StageNow = x;
	}

	//���݃X�e�[�W��Ԃ�
	int GameData::GetStageNo() {
		return StageNow;
	}

	//�ő�WAVE�iBOSS�j������
	void GameData::SetMAX_WaveNo(int x) {
		WaveMAX = x;
	}

	//�ő�WAVE�iBOSS�j��Ԃ�
	int GameData::GetMAX_WaveNo() {
		return WaveMAX;
	}

	//���x���̏������ł�����Ă�
	void GameData::LevelSetComplete() {
		LevelSetFlag = true;
	}

	//���x���t���O��Ԃ�
	bool GameData::GetLevelSet() {
		return LevelSetFlag;
	}

	//���U���g�̏������ł�����Ă�
	void GameData::ResultFlagSet(bool flag) {
		ResultFlag = flag;
	}

	//���U���g�t���O��Ԃ�
	bool GameData::GetResultFlag() {
		return ResultFlag;
	}

	//�Q�[���f�[�^�����Z�b�g
	//�X�e�[�W�J�n���ɕK���Ăяo�����ƁI�I�I�I�I�I�I�I
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
		LevelSetFlag = false;
		ResultFlag = false;
	}

///////////////////////////////////////////////////////////////////

private:

	int Zanki = 50; //�c�@
	int Star_Power = 0; //�����_�b�V�������܂ł̃Q�[�W

	int Point = 0; //�����|�C���g

	int ItemCount = 0; //�E�����A�C�e�����J�E���g�����
	int GiriCount = 0; //�M���M���{�[�i�X���J�E���g

	GameMode m_stete = NotGame;		 //���

	bool LevelSetFlag = false; //���x���̏����ł��܂�����
	bool ResultFlag = false; //���U���g�ւ̑J��

	//�퓬���݂̕ϐ��u����
	int EnemyCount = 0; //�G�̐�
	int WaveNow = 0; //����Wave
	int StageNow = 1; //���݃X�e�[�W
	int WaveMAX = 0; //�ŏIWave

	//�ȉ��|�C���g�ŋ����ł��镔��
	int ATK = 100; //��{�U����
	int DEF_Zanki = 50; //�f�t�H���g�c�@
	int DEF_Life = 100; //�f�t�H���g����

	//�萔
	const int MAXStarPower = 100; //�����Q�[�W�̍ő�l
	const float GiriBonus_Line = 0.5f; //�M���M���{�[�i�X���������郉�C�� �ő��1.0f�i100%�j
	const int MAX_ZankiBonus = 10000; //�c�@�{�[�i�X�̍ő�l
	const int GiriBonusHosei = 200; //�M���M���œ|�����G�̐�*���̕ϐ����M���M���{�[�i�X�̒l
	const int ItemBonusHosei = 10; //�E�����A�C�e���̐�*���̕ϐ����A�C�e���{�[�i�X�̒l
	const int ZankiDEF_MAX = 99; //�����c�@�ő�l

};
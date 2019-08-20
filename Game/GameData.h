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
		Pause, //�|�[�Y���
		Tutorial,//�`���[�g���A����
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
	int GameData::GetGameOverKeisan();

	//�c�@����
	void GameData::SetZanki(int x) {
		Zanki += x;
		if (Zanki < 0) {
			Zanki = 0;
		}
		if (Zanki > 99) {
			Zanki = 99;
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
		if (Mode == 0) {
			FinalMode = false;
		}		
		if (Mode == 1) {
			FinalMode = true;
		}
	}

	//�ŏI���[�h�ύX
	void GameData::SetFinalMode(bool flag) {
		FinalMode = flag;
	}

	//�Q�[�����[�h�擾
	int GameData::GetGameMode() {
		return m_stete;
	}

	//�t�@�C�i�����[�h��Ԃ�
	bool GameData::GetFinalMode() {
		return FinalMode;
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

	//�n�[�h���[�h�t���O�̕ύX
	void GameData::SetHardModeFlag(bool flag) {
		HardModeFlag = flag;
	}

	//�n�[�h���[�h�t���O��Ԃ�
	bool GameData::GetHardModeFlag() {
		return HardModeFlag;
	}

	//�n�[�h�{�XHP�␳��Ԃ�
	float GameData::GetHardBossHosei() {
		return Hard_BossHosei;
	}
	//�n�[�h�X�R�A�␳��Ԃ�
	float GameData::GetHardScoreHosei() {
		return Hard_ScoreHosei;
	}

	//�L�R�E�`���E�t���O��true��
	void GameData::SetKikoFlag() {
		KikoFlag = true;
	}
	//�L�R�E�`���E�t���O��Ԃ�
	bool GameData::GetKikoFlag() {
		return KikoFlag;
	}

	//�����S�{���t���O��true��
	void GameData::SetBombFlag() {
		BomFlag = true;
	}
	//�����S�{���t���O��Ԃ�
	bool GameData::GetBombFlag() {
		return BomFlag;
	}

	//�d�ԃt���O��true��
	void GameData::SetDensyaFlag() {
		DensyaFlag = true;
	}
	//�d�ԃt���O��Ԃ�
	bool GameData::GetDensyaFlag() {
		return DensyaFlag;
	}

	//���X�g�_���[�W�X�^�[�_�b�V���t���O�i�������������O�j��Ԃ�
	bool GameData::GetLastDamage_StarDashFlag() {
		return LastDamage_StarDashFlag;
	}

	//�L�R�E�`���E�{�[�i�X��Ԃ�
	int GameData::GetKikoBonus() {
		return KikoBonus;
	}

	//�|�����G�̐���+1����
	void GameData::PlusGekihaEnemy() {
		GekihaEnemy++;
		Ruikei_GekihaEnemy++;
	}
	//�|�����G�̐���Ԃ�
	int GameData::GetGekihaEnemy() {
		return GekihaEnemy;
	}
	//�݌v�œ|�����G�̐���Ԃ�
	int GameData::GetRuikeiGekihaEnemy() {
		return Ruikei_GekihaEnemy;
	}

	//�����_�b�V���Ńg�h�����h�����񐔂�+1����
	void GameData::PlusLastStarDash() {
		LastStarDash++;
	}
	//�����_�b�V���Ńg�h�����h�����񐔂�Ԃ�
	int GameData::GetLastStarDash() {
		return LastStarDash;
	}

	//�n�[�h���[�h�N���A�񐔂�+1����
	void GameData::HardClearPlus() {
		HardClear++;
	}
	//�n�[�h���[�h�N���A�񐔂�Ԃ�
	int GameData::GetHardClear() {
		return HardClear;
	}

	//�{�X�Ƀ_���[�W�񐔂�+1����
	void GameData::PlusBossDamage() {
		BossDamage++;
	}
	//�{�X�Ƀ_���[�W�񐔂�Ԃ�
	int GameData::GetBossDamage() {
		return BossDamage;
	}

	//�L�R�E�`���E���j�񐔂�+1
	void GameData::KikoGekihaPlus() {
		KikoGekihaKazu++;
	}
	//�L�R�E�`���E���j�񐔂�Ԃ�
	short GameData::GetKikoGekiha() {
		return KikoGekihaKazu;
	}

	//�Q�[���f�[�^�����Z�b�g
	//�X�e�[�W�J�n���ɕK���Ăяo�����ƁI�I�I�I�I�I�I�I
	void GameData::GameDataReset();

///////////////////////////////////////////////////////////////////

private:

	int Zanki = 30; //�c�@
	int Star_Power = 0; //�����_�b�V�������܂ł̃Q�[�W

	int Point = 0; //�����|�C���g

	int ItemCount = 0; //�E�����A�C�e�����J�E���g�����
	int GiriCount = 0; //�M���M���{�[�i�X���J�E���g

	GameMode m_stete = NotGame;		 //���

	bool LevelSetFlag = false; //���x���̏����ł��܂�����
	bool ResultFlag = false; //���U���g�ւ̑J��
	bool FinalMode = false; //�Ō��2D�Ȃ�false 3D�Ȃ�true
	short KikoGekihaKazu = 0; //�L�R�E�`���E���j��

	//�n�[�h���[�h
	bool HardModeFlag = false; //true�Ȃ�n�[�h���[�h�I

	//�퓬���݂̕ϐ��u����
	int EnemyCount = 0; //�G�̐�
	int WaveNow = 0; //����Wave
	int StageNow = 1; //���݃X�e�[�W
	int WaveMAX = 0; //�ŏIWave
	bool KikoFlag = false; //�L�R�E�`���E���j�t���O
	int GekihaEnemy = 0; //�|�����G�̐�
	int Ruikei_GekihaEnemy = 0; //�|�����G�̐��i�݌v�j
	int BossDamage = 0; //�{�X�Ƀ_���[�W��^������
	bool BomFlag = false; //�����S�{����e�t���O
	bool DensyaFlag = false; //�d�Ԃ�瀂��ꂽ�t���O
	bool LastDamage_StarDashFlag = false; //�Ō�̃_���[�W�ŗ����_�b�V��������s�������ǂ����������N�\�������O�̕ϐ��I�I�I
	int LastStarDash = 0; //�����_�b�V���Ńg�h�����h������
	int HardClear = 0; //�n�[�h���[�h�N���A��

	//�ȉ��|�C���g�ŋ����ł��镔��
	int ATK = 100; //��{�U����
	int DEF_Zanki = 30; //�f�t�H���g�c�@
	int DEF_Life = 100; //�f�t�H���g����

	//�萔
	const int MAXStarPower = 100; //�����Q�[�W�̍ő�l
	const float GiriBonus_Line = 0.5f; //�M���M���{�[�i�X���������郉�C�� �ő��1.0f�i100%�j
	const int MAX_ZankiBonus = 10000; //�c�@�{�[�i�X�̍ő�l
	const int GiriBonusHosei = 200; //�M���M���œ|�����G�̐�*���̕ϐ����M���M���{�[�i�X�̒l
	const int ItemBonusHosei = 50; //�E�����A�C�e���̐�*���̕ϐ����A�C�e���{�[�i�X�̒l
	const int GameOverBonus = 50; //�Q�[���I�[�o�[�ɂȂ�����A���̕ϐ�*�|�����G�̐��̃|�C���g�����炦��
	const int ZankiDEF_MAX = 99; //�����c�@�ő�l
	const float Hard_BossHosei = 1.4f; //�n�[�h���[�h�Ń{�X��HP�ɂ�����␳
	const float Hard_ScoreHosei = 2.0f; //�n�[�h���[�h�ŃX�R�A�ɂ�����␳
	const int KikoBonus = 2000; //�L�R�E�`���E��|�����Ƃ��ɃX�R�A�ɉ��Z����鐔
};
#pragma once
#include "stdafx.h"

class GameData 
{
	static GameData* m_instance;
public:

	//ゲームモード
	enum GameMode {
		Battle2D_Mode,
		Battle3D_Mode,
		BattleMode_Swap,//2Dモードと3Dモード入れ替え中
		Result,
		GameEnd,
		GameOver,
		NotGame,
		Pause, //ポーズ画面
		Tutorial,//チュートリアル中
	};

	/////////////// Singleton //////////////////////////////
	
	GameData::GameData()
	{

		if (m_instance != nullptr) {
			std::abort(); //すでにカメラが出ているためクラッシュ
		}

		//このインスタンスを唯一のインスタンスとして記録する
		m_instance = this;
	}

	GameData::~GameData()
	{
		//インスタンスが破棄されたので、nullptrを代入
		m_instance = nullptr;
	}

	//インスタンスの取得
	static GameData* GameData::GetInstance() {
		return m_instance;
	}

	//////////////////////////////////////////////////////

	//x=0で割合を、x=1で減少値を返す
	float GameData::GetLifePercent(int x);
	bool GameData::GiriBonusKeisan();
	int GameData::ZankiBonusKeisan();
	int GameData::DamageKeisan(bool dashflag);
	void GameData::TestMessage();
	int GameData::GetGameOverKeisan();

	//残機増減
	void GameData::SetZanki(int x) {
		Zanki += x;
		if (Zanki < 0) {
			Zanki = 0;
		}
		if (Zanki > 99) {
			Zanki = 99;
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

	//引数分基本攻撃力を加算
	void GameData::PlusATK(int x) {

		ATK += x;
	}

	//基本体力取得
	int GameData::GetDEF_Life() {

		return DEF_Life;
	}
	//引数分基本体力を加算
	void GameData::PlusLife(int x) {

		DEF_Life += x;
	}

	//初期残機取得
	int GameData::GetDEF_Zanki() {

		return DEF_Zanki;
	}
	//引数分初期残機を加算
	void GameData::PlusDEF_Zanki(int x) {

		DEF_Zanki += x;
		if (DEF_Zanki > ZankiDEF_MAX) {
			DEF_Zanki = ZankiDEF_MAX;
		}
	}

	//ゲームモード変更
	void GameData::SetGameMode(GameMode Mode) {
		m_stete = Mode;
		if (Mode == 0) {
			FinalMode = false;
		}		
		if (Mode == 1) {
			FinalMode = true;
		}
	}

	//最終モード変更
	void GameData::SetFinalMode(bool flag) {
		FinalMode = flag;
	}

	//ゲームモード取得
	int GameData::GetGameMode() {
		return m_stete;
	}

	//ファイナルモードを返す
	bool GameData::GetFinalMode() {
		return FinalMode;
	}

	//最大残機-現在残機を返す
	int GameData::ZankiKeisan() {
		int x = DEF_Zanki - Zanki;
		return x;
	}

	//現在残機/最大残機をするよ
	float GameData::ZankiWariai() {
		float x = (float)Zanki / (float)DEF_Zanki;
		return x;
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

	//実行すると2Dモードから3Dモードへ移行（演出込）
	void GameData::SwapGameMode() {
		SetGameMode(BattleMode_Swap);
	}

	//アイテムカウント（変数）を1増やすだけ
	//アイテムを拾ったときに実行する
	void GameData::ItemCounter() {
		ItemCount++;
	}

	//アイテムカウント取得
	int GameData::GetItemCount() {
		return ItemCount;
	}

	//アイテムカウントをボーナスとして計算して取得
	int GameData::GetItemCountKeisan() {
		int x = ItemCount * ItemBonusHosei;
		return x;
	}

	//ギリギリボーナスのカウント（変数）を1増やすだけ
	//寿命が一定値以下で敵を倒したときに呼び出します
	void GameData::GiriCounter() {
		GiriCount++;
	}

	//ギリギリボーナス取得
	int GameData::GetGiriCount() {
		return GiriCount;
	}

	//ギリギリボーナスを計算して取得
	int GameData::GetGiriCountKeisan() {
		int x = GiriCount * GiriBonusHosei;
		return x;
	}

	//ポイント加算（引数を所持ポイントに加算するよ）
	void GameData::PlusPoint(int x) {

		Point += x;
	}

	//エネミーカウンターを減少させる
	void GameData::EnemyCounterGensyou() {
		EnemyCount--;
	}
	//引数をエネミーカウンターに代入
	void GameData::EnemyCounterSet(int x) {
		EnemyCount = x;
	}

	//エネミーカウンター取得
	int GameData::GetEnemyCounter() {
		return EnemyCount;
	}

	//現在Wave（変数）を1増やすだけ
	void GameData::WavePlus() {
		WaveNow++;
	}

	//現在Wave取得
	int GameData::GetWave() {
		return WaveNow;
	}

	//現在ステージを決定
	void GameData::SetStageNo(int x) {
		StageNow = x;
	}

	//現在ステージを返す
	int GameData::GetStageNo() {
		return StageNow;
	}

	//最大WAVE（BOSS）を決定
	void GameData::SetMAX_WaveNo(int x) {
		WaveMAX = x;
	}

	//最大WAVE（BOSS）を返す
	int GameData::GetMAX_WaveNo() {
		return WaveMAX;
	}

	//レベルの準備ができたら呼ぶ
	void GameData::LevelSetComplete() {
		LevelSetFlag = true;
	}

	//レベルフラグを返す
	bool GameData::GetLevelSet() {
		return LevelSetFlag;
	}

	//リザルトの準備ができたら呼ぶ
	void GameData::ResultFlagSet(bool flag) {
		ResultFlag = flag;
	}

	//リザルトフラグを返す
	bool GameData::GetResultFlag() {
		return ResultFlag;
	}

	//ハードモードフラグの変更
	void GameData::SetHardModeFlag(bool flag) {
		HardModeFlag = flag;
	}

	//ハードモードフラグを返す
	bool GameData::GetHardModeFlag() {
		return HardModeFlag;
	}

	//ハードボスHP補正を返す
	float GameData::GetHardBossHosei() {
		return Hard_BossHosei;
	}
	//ハードスコア補正を返す
	float GameData::GetHardScoreHosei() {
		return Hard_ScoreHosei;
	}

	//キコウチュウフラグをtrueに
	void GameData::SetKikoFlag() {
		KikoFlag = true;
	}
	//キコウチュウフラグを返す
	bool GameData::GetKikoFlag() {
		return KikoFlag;
	}

	//リンゴボムフラグをtrueに
	void GameData::SetBombFlag() {
		BomFlag = true;
	}
	//リンゴボムフラグを返す
	bool GameData::GetBombFlag() {
		return BomFlag;
	}

	//電車フラグをtrueに
	void GameData::SetDensyaFlag() {
		DensyaFlag = true;
	}
	//電車フラグを返す
	bool GameData::GetDensyaFlag() {
		return DensyaFlag;
	}

	//ラストダメージスターダッシュフラグ（かっこいい名前）を返す
	bool GameData::GetLastDamage_StarDashFlag() {
		return LastDamage_StarDashFlag;
	}

	//キコウチュウボーナスを返す
	int GameData::GetKikoBonus() {
		return KikoBonus;
	}

	//倒した敵の数を+1する
	void GameData::PlusGekihaEnemy() {
		GekihaEnemy++;
		Ruikei_GekihaEnemy++;
	}
	//倒した敵の数を返す
	int GameData::GetGekihaEnemy() {
		return GekihaEnemy;
	}
	//累計で倒した敵の数を返す
	int GameData::GetRuikeiGekihaEnemy() {
		return Ruikei_GekihaEnemy;
	}

	//流星ダッシュでトドメを刺した回数を+1する
	void GameData::PlusLastStarDash() {
		LastStarDash++;
	}
	//流星ダッシュでトドメを刺した回数を返す
	int GameData::GetLastStarDash() {
		return LastStarDash;
	}

	//ハードモードクリア回数を+1する
	void GameData::HardClearPlus() {
		HardClear++;
	}
	//ハードモードクリア回数を返す
	int GameData::GetHardClear() {
		return HardClear;
	}

	//ボスにダメージ回数を+1する
	void GameData::PlusBossDamage() {
		BossDamage++;
	}
	//ボスにダメージ回数を返す
	int GameData::GetBossDamage() {
		return BossDamage;
	}

	//キコウチュウ撃破回数を+1
	void GameData::KikoGekihaPlus() {
		KikoGekihaKazu++;
	}
	//キコウチュウ撃破回数を返す
	short GameData::GetKikoGekiha() {
		return KikoGekihaKazu;
	}

	//ゲームデータをリセット
	//ステージ開始時に必ず呼び出すこと！！！！！！！！
	void GameData::GameDataReset();

///////////////////////////////////////////////////////////////////

private:

	int Zanki = 30; //残機
	int Star_Power = 0; //流星ダッシュ発動までのゲージ

	int Point = 0; //所持ポイント

	int ItemCount = 0; //拾ったアイテムをカウントするよ
	int GiriCount = 0; //ギリギリボーナスをカウント

	GameMode m_stete = NotGame;		 //状態

	bool LevelSetFlag = false; //レベルの準備できましたか
	bool ResultFlag = false; //リザルトへの遷移
	bool FinalMode = false; //最後は2Dならfalse 3Dならtrue
	short KikoGekihaKazu = 0; //キコウチュウ撃破回数

	//ハードモード
	bool HardModeFlag = false; //trueならハードモード！

	//戦闘絡みの変数置き場
	int EnemyCount = 0; //敵の数
	int WaveNow = 0; //現在Wave
	int StageNow = 1; //現在ステージ
	int WaveMAX = 0; //最終Wave
	bool KikoFlag = false; //キコウチュウ撃破フラグ
	int GekihaEnemy = 0; //倒した敵の数
	int Ruikei_GekihaEnemy = 0; //倒した敵の数（累計）
	int BossDamage = 0; //ボスにダメージを与えた回数
	bool BomFlag = false; //リンゴボム被弾フラグ
	bool DensyaFlag = false; //電車に轢かれたフラグ
	bool LastDamage_StarDashFlag = false; //最後のダメージで流星ダッシュ判定を行ったかどうかを示すクソ長い名前の変数！！！
	int LastStarDash = 0; //流星ダッシュでトドメを刺した回数
	int HardClear = 0; //ハードモードクリア回数

	//以下ポイントで強化できる部分
	int ATK = 100; //基本攻撃力
	int DEF_Zanki = 30; //デフォルト残機
	int DEF_Life = 100; //デフォルト寿命

	//定数
	const int MAXStarPower = 100; //流星ゲージの最大値
	const float GiriBonus_Line = 0.5f; //ギリギリボーナスが成立するライン 最大は1.0f（100%）
	const int MAX_ZankiBonus = 10000; //残機ボーナスの最大値
	const int GiriBonusHosei = 200; //ギリギリで倒した敵の数*この変数→ギリギリボーナスの値
	const int ItemBonusHosei = 50; //拾ったアイテムの数*この変数→アイテムボーナスの値
	const int GameOverBonus = 50; //ゲームオーバーになったら、この変数*倒した敵の数のポイントがもらえる
	const int ZankiDEF_MAX = 99; //初期残機最大値
	const float Hard_BossHosei = 1.4f; //ハードモードでボスのHPにかかる補正
	const float Hard_ScoreHosei = 2.0f; //ハードモードでスコアにかかる補正
	const int KikoBonus = 2000; //キコウチュウを倒したときにスコアに加算される数
};
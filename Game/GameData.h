#pragma once
#include "stdafx.h"

class GameData : public IGameObject
{
	static GameData* m_instance;
public:

	//ゲームモード
	enum GameMode {
		Battle2D_Mode,
		Battle3D_Mode,
		BattleMode_Swap,//2Dモードと3Dモード入れ替え中
		Result,
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
	int GameData::PlusPoint(int x) {

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
	//ゲームデータをリセット
	//ステージ開始時に必ず呼び出すこと！！！！！！！！
	void GameData::GameDataReset() {
		//現在残機をデフォルト残機に設定
		Zanki = DEF_Zanki;
		//カウント系もろもろ0にする
		Star_Power = 0;
		ItemCount = 0;
		GiriCount = 0;
		EnemyCount = 0;
		WaveNow = 0;
		LevelSetFlag = false;
		ResultFlag = false;
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

///////////////////////////////////////////////////////////////////

private:

	int Zanki = 50; //残機
	int Star_Power = 0; //流星ダッシュ発動までのゲージ

	int Point = 0; //所持ポイント

	int ItemCount = 0; //拾ったアイテムをカウントするよ
	int GiriCount = 0; //ギリギリボーナスをカウント

	GameMode m_stete = Battle2D_Mode;		 //状態

	bool LevelSetFlag = false; //レベルの準備できましたか
	bool ResultFlag = false; //リザルトへの遷移

	//戦闘絡みの変数置き場
	int EnemyCount = 0; //敵の数
	int WaveNow = 0; //現在Wave
	int StageNow = 1; //現在ステージ

	//以下ポイントで強化できる部分
	int ATK = 100; //基本攻撃力
	int DEF_Zanki = 50; //デフォルト残機
	int DEF_Life = 100; //デフォルト寿命

	//定数
	const int MAXStarPower = 100; //流星ゲージの最大値
	const float GiriBonus_Line = 0.5f; //ギリギリボーナスが成立するライン 最大は1.0f（100%）
	const int MAX_ZankiBonus = 10000; //残機ボーナスの最大値
	const int GiriBonusHosei = 200; //ギリギリで倒した敵の数*この変数→ギリギリボーナスの値
	const int ItemBonusHosei = 10; //拾ったアイテムの数*この変数→アイテムボーナスの値

};
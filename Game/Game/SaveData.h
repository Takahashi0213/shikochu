#pragma once
#include "LevelData.h"
#include "ZukanData.h"

class SaveData : public IGameObject
{
	static SaveData* m_instance;

public:

	/////////////// Singleton //////////////////////////////

	SaveData::SaveData()
	{

		if (m_instance != nullptr) {
			std::abort(); //すでにカメラが出ているためクラッシュ
		}

		//このインスタンスを唯一のインスタンスとして記録する
		m_instance = this;
	}

	SaveData::~SaveData()
	{
		//インスタンスが破棄されたので、nullptrを代入
		m_instance = nullptr;
	}

	//インスタンスの取得
	static SaveData* SaveData::GetInstance() {
		return m_instance;
	}

	//////////////////////////////////////////////////////

	//ハイスコアを設定 (設定場所,数値)
	void SaveData::SetHighScore(int x, int y) {
	HighScore[x] = y;
	}

	//引数に設定した場所のハイスコアを取得
	int SaveData::GetHighScore(int x) {
	return HighScore[x];
	}

	//引数に設定した場所のモンスターフラグをtrueにする
	void SaveData::SetMonFlag(int x) {
		MonstarFlag[x] = true;
	}

	//引数に設定した場所のモンスターフラグを取得
	bool SaveData::GetMonFlag(int x) {
		return MonstarFlag[x];
	}


	//クリアしたステージを増やす
	void SaveData::PlusClearedStage() {
		ClearedStage++;
	}

	//クリアしたステージを取得
	int SaveData::GetClearedStage() {
		return ClearedStage;
	}

	//残機強化回数取得
	int SaveData::GetZanki_Upgrade() {
		return Zanki_Upgrade;
	}
	//攻撃強化回数取得
	int SaveData::GetAttack_Upgrade() {
		return Attack_Upgrade;
	}
	//寿命強化回数取得
	int SaveData::GetLife_Upgrade() {
		return Life_Upgrade;
	}

	//残機強化回数加算
	void SaveData::PlusZanki_Upgrade() {
		Zanki_Upgrade++;
	}
	//攻撃強化回数加算
	void SaveData::PlusAttack_Upgrade() {
		Attack_Upgrade++;
	}
	//寿命強化回数加算
	void SaveData::PlusLife_Upgrade() {
		Life_Upgrade++;
	}

private:
	//ハイスコア
	int HighScore[Stage]{
		0,
		0,
	};

	//モンスターの図鑑登録済みフラグ
	bool MonstarFlag[Monster]{
		false,
		false,
		false,
		false,
		false,
	};

	int Zanki_Upgrade = 0; //残機強化回数
	int Attack_Upgrade = 0; //攻撃強化回数
	int Life_Upgrade = 0; //寿命強化回数

	//クリアしたステージ
	int ClearedStage = 0;
};


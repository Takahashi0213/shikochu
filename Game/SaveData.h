#pragma once
#include "LevelData.h"
#include "ZukanData.h"

class SaveData 
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

	//ハード版ハイスコアを設定 (設定場所,数値)
	void SaveData::SetHighScore_Hard(int x, int y) {
		HighScore_Hard[x] = y;
	}

	//引数に設定した場所のハード版ハイスコアを取得
	int SaveData::GetHighScore_Hard(int x) {
		return HighScore_Hard[x];
	}

	//引数に設定した場所のモンスターフラグをtrueにする
	void SaveData::SetMonFlag(int x) {
		MonstarFlag[x] = true;
	}

	//引数に設定した場所のモンスターフラグを取得
	bool SaveData::GetMonFlag(int x) {
		return MonstarFlag[x];
	}

	//引数に設定した場所のキコウチュウフラグをtrueにする
	void SaveData::SetKikoFlag(int x) {
		KikoFlag[x] = true;
	}
	//引数に設定した場所のキコウチュウフラグを取得
	bool SaveData::GetKikoFlag(int x) {
		return KikoFlag[x];
	}

	//引数に設定した場所のキコウチュウフラグ ハードをtrueにする
	void SaveData::SetKikoFlag_Hard(int x) {
		KikoFlag_Hard[x] = true;
	}

	//引数に設定した場所のキコウチュウフラグ（ハード）を取得
	bool SaveData::GetKikoFlag_Hard(int x) {
		return KikoFlag_Hard[x];
	}

	//引数に設定した場所のサポートチュートリアルフラグをtrueにする
	void SaveData::SetSupportFlag(int x) {
		SupportFlag[x] = true;
	}
	//引数に設定した場所のサポートチュートリアルフラグを取得
	bool SaveData::GetSupportFlag(int x) {
		return SupportFlag[x];
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

	//引数位置のスキル取得フラグをtrueにする
	void SaveData::SkillGetFlag_Set(int x) {
		SkillGetFlag[x] = true;
	}
	//引数位置のスキル取得フラグを取得する
	bool SaveData::SkillGetFlag_Get(int x) {
		return SkillGetFlag[x];
	}

	//第一引数→変更するスキル場所(false→Y、true→X）
	//第二引数→セットするスキルNo（-1なら無）
	//スキルを設定する
	void SaveData::SkillSetting(bool YorX, int skill) {
		if (YorX == false) { //Yボタンにセット
			SkillSet[0] = skill;
		}
		else { //Xボタンにセット
			SkillSet[1] = skill;
		}
	}
	//第一引数→変更するスキル場所(false→Y、true→X）
	//設定されているスキルNoを返す
	int SaveData::GetSkill(bool YorX) {
		if (YorX == false) { //Yボタン
			return SkillSet[0];
		}
		else { //Xボタン
			return SkillSet[1];
		}
	}
	
private:
	//ハイスコア
	int HighScore[Stage]{
		0,
		0,
		0,
		0,
		0,
	};

	//ハイスコア（ハード）
	int HighScore_Hard[Stage]{
		0,
		0,
		0,
		0,
		0,
	};

	//キコウチュウフラグ
	bool KikoFlag[Stage]{
		false,
	};

	//キコウチュウフラグ ハード
	bool KikoFlag_Hard[Stage]{
		false,
	};

	//モンスターの図鑑登録済みフラグ
	bool MonstarFlag[Monster]{
		false,
	};

	int Zanki_Upgrade = 0; //残機強化回数
	int Attack_Upgrade = 0; //攻撃強化回数
	int Life_Upgrade = 0; //寿命強化回数

	//クリアしたステージ
	int ClearedStage = 0;

	//サポートチュートリアルフラグ
	bool SupportFlag[4]{
		false, //敵を4体倒したら削除
		false, //りゅうせいダッシュを使用したら削除
		false, //ボスにダメージを与えたら削除
		false, //ボスに3回ダメージを与えたら削除
	};

	int SkillSet[2]{//セット中のスキルデータ（-1なら無し）
		0, //Yボタン
		-1, //Xボタン
	};

	//スキル入手フラグ
	bool SkillGetFlag[24]{
		true,
		false,
	};

};


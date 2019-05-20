#pragma once
class GameResult : public IGameObject
{
	static GameResult* m_instance;
public:
	GameResult();
	~GameResult();
	bool Start();
	void Update();
private:

	//カウント変数どもをリセット
	void CountReset() {
		Hoge_Couneter = 0;
		MulAlpha = 0.0f;
		MulColor = { 1.0f,1.0f,1.0f,1.0f };
		HogePosition1 = 0.0f;
		HogePosition2 = 0.0f;
		HogeFlag = false;
	}

	//MulAlpha変数をいい感じにします
	void MulPuls() {
		MulAlpha += 0.05f;
		if (MulAlpha > 1.0f) {
			MulAlpha = 1.0f;
		}
	}

	//消えてしまえ～～～～
	void DeleteAllSpriteRender() {
		for (int i = 0; i < m_spriteRender.size(); i++) {
			DeleteGO(m_spriteRender[i]);
		}
	}

	//消えてしまえ～～～～！！！
	void DeleteAllFontRender() {
		for (int i = 0; i < m_fontRender.size(); i++) {
			DeleteGO(m_fontRender[i]);
		}
	}

	enum resultscene {
		scene1,
		scene2,
	};
	enum resultturn {
		scene1_Background,
		scene1_ResultMozi,
		scene1_ZankiBonus,
		scene1_GiriBonus,
		scene1_ItemBonus,
		scene1_MatometeScore,
		scene1_Runk,
		scene2_Seni,
		scene2_ScoreUp,
		scene2_ScoreIdou,
		scene2_ScoreKasan,
	};

	std::vector<prefab::CSpriteRender*> m_spriteRender;
	std::vector<prefab::CFontRender*> m_fontRender;

	resultscene ResultScene = scene1;		 //状態
	resultturn ResultTurn = scene1_Background;		 //状態

	prefab::CSpriteRender* r;
	prefab::CFontRender* f;

	int FinalScore = 0; //結果スコア
	int Point = 0; //所持ポイント
	int Point_Count = 0; //表示用ポイント

	int NowStage = 0;

	bool OK_Flag = false; //決定キーを押すまで待ちなさい
	bool FinalFlag = false;
	int FinalCount = 0;

	//以下カウント用
	int Hoge_Couneter = 0; //タイマー
	float MulAlpha = 0.0f;
	CVector4 MulColor{ 1.0f,1.0f,1.0f,1.0f };
	float HogePosition1 = 0.0f;
	float HogePosition2 = 0.0f;

	//以下アニメーション用
	float ResultIconMoveY = 210.0f; //リザルトアイコンが上下移動するぞ
	bool ResultIconUpDownFlag = false; //falseなら上、trueなら下
	int ResultIconTimer = 0; //上のFlagを切り替えるまでのタイマー
	bool ResultIconMoveFlag = false; //これがtrueの間アニメーションする

	//以下リザルト処理用
	int ZankiBonus = 0;
	int GiriBonus = 0;
	int ItemBonus = 0;

	//フラグ
	bool HogeFlag = false; //汎用フラグ
	bool RunkFlag = false; //ランク表示用フラグ
	bool PointFlag = false; //ポイントが上下移動する時のフラグ

	//////////////////////////////////////////定数色々///////////////////////////////////////
	//フェイズ１ 背景表示
	const int PhaseTimer1 = 40; //動作の制限時間
	const float WakuPositon = 600.0f; //左右枠の最終ポジション
	const float WakuMoveSpeed = 20.0f; //左右枠の移動速度
	const float WakuSpeedDown = 700.0f; //左右枠の速度が落ちるポジション
	const float WakuSpeedDownHosei = 0.6; //左右枠の減少速度（左右枠の移動速度に乗算される）

	//フェイズ２ リザルト移動
	const int PhaseTimer2 = 80; //動作の制限時間
	const float ResultMoziHigh = 200.0f; //リザルトの表示高さ
	const float ResultMoziMoveSpeed = 20.0f; //リザルトの移動速度
	const float ResultMoziMove = 40.0f; //リザルトが戻る長さ
	const int ResultMoziModoriTime = 20; //リザルトが戻る時間
	const float ResultMoziMoveX = ResultMoziMove / (float)ResultMoziModoriTime; //リザルトの移動距離
	const float ResultIconMove = 1.0f; //リザルトアイコンの移動距離
	const int ResultIconMoveTime = 48; //リザルトアイコンが1ループする間隔

	//フェイズ３ 残機ボーナス！
	const int PhaseTimer3 = 30; //動作の制限時間
	const int BonusAverage = 10; //表示されるまでの時間（フェイズ５まで流用）
	const float BonusFontSize = 1.2f; //ボーナスの文字サイズ（フェイズ５まで流用）

	//フェイズ４ ギリギリボーナス！
	const int PhaseTimer4 = 30; //動作の制限時間
	const float BonusMoziIdou = 80.0f; //フェイズ3より下に移動する量（フェイズ５まで流用）

	//フェイズ５ アイテムボーナス！
	const int PhaseTimer5 = 30; //動作の制限時間

	//フェイズ６ 最終スコア
	const int PhaseTimer6 = 40; //動作の制限時間
	const int ScoreAverage = 30; //表示されるまでの時間
	const float ScoreFontSize = 2.0f; //スコアの文字サイズ（フェイズ９でも使用）
	const float ScoreYHosei = 40.0f; //スコアの表示が下すぎるので上に動かす

	//フェイズ７ 評価してやろう
	const int PhaseTimer7 = 90; //動作の制限時間
	const int RunkAverage = 30; //表示されるまでの時間
	const CVector3 RunkPos = { 230.0f,200.0f,1.0f };
	const float RunkKakudaiMin = 0.5f; //評価のサイズ縮小下限
	const float RunkScaleSpeed = 0.4f; //評価の拡大率変更速度

	//フェイズ８ 遷移
	const int PhaseTimer8 = 40; //動作の制限時間
	const float SeniMove = 30.0f; //スコアもろもろの移動速度（フェイズ９でも使用）

	//フェイズ９ 最終決戦 ～移動処理を添えて～
	const int PhaseTimer9 = 60; //動作の制限時間
	const float KeisanFontSize = 1.5f; //スコア文字サイズ
	const float SeniMoveHosei = 5.0f; //スコアもろもろの移動速度補正

	//フェイズ１０ あれは移動するスコアだった
	const int PhaseTimer10 = 14; //動作の制限時間

	//フェイズ１１ これでほんとうにサヨナラ
	const int ScoreKasan = 100.0f; //1フレームで加算される数
	const int DeleteTime = 60; //終了演出の時間
};


#include "stdafx.h"
#include "GameResult.h"
#include "GameData.h"
#include "DataBase.h"
#include "SaveData.h"
#include "TransitionMaker.h"
#include "SkillData.h"

GameResult* GameResult::m_instance = nullptr;

GameResult::GameResult()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

}

GameResult::~GameResult()
{
	DeleteAllSpriteRender();
	DeleteAllFontRender();
	for (int i = 0; i < m_spriteRender_skill.size(); i++) {
		DeleteGO(m_spriteRender_skill[i]);
	}
	for (int i = 0; i < m_fontRender_skill.size(); i++) {
		DeleteGO(m_fontRender_skill[i]);
	}

	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;

}

bool GameResult::Start() {

	ss = NewGO<prefab::CSoundSource>(0);
	//SE再生
	ss->Init(L"sound/result.wav");
	ss->SetVolume(BMG_V);
	ss->Play(false);

	//変数の準備
	GameData * gamedata = GameData::GetInstance();
	SaveData * savedata = SaveData::GetInstance();
	ZankiBonus = gamedata->ZankiBonusKeisan();
	GiriBonus = gamedata->GetGiriCountKeisan();
	ItemBonus = gamedata->GetItemCountKeisan();
	FinalScore = ZankiBonus + GiriBonus + ItemBonus;
	NowStage = gamedata->GetStageNo();
	Point_Count = gamedata->GetPoint();
	Point = Point_Count + FinalScore;
	HardFlag = gamedata->GetHardModeFlag();
	HardHosei = gamedata->GetHardScoreHosei();
	KikoFlag = gamedata->GetKikoFlag();
	KikoBonus= gamedata->GetKikoBonus();
	if (savedata->GetSkill(false) == 19 || savedata->GetSkill(true) == 19 || savedata->GetSkill(false) == 20 || savedata->GetSkill(true) == 20 || savedata->GetSkill(false) == 21 || savedata->GetSkill(true) == 21) {
		SkillFlag = true;
	}
	SkillGetSetup(); //スキルの判定

	//0番→背景
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/ResultBG.dds", 1920.0f, 1080.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//1番→枠（左）
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/Result_Back.dds", 400.0f, 1080.0f);
	HogePosition1 = -1200.0f;
	r->SetPosition({ HogePosition1 ,0.0f,0.0f });
	m_spriteRender.push_back(r);
	//2番→枠（右）
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/Result_Back.dds", 400.0f, 1080.0f);
	HogePosition2 = 1200.0f;
	r->SetPosition({ HogePosition2 ,0.0f,0.0f });
	m_spriteRender.push_back(r);
	//3番→装飾1
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/ResultAccessory.dds", 300.0f, 720.0f);
	r->SetPosition({ ACCPositionX ,0.0f,0.0f });
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//4番→装飾2
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/ResultAccessory.dds", 300.0f, 720.0f);
	r->SetPosition({ ACCPositionX ,-720.0f,0.0f });
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//5番→装飾1
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/ResultAccessoryM.dds", 300.0f, 720.0f);
	r->SetPosition({ -ACCPositionX ,360.0f,0.0f });
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//6番→装飾2
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/ResultAccessoryM.dds", 300.0f, 720.0f);
	r->SetPosition({ -ACCPositionX ,-360.0f,0.0f });
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);

	return true;
}

void GameResult::Update() {

	switch (ResultTurn) {

	case scene1_Background://背景モロモロ表示
	{
		//背景をフェード
		MulColor.a=MulAlpha;
		m_spriteRender[0]->SetMulColor(MulColor);
		m_spriteRender[3]->SetMulColor(MulColor);
		m_spriteRender[4]->SetMulColor(MulColor);
		m_spriteRender[5]->SetMulColor(MulColor);
		m_spriteRender[6]->SetMulColor(MulColor);

		//左右枠を移動
		HogePosition1 += WakuMoveSpeed;
		if (HogePosition1 > -WakuSpeedDown) {
			HogePosition1 -= WakuMoveSpeed * WakuSpeedDownHosei;
		}
		if (HogePosition1 > -WakuPositon) {
			HogePosition1 = -WakuPositon;
		}
		//
		HogePosition2 -= WakuMoveSpeed;
		if (HogePosition2 < WakuSpeedDown) {
			HogePosition2 += WakuMoveSpeed * WakuSpeedDownHosei;
		}
		if (HogePosition2 < WakuPositon) {
			HogePosition2 = WakuPositon;
		}
		m_spriteRender[1]->SetPosition({ HogePosition1 ,0.0f,0.0f });
		m_spriteRender[2]->SetPosition({ HogePosition2 ,0.0f,0.0f });

		MulPuls();

		//刻時計が終焉と共鳴せし時、時代の遷移が訪れる（タイマーが終了時間と一致した時にフェイズを次に進めます！）
		if (Hoge_Couneter >= PhaseTimer1) {
			CountReset();
			ResultTurn = scene1_ResultMozi;
		}
		break;
	}

	case scene1_ResultMozi://リザルトの文字を表示する
	{
		if (Hoge_Couneter == 1) {//最初に
			//7番→リザルト
			r = NewGO<prefab::CSpriteRender>(1);
			r->Init(L"sprite/Result_Bar.dds", 691.0f, 218.0f);
			HogePosition1 = -850.0f;
			r->SetPosition({ HogePosition1 ,ResultMoziHigh,0.0f });
			m_spriteRender.push_back(r);
			//8番→リザルトアイコン
			r = NewGO<prefab::CSpriteRender>(2);
			r->Init(L"sprite/Icon2.dds", 200.0f, 200.0f);
			r->SetPosition({ 100.0f ,ResultIconMoveY,0.0f });
			MulColor = { 1.0f,1.0f,1.0f,0.0f };
			r->SetMulColor(MulColor);
			m_spriteRender.push_back(r);
			ResultIconMoveFlag = true; //フラグオン
		}

		//リザルトを移動
		if (Hoge_Couneter < 40.0f) {
			HogePosition1 += ResultMoziMoveSpeed;
		}
		else if(Hoge_Couneter < 60.0f) {
			HogePosition1 -= ResultMoziMoveX;
		}
		m_spriteRender[7]->SetPosition({ HogePosition1 ,ResultMoziHigh,0.0f });

		if (Hoge_Couneter >= PhaseTimer2 / 3) {
			MulColor.a = MulAlpha;
			m_spriteRender[8]->SetMulColor(MulColor);
			MulPuls();
		}

		//刻時計が終焉と共鳴せし時、時代の遷移が訪れる（タイマーが終了時間と一致した時にフェイズを次に進めます！）
		if (Hoge_Couneter >= PhaseTimer2) {
			CountReset();
			ResultTurn = scene1_ZankiBonus;
		}
		break;
	}

	case scene1_ZankiBonus://残機ボーナスを表示する
	{
		if (Hoge_Couneter == BonusAverage) {//ある程度経ったら

			prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/kettei.wav");
			ss->SetVolume(0.5f);
			ss->Play(false);

			f = NewGO<prefab::CFontRender>(1);
			//表示
			wchar_t text[256];
			//おわ
			swprintf(text, L"ざんきボーナス:%d", ZankiBonus);
			//はい。
			f->SetText(text);
			f->SetPosition({ 280.0f,0.0f });
			f->SetScale(BonusFontSize);
			f->SetPivot({ 1.0f,0.0f });
			m_fontRender.push_back(f);
		}

		//刻時計が終焉と共鳴せし時、時代の遷移が訪れる（タイマーが終了時間と一致した時にフェイズを次に進めます！）
		if (Hoge_Couneter >= PhaseTimer3) {
			CountReset();
			ResultTurn = scene1_GiriBonus;
		}
		break;
	}

	case scene1_GiriBonus://ギリギリボーナスを表示する
	{
		if (Hoge_Couneter == BonusAverage) {//ある程度経ったら

			prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/kettei.wav");
			ss->SetVolume(0.5f);
			ss->Play(false);

			f = NewGO<prefab::CFontRender>(1);
			//表示
			wchar_t text[256];
			//おわ
			swprintf(text, L"ギリギリボーナス:%d", GiriBonus);
			//はい。
			f->SetText(text);
			f->SetPosition({ 280.0f,-BonusMoziIdou });
			f->SetScale(BonusFontSize);
			f->SetPivot({ 1.0f,0.0f });
			m_fontRender.push_back(f);
		}

		//刻時計が終焉と共鳴せし時、時代の遷移が訪れる（タイマーが終了時間と一致した時にフェイズを次に進めます！）
		if (Hoge_Couneter >= PhaseTimer4) {
			CountReset();
			ResultTurn = scene1_ItemBonus;
		}
		break;
	}

	case scene1_ItemBonus://アイテムボーナスを表示する
	{
		if (Hoge_Couneter == BonusAverage) {//ある程度経ったら

			prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/kettei.wav");
			ss->SetVolume(0.5f);
			ss->Play(false);

			f = NewGO<prefab::CFontRender>(1);
			//表示
			wchar_t text[256];
			//おわ
			swprintf(text, L"アイテムボーナス:%d", ItemBonus);
			//はい。
			f->SetText(text);
			f->SetPosition({ 280.0f,-BonusMoziIdou *2 });
			f->SetScale(BonusFontSize);
			f->SetPivot({ 1.0f,0.0f });
			m_fontRender.push_back(f);
			f = NewGO<prefab::CFontRender>(1);
			//表示
			text[256];
			//おわ
			swprintf(text, L"----------------------");
			//はい。
			f->SetText(text);
			f->SetPosition({ 280.0f,-BonusMoziIdou * 2 });
			f->SetScale(BonusFontSize);
			f->SetPivot({ 1.0f,0.0f });
			m_fontRender.push_back(f);
		}

		//刻時計が終焉と共鳴せし時、時代の遷移が訪れる（タイマーが終了時間と一致した時にフェイズを次に進めます！）
		if (Hoge_Couneter >= PhaseTimer5) {
			CountReset();
			ResultTurn = scene1_MatometeScore;
		}
		break;
	}

	case scene1_MatometeScore://スコアを表示する
	{
		if (Hoge_Couneter == ScoreAverage) {//ある程度経ったら

			prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/kettei.wav");
			ss->SetVolume(0.5f);
			ss->Play(false);

			f = NewGO<prefab::CFontRender>(1);
			//表示
			wchar_t text[256];
			//おわ
			swprintf(text, L"%d", FinalScore);
			//はい。
			f->SetText(text);
			f->SetPosition({ 280.0f,-BonusMoziIdou * 3 + ScoreYHosei });
			f->SetScale(ScoreFontSize);
			f->SetPivot({ 1.0f,1.0f });
			m_fontRender.push_back(f);

			//ボーナス文字
			f = NewGO<prefab::CFontRender>(1);
			//表示
			text[256];
			//おわ
			swprintf(text, L"X");
			//はい。
			f->SetText(text);
			f->SetPosition({ 280.0f,-BonusMoziIdou * 3 - ScoreYHosei - 20.0f });
			f->SetPivot({ 1.0f,1.0f });
			f->SetColor({ 1.0f,1.0f,1.0f,0.0f });//透明に表示される
			m_fontRender.push_back(f);

			//キコウチュウ確認
			if (KikoFlag == true) {
				hoge += HardTimerHosei;
				hoge2 += HardTimerHosei;
				hoge3 += HardTimerHosei;
			}
			//ハード確認
			if (HardFlag == true) {
				hoge += HardTimerHosei;
				hoge3 += HardTimerHosei;
			}
			//スキル確認
			if (SkillFlag == true) {
				hoge += HardTimerHosei;
			}

		}

		//キコウチュウボーナス
		if (KikoFlag == true && Hoge_Couneter == PhaseTimer6_Hard) {
			prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/kettei.wav");
			ss->SetVolume(0.5f);
			ss->Play(false);

			wchar_t text[256];
			swprintf(text, L"キコウチュウボーナス！");
			m_fontRender[5]->SetText(text);
			m_fontRender[5]->SetColor({ 1.0f,0.0f,0.0f,1.0f });
			float score = (float)FinalScore;
			score += KikoBonus;
			FinalScore = (int)score;
			Point = Point_Count + FinalScore;
			text[256];
			//おわ
			swprintf(text, L"%d", FinalScore);
			//はい。
			m_fontRender[4]->SetText(text);
			m_fontRender[4]->SetColor({ 1.0f,0.8f,0.1f,1.0f });
		}

		//キコウチュウ移動
		if (KikoFlag == true && Hoge_Couneter < PhaseTimer6_Hard + 5 && Hoge_Couneter>PhaseTimer6_Hard) {
			CVector2 pos = m_fontRender[4]->GetPosition();
			pos.y += 5.0f;
			m_fontRender[4]->SetPosition(pos);
		}
		else if (KikoFlag == true && Hoge_Couneter < PhaseTimer6_Hard + 10 && Hoge_Couneter>PhaseTimer6_Hard) {
			CVector2 pos = m_fontRender[4]->GetPosition();
			pos.y -= 5.0f;
			m_fontRender[4]->SetPosition(pos);
		}

		//ハードボーナス
		if (HardFlag == true && Hoge_Couneter == PhaseTimer6_Hard + hoge2) {
			prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/kettei.wav");
			ss->SetVolume(0.5f);
			ss->Play(false);

			wchar_t text[256];
			swprintf(text, L"ハードボーナス！");
			m_fontRender[5]->SetText(text);
			m_fontRender[5]->SetColor({ 1.0f,0.0f,0.0f,1.0f });
			float score = (float)FinalScore;
			score *= HardHosei;
			FinalScore = (int)score;
			Point = Point_Count + FinalScore;
			text[256];
			//おわ
			swprintf(text, L"%d", FinalScore);
			//はい。
			m_fontRender[4]->SetText(text);
			m_fontRender[4]->SetColor({ 1.0f,0.8f,0.1f,1.0f });
		}

		//ハード移動
		if (HardFlag == true && Hoge_Couneter < PhaseTimer6_Hard + hoge2 + 5 && Hoge_Couneter>PhaseTimer6_Hard + hoge2) {
			CVector2 pos = m_fontRender[4]->GetPosition();
			pos.y += 5.0f;
			m_fontRender[4]->SetPosition(pos);
		}else if (HardFlag == true && Hoge_Couneter < PhaseTimer6_Hard + hoge2 + 10 && Hoge_Couneter>PhaseTimer6_Hard + hoge2) {
			CVector2 pos = m_fontRender[4]->GetPosition();
			pos.y -= 5.0f;
			m_fontRender[4]->SetPosition(pos);
		}

		//スキルボーナス
		if (SkillFlag == true && Hoge_Couneter == PhaseTimer6_Hard + hoge3) {
			prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/kettei.wav");
			ss->SetVolume(0.5f);
			ss->Play(false);

			wchar_t text[256];
			swprintf(text, L"スキルボーナス！");
			m_fontRender[5]->SetText(text);
			m_fontRender[5]->SetColor({ 1.0f,0.0f,0.0f,1.0f });
			float score = (float)FinalScore;
			//計算
			SaveData * savedata = SaveData::GetInstance();
			if (savedata->GetSkill(false) == 19 || savedata->GetSkill(true) == 19) {
				score *= 1.5f;
			}			
			if (savedata->GetSkill(false) == 20 || savedata->GetSkill(true) == 20) {
				score *= 1.5f;
			}
			if (savedata->GetSkill(false) == 21 || savedata->GetSkill(true) == 21) {
				score *= 2.0f;
			}
			FinalScore = (int)score;
			Point = Point_Count + FinalScore;
			text[256];
			//おわ
			swprintf(text, L"%d", FinalScore);
			//はい。
			m_fontRender[4]->SetText(text);
			m_fontRender[4]->SetColor({ 1.0f,0.8f,0.1f,1.0f });
		}

		//スキル移動
		if (SkillFlag == true && Hoge_Couneter < PhaseTimer6_Hard + hoge3 + 5 && Hoge_Couneter>PhaseTimer6_Hard + hoge3) {
			CVector2 pos = m_fontRender[4]->GetPosition();
			pos.y += 5.0f;
			m_fontRender[4]->SetPosition(pos);
		}
		else if (SkillFlag == true && Hoge_Couneter < PhaseTimer6_Hard + hoge3 + 10 && Hoge_Couneter>PhaseTimer6_Hard + hoge3) {
			CVector2 pos = m_fontRender[4]->GetPosition();
			pos.y -= 5.0f;
			m_fontRender[4]->SetPosition(pos);
		}

		//刻時計が終焉と共鳴せし時、時代の遷移が訪れる（タイマーが終了時間と一致した時にフェイズを次に進めます！）
		if (Hoge_Couneter >= PhaseTimer6 + hoge ) {
			CountReset();
			ResultTurn = scene1_Runk;
		}
		break;
	}

	case scene1_Runk://評価を表示する
	{
		if (Hoge_Couneter == RunkAverage) {//ある程度経ったら

			//9番→ランク
			r = NewGO<prefab::CSpriteRender>(1);

			if (HardFlag == false) {
				if (FinalScore >= ScoreData[NowStage][3]) {
					//Sランク
					r->Init(L"sprite/S_Runk.dds", 256.0f, 256.0f);
				}
				else if (FinalScore >= ScoreData[NowStage][2]) {
					//Aランク
					r->Init(L"sprite/A_Runk.dds", 256.0f, 256.0f);
				}
				else if (FinalScore >= ScoreData[NowStage][1]) {
					//Bランク
					r->Init(L"sprite/B_Runk.dds", 256.0f, 256.0f);
				}
				else if (FinalScore >= ScoreData[NowStage][0]) {
					//Cランク
					r->Init(L"sprite/C_Runk.dds", 256.0f, 256.0f);
				}
				else {
					//Dランク
					r->Init(L"sprite/D_Runk.dds", 256.0f, 256.0f);
				}
			}
			else {
				if (FinalScore >= (ScoreData[NowStage][3]*2)) {
					//Sランク
					r->Init(L"sprite/S_Runk.dds", 256.0f, 256.0f);
				}
				else if (FinalScore >= (ScoreData[NowStage][2]*2)) {
					//Aランク
					r->Init(L"sprite/A_Runk.dds", 256.0f, 256.0f);
				}
				else if (FinalScore >= (ScoreData[NowStage][1]*2)) {
					//Bランク
					r->Init(L"sprite/B_Runk.dds", 256.0f, 256.0f);
				}
				else if (FinalScore >= (ScoreData[NowStage][0]*2)) {
					//Cランク
					r->Init(L"sprite/C_Runk.dds", 256.0f, 256.0f);
				}
				else {
					//Dランク
					r->Init(L"sprite/D_Runk.dds", 256.0f, 256.0f);
				}
			}

			//ココカラファイン
			r->SetPosition(RunkPos);
			HogePosition2 = 0.0f;
			MulColor = { 1.0f,1.0f,1.0f,HogePosition2 };
			r->SetMulColor(MulColor); 
			HogePosition1 = 10.0f;
			r->SetScale({ HogePosition1,HogePosition1,HogePosition1 });
			m_spriteRender.push_back(r);
			HogeFlag = true;
		}

		if (HogeFlag == true && OK_Flag == false ) {
			HogePosition2 += 0.03f;
			if (RunkFlag == false) {
				HogePosition1 -= RunkScaleSpeed;
			}
			else {
				HogePosition1 += RunkScaleSpeed / 2;
			}
			if (RunkKakudaiMin > HogePosition1) {//下限になった！
				HogePosition1 = RunkKakudaiMin;

				prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
				ss->Init(L"sound/Result_dodon.wav");
				ss->SetVolume(0.5f);
				ss->Play(false);

				RunkFlag = true;
			}
			if (RunkFlag == true && HogePosition1 > 1.0f) {//上限になった！
				HogePosition1 = 1.0f;
			}
			if (HogePosition2 > 1.0f) {//透明度が1.0fより大きくならないようにする
				HogePosition2 = 1.0f;
			}
			MulColor = { 1.0f,1.0f,1.0f,HogePosition2 };
			m_spriteRender[9]->SetMulColor(MulColor);
			m_spriteRender[9]->SetScale({ HogePosition1,HogePosition1,HogePosition1 });
		}

		//刻時計が終焉と共鳴せし時、時代の遷移が訪れる（タイマーが終了時間と一致した時にフェイズを次に進めます！）
		if (Hoge_Couneter >= PhaseTimer7) {
			CountReset();
			OK_Flag = true;
		}
		break;
	}

///////////////////////////////////////////////('ω')////////////////////////////////////////////////

	case scene2_Seni://1から2へ…
	{
		//移動する
		for (int i = 0; i < m_fontRender.size(); i++) {
			CVector2 pos = m_fontRender[i]->GetPosition();
			pos.x -= SeniMove;
			m_fontRender[i]->SetPosition(pos);
		}

		//刻時計が終焉と共鳴せし時、時代の遷移が訪れる（タイマーが終了時間と一致した時にフェイズを次に進めます！）
		if (Hoge_Couneter >= PhaseTimer8) {
			CountReset();
			ResultTurn = scene2_ScoreUp;
		}
		break;
	}

	case scene2_ScoreUp://シーン2の準備をする
	{
		if (Hoge_Couneter == 1) {//初手
			f = NewGO<prefab::CFontRender>(1);
			//表示
			wchar_t text[256];
			//おわ
			swprintf(text, L"Score:%d", FinalScore);
			//はい。
			f->SetText(text);
			f->SetPosition({ 600.0f,0.0f });
			f->SetScale(KeisanFontSize);
			f->SetPivot({ 0.5f,0.5f });
			m_fontRender.push_back(f);
			f = NewGO<prefab::CFontRender>(1);
			//表示
			text[256];
			//おわ
			swprintf(text, L"Point:%d", Point_Count);
			//はい。
			f->SetText(text);
			f->SetPosition({ 600.0f,-200.0f });
			f->SetScale(ScoreFontSize);
			f->SetPivot({ 0.5f,0.5f });
			m_fontRender.push_back(f);
		}

		//移動する
			CVector2 pos = m_fontRender[6]->GetPosition();
			pos.x -= (SeniMove - SeniMoveHosei);
			if (pos.x < 0.0f) {
				pos.x = 0.0f;
			}
			m_fontRender[6]->SetPosition(pos);
			pos = m_fontRender[7]->GetPosition();
			pos.x -= (SeniMove - SeniMoveHosei);
			if (pos.x < 0.0f) {
				pos.x = 0.0f;
			}
			m_fontRender[7]->SetPosition(pos);

		//刻時計が終焉と共鳴せし時、時代の遷移が訪れる（タイマーが終了時間と一致した時にフェイズを次に進めます！）
		if (Hoge_Couneter >= PhaseTimer9) {
			CountReset();
			ResultTurn = scene2_ScoreIdou;
		}
		break;
	}

	case scene2_ScoreIdou://スコアの演出
	{
		if (Hoge_Couneter <= 6) {//上に移動
			CVector2 pos = m_fontRender[6]->GetPosition();
			pos.y += 5.0f;
			m_fontRender[6]->SetPosition(pos);
			HogePosition1 = 1.0f; //後で不透明度を変更する準備
		}
		else {//下に移動＆フェードアウト！
			CVector2 pos = m_fontRender[6]->GetPosition();
			pos.y -= 40.0f;
			m_fontRender[6]->SetPosition(pos);
			//ここで不透明度を変更
			HogePosition1 -= 0.15f;
			m_fontRender[6]->SetColor({ 1.0f, 1.0f, 1.0f, HogePosition1 });
		}

		//刻時計が終焉と共鳴せし時、時代の遷移が訪れる（タイマーが終了時間と一致した時にフェイズを次に進めます！）
		if (Hoge_Couneter >= PhaseTimer10) {
			CountReset();
			ResultTurn = scene2_ScoreKasan;
		}
		break;
	}

	case scene2_ScoreKasan://スコア分がポイントになるぞ
	{
		if (HogeFlag == false) {//加算
			prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/Result_Ka.wav");
			ss->SetVolume(0.5f);
			ss->Play(false);

			Point_Count += ScoreKasan; 
			if (Point_Count > Point) {
				prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
				ss->Init(L"sound/Result_gageEND.wav");
				ss->SetVolume(0.5f);
				ss->Play(false);

				Point_Count = Point;
				HogeFlag = true;
			}
			wchar_t text[256];
			//おわ
			swprintf(text, L"Point:%d", Point_Count);
			//はい。
			m_fontRender[7]->SetText(text);
		}
		else {//終了演出

			if (HogePosition1 < 5.0f) {
				CVector2 pos = m_fontRender[7]->GetPosition();
				pos.y += 5.0f;
				m_fontRender[7]->SetPosition(pos);
			}	
			else if (HogePosition1 < 10.0f) {
				CVector2 pos = m_fontRender[7]->GetPosition();
				pos.y -= 5.0f;
				m_fontRender[7]->SetPosition(pos);
				m_fontRender[7]->SetColor({ 1.0f,0.8f,0.1f,1.0f });
			}
			else if (HogePosition1 >= 60.0f && HogePosition1 < 90.0f) {
				CVector2 pos = m_fontRender[7]->GetPosition();
				pos.y += 6.0f;
				m_fontRender[7]->SetPosition(pos);
			}
			else if (HogePosition1 == 90.0f) { //ここで一度ストップ！
				//スキル取得処理

				if (SkillGetFlag[CheckSkillNow] == true) { //取得フラグがオンです
					if (Skill_EffectNow == false) { //エフェクト実行中でない
						Skill_EffectNow = true;
					}
					else {
						if (Skill_EffectEnd == false) {
							SkillGet(CheckSkillNow); //エフェクト実行中
						}
						else { //エフェクトが終了した
							Skill_EffectNow = false;
							Skill_EffectEnd = false;
							CheckSkillNow++;
						}
					}
				}
				else { //確認位置を加算
					CheckSkillNow++;
				}


				if (CheckSkillNow == 24) { //確認終了
					//10番→サヨナラベイベー
					r = NewGO<prefab::CSpriteRender>(2);
					r->Init(L"sprite/GoodBye.dds", 325.0f, 114.0f);
					MulColor = { 1.0f,1.0f,1.0f,0.0f };
					r->SetMulColor(MulColor);
					r->SetPosition({ 0.0f ,-200.0f,0.0f });
					r->SetScale(CVector3::One);
					m_spriteRender.push_back(r);

					HogePosition1 += 1.0f;//これで停止タイム終了
				}
				}
			else if (HogePosition1 >= 91.0f && HogePosition1 < 120.0f) {
				//フェード
				MulAlpha += 0.05f;
				MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
				m_spriteRender[10]->SetMulColor(MulColor);
				m_spriteRender[10]->SetScale(CVector3::One);

				CVector4 Hoge_Pos;
				for (int pos = 2; pos < 9; pos++) {
					Hoge_Pos = m_fontRender_skill[pos]->GetColor();
					Hoge_Pos.a -= 0.1f;
					if (Hoge_Pos.a < 0.0f) {
						Hoge_Pos.a = 0.0f;
					}
					m_fontRender_skill[pos]->SetColor(Hoge_Pos);
				}
			}
			else if (HogePosition1 >= 120.0f) {//全て終わったのだよ、全て
				OK_Flag = true;
			}

			if (HogePosition1 != 90.0f) {
				HogePosition1 += 1.0f;//ここではカウンタ扱い
			}

		}

		break;
	}

	}//switch終了

	//次のページへ…
	if (OK_Flag == true) {
		if (Pad(0).IsTrigger(enButtonA) || Pad(0).IsTrigger(enButtonB) || Pad(0).IsTrigger(enButtonY) || Pad(0).IsTrigger(enButtonX)) {
			//切り替えます
			if (ResultScene == scene1) {
				//シーン2へ…
				CountReset();
				ResultTurn = scene2_Seni;
				OK_Flag = false;
				ResultScene = scene2;
			}else if (ResultScene == scene2) {
				//終了！
				if (FinalFlag == false) {
					TransitionMaker * tm = TransitionMaker::GetInstance();
					tm->TransitionSetting(TransitionMaker::Fade, 60, 0, false);

					FinalFlag = true;//終了演出フラグを立てる			
				}
			}
		}
	}

	//最終処理
	if (FinalFlag == true) {

		if (FinalCount >= DeleteTime) {

			TransitionMaker * tm = TransitionMaker::GetInstance();
			tm->TransitionSetting(TransitionMaker::Fade, 60, 30, true);

			//セーブデータを設定する
			SaveData * savedata = SaveData::GetInstance();
			GameData * gamedata = GameData::GetInstance();
			int stage = gamedata->GetStageNo();
			stage -= 1;
			//もしハイスコアが0なら歴代クリア数を加算
			if (savedata->GetHighScore(stage) == 0) {
				if (stage < 4) {
					savedata->PlusClearedStage();
				}
			}
			//ハイスコアならハイスコアに代入
			if (HardFlag == false) {//ノーマルモード
				if (savedata->GetHighScore(stage) < FinalScore) {
					savedata->SetHighScore(stage, FinalScore);
				}
			}
			else if (HardFlag == true) {//ハードモード
				if (savedata->GetHighScore_Hard(stage) < FinalScore) {
					savedata->SetHighScore_Hard(stage, FinalScore);
				}
			}

			//キコウチュウ登録処理
			if (KikoFlag == true) {
				savedata->SetMonFlag(5);
				if (HardFlag == false) {
					savedata->SetKikoFlag(stage);
				}
				else if (HardFlag == true) {
					savedata->SetKikoFlag_Hard(stage);
				}
			}

			//モンスター登録処理
			if (stage == 0) {
				savedata->SetMonFlag(0);
				savedata->SetMonFlag(1);
				savedata->SetMonFlag(2);
				savedata->SetMonFlag(3);
				savedata->SetMonFlag(4);
				if (HardFlag == true) {
					savedata->SetMonFlag(6);
					savedata->SetMonFlag(7);
				}
			}
			if (stage == 1) {
				savedata->SetMonFlag(8);
				savedata->SetMonFlag(9);
				savedata->SetMonFlag(10);
				savedata->SetMonFlag(11);
				if (HardFlag == true) {
					savedata->SetMonFlag(12);
					savedata->SetMonFlag(13);
				}
			}
			if (stage == 2) {
				savedata->SetMonFlag(14);
				savedata->SetMonFlag(15);
				savedata->SetMonFlag(16);
				savedata->SetMonFlag(17);
				if (HardFlag == true) {
					savedata->SetMonFlag(18);
					savedata->SetMonFlag(19);
				}
			}
			if (stage == 3) {
				savedata->SetMonFlag(20);
				savedata->SetMonFlag(21);
				savedata->SetMonFlag(22);
				savedata->SetMonFlag(23);
				if (HardFlag == true) {
					savedata->SetMonFlag(24);
					savedata->SetMonFlag(25);
					savedata->SetMonFlag(26);
				}

			}
			if (stage == 4) {
				savedata->SetMonFlag(27);
				savedata->SetMonFlag(28);
				savedata->SetMonFlag(29);
				savedata->SetMonFlag(30);
				if (HardFlag == true) {
					savedata->SetMonFlag(31);
					savedata->SetMonFlag(32);
				}
			}

			gamedata->SetGameMode(GameData::GameEnd);
			gamedata->PlusPoint(FinalScore);
			DeleteGO(this);//おしまい
		}
		FinalCount++;
	}

	//アイコン移動フラグがtrueなら上下移動！
	if (ResultIconMoveFlag == true) {
		if (ResultIconUpDownFlag == false) {
			ResultIconMoveY += ResultIconMove;
		}
		else {
			ResultIconMoveY -= ResultIconMove;
		}
		m_spriteRender[8]->SetPosition({ 100.0f ,ResultIconMoveY,0.0f });

		ResultIconTimer++;
		if (ResultIconTimer == ResultIconMoveTime/2) {
			ResultIconUpDownFlag = true;
		}
		else if (ResultIconTimer == ResultIconMoveTime) {
			ResultIconUpDownFlag = false;
			ResultIconTimer = 0;
		}
	}

	//アクセサリーループ！
	m_spriteRender[3]->SetPosition({ ACCPositionX ,AccPosY1,0.0f });
	m_spriteRender[4]->SetPosition({ ACCPositionX ,AccPosY2,0.0f });
	m_spriteRender[5]->SetPosition({ -ACCPositionX ,AccPosY1m,0.0f });
	m_spriteRender[6]->SetPosition({ -ACCPositionX ,AccPosY2m,0.0f });
	AccPosY1 += 1.0f;
	AccPosY2 += 1.0f;
	AccPosY1m += 1.0f;
	AccPosY2m += 1.0f;
	if (AccPosY1 >= 720.0f) {
		AccPosY1 = -720.0f;
	}
	if (AccPosY2 >= 720.0f) {
		AccPosY2 = -720.0f;
	}
	if (AccPosY1m >= 720.0f) {
		AccPosY1m = -720.0f;
	}
	if (AccPosY2m >= 720.0f) {
		AccPosY2m = -720.0f;
	}

	//カウンターを加算する…
	Hoge_Couneter++;

}

void GameResult::SkillGetSetup() {

	//すたんばーい
	GameData * gamedata = GameData::GetInstance();
	SaveData * savedata = SaveData::GetInstance();
	short SetSkillPosition = 1; //スキルフラグを設定する場所
	int stage = gamedata->GetStageNo();
	stage -= 1;
	//最終スコアは結局前もって計算ですかい
	int Setup_FinalScore = FinalScore;
	//計算
	if (KikoFlag == true) { //キコウチュウ
		float score = (float)Setup_FinalScore;
		score += KikoBonus;
		Setup_FinalScore = (int)score;
	}
	if (HardFlag == true) { //ハード
		float score = (float)Setup_FinalScore;
		score *= HardHosei;
		Setup_FinalScore = (int)score;
		gamedata->HardClearPlus(); //ハードモードクリア回数を加算
	}
	//スキル
	float score = (float)Setup_FinalScore;
	if (savedata->GetSkill(false) == 19 || savedata->GetSkill(true) == 19) {
		score *= 1.5f;
	}
	if (savedata->GetSkill(false) == 20 || savedata->GetSkill(true) == 20) {
		score *= 1.5f;
	}
	if (savedata->GetSkill(false) == 21 || savedata->GetSkill(true) == 21) {
		score *= 2.0f;
	}
	Setup_FinalScore = (int)score;

	//キコウチュウ撃破回数
	if (KikoFlag == true) {
		//まだ倒してない場所なら倒した数を増やす
		if (HardFlag == false && savedata->GetKikoFlag(stage) == false) { //ノーマル
			gamedata->KikoGekihaPlus();
		}
		else if (HardFlag == true && savedata->GetKikoFlag_Hard(stage) == false) { //ハード
			gamedata->KikoGekihaPlus();
		}
	}

	////////////////////////////////////////////////////////////

	//こんぺいとうダッシュ取得フラグ
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false ) {
		if (stage == 0) { //シーソークスを倒した
			SkillGetFlag[SetSkillPosition] = true; //フラグオン
		}
	}
	SetSkillPosition++;
	//すいせいダッシュ取得フラグ
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (stage == 0 && HardFlag==true && Setup_FinalScore >= (ScoreData[NowStage][3]*2)) { //海ハードでSランク
			SkillGetFlag[SetSkillPosition] = true; //フラグオン
		}
	}
	SetSkillPosition++;
	//スタードロップ取得フラグ
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (gamedata->GetKikoGekiha()==1) { //キコウチュウ撃破回数1
			SkillGetFlag[SetSkillPosition] = true; //フラグオン
		}
	}
	SetSkillPosition++;
	//カガヤキノウミ取得フラグ
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (gamedata->GetKikoGekiha() == 3) { //キコウチュウ撃破回数3
			SkillGetFlag[SetSkillPosition] = true; //フラグオン
		}
	}
	SetSkillPosition++;
	//スターフィーバー取得フラグ
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (gamedata->GetKikoGekiha() == 5) { //キコウチュウ撃破回数5
			SkillGetFlag[SetSkillPosition] = true; //フラグオン
		}
	}
	SetSkillPosition++;
	//ミルキーウェイ取得フラグ
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (gamedata->GetKikoGekiha() == 10) { //キコウチュウ撃破回数10
			SkillGetFlag[SetSkillPosition] = true; //フラグオン
		}
	}
	SetSkillPosition++;
	//ゾンビタイム取得フラグ
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (stage == 3 && gamedata->GetItemCount() >= 15 ) { //遺跡でアイテム15個以上
			SkillGetFlag[SetSkillPosition] = true; //フラグオン
		}
	}
	SetSkillPosition++;
	//ナガレボシ取得フラグ
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (stage == 1 && Setup_FinalScore >= ScoreData[NowStage][3]) { //森でSランク
			SkillGetFlag[SetSkillPosition] = true; //フラグオン
		}
	}
	SetSkillPosition++;
	//ソウルフレア取得フラグ
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (stage == 1 && gamedata->GetBombFlag() == false) { //爆弾に当たらずクリア
			SkillGetFlag[SetSkillPosition] = true; //フラグオン
		}
	}
	SetSkillPosition++;
	//コメットキャノン取得フラグ
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (stage == 2 && gamedata->GetDensyaFlag() == false) { //電車に当たらずクリア
			SkillGetFlag[SetSkillPosition] = true; //フラグオン
		}
	}
	SetSkillPosition++;
	//せいめいりょく取得フラグ
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (stage == 2 && HardFlag == true && Setup_FinalScore >= (ScoreData[NowStage][3]*2)) { //駅ハードでSランク
			SkillGetFlag[SetSkillPosition] = true; //フラグオン
		}
	}
	SetSkillPosition++;
	//アタックアップ取得フラグ
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (gamedata->GetRuikeiGekihaEnemy() >= 10) { //累計敵撃破10
			SkillGetFlag[SetSkillPosition] = true; //フラグオン
		}
	}
	SetSkillPosition++;
	//ムテキノバシ取得フラグ
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (gamedata->GetRuikeiGekihaEnemy() >= 30) { //累計敵撃破30
			SkillGetFlag[SetSkillPosition] = true; //フラグオン
		}
	}
	SetSkillPosition++;
	//アイテムブースト取得フラグ
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (gamedata->GetRuikeiGekihaEnemy() >= 50) { //累計敵撃破50
			SkillGetFlag[SetSkillPosition] = true; //フラグオン
		}
	}
	SetSkillPosition++;
	//セツヤク取得フラグ
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (gamedata->GetRuikeiGekihaEnemy() >= 70) { //累計敵撃破70
			SkillGetFlag[SetSkillPosition] = true; //フラグオン
		}
	}
	SetSkillPosition++;
	//イノチカンゲン取得フラグ
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (gamedata->GetRuikeiGekihaEnemy() >= 100) { //累計敵撃破100
			SkillGetFlag[SetSkillPosition] = true; //フラグオン
		}
	}
	SetSkillPosition++;
	//ハガネノカラダ取得フラグ
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (gamedata->GetRuikeiGekihaEnemy() >= 150) { //累計敵撃破150
			SkillGetFlag[SetSkillPosition] = true; //フラグオン
		}
	}
	SetSkillPosition++;
	//カミカゼバトル取得フラグ
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (gamedata->GetLastStarDash() >= 5) { //流星ダッシュでトドメを刺した回数5回
			SkillGetFlag[SetSkillPosition] = true; //フラグオン
		}
	}
	SetSkillPosition++;
	//アクム取得フラグ
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (gamedata->GetHardClear() >= 1) { //ハードモードクリア回数1
			SkillGetFlag[SetSkillPosition] = true; //フラグオン
		}
	}
	SetSkillPosition++;
	//キョウフ取得フラグ
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (gamedata->GetHardClear() >= 3) { //ハードモードクリア回数3
			SkillGetFlag[SetSkillPosition] = true; //フラグオン
		}
	}
	SetSkillPosition++;
	//ナミダ取得フラグ
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (gamedata->GetHardClear() >= 5) { //ハードモードクリア回数5
			SkillGetFlag[SetSkillPosition] = true; //フラグオン
		}
	}
	SetSkillPosition++;
	//キコサーチ取得フラグ
	if (savedata->SkillGetFlag_Get(SetSkillPosition) == false) {
		if (stage == 4 && HardFlag == true && Setup_FinalScore >= (ScoreData[NowStage][3]*2)) { //異空間ハードSランク
			SkillGetFlag[SetSkillPosition] = true; //フラグオン
		}
	}
	SetSkillPosition++;

	//取得画像を準備！

	//0番→背景
	r_skill = NewGO<prefab::CSpriteRender>(8);
	r_skill->Init(L"sprite/Skill.dds", 660.0f, 200.0f);
	r_skill->SetPosition({ 0.0f + SkillX_Hosei,-220.0f,0.0f });
	r_skill->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_spriteRender_skill.push_back(r_skill);

	//1番→アイコン
	r_skill = NewGO<prefab::CSpriteRender>(8);
	r_skill->Init(L"sprite/skillicon_0.dds", 150.0f, 100.0f);
	r_skill->SetPosition({ -200.0f + SkillX_Hosei,-220.0f,0.0f });
	r_skill->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_spriteRender_skill.push_back(r_skill);

	//2番→アイコン枠
	r_skill = NewGO<prefab::CSpriteRender>(9);
	r_skill->Init(L"sprite/skilliconWaku.dds", 150.0f, 100.0f);
	r_skill->SetPosition({ -200.0f + SkillX_Hosei,-220.0f,0.0f });
	r_skill->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_spriteRender_skill.push_back(r_skill);

	//0番→スキル名
	f_skill = NewGO<prefab::CFontRender>(9);
	//表示
	wchar_t text[256];
	//おわ
	swprintf(text, L"テストメッセージ");
	//はい。
	f_skill->SetText(text);
	f_skill->SetPosition({ -100.0f + SkillX_Hosei,-172.0f });
	f_skill->SetScale(0.8f);
	f_skill->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	f_skill->SetPivot({ 0.0f,1.0f });
	m_fontRender_skill.push_back(f_skill);

	//1番→説明文
	f_skill = NewGO<prefab::CFontRender>(9);
	//表示
	text[256];
	//おわ
	swprintf(text, L"ほげほげほげほげ\nもげもげもげろんぼょ");
	//はい。
	f_skill->SetText(text);
	f_skill->SetPosition({ -100.0f + SkillX_Hosei,-215.0f });
	f_skill->SetScale(0.5f);
	f_skill->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	f_skill->SetPivot({ 0.0f,1.0f });
	m_fontRender_skill.push_back(f_skill);

	//2番→ス
	f_skill = NewGO<prefab::CFontRender>(9);
	//表示
	text[256];
	//おわ
	swprintf(text, L"ス");
	//はい。
	f_skill->SetText(text);
	f_skill->SetPosition({ -180.0f,-90.0f });
	f_skill->SetScale(1.2f);
	f_skill->SetColor({ 1.0f,1.0f,0.2f,0.0f });
	f_skill->SetPivot({ 0.0f,1.0f });
	m_fontRender_skill.push_back(f_skill);

	//3番→キ
	f_skill = NewGO<prefab::CFontRender>(9);
	//表示
	text[256];
	//おわ
	swprintf(text, L"　キ");
	//はい。
	f_skill->SetText(text);
	f_skill->SetPosition({ -180.0f,-90.0f });
	f_skill->SetScale(1.2f);
	f_skill->SetColor({ 1.0f,1.0f,0.2f,0.0f });
	f_skill->SetPivot({ 0.0f,1.0f });
	m_fontRender_skill.push_back(f_skill);

	//4番→ル
	f_skill = NewGO<prefab::CFontRender>(9);
	//表示
	text[256];
	//おわ
	swprintf(text, L"　　ル");
	//はい。
	f_skill->SetText(text);
	f_skill->SetPosition({ -180.0f,-90.0f });
	f_skill->SetScale(1.2f);
	f_skill->SetColor({ 1.0f,1.0f,0.2f,0.0f });
	f_skill->SetPivot({ 0.0f,1.0f });
	m_fontRender_skill.push_back(f_skill);

	//5番→ゲ
	f_skill = NewGO<prefab::CFontRender>(9);
	//表示
	text[256];
	//おわ
	swprintf(text, L"　　　ゲ");
	//はい。
	f_skill->SetText(text);
	f_skill->SetPosition({ -180.0f,-90.0f });
	f_skill->SetScale(1.2f);
	f_skill->SetColor({ 1.0f,1.0f,0.2f,0.0f });
	f_skill->SetPivot({ 0.0f,1.0f });
	m_fontRender_skill.push_back(f_skill);

	//6番→ッ
	f_skill = NewGO<prefab::CFontRender>(9);
	//表示
	text[256];
	//おわ
	swprintf(text, L"　　　　ッ");
	//はい。
	f_skill->SetText(text);
	f_skill->SetPosition({ -180.0f,-90.0f });
	f_skill->SetScale(1.2f);
	f_skill->SetColor({ 1.0f,1.0f,0.2f,0.0f });
	f_skill->SetPivot({ 0.0f,1.0f });
	m_fontRender_skill.push_back(f_skill);

	//7番→ト
	f_skill = NewGO<prefab::CFontRender>(9);
	//表示
	text[256];
	//おわ
	swprintf(text, L"　　　　　ト");
	//はい。
	f_skill->SetText(text);
	f_skill->SetPosition({ -180.0f,-90.0f });
	f_skill->SetScale(1.2f);
	f_skill->SetColor({ 1.0f,1.0f,0.2f,0.0f });
	f_skill->SetPivot({ 0.0f,1.0f });
	m_fontRender_skill.push_back(f_skill);

	//8番→！
	f_skill = NewGO<prefab::CFontRender>(9);
	//表示
	text[256];
	//おわ
	swprintf(text, L"　　　　　　！");
	//はい。
	f_skill->SetText(text);
	f_skill->SetPosition({ -180.0f,-90.0f });
	f_skill->SetScale(1.2f);
	f_skill->SetColor({ 1.0f,1.0f,0.2f,0.0f });
	f_skill->SetPivot({ 0.0f,1.0f });
	m_fontRender_skill.push_back(f_skill);

}

void GameResult::SkillGet(short SetPos) {

	if (SkillTimer == 0) {
		//取得画像を引数のスキル仕様に変更！
		wchar_t text[256];

		//アイコン
		for (int i = 0; i < 256; i++) { //リセット
			text[i] = Reset[0];
		}
		int len = (int)wcslen(Skill_Data[SetPos].SkillIcon);
		for (int z = 0; z < len + 1; z++) { //名前の取得
			text[z] = Skill_Data[SetPos].SkillIcon[z];
		}
		m_spriteRender_skill[1]->Init(text, 150.0f, 100.0f);

		//名前の取得
		for (int i = 0; i < 256; i++) { //リセット
			text[i] = Reset[0];
		}
		len = (int)wcslen(Skill_Data[SetPos].SkillName);
		for (int z = 0; z < len + 1; z++) { //名前の取得
			text[z] = Skill_Data[SetPos].SkillName[z];
		}
		swprintf(text, text);
		//はい。
		m_fontRender_skill[0]->SetText(text);

		//説明文の取得
		for (int i = 0; i < 256; i++) { //リセット
			text[i] = Reset[0];
		}
		len = (int)wcslen(Skill_Data[SetPos].SkillSetumei);
		for (int z = 0; z < len + 1; z++) { //名前の取得
			text[z] = Skill_Data[SetPos].SkillSetumei[z];
		}
		swprintf(text, text);
		//はい。
		m_fontRender_skill[1]->SetText(text);

	}

	//登場移動
	if (SkillTimer < SkillMoveSpeed + SkillMoveWait) { //移動

		CVector3 Hoge_Pos;
		CVector2 Hoge_Pos2;
		CVector4 Hoge_Pos3;

		if (SkillTimer < SkillMoveSpeed) {

			float MoveSpeed = SkillX_Hosei / (float)SkillMoveSpeed; //移動距離を計算

			Hoge_Pos = m_spriteRender_skill[0]->GetPosition();
			Hoge_Pos.x -= MoveSpeed;
			m_spriteRender_skill[0]->SetPosition(Hoge_Pos);
			Hoge_Pos = m_spriteRender_skill[1]->GetPosition();
			Hoge_Pos.x -= MoveSpeed;
			m_spriteRender_skill[1]->SetPosition(Hoge_Pos);
			Hoge_Pos = m_spriteRender_skill[2]->GetPosition();
			Hoge_Pos.x -= MoveSpeed;
			m_spriteRender_skill[2]->SetPosition(Hoge_Pos);
			Hoge_Pos2 = m_fontRender_skill[0]->GetPosition();
			Hoge_Pos2.x -= MoveSpeed;
			m_fontRender_skill[0]->SetPosition(Hoge_Pos2);
			Hoge_Pos2 = m_fontRender_skill[1]->GetPosition();
			Hoge_Pos2.x -= MoveSpeed;
			m_fontRender_skill[1]->SetPosition(Hoge_Pos2);

			//スキルゲットの文字…（もうちょっと頭いい方法なかったんですか？）
			Hoge_Pos3 = m_fontRender_skill[2]->GetColor();
			Hoge_Pos3.a += 0.1f;
			if (Hoge_Pos3.a > 1.0f) {
				Hoge_Pos3.a = 1.0f;
			}
			m_fontRender_skill[2]->SetColor(Hoge_Pos3);

			Hoge_Pos3 = m_fontRender_skill[3]->GetColor();
			Hoge_Pos3.a += 0.1f;
			if (Hoge_Pos3.a > 1.0f) {
				Hoge_Pos3.a = 1.0f;
			}
			m_fontRender_skill[3]->SetColor(Hoge_Pos3);

			Hoge_Pos3 = m_fontRender_skill[4]->GetColor();
			Hoge_Pos3.a += 0.1f;
			if (Hoge_Pos3.a > 1.0f) {
				Hoge_Pos3.a = 1.0f;
			}
			m_fontRender_skill[4]->SetColor(Hoge_Pos3);

			Hoge_Pos3 = m_fontRender_skill[5]->GetColor();
			Hoge_Pos3.a += 0.1f;
			if (Hoge_Pos3.a > 1.0f) {
				Hoge_Pos3.a = 1.0f;
			}
			m_fontRender_skill[5]->SetColor(Hoge_Pos3);

			Hoge_Pos3 = m_fontRender_skill[6]->GetColor();
			Hoge_Pos3.a += 0.1f;
			if (Hoge_Pos3.a > 1.0f) {
				Hoge_Pos3.a = 1.0f;
			}
			m_fontRender_skill[6]->SetColor(Hoge_Pos3);

			Hoge_Pos3 = m_fontRender_skill[7]->GetColor();
			Hoge_Pos3.a += 0.1f;
			if (Hoge_Pos3.a > 1.0f) {
				Hoge_Pos3.a = 1.0f;
			}
			m_fontRender_skill[7]->SetColor(Hoge_Pos3);

			Hoge_Pos3 = m_fontRender_skill[8]->GetColor();
			Hoge_Pos3.a += 0.1f;
			if (Hoge_Pos3.a > 1.0f) {
				Hoge_Pos3.a = 1.0f;
			}
			m_fontRender_skill[8]->SetColor(Hoge_Pos3);

		}

		//移動
		if (SkillMove == false) {
			if (SkillTimer == 3 + SkillMoveWait) {
				Hoge_Pos2 = m_fontRender_skill[2]->GetPosition();
				Hoge_Pos2.y -= 7.5f;
				m_fontRender_skill[2]->SetPosition(Hoge_Pos2);
			}
			if (SkillTimer == 4 + SkillMoveWait) {
				Hoge_Pos2 = m_fontRender_skill[2]->GetPosition();
				Hoge_Pos2.y -= 7.5f;
				m_fontRender_skill[2]->SetPosition(Hoge_Pos2);
			}
			if (SkillTimer == 5 + SkillMoveWait) {
				Hoge_Pos2 = m_fontRender_skill[2]->GetPosition();
				Hoge_Pos2.y += 7.5f;
				m_fontRender_skill[2]->SetPosition(Hoge_Pos2);

				Hoge_Pos2 = m_fontRender_skill[3]->GetPosition();
				Hoge_Pos2.y -= 7.5f;
				m_fontRender_skill[3]->SetPosition(Hoge_Pos2);
			}
			if (SkillTimer == 6 + SkillMoveWait) {
				Hoge_Pos2 = m_fontRender_skill[2]->GetPosition();
				Hoge_Pos2.y += 7.5f;
				m_fontRender_skill[2]->SetPosition(Hoge_Pos2);

				Hoge_Pos2 = m_fontRender_skill[3]->GetPosition();
				Hoge_Pos2.y -= 7.5f;
				m_fontRender_skill[3]->SetPosition(Hoge_Pos2);
			}
			if (SkillTimer == 7 + SkillMoveWait) {
				Hoge_Pos2 = m_fontRender_skill[3]->GetPosition();
				Hoge_Pos2.y += 7.5f;
				m_fontRender_skill[3]->SetPosition(Hoge_Pos2);

				Hoge_Pos2 = m_fontRender_skill[4]->GetPosition();
				Hoge_Pos2.y -= 7.5f;
				m_fontRender_skill[4]->SetPosition(Hoge_Pos2);

			}
			if (SkillTimer == 8 + SkillMoveWait) {
				Hoge_Pos2 = m_fontRender_skill[3]->GetPosition();
				Hoge_Pos2.y += 7.5f;
				m_fontRender_skill[3]->SetPosition(Hoge_Pos2);

				Hoge_Pos2 = m_fontRender_skill[4]->GetPosition();
				Hoge_Pos2.y -= 7.5f;
				m_fontRender_skill[4]->SetPosition(Hoge_Pos2);
			}
			if (SkillTimer == 9 + SkillMoveWait) {
				Hoge_Pos2 = m_fontRender_skill[4]->GetPosition();
				Hoge_Pos2.y += 7.5f;
				m_fontRender_skill[4]->SetPosition(Hoge_Pos2);

				Hoge_Pos2 = m_fontRender_skill[5]->GetPosition();
				Hoge_Pos2.y -= 7.5f;
				m_fontRender_skill[5]->SetPosition(Hoge_Pos2);
			}
			if (SkillTimer == 10 + SkillMoveWait) {
				Hoge_Pos2 = m_fontRender_skill[4]->GetPosition();
				Hoge_Pos2.y += 7.5f;
				m_fontRender_skill[4]->SetPosition(Hoge_Pos2);

				Hoge_Pos2 = m_fontRender_skill[5]->GetPosition();
				Hoge_Pos2.y -= 7.5f;
				m_fontRender_skill[5]->SetPosition(Hoge_Pos2);
			}
			if (SkillTimer == 11 + SkillMoveWait) {
				Hoge_Pos2 = m_fontRender_skill[5]->GetPosition();
				Hoge_Pos2.y += 7.5f;
				m_fontRender_skill[5]->SetPosition(Hoge_Pos2);

				Hoge_Pos2 = m_fontRender_skill[6]->GetPosition();
				Hoge_Pos2.y -= 7.5f;
				m_fontRender_skill[6]->SetPosition(Hoge_Pos2);

			}
			if (SkillTimer == 12 + SkillMoveWait) {
				Hoge_Pos2 = m_fontRender_skill[5]->GetPosition();
				Hoge_Pos2.y += 7.5f;
				m_fontRender_skill[5]->SetPosition(Hoge_Pos2);

				Hoge_Pos2 = m_fontRender_skill[6]->GetPosition();
				Hoge_Pos2.y -= 7.5f;
				m_fontRender_skill[6]->SetPosition(Hoge_Pos2);

			}
			if (SkillTimer == 13 + SkillMoveWait) {
				Hoge_Pos2 = m_fontRender_skill[6]->GetPosition();
				Hoge_Pos2.y += 7.5f;
				m_fontRender_skill[6]->SetPosition(Hoge_Pos2);

				Hoge_Pos2 = m_fontRender_skill[7]->GetPosition();
				Hoge_Pos2.y -= 7.5f;
				m_fontRender_skill[7]->SetPosition(Hoge_Pos2);

			}
			if (SkillTimer == 14 + SkillMoveWait) {
				Hoge_Pos2 = m_fontRender_skill[6]->GetPosition();
				Hoge_Pos2.y += 7.5f;
				m_fontRender_skill[6]->SetPosition(Hoge_Pos2);

				Hoge_Pos2 = m_fontRender_skill[7]->GetPosition();
				Hoge_Pos2.y -= 7.5f;
				m_fontRender_skill[7]->SetPosition(Hoge_Pos2);

			}
			if (SkillTimer == 15 + SkillMoveWait) {
				Hoge_Pos2 = m_fontRender_skill[7]->GetPosition();
				Hoge_Pos2.y += 7.5f;
				m_fontRender_skill[7]->SetPosition(Hoge_Pos2);

				Hoge_Pos2 = m_fontRender_skill[8]->GetPosition();
				Hoge_Pos2.y -= 7.5f;
				m_fontRender_skill[8]->SetPosition(Hoge_Pos2);

			}
			if (SkillTimer == 16 + SkillMoveWait) {
				Hoge_Pos2 = m_fontRender_skill[7]->GetPosition();
				Hoge_Pos2.y += 7.5f;
				m_fontRender_skill[7]->SetPosition(Hoge_Pos2);

				Hoge_Pos2 = m_fontRender_skill[8]->GetPosition();
				Hoge_Pos2.y -= 7.5f;
				m_fontRender_skill[8]->SetPosition(Hoge_Pos2);

			}
			if (SkillTimer == 17 + SkillMoveWait) {
				Hoge_Pos2 = m_fontRender_skill[8]->GetPosition();
				Hoge_Pos2.y += 7.5f;
				m_fontRender_skill[8]->SetPosition(Hoge_Pos2);
			}
			if (SkillTimer == 18 + SkillMoveWait) {
				Hoge_Pos2 = m_fontRender_skill[8]->GetPosition();
				Hoge_Pos2.y += 7.5f;
				m_fontRender_skill[8]->SetPosition(Hoge_Pos2);

				prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
				ss->Init(L"sound/skillget.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

			}
		}

		SkillTimer++;
	}
	else { //決定待ち
		if (SkillMove == false) {
			if (Pad(0).IsTrigger(enButtonA)) {
				SkillMove = true;
				SkillTimer = 0;
				SaveData * savedata = SaveData::GetInstance();
				savedata->SkillGetFlag_Set(SetPos);
			}
		}
		else { //終了
			SkillMove = false;
			SkillTimer = 0;
			Skill_EffectEnd = true;
			//ポジションを戻す
			m_spriteRender_skill[0]->SetPosition({ 0.0f + SkillX_Hosei,-220.0f,0.0f });
			m_spriteRender_skill[1]->SetPosition({ -200.0f + SkillX_Hosei,-220.0f,0.0f });
			m_spriteRender_skill[2]->SetPosition({ -200.0f + SkillX_Hosei,-220.0f,0.0f });
			m_fontRender_skill[0]->SetPosition({ -100.0f + SkillX_Hosei,-172.0f });
			m_fontRender_skill[1]->SetPosition({ -100.0f + SkillX_Hosei,-215.0f });
		}
	}


}
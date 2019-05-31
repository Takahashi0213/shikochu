#include "stdafx.h"
#include "GameResult.h"
#include "GameData.h"
#include "DataBase.h"
#include "SaveData.h"
#include "TransitionMaker.h"

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
	ZankiBonus = gamedata->ZankiBonusKeisan();
	GiriBonus = gamedata->GetGiriCountKeisan();
	ItemBonus = gamedata->GetItemCountKeisan();
	FinalScore = ZankiBonus + GiriBonus + ItemBonus;
	NowStage = gamedata->GetStageNo();
	Point_Count = gamedata->GetPoint();
	Point = Point_Count + FinalScore;

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
		}

		//刻時計が終焉と共鳴せし時、時代の遷移が訪れる（タイマーが終了時間と一致した時にフェイズを次に進めます！）
		if (Hoge_Couneter >= PhaseTimer6) {
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
			CVector2 pos = m_fontRender[5]->GetPosition();
			pos.x -= (SeniMove - SeniMoveHosei);
			if (pos.x < 0.0f) {
				pos.x = 0.0f;
			}
			m_fontRender[5]->SetPosition(pos);
			pos = m_fontRender[6]->GetPosition();
			pos.x -= (SeniMove - SeniMoveHosei);
			if (pos.x < 0.0f) {
				pos.x = 0.0f;
			}
			m_fontRender[6]->SetPosition(pos);

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
			CVector2 pos = m_fontRender[5]->GetPosition();
			pos.y += 5.0f;
			m_fontRender[5]->SetPosition(pos);
			HogePosition1 = 1.0f; //後で不透明度を変更する準備
		}
		else {//下に移動＆フェードアウト！
			CVector2 pos = m_fontRender[5]->GetPosition();
			pos.y -= 40.0f;
			m_fontRender[5]->SetPosition(pos);
			//ここで不透明度を変更
			HogePosition1 -= 0.15f;
			m_fontRender[5]->SetColor({ 1.0f, 1.0f, 1.0f, HogePosition1 });
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
			m_fontRender[6]->SetText(text);
		}
		else {//終了演出

			if (HogePosition1 < 5.0f) {
				CVector2 pos = m_fontRender[6]->GetPosition();
				pos.y += 5.0f;
				m_fontRender[6]->SetPosition(pos);
			}	
			else if (HogePosition1 < 10.0f) {
				CVector2 pos = m_fontRender[6]->GetPosition();
				pos.y -= 5.0f;
				m_fontRender[6]->SetPosition(pos);
				m_fontRender[6]->SetColor({ 1.0f,0.8f,0.1f,1.0f });
			}
			else if (HogePosition1 >= 60.0f && HogePosition1 < 90.0f) {
				CVector2 pos = m_fontRender[6]->GetPosition();
				pos.y += 6.0f;
				m_fontRender[6]->SetPosition(pos);
			}
			else if (HogePosition1 == 90.0f) {
				//10番→サヨナラベイベー
				r = NewGO<prefab::CSpriteRender>(2);
				r->Init(L"sprite/GoodBye.dds", 325.0f, 114.0f);
				MulColor = { 1.0f,1.0f,1.0f,0.0f };
				r->SetMulColor(MulColor);
				r->SetPosition({ 0.0f ,-200.0f,0.0f });
				r->SetScale(CVector3::One);
				m_spriteRender.push_back(r);
			}
			else if (HogePosition1 >= 91.0f && HogePosition1 < 120.0f) {
				//フェード
				MulAlpha += 0.05f;
				MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
				m_spriteRender[10]->SetMulColor(MulColor);
				m_spriteRender[10]->SetScale(CVector3::One);
			}
			else if (HogePosition1 >= 120.0f) {//全て終わったのだよ、全て
				OK_Flag = true;
			}

			HogePosition1 += 1.0f;//ここではカウンタ扱い

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

		if (FinalCount > DeleteTime) {

			TransitionMaker * tm = TransitionMaker::GetInstance();
			tm->TransitionSetting(TransitionMaker::Fade, 60, 30, true);

			//セーブデータを設定する
			SaveData * savedata = SaveData::GetInstance();
			GameData * gamedata = GameData::GetInstance();
			int stage= gamedata->GetStageNo();
			stage -= 1;
			//もしハイスコアが0なら歴代クリア数を加算
			if (savedata->GetHighScore(stage) == 0) {
				if (stage < 2) {
					savedata->PlusClearedStage();
				}
			}
			//ハイスコアならハイスコアに代入
			if (savedata->GetHighScore(stage) < FinalScore) {
				savedata->SetHighScore(stage, FinalScore);
			}
			//モンスター登録処理
			if (stage == 0) {
				savedata->SetMonFlag(0);
				savedata->SetMonFlag(1);
				savedata->SetMonFlag(2);
				savedata->SetMonFlag(3);
				savedata->SetMonFlag(4);
			}
			if (stage == 1) {
				savedata->SetMonFlag(5);
				savedata->SetMonFlag(6);
				savedata->SetMonFlag(7);
				savedata->SetMonFlag(8);
			}
			if (stage == 2) {
				savedata->SetMonFlag(9);
				savedata->SetMonFlag(10);
				savedata->SetMonFlag(11);
				savedata->SetMonFlag(12);
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



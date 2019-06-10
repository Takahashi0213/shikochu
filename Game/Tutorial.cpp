#include "stdafx.h"
#include "Tutorial.h"

#include "GameData.h"
#include "Player.h"
#include "Bunbogu.h"
#include "BackGround.h"
#include "Player_Status.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "GameCamera.h"
#include "UICamera.h"
#include "StageSelect.h"
#include "StarItem.h"
#include "TransitionMaker.h"

Tutorial* Tutorial::m_instance = nullptr;

Tutorial::Tutorial()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;
}

Tutorial::~Tutorial()
{
	for (int i = 0; i < m_spriteRender.size(); i++) {
		DeleteGO(m_spriteRender[i]);
	}
	for (int i = 0; i < m_fontRender.size(); i++) {
		DeleteGO(m_fontRender[i]);
	}

	QueryGOs<Bunbogu>("bun", [&](Bunbogu* bunbogu) {
		bunbogu->SetDeath2();
		return true;
		});
	QueryGOs<StarItem>("Item", [&](StarItem* staritem) {
		staritem->DeleteItem2();
		return true;
		});

	DeleteGOs("Gamecamera");
	DeleteGOs("Status");
	DeleteGOs("WaveManager");
	DeleteGOs("BackGround");
	DeleteGOs("Player_Status");
	DeleteGOs("LevelSet");
	DeleteGOs("Sky");
	DeleteGOs("L_Light");

	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;

	DeleteGOs("Bug");

	NewGO<UICamera>(0, "UICamera");
	NewGO<StageSelect>(0);
	//輝度を戻す。
	postEffect::Tonemap().SetLuminance(0.4);

}
bool Tutorial::Start() {

	//準備
	EnableSpecialLigRange();

	GameData * gamedata = GameData::GetInstance();
	gamedata->SetGameMode(GameData::Tutorial);
	gamedata->GameDataReset();
	DeleteGOs("UICamera");

	NewGO<Player>(0, "Bug");
	NewGO<Player_Status>(0, "Status");
	NewGO<BackGround>(0, "BackGround");
	NewGO<GameCamera>(0, "Gamecamera");

	//背景を表示
	BackGround * background = BackGround::GetInstance();
	background->StageMaker(-100);

	prefab::CSky* sky = NewGO<prefab::CSky>(0, "Sky");
	sky->SetScale({ 20000.0f, 20000.0f, 20000.0f });
	sky->SetEmissionColor({ 6.1f, 6.1f, 8.1f });
	LightManager().SetAmbientLight({ 100.1f,100.1f, 100.1f });

	m_directionLig = NewGO<prefab::CDirectionLight>(0, "L_Light");
	m_directionLig->SetColor({ 900.0f, 900.0f, 1000.0f, 1.0f });
	CVector3 ligDir = { 1, -1, 1 };
	ligDir.Normalize();
	m_directionLig->SetDirection(ligDir);
	GraphicsEngine().GetShadowMap().SetLightDirection(ligDir);



	//0番→枠
	r = NewGO<prefab::CSpriteRender>(5);
	r->Init(L"sprite/MemoWaku.dds", 750.0f, 366.0f*1.5f);
	r->SetPosition({ 0.0f ,M_PosY - M_YHosei,0.0f });
	MulColor = { 1.0f,1.0f,1.0f,1.0f };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//1番→Aボタン
	r = NewGO<prefab::CSpriteRender>(7);
	r->Init(L"sprite/A_Button.dds", 50.0f, 50.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetPosition({ 250.0f,-150.0f,0.0f });
	r->SetMulColor(MulColor);
	r->SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRender.push_back(r);
	//2番→矢印
	r = NewGO<prefab::CSpriteRender>(7);
	r->Init(L"sprite/yazirusi.dds", 100.0f, 100.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetPosition({ -500.0f,-180.0f,0.0f });
	r->SetMulColor(MulColor);
	r->SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRender.push_back(r);

	//メッセージ 0番
	f = NewGO<prefab::CFontRender>(5);
	//表示
	text[256];
	//おわ
	swprintf(text, L"シコウチュウのせかいへようこそ！");
	//はい。
	f->SetText(text);
	f->SetPosition({ -300.0f,M_PosY2 - M_YHosei });
	f->SetScale(1.0f);
	f->SetColor({ 0.2f,1.0f,0.2f,1.0f });
	f->SetPivot({ 0.0f,1.0f });
	m_fontRender.push_back(f);
	//メッセージ 1番
	f = NewGO<prefab::CFontRender>(5);
	//表示
	text[256];
	//おわ
	swprintf(text, L"じゅうじキー か スライドパッド でいどう");
	//はい。
	f->SetText(text);
	f->SetPosition({ 0.0f,-250.0f });
	f->SetScale(1.0f);
	f->SetColor({ 1.0f,1.0f,1.0f,0.0f });
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);
	return true;
}

void Tutorial::Update() {

	m_tonemapDisableTimer -= GameTime().GetFrameDeltaTime();
	if (m_tonemapDisableTimer <= 0.0f) {
		m_tonemapDisableTimer = 0.0f;
	}
	if (m_tonemapDisableTimer > 0.0f) {
		GraphicsEngine().GetTonemap().Reset();
	}

	switch (Tutorialscene) {

	case scene1://最初
	{
		if (PushCount == 0) {//準備

			if (Timer > 20) {

				CVector3 pos = m_spriteRender[0]->GetPosition();
				pos.y -= M_PosY / 20.0f;
				m_spriteRender[0]->SetPosition(pos);
				CVector2 pos2 = m_fontRender[0]->GetPosition();
				pos2.y -= M_PosY / 20.0f;
				m_fontRender[0]->SetPosition(pos2);

			}

			Timer++;

			if (Timer == 40) {
				PushCount++;
				Timer = 0;
				m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
			}
		}
		else if (PushCount == 1) {
			if (Pad(0).IsTrigger(enButtonA)) {
				text[256];
				//おわ
				swprintf(text, L"じゅうじキー か スライドパッド で\nいどう できます");
				//はい。
				m_fontRender[0]->SetText(text);

				PushCount++;
			}

		}
		else if (PushCount == 2) {
			if (Pad(0).IsTrigger(enButtonA)) {
				PushCount++;
			}

		}
		else if (PushCount == 3) {
			if (Timer > 20) {

				CVector3 pos = m_spriteRender[0]->GetPosition();
				pos.y -= M_PosY / 20.0f;
				m_spriteRender[0]->SetPosition(pos);
				CVector2 pos2 = m_fontRender[0]->GetPosition();
				pos2.y -= M_PosY / 20.0f;
				m_fontRender[0]->SetPosition(pos2);

			}

			Timer++;

			if (Timer == 40) {
				PushCount++;
				Timer = 0;
			}
		}
		else if (PushCount == 4) {//終了処理
			m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
			m_spriteRender[0]->SetPosition({ 0.0f ,M_PosY - M_YHosei,0.0f });
			m_fontRender[0]->SetPosition({ -300.0f,M_PosY2 - M_YHosei });
			m_fontRender[1]->SetColor({ 1.0f,1.0f,1.0f,1.0f });
			GameData * gamedata = GameData::GetInstance();
			gamedata->SetGameMode(GameData::Battle2D_Mode);
			Tutorialscene = scene1_Play;
			text[256];
			//おわ
			swprintf(text, L"とつぜんしんでしまって\nおどろきましたか？");
			//はい。
			m_fontRender[0]->SetText(text);
			PushCount = 0;
		}

		break;
	}
	case scene1_Play://移動
	{
		GameData * gamedata = GameData::GetInstance();
		int zanki = gamedata->GetZanki();
		if (zanki == 49) {
			gamedata->SetGameMode(GameData::Tutorial);
			Tutorialscene = scene2;
			m_fontRender[1]->SetColor({ 1.0f,1.0f,1.0f,0.0f });
		}

		break;
	}

	case scene2://敵だ
	{
		if (PushCount == 0) {//準備

			if (Timer > 20) {

				CVector3 pos = m_spriteRender[0]->GetPosition();
				pos.y -= M_PosY / 20.0f;
				m_spriteRender[0]->SetPosition(pos);
				CVector2 pos2 = m_fontRender[0]->GetPosition();
				pos2.y -= M_PosY / 20.0f;
				m_fontRender[0]->SetPosition(pos2);

			}

			Timer++;

			if (Timer == 40) {
				m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
				PushCount++;
				Timer = 0;
			}
		}
		else if (PushCount == 1) {
			if (Pad(0).IsTrigger(enButtonA)) {
				m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

				text[256];
				//おわ
				swprintf(text, L"ひだりにあるのがじゅみょうです");
				//はい。
				m_fontRender[0]->SetText(text);

				PushCount++;
			}
		}
		else if (PushCount == 2) {
			if (Pad(0).IsTrigger(enButtonA)) {
				text[256];
				//おわ
				swprintf(text, L"じかんがたつと、どんどん\nへっていき...");
				//はい。
				m_fontRender[0]->SetText(text);

				PushCount++;
			}
		}
		else if (PushCount == 3) {
			if (Pad(0).IsTrigger(enButtonA)) {
				m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
				PushCount++;
			}
		}
		else if (PushCount == 4) {

			Player * player = Player::GetInstance();
			player->SetLife(1);

			if (Timer == 60) {
				text[256];
				//おわ
				swprintf(text, L"なくなるとしんでしまいます");
				//はい。
				m_fontRender[0]->SetText(text);
				m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

				Timer = -1;
				PushCount++;
			}

			Timer++;
		}
		else if (PushCount == 5) {
			if (Pad(0).IsTrigger(enButtonA)) {
				m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
				PushCount++;
			}
		}
		else if (PushCount == 6) {

			Player * player = Player::GetInstance();
			player->SetLife(1);

			if (Timer == 40) {
				m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });

				text[256];
				//おわ
				swprintf(text, L"でもだいじょうぶ！\nシコウチュウ にはたくさんの\nなかまがいます");
				//はい。
				m_fontRender[0]->SetText(text);
				m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

				Timer = -1;
				PushCount++;
			}

			Timer++;
		}
		else if (PushCount == 7) {
			if (Pad(0).IsTrigger(enButtonA)) {
				//セット
				Player * player = Player::GetInstance();
				player->SetLife(-100);
				GameData * gamedata = GameData::GetInstance();
				gamedata->SetZanki(-1);//残機減少

				m_spriteRender[2]->SetPosition({ -350.0f,250.0f,0.0f });
				m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

				text[256];
				//おわ
				swprintf(text, L"ひだりうえの「ざんき」があるかぎり、\nなんどでも あたらしいシコウチュウが\nたたかってくれます");
				//はい。
				m_fontRender[0]->SetText(text);

				PushCount++;
			}
		}
		else if (PushCount == 8) {
			if (Pad(0).IsTrigger(enButtonA)) {
				//ブンローグ召喚
				Bunbogu* bun = NewGO<Bunbogu>(0, "bun");
				bun->SetPosition({ 500.0f,0.0f,500.0f });
				m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
				GameData * gamedata = GameData::GetInstance();
				gamedata->EnemyCounterSet(1);

				m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,0.0f });
				m_spriteRender[0]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
				m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
				PushCount++;
			}
		}
		else if (PushCount == 9) {

			if (Timer == 60) {
				text[256];
				//おわ
				swprintf(text, L"てきがあらわれました！！");
				//はい。
				m_fontRender[0]->SetText(text);
				m_fontRender[0]->SetColor({ 0.2f,1.0f,0.2f,1.0f });
				m_spriteRender[0]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
				m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

				Timer = -1;
				PushCount++;
			}

			Timer++;
		}
		else if (PushCount == 10) {
			if (Pad(0).IsTrigger(enButtonA)) {
				text[256];
				//おわ
				swprintf(text, L"シコウチュウは Aボタン で\n「ダッシュ」ができます");
				//はい。
				m_fontRender[0]->SetText(text);

				PushCount++;
			}
		}
		else if (PushCount == 11) {
			if (Pad(0).IsTrigger(enButtonA)) {
				text[256];
				//おわ
				swprintf(text, L"ダッシュしながら\nてきにたいあたりすることで\nたおすことができます");
				//はい。
				m_fontRender[0]->SetText(text);

				PushCount++;
			}
		}
		else if (PushCount == 12) {
			if (Pad(0).IsTrigger(enButtonA)) {
				text[256];
				//おわ
				swprintf(text, L"ただし てきがこうげきしているときに\nたいあたりしてもたおせないので\nちゅういしてくださいね");
				//はい。
				m_fontRender[0]->SetText(text);

				PushCount++;
			}
		}
		else if (PushCount == 13) {
			if (Pad(0).IsTrigger(enButtonA)) {
				text[256];
				//おわ
				swprintf(text, L"シコウチュウのまわりにある\nあかいてん はてきのほうこうを\nしめしています");
				//はい。
				m_fontRender[0]->SetText(text);

				PushCount++;
			}
		}
		else if (PushCount == 14) {
			if (Pad(0).IsTrigger(enButtonA)) {
				text[256];
				//おわ
				swprintf(text, L"それでは、てきをたおしてみましょう！");
				//はい。
				m_fontRender[0]->SetText(text);

				PushCount++;
			}
		}
		else if (PushCount == 15) {
			if (Pad(0).IsTrigger(enButtonA)) {
				PushCount++;
				text[256];
				//おわ
				swprintf(text, L"Aボタンでダッシュ しながら てきにとつげき");
				//はい。
				m_fontRender[1]->SetText(text);
			}

		}
		else if (PushCount == 16) {
			if (Timer > 20) {

				CVector3 pos = m_spriteRender[0]->GetPosition();
				pos.y -= M_PosY / 20.0f;
				m_spriteRender[0]->SetPosition(pos);
				CVector2 pos2 = m_fontRender[0]->GetPosition();
				pos2.y -= M_PosY / 20.0f;
				m_fontRender[0]->SetPosition(pos2);

			}

			Timer++;

			if (Timer == 40) {
				PushCount++;
				Timer = 0;
			}
		}
		else if (PushCount == 17) {//終了処理
			m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
			m_spriteRender[0]->SetPosition({ 0.0f ,M_PosY - M_YHosei,0.0f });
			m_fontRender[0]->SetPosition({ -300.0f,M_PosY2 - M_YHosei });
			m_fontRender[1]->SetColor({ 1.0f,1.0f,1.0f,1.0f });
			GameData * gamedata = GameData::GetInstance();
			gamedata->SetGameMode(GameData::Battle2D_Mode);
			Tutorialscene = scene2_Play;
			text[256];
			//おわ
			swprintf(text, L"おみごとです！！");
			//はい。
			m_fontRender[0]->SetText(text);
			PushCount = 0;
		}


		break;
	}
	case scene2_Play://バトル！
	{
			GameData * gamedata = GameData::GetInstance();
			int enemy = gamedata->GetEnemyCounter();
			if (enemy == 0) {
				if (Timer == 60) {
					Timer = -1;
					gamedata->SetGameMode(GameData::Tutorial);
					Tutorialscene = scene3;
					m_fontRender[1]->SetColor({ 1.0f,1.0f,1.0f,0.0f });
				}

				Timer++;
			}

			break;
		}

	case scene3://流星ダッシュ
	{
			if (PushCount == 0) {//準備

				if (Timer > 40) {

					CVector3 pos = m_spriteRender[0]->GetPosition();
					pos.y -= M_PosY / 20.0f;
					m_spriteRender[0]->SetPosition(pos);
					CVector2 pos2 = m_fontRender[0]->GetPosition();
					pos2.y -= M_PosY / 20.0f;
					m_fontRender[0]->SetPosition(pos2);

				}

				Timer++;

				if (Timer == 60) {
					PushCount++;
					Timer = 0;
					m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
				}
			}
			else if (PushCount == 1) {
				if (Pad(0).IsTrigger(enButtonA)) {
					text[256];
					//おわ
					swprintf(text, L"そうそう、\nすでにごぞんじかもしれませんが...");
					//はい。
					m_fontRender[0]->SetText(text);

					PushCount++;
				}
			}
			else if (PushCount == 2) {
				if (Pad(0).IsTrigger(enButtonA)) {
					text[256];
					//おわ
					swprintf(text, L"シコウチュウ はしぬと\nほし になります");
					//はい。
					m_fontRender[0]->SetText(text);

					PushCount++;
				}
			}
			else if (PushCount == 3) {
				if (Pad(0).IsTrigger(enButtonA)) {
					text[256];
					//おわ
					swprintf(text, L"そのほしはくらやみをてらし、\nあなたをたすけてくれるでしょう");
					//はい。
					m_fontRender[0]->SetText(text);

					PushCount++;
				}
			}
			else if (PushCount == 4) {
				if (Pad(0).IsTrigger(enButtonA)) {
					text[256];
					//おわ
					swprintf(text, L"しんでしまったからといって\nむだになることはありません");
					//はい。
					m_fontRender[0]->SetText(text);

					PushCount++;
				}
			}
			else if (PushCount == 5) {
				if (Pad(0).IsTrigger(enButtonA)) {
					//アイテム出現
					StarItem* ITEM = NewGO<StarItem>(0, "Item");
					ITEM->SetPosition({ 0.0f,0.0f,80.0f });
					ITEM = NewGO<StarItem>(0, "Item");
					ITEM->SetPosition({ 120.0f,0.0f,120.0f });
					ITEM = NewGO<StarItem>(0, "Item");
					ITEM->SetPosition({ -120.0f,0.0f,120.0f });
					ITEM = NewGO<StarItem>(0, "Item");
					ITEM->SetPosition({ 120.0f,0.0f,-120.0f });
					ITEM = NewGO<StarItem>(0, "Item");
					ITEM->SetPosition({ -120.0f,0.0f,-120.0f });
					m_spriteRender[2]->SetPosition({ 100.0f,150.0f,0.0f });
					m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

					m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,0.0f });
					m_spriteRender[0]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
					m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
					PushCount++;
				}
			}
			else if (PushCount == 6) {

				if (Timer == 120) {
					text[256];
					//おわ
					swprintf(text, L"ステージには「スターボックス」という\nアイテムがおちています");
					//はい。
					m_fontRender[0]->SetText(text);
					m_fontRender[0]->SetColor({ 0.2f,1.0f,0.2f,1.0f });
					m_spriteRender[0]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
					m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
					m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });

					Timer = -1;
					PushCount++;
				}

				Timer++;
			}
			else if (PushCount == 7) {
				if (Pad(0).IsTrigger(enButtonA)) {
					m_spriteRender[2]->SetPosition({ -450.0f,-120.0f,0.0f });
					m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

					text[256];
					//おわ
					swprintf(text, L"スターボックスをひろうと\n「りゅうせいゲージ」が\nじょうしょうします");
					//はい。
					m_fontRender[0]->SetText(text);

					PushCount++;
				}
			}
			else if (PushCount == 8) {
				if (Pad(0).IsTrigger(enButtonA)) {
					text[256];
					//おわ
					swprintf(text, L"じかんけいかでも、\nりゅうせいゲージはじょうしょうします");
					//はい。
					m_fontRender[0]->SetText(text);

					PushCount++;
				}
			}
			else if (PushCount == 9) {
				if (Pad(0).IsTrigger(enButtonA)) {
					m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });

					text[256];
					//おわ
					swprintf(text, L"シコウチュウのまわりに\nスターボックスを5つおきました");
					//はい。
					m_fontRender[0]->SetText(text);

					PushCount++;
				}
			}
			else if (PushCount == 10) {
				if (Pad(0).IsTrigger(enButtonA)) {
					text[256];
					//おわ
					swprintf(text, L"さっそくひろってみましょう！");
					//はい。
					m_fontRender[0]->SetText(text);

					PushCount++;
				}
			}
			else if (PushCount == 11) {
				if (Pad(0).IsTrigger(enButtonA)) {
					PushCount++;
					text[256];
					//おわ
					swprintf(text, L"スターボックスをひろってみよう");
					//はい。
					m_fontRender[1]->SetText(text);
				}

			}
			else if (PushCount == 12) {
				if (Timer > 20) {

					CVector3 pos = m_spriteRender[0]->GetPosition();
					pos.y -= M_PosY / 20.0f;
					m_spriteRender[0]->SetPosition(pos);
					CVector2 pos2 = m_fontRender[0]->GetPosition();
					pos2.y -= M_PosY / 20.0f;
					m_fontRender[0]->SetPosition(pos2);

				}

				Timer++;

				if (Timer == 40) {
					PushCount++;
					Timer = 0;
				}
			}
			else if (PushCount == 13) {//終了処理
				m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
				m_spriteRender[0]->SetPosition({ 0.0f ,M_PosY - M_YHosei,0.0f });
				m_fontRender[0]->SetPosition({ -300.0f,M_PosY2 - M_YHosei });
				m_fontRender[1]->SetColor({ 1.0f,1.0f,1.0f,1.0f });
				GameData * gamedata = GameData::GetInstance();
				gamedata->SetGameMode(GameData::Battle2D_Mode);
				Tutorialscene = scene3_Play;
				text[256];
				//おわ
				swprintf(text, L"りゅうせいダッシュちゅうは\nむてきになり てきをたおしても\nじぶんはたおれません");
				//はい。
				m_fontRender[0]->SetText(text);
				PushCount = 0;
			}

			break;
		}

	case scene3_Play://流星ダッシュ
	{
			GameData * gamedata = GameData::GetInstance();
			int star = gamedata->GetStar_Power();

			if (StarFlag == false) {
				if (star == gamedata->GetMAXStar_Power()) {
					text[256];
					//おわ
					swprintf(text, L"Yボタンで りゅうせいダッシュ！");
					//はい。
					m_fontRender[1]->SetText(text);

					StarFlag = true;
				}
			}
			else if (StarFlag == true) {
				if (star != gamedata->GetMAXStar_Power()) {
					if (Timer == 120) {
						Timer = -1;
						gamedata->SetGameMode(GameData::Tutorial);
						Tutorialscene = scene4;
						m_fontRender[1]->SetColor({ 1.0f,1.0f,1.0f,0.0f });
					}
					Timer++;
				}

			}

			break;
				}

	case scene4://おわり
	{
		if (PushCount == 0) {//準備

			if (Timer > 20) {

				CVector3 pos = m_spriteRender[0]->GetPosition();
				pos.y -= M_PosY / 20.0f;
				m_spriteRender[0]->SetPosition(pos);
				CVector2 pos2 = m_fontRender[0]->GetPosition();
				pos2.y -= M_PosY / 20.0f;
				m_fontRender[0]->SetPosition(pos2);

			}

			Timer++;

			if (Timer == 40) {
				PushCount++;
				Timer = 0;
				m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
			}
		}
		else if (PushCount == 1) {
			if (Pad(0).IsTrigger(enButtonA)) {
				text[256];
				//おわ
				swprintf(text, L"たくさんのてきが かたまっている\nばしょにつかうと、\nまとめてたおせますよ！");
				//はい。
				m_fontRender[0]->SetText(text);

				Tutorialscene = END;
				PushCount = 0;
			}
		}

		break;
	}

	case END://さいごに
	{
		if (PushCount == 0) {//準備

			if (GameOverFlag == false) {
				PushCount++;
				Timer = -1;
				m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
			}

			if (Timer > 20) {

				CVector3 pos = m_spriteRender[0]->GetPosition();
				pos.y -= M_PosY / 20.0f;
				m_spriteRender[0]->SetPosition(pos);
				CVector2 pos2 = m_fontRender[0]->GetPosition();
				pos2.y -= M_PosY / 20.0f;
				m_fontRender[0]->SetPosition(pos2);

			}

			Timer++;

			if (Timer == 40) {
				PushCount++;
				Timer = 0;
				m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
			}
		}
		else if (PushCount == 1) {
			if (Pad(0).IsTrigger(enButtonA)) {
				text[256];
				//おわ
				swprintf(text, L"たくさんのせつめいがありましたが\n「ならうよりなれろ」です");
				//はい。
				m_fontRender[0]->SetText(text);

				PushCount++;
			}

		}
		else if (PushCount == 2) {
			if (Pad(0).IsTrigger(enButtonA)) {
				text[256];
				//おわ
				swprintf(text, L"ぜひ あなたのちからで\nシコウチュウをあたらしいせかいへ\nつれていってあげてくださいね");
				//はい。
				m_fontRender[0]->SetText(text);

				PushCount++;
			}

		}
		else if (PushCount == 3) {
			if (Pad(0).IsTrigger(enButtonA)) {
				text[256];
				//おわ
				swprintf(text, L"おつかれさまでした！");
				//はい。
				m_fontRender[0]->SetText(text);

				PushCount++;
			}

		}
		else if (PushCount == 4) {
			if (Pad(0).IsTrigger(enButtonA)) {
				PushCount++;
			}

		}
		else if (PushCount == 5) {

			//終了
			if (Timer == 0) {
				TransitionMaker * tm = TransitionMaker::GetInstance();
				tm->TransitionSetting(TransitionMaker::Fade, 12, 0, false);
			}

			if (Timer == 60) {
				TransitionMaker * tm = TransitionMaker::GetInstance();
				tm->TransitionSetting(TransitionMaker::Fade, 12, 12, true);
				DeleteGO(this);
			}

			Timer++;
		}

		break;
	}

	}

	//ゲームオーバーなら終了
	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();
	if (mode == GameData::GameOver) {
		gamedata->SetGameMode(GameData::Tutorial);
		Tutorialscene = END;
		Timer = 0;
		GameOverFlag = true;
		text[256];
		//おわ
		swprintf(text, L"ざんきがなくなったので\nチュートリアルはおしまいです");
		//はい。
		m_fontRender[0]->SetText(text);
		m_fontRender[1]->SetColor({ 1.0f,1.0f,1.0f,0.0f });

	}

	//ボタンプッシュ
	if (A_Timer == 24) {
		m_spriteRender[1]->Init(L"sprite/A_Button2.dds", 50.0f, 50.0f);
	}
	else if (A_Timer == 48) {
		A_Timer = -1;
		m_spriteRender[1]->Init(L"sprite/A_Button.dds", 50.0f, 50.0f);
	}
	A_Timer++;

	//矢印ムーブ
	if (YazirusiTimer == 12) {
		YazirusiFlag = true;
	}
	else if (YazirusiTimer == 24) {
		YazirusiFlag = false;
		YazirusiTimer = -1;
	}
	if (YazirusiFlag == false) {
		CVector3 pos = m_spriteRender[2]->GetPosition();
		pos.x += 1.0f;
		m_spriteRender[2]->SetPosition(pos);
	}
	else if (YazirusiFlag == true) {
		CVector3 pos = m_spriteRender[2]->GetPosition();
		pos.x -= 1.0f;
		m_spriteRender[2]->SetPosition(pos);
	}
	
	YazirusiTimer++;
}

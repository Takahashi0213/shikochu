#include "stdafx.h"
#include "GameData.h"
#include "Player_Status.h"
#include "Player.h"
#include "SaveData.h"
#include "SkillData.h"

Player_Status* Player_Status::m_instance = nullptr;

Player_Status::Player_Status()
{
	if (m_instance != nullptr) {
		std::abort(); //すでにプレイヤーが出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

}


Player_Status::~Player_Status()
{
	for (int i = 0; i < m_spriteRender.size(); i++) {
		DeleteGO(m_spriteRender[i]);
	}
	for (int i = 0; i < m_spriteRenderBar.size(); i++) {
		DeleteGO(m_spriteRenderBar[i]);
	}
	DeleteGO(m_fontRender);

	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;

}

bool Player_Status::Start() {

	GameData * gamedata = GameData::GetInstance();
	BeforeZanki = gamedata->GetZanki();

	//流星ゲージ土台 0
	prefab::CSpriteRender* r = NewGO<prefab::CSpriteRender>(7);
	r->Init(L"sprite/StarBar_base.dds", 20.0f, 300.0f);
	CVector3 Position = { -550.0f, -10.0f, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	m_spriteRender.push_back(r);
	//流星ゲージ 1
	r = NewGO<prefab::CSpriteRender>(7);
	r->Init(L"sprite/StarBar.dds", 20.0f, 300.0f);
	Position = { -550.0f, -160.0f, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	m_spriteRender.push_back(r);
	//流星ゲージ上部分 2
	r = NewGO<prefab::CSpriteRender>(8);
	r->Init(L"sprite/StarBarUe.dds", 30.0f, 330.0f);
	Position = { -550.0f, -28.0f, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	m_spriteRender.push_back(r);

	//寿命土台 3
	r = NewGO<prefab::CSpriteRender>(7);
	r->Init(L"sprite/LifeBar_base.dds", 120.0f, 480.0f);
	Position = { -600.0f, -20.0f, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	m_spriteRender.push_back(r);
	//バー 4
	r = NewGO<prefab::CSpriteRender>(7);
	r->Init(L"sprite/LifeBar.dds", 120.0f, 480.0f);
	Position = { -600.0f, -215.0f, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	m_spriteRender.push_back(r);
	//寿命白 0
	prefab::CSpriteRender* rr = NewGO<prefab::CSpriteRender>(7);
	rr->Init(L"sprite/LifeBar_white.dds", 120.0f, 480.0f);
	Position = { -600.0f, 170.0f, 1.0f };//座標
	rr->SetPosition(Position);//座標を反映
	m_spriteRenderBar.push_back(rr);
	//寿命黒 1
	rr = NewGO<prefab::CSpriteRender>(7);
	rr->Init(L"sprite/LifeBar_base.dds", 120.0f, 480.0f);
	Position = { -600.0f, 170.0f, 1.0f };//座標
	rr->SetPosition(Position);//座標を反映
	rr->SetScale({ 1.0f,0.0f,1.0f });//拡大率を反映
	m_spriteRenderBar.push_back(rr);
	//寿命上部分 5
	r = NewGO<prefab::CSpriteRender>(8);
	r->Init(L"sprite/LifeBarUe.dds", 120.0f, 480.0f);
	Position = { -600.0f, -20.0f, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	m_spriteRender.push_back(r);

	//ソウルアイコン 6
	r = NewGO<prefab::CSpriteRender>(8);
	r->Init(L"sprite/soulIC.dds", 100.0f, 100.0f);
	Position = { -600.0f, -220.0f, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	m_spriteRender.push_back(r);
	//残機アンダー 7
	r = NewGO<prefab::CSpriteRender>(8);
	r->Init(L"sprite/Zanki.dds", 300.0f, 300.0f);
	Position = { -550.0f, 280.0f, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	m_spriteRender.push_back(r);

	//ゲージマックスアイコン 8(解雇)
	r = NewGO<prefab::CSpriteRender>(8);
	r->Init(L"sprite/starMax.dds", 150.0f, 100.0f);
	Position = { -480.0f, -150.0f, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	r->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
	m_spriteRender.push_back(r);

	//ボーナスアイコン 9
	r = NewGO<prefab::CSpriteRender>(8);
	r->Init(L"sprite/KikoIC_Full.dds", 200.0f, 200.0f);
	Position = { 640.0f, -50.0f, 1.0f };//座標
	r->SetPosition(Position);//座標を反映
	r->SetMulColor({ 1.0f,1.0f,1.0f,Kiko_Alpha });
	m_spriteRender.push_back(r);

	//YスキルIC 10
	r = NewGO<prefab::CSpriteRender>(5);
	r->Init(L"sprite/skillicon_1.dds", 150.0f, 100.0f);
	r->SetPosition({ -510.0f,105.0f ,0.0f });//座標を反映
	r->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	r->SetScale({ SkillScale,SkillScale, SkillScale });
	m_spriteRender.push_back(r);

	//Yスキル枠 11
	r = NewGO<prefab::CSpriteRender>(6);
	r->Init(L"sprite/skilliconWakuY.dds", 190.0f, 100.0f);
	r->SetPosition({ -510.0f,105.0f ,0.0f });//座標を反映
	r->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	r->SetScale({ SkillScale,SkillScale, SkillScale });
	m_spriteRender.push_back(r);

	//XスキルIC 12
	r = NewGO<prefab::CSpriteRender>(5);
	r->Init(L"sprite/skillicon_10.dds", 150.0f, 100.0f);
	r->SetPosition({ -515.0f,50.0f ,0.0f });//座標を反映
	r->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	r->SetScale({ SkillScale,SkillScale, SkillScale });
	m_spriteRender.push_back(r);

	//Xスキル枠 13
	r = NewGO<prefab::CSpriteRender>(6);
	r->Init(L"sprite/skilliconWakuX.dds", 190.0f, 100.0f);
	r->SetPosition({ -515.0f,50.0f ,0.0f });//座標を反映
	r->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	r->SetScale({ SkillScale,SkillScale, SkillScale });
	m_spriteRender.push_back(r);

	//黄色のアレY 14
	r = NewGO<prefab::CSpriteRender>(7);
	r->Init(L"sprite/Yellow.dds", 20.0f, 4.0f);
	r->SetPosition({ -550.0f, 0.0f, 1.0f });//座標を反映
	r->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	r->SetScale({ 1.0f,1.0f, 1.0f });
	m_spriteRender.push_back(r);

	//青色のアレX 15
	r = NewGO<prefab::CSpriteRender>(7);
	r->Init(L"sprite/Blue.dds", 20.0f, 4.0f);
	r->SetPosition({ -550.0f, -156.0f, 1.0f });//座標を反映
	r->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	r->SetScale({ 1.0f,1.0f, 1.0f });
	m_spriteRender.push_back(r);

	///////ここからテキスト//////
	//残機文字
	m_fontRender = NewGO<prefab::CFontRender>(8);
	m_fontRender->SetPivot({ 0.5f,0.5f });

	//ボーナス文字
	m_fontRender_bonus = NewGO<prefab::CFontRender>(8);
	//表示
	wchar_t text[256];
	//おわ
	swprintf(text, L"BONUS!");
	//はい。
	m_fontRender_bonus->SetText(text);
	m_fontRender_bonus->SetPosition({ 640.0f, -130.0f });
	m_fontRender_bonus->SetPivot({ 0.5f,0.5f });
	m_fontRender_bonus->SetScale(0.8f);
	m_fontRender_bonus->SetColor({ 1.0f,0.5f,0.0f,Kiko_Alpha });

	SkillSetUp();

	return true;

}

void Player_Status::Update() {

	//準備
	CVector3 LifeScale = CVector3::Zero;
	CVector3 StarScale = CVector3::Zero;
	Player * player = Player::GetInstance();
	GameData * gamedata = GameData::GetInstance();

	//寿命ゲージを動かす
	float DEF_Life = (float)gamedata->GetDEF_Life();
	float NOW_Life = (float)player->GetLife();

	//寿命の拡大率を計算
	float LifeY = NOW_Life / DEF_Life;
	if (LifeY == 1.0f) {//寿命がマンタン
		m_spriteRenderBar[1]->SetPivot(LifePivot);
		m_spriteRenderBar[1]->SetScale({ 1.0f,0.0f,1.0f });
	}
	else if (LifeY == 0.0f) {//寿命がゼロ
		m_spriteRenderBar[1]->SetPivot(LifePivot);
		m_spriteRenderBar[1]->SetScale({ 1.0f,1.0f,1.0f });
	}
	LifeY = 1.0f - LifeY;
	//LifeY *= 480.0f;
	LifeScale = { 1.0f,LifeY,1.0f };
	//寿命バーの色が変わる基準は？
	float RED_Life = DEF_Life / 2.0f;
	//寿命バーの色変え
	if (NOW_Life < RED_Life) {
		LifeColor = { 255.0f,0.5f,0.5f,1.0f };
	}else {
		LifeColor = { 1.0f,1.0f,1.0f,1.0f };
	}

	m_spriteRenderBar[0]->SetPivot(LifePivot);
	m_spriteRenderBar[0]->SetScale(LifeScale);	
	m_spriteRender[4]->SetPivot(LifePivot2);
	m_spriteRender[4]->SetMulColor(LifeColor);

	CVector3 Ue_Gage = m_spriteRenderBar[1]->GetScale();
	CVector3 Sita_Gage = m_spriteRenderBar[0]->GetScale();

	if (player->GetA_DashFlag() == true) {//Aダッシュ中なら減少させる
		WhiteGage = true;

			Ue_Gage.y += 0.01f;
			if (Ue_Gage.y > Sita_Gage.y) {
				Ue_Gage.y = Sita_Gage.y;
			}

	}
	else {
		WhiteGage = false;
		Ue_Gage.y = Sita_Gage.y;
	}
	m_spriteRenderBar[1]->SetPivot(LifePivot);
	m_spriteRenderBar[1]->SetScale(Ue_Gage);

	//流星ゲージを動かす
	float NOW_StarPower = (float)gamedata->GetStar_Power();
	float DEF_StarPower = (float)gamedata->GetMAXStar_Power();
	//色が変わるボーダーを設定（一番小さい消費値がボーダー）
	int Star_border = 100;
	if (Skill_Data[SkillNoY].StarPower > 0) {
		if (Skill_Data[SkillNoY].StarPower < Star_border) {
			Star_border = Skill_Data[SkillNoY].StarPower;
		}
	}
	if (Skill_Data[SkillNoX].StarPower > 0) {
		if (Skill_Data[SkillNoX].StarPower < Star_border) {
			Star_border = Skill_Data[SkillNoX].StarPower;
		}
	}

	//ゲージの拡大率を計算
	float StarY = NOW_StarPower / DEF_StarPower;
	StarScale = { 1.0f,StarY,1.0f };
	//流星バーの色変え
	if ((int)NOW_StarPower >= Star_border) {
		StarColor = { 1.0f,1.0f,1.0f,1.0f };
	}
	else {
		StarColor = { 0.5f,0.5f,255.0f,1.0f };
	}

	m_spriteRender[1]->SetPivot(StarPivot);
	m_spriteRender[1]->SetScale(StarScale);
	m_spriteRender[1]->SetMulColor(StarColor);
	
	//ゲージ到達で効果音

	//Yスキル
	if (SkillNoY > -1) { //セットされているか
		if (Skill_Data[SkillNoY].StarPower > 0) { //パッシブスキルでないか
			if (NOW_StarPower >= Skill_Data[SkillNoY].StarPower) {
				if (StarMaxSE == false) { //SEフラグチェック
					prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
					ss->Init(L"sound/StarGageMAX.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);

					StarMaxSE = true;
				}
			}
			else {
				StarMaxSE = false;
			}
		}
	}

	//Xスキル
	if (SkillNoX > -1) { //セットされているか
		if (Skill_Data[SkillNoX].StarPower > 0) { //パッシブスキルでないか
			if (NOW_StarPower >= Skill_Data[SkillNoX].StarPower) {
				if (StarMaxSE2 == false) { //SEフラグチェック
					prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
					ss->Init(L"sound/StarGageMAX.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);

					StarMaxSE2 = true;
				}
			}
			else {
				StarMaxSE2 = false;
			}
		}
	}

	//流星ゲージに応じて見えたり見えなかったりしろ
	/*
	if (StarMaxFlag == true) {
		//見える＆点滅する
		if (StarMaxColorFlag == false) {
			StarMaxColor += 0.05f;
			StarMaxScale += 0.01f;
			if (StarMaxColor > 2.0f) {
				StarMaxColor = 2.0f;
				StarMaxColorFlag = true;
			}
		}
		else if (StarMaxColorFlag == true) {
			StarMaxColor -= 0.05f;
			StarMaxScale -= 0.01f;
			if (StarMaxColor < 1.0f) {
				StarMaxColor = 1.0f;
				StarMaxColorFlag = false;
			}
			m_spriteRender[8]->SetMulColor({ StarMaxColor,StarMaxColor,StarMaxColor,0.8f });
			m_spriteRender[8]->SetScale({ StarMaxScale ,StarMaxScale ,StarMaxScale });
		}
	}
	else {
		//非表示
		m_spriteRender[8]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
	}
	*/

	//残機を更新
	wchar_t text[256];
	//おわ
	swprintf(text, L"%d", gamedata->GetZanki());
	//はい。
	m_fontRender->SetText(text);
	if (gamedata->GetZanki() <= 9) { //残機が1桁です！
		m_fontRender->SetPosition({ ZankiPos.x + ZankiPosXHosei ,ZankiPos.y});
	}
	else {
		m_fontRender->SetPosition(ZankiPos);
	}
	m_fontRender->SetScale(ZankiScaleNow);
	
	//もし現在残機と前残機が違うならアニメフラグオン
	if (gamedata->GetZanki() != BeforeZanki) {
		ZankiAnimeFlag = true;
		BeforeZanki = gamedata->GetZanki();
		ZankiAnimeTimer = 0;
	}

	//残機アニメーション
	if (ZankiAnimeFlag == true) {

		if (ZankiAnimeTimer < ZankiAnimeLimit/2) {//拡大
			ZankiScaleNow += 0.1f;
		}
		else {//戻す
			ZankiScaleNow -= 0.1f;
			if (ZankiScaleNow < ZankiScale) {
				ZankiScaleNow = ZankiScale;
			}
		}

		if (ZankiAnimeTimer == ZankiAnimeLimit) { //残機アニメーション終了
			ZankiAnimeFlag = false;
		}
		ZankiAnimeTimer++;
	}

	//キコウチュウ演出
	if (gamedata->GetKikoFlag() == true && KikoFlag == false) { //キコウチュウを撃破しているのに演出がまだ未表示なら実行
		CVector3 pos = m_spriteRender[9]->GetPosition();
		CVector2 pos_2 = m_fontRender_bonus->GetPosition();
		if (KikoTimer < KikoLimit / 2) { //左へ移動
			pos.x -= KikoMoveX;
			pos_2.x -= KikoMoveX;
			Kiko_Alpha += Kiko_AlphaSpeed;
			if (Kiko_Alpha > 1.0f) {
				Kiko_Alpha = 1.0f;
			}
		}
		else if (KikoTimer > (KikoLimit / 2) + KikoWait) { //右へ移動
			pos.x += KikoMoveX;
			pos_2.x += KikoMoveX;
			Kiko_Alpha -= Kiko_AlphaSpeed;
			if (Kiko_Alpha < 0.0f) {
				Kiko_Alpha = 0.0f;
			}
		}
		m_spriteRender[9]->SetPosition(pos);
		m_spriteRender[9]->SetMulColor({ 1.0f,1.0f,1.0f,Kiko_Alpha });
		m_fontRender_bonus->SetPosition(pos_2);
		m_fontRender_bonus->SetColor({ 1.0f,0.5f,0.0f,Kiko_Alpha });

		//終了する
		if (KikoTimer == KikoLimit + KikoWait) {
			KikoFlag = true;
		}

		KikoTimer++;
	}

	SkillUpdate(); //あぷで

}

void Player_Status::SkillSetUp(){

	//プレイヤーがセットしてるスキルを引っ張ってくる
	SaveData * savedata = SaveData::GetInstance();

	SkillNoY = savedata->GetSkill(false);
	SkillNoX = savedata->GetSkill(true);

}

void Player_Status::SkillUpdate() {

	//スキルデータあれやそれや
	GameData * gamedata = GameData::GetInstance();
	Player * player = Player::GetInstance();
	//SaveData * savedata = SaveData::GetInstance();
	wchar_t text[256];

	//Yスキル編//

	//セット済み判定
	if (SkillNoY != -1) {

		//パッシブスキル判定
		if (Skill_Data[SkillNoY].StarPower == 0) {
			//アイコンを表示して目印は表示しない
			int len = (int)wcslen(Skill_Data[SkillNoY].SkillIcon);
			for (int z = 0; z < len + 1; z++) { //名前の取得
				text[z] = Skill_Data[SkillNoY].SkillIcon[z];
			}
			m_spriteRender[10]->Init(text, 150.0f, 100.0f);

			m_spriteRender[14]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });

		}
		else { //発動型
			if (Skill_Data[SkillNoY].StarPower <= gamedata->GetStar_Power() && player->GetNowSkill() == -1) { //発動可能
				if (SkillIconMAX_Timer < 15) {
					m_spriteRender[10]->Init(L"sprite/skillicon_Y.dds", 150.0f, 100.0f);
				}
				else {
					m_spriteRender[10]->Init(L"sprite/skillicon_Y2.dds", 150.0f, 100.0f);
				}
			}
			else {
				//アイコンを表示して目印は表示しない
				int len = (int)wcslen(Skill_Data[SkillNoY].SkillIcon);
				for (int z = 0; z < len + 1; z++) { //名前の取得
					text[z] = Skill_Data[SkillNoY].SkillIcon[z];
				}
				m_spriteRender[10]->Init(text, 150.0f, 100.0f);
			}

			//バー表示
			float SkillY = (float)Skill_Data[SkillNoY].StarPower / gamedata->GetMAXStar_Power();
			SkillY = StarPOS + (StarMAX * SkillY);

			m_spriteRender[14]->SetPosition({ -550.0f, SkillY, 1.0f });

			m_spriteRender[14]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		}
	}
	else {//何も設定されていない

		m_spriteRender[10]->Init(L"sprite/skillicon_0.dds", 150.0f, 100.0f);

		m_spriteRender[14]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });

	}

	//Xスキル編//

	//セット済み判定
	if (SkillNoX != -1) {

		//パッシブスキル判定
		if (Skill_Data[SkillNoX].StarPower == 0) {
			//アイコンを表示して目印は表示しない
			int len = (int)wcslen(Skill_Data[SkillNoX].SkillIcon);
			for (int z = 0; z < len + 1; z++) { //名前の取得
				text[z] = Skill_Data[SkillNoX].SkillIcon[z];
			}
			m_spriteRender[12]->Init(text, 150.0f, 100.0f);

			m_spriteRender[15]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });

		}
		else { //発動型
			if (Skill_Data[SkillNoX].StarPower <= gamedata->GetStar_Power() && player->GetNowSkill() == -1) { //発動可能
				if (SkillIconMAX_Timer < 15) {
					m_spriteRender[12]->Init(L"sprite/skillicon_X.dds", 150.0f, 100.0f);
				}
				else {
					m_spriteRender[12]->Init(L"sprite/skillicon_X2.dds", 150.0f, 100.0f);
				}
			}
			else {
				//アイコンを表示して目印は表示しない
				int len = (int)wcslen(Skill_Data[SkillNoX].SkillIcon);
				for (int z = 0; z < len + 1; z++) { //名前の取得
					text[z] = Skill_Data[SkillNoX].SkillIcon[z];
				}
				m_spriteRender[12]->Init(text, 150.0f, 100.0f);
			}

			//バー表示
			float SkillY = (float)Skill_Data[SkillNoX].StarPower / gamedata->GetMAXStar_Power();
			SkillY = StarPOS + (StarMAX * SkillY);

			m_spriteRender[15]->SetPosition({ -550.0f, SkillY, 1.0f });

			m_spriteRender[15]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });

		}
	}
	else {//何も設定されていない

		m_spriteRender[12]->Init(L"sprite/skillicon_0.dds", 150.0f, 100.0f);

		m_spriteRender[15]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });

	}

	//スキル発動中ならそのスキルアイコンの色を変える！！
	int skill = player->GetNowSkill();
	if (skill > -1) {
		if (skill == SkillNoY) {
			m_spriteRender[12]->SetMulColor({ 0.2f,0.2f,0.2f,1.0f });

			if (SkillIconMAX_Timer < 15) {
				m_spriteRender[10]->SetMulColor({ 1.0f,1.0f,0.0f,1.0f });
			}
			else {
				m_spriteRender[10]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
			}
		}
		else if (skill == SkillNoX) {
			m_spriteRender[10]->SetMulColor({ 0.2f,0.2f,0.2f,1.0f });

			if (SkillIconMAX_Timer < 15) {
				m_spriteRender[12]->SetMulColor({ 1.0f,1.0f,0.0f,1.0f });
			}
			else {
				m_spriteRender[12]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
			}
		}
	}
	else {
		m_spriteRender[10]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		m_spriteRender[12]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	}

	//タイマー
	SkillIconMAX_Timer++;
	if (SkillIconMAX_Timer >= 30) {
		SkillIconMAX_Timer = 0;
	}

}

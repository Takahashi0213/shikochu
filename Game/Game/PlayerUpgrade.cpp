#include "stdafx.h"
#include "PlayerUpgrade.h"
#include "GameData.h"
#include "SaveData.h"
#include "StageSelect.h"
#include "TransitionMaker.h"

PlayerUpgrade* PlayerUpgrade::m_instance = nullptr;

PlayerUpgrade::PlayerUpgrade()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;
}

PlayerUpgrade::~PlayerUpgrade()
{

	for (int i = 0; i < m_spriteRender.size(); i++) {
		DeleteGO(m_spriteRender[i]);
	}
	for (int i = 0; i < m_fontRender.size(); i++) {
		DeleteGO(m_fontRender[i]);
	}

	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

bool PlayerUpgrade::Start() {

	//SE
	ss = NewGO<prefab::CSoundSource>(0);
	ss->Init(L"sound/SE_On.wav");
	ss->SetVolume(1.0f);
	ss->Play(false);
	ss = NewGO<prefab::CSoundSource>(0);
	ss->Init(L"sound/SE_On2.wav");
	ss->SetVolume(0.5f);
	ss->Play(false);

	Setting();

	//0番→背景
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/Black.dds", 1280.0f, 720.0f);
	MulColor = { 1.0f,1.0f,1.0f,1.0f };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//1番→背景
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/kyoka1.dds", 1280.0f, 720.0f);
	MulColor = { 1.0f,1.0f,1.0f,DEF_Mul };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//2番→明かり差分
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/kyoka2.dds", 1280.0f, 720.0f);
	MulColor = { 1.0f,1.0f,1.0f,DEF_Mul2 };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//3番→むしさん
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/kyoka3.dds", 1280.0f, 720.0f);
	MulColor = { 1.0f,1.0f,1.0f,1.0f };
	r->SetPosition({ 0.0f,720.0f,0.0f });
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//4番→枠1
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/kyokawaku.dds", 398.0f, 140.0f);
	MulColor = { 0.5f,0.5f,0.5f,0.5f };
	r->SetPosition({ wakuPosDEF_X,wakuPosDefY*2.0f + 720.0f ,0.0f });
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//5番→枠2
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/kyokawaku.dds", 398.0f, 140.0f);
	MulColor = { 0.5f,0.5f,0.5f,0.5f };
	r->SetPosition({ wakuPosDEF_X,wakuPosDefY + 720.0f ,0.0f });
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//6番→枠3
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/kyokawaku.dds", 398.0f, 140.0f);
	MulColor = { 0.5f,0.5f,0.5f,0.5f };
	r->SetPosition({ wakuPosDEF_X, 720.0f ,0.0f });
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//7番→トランシーバー
	r = NewGO<prefab::CSpriteRender>(4);
	r->Init(L"sprite/tr_waku.dds", 400.0f, 267.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetPosition({ -350.0f,-100.0f,0.0f });
	r->SetMulColor(MulColor);
	r->SetScale({ 0.0f,0.0f,1.0f });
	m_spriteRender.push_back(r);
	//8番→退出アイコン
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/ExitP.dds", 300.0f, 300.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetPosition({ -380.0f,100.0f,0.0f });
	r->SetMulColor(MulColor);
	r->SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRender.push_back(r);
	//9番→LB
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/LB.dds", 100.0f, 100.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetPosition({ -380.0f,250.0f,0.0f });
	r->SetMulColor(MulColor);
	r->SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRender.push_back(r);
	//10番→Aボタン
	r = NewGO<prefab::CSpriteRender>(7);
	r->Init(L"sprite/A_Button.dds", 50.0f, 50.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetPosition({ -130.0f,wakuPosDefY*2.0f,0.0f });
	r->SetMulColor(MulColor);
	r->SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRender.push_back(r);
	//11番→くも
	r = NewGO<prefab::CSpriteRender>(6);
	r->Init(L"sprite/kumo.dds", 100.0f, 150.0f);
	MulColor = { 1.0f,1.0f,1.0f,1.0f };
	r->SetPosition({ 580.0f,320.0f,0.0f });
	r->SetMulColor(MulColor);
	r->SetScale({ 1.0f,1.0f,1.0f });
	m_spriteRender.push_back(r);

	//テキストン
	//ポイント 0番
	f = NewGO<prefab::CFontRender>(3);
	//表示
	wchar_t text[256];
	//おわ
	swprintf(text, L"%d", point);
	//はい。
	f->SetText(text);
	f->SetPosition({ 350.0f, -50.0f + 720.0f });
	f->SetScale(1.5f);
	f->SetColor({ 1.0f,0.2f,0.8f,1.0f });
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);
	//ポイント文字 1番
	f = NewGO<prefab::CFontRender>(3);
	//表示
	text[256];
	//おわ
	swprintf(text, L"point");
	//はい。
	f->SetText(text);
	f->SetPosition({ 500.0f, -70.0f + 720.0f });
	f->SetScale(0.6f);
	f->SetColor({ 0.8f,0.2f,0.7f,1.0f });
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);
	//残機 2番
	f = NewGO<prefab::CFontRender>(3);
	//表示
	text[256];
	//おわ
	swprintf(text, L"ざんき:%d",zanki);
	//はい。
	f->SetText(text);
	f->SetPosition({ wakuPosDEF_X, wakuPosDefY * 2.0f + statusPosY + Ypos_hoge });
	f->SetScale(1.0f);
	f->SetColor({ 0.5f,0.5f,0.5f,0.5f });
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);
	//残機値段 3番
	f = NewGO<prefab::CFontRender>(3);
	//表示
	text[256];
	//おわ
	if (zanki_X < MAX_Upgrade) {
		swprintf(text, L"-%dpoint", zanki_Point);
	}
	else {
		zanki_Point = -1;
		swprintf(text, L"MAX");
	}
	//はい。
	f->SetText(text);
	f->SetPosition({ wakuPosDEF_X, wakuPosDefY * 2.0f - 15.0f + Ypos_hoge });
	f->SetScale(0.8f);
	f->SetColor({ 0.5f,0.5f,0.5f,0.5f });
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);
	//攻撃 4番
	f = NewGO<prefab::CFontRender>(3);
	//表示
	text[256];
	//おわ
	swprintf(text, L"こうげき:%d", attack);
	//はい。
	f->SetText(text);
	f->SetPosition({ wakuPosDEF_X, wakuPosDefY + statusPosY + Ypos_hoge });
	f->SetScale(1.0f);
	f->SetColor({ 0.5f,0.5f,0.5f,0.5f });
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);
	//攻撃値段 5番
	f = NewGO<prefab::CFontRender>(3);
	//表示
	text[256];
	//おわ
	if (attack_X < MAX_Upgrade) {
		swprintf(text, L"-%dpoint", attack_Point);
	}
	else {
		attack_Point = -1;
		swprintf(text, L"MAX");
	}
	//はい。
	f->SetText(text);
	f->SetPosition({ wakuPosDEF_X, wakuPosDefY - 15.0f + Ypos_hoge });
	f->SetScale(0.8f);
	f->SetColor({ 0.5f,0.5f,0.5f,0.5f });
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);
	//寿命 6番
	f = NewGO<prefab::CFontRender>(3);
	//表示
	text[256];
	//おわ
	swprintf(text, L"じゅみょう:%d", jyumyo);
	//はい。
	f->SetText(text);
	f->SetPosition({ wakuPosDEF_X, statusPosY + Ypos_hoge });
	f->SetScale(1.0f);
	f->SetColor({ 0.5f,0.5f,0.5f,0.5f });
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);
	//寿命値段 7番
	f = NewGO<prefab::CFontRender>(3);
	//表示
	text[256];
	//おわ
	if (jyumyo_X < MAX_Upgrade) {
		swprintf(text, L"-%dpoint", jyumyo_Point);
	}
	else {
		jyumyo_Point = -1;
		swprintf(text, L"MAX");
	}
	//はい。
	f->SetText(text);
	f->SetPosition({ wakuPosDEF_X,- 15.0f + Ypos_hoge });
	f->SetScale(0.8f);
	f->SetColor({ 0.5f,0.5f,0.5f,0.5f });
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);
	//コメントくん 8番
	f = NewGO<prefab::CFontRender>(4);
	//表示
	text[256];
	//おわ
	swprintf(text, L"");
	//はい。
	f->SetText(text);
	f->SetPosition({ -480.0f,15.0f });
	f->SetScale(0.8f);
	f->SetColor({ 0.2f,1.0f,0.2f,1.0f });
	f->SetPivot({ 0.0f,1.0f });
	m_fontRender.push_back(f);
	//ステータスUP演出用 9番
	f = NewGO<prefab::CFontRender>(3);
	//表示
	text[256];
	//おわ
	swprintf(text, L"XXXXX");
	//はい。
	f->SetText(text);
	f->SetPosition({ 380.0f, 50.0f });
	f->SetScale(1.0f);
	f->SetColor({ 1.0f,0.2f,0.2f,0.0f });
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);

	return true;
}

void PlayerUpgrade::Update() {

	//スタート演出！
	if (startTimer >= 48 && startTimer < 72) {
		//明るく
		DEF_Mul += 0.05f;
		if (DEF_Mul > 1.0f) {
			DEF_Mul = 1.0f;
		}
		m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,DEF_Mul });
		DEF_Mul2 += 0.1f;
		if (DEF_Mul2 > 1.0f) {
			DEF_Mul2 = 1.0f;
		}
		m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,DEF_Mul2 });
		m_spriteRender[3]->SetMulColor({ 1.0f,1.0f,1.0f,DEF_Mul2 });
		m_spriteRender[7]->SetMulColor({ 1.0f,1.0f,1.0f,DEF_Mul2 });
		m_spriteRender[8]->SetMulColor({ 1.0f,1.0f,1.0f,DEF_Mul2 });
		m_spriteRender[9]->SetMulColor({ 1.0f,1.0f,1.0f,DEF_Mul2 });
		m_spriteRender[10]->SetMulColor({ 1.0f,1.0f,1.0f,DEF_Mul2 });

		//動け！
		CVector3 pos = m_spriteRender[3]->GetPosition();
		pos.y -= Move_Hoge;
		Move_Hoge *= 0.6f;
		if (pos.y < 0.0f) {
			pos.y = 0.0f;
		}
		//見た目がすごく汚い更新
		m_spriteRender[3]->SetPosition(pos);
		m_fontRender[0]->SetPosition({ 350.0f,pos.y - 50.0f });
		m_fontRender[1]->SetPosition({ 500.0f,pos.y - 70.0f });
		m_spriteRender[4]->SetPosition({ wakuPosDEF_X,pos.y + wakuPosDefY * 2.0f ,pos.z });
		m_spriteRender[5]->SetPosition({ wakuPosDEF_X,pos.y + wakuPosDefY,pos.z });
		m_spriteRender[6]->SetPosition({ wakuPosDEF_X,pos.y,pos.z });
		m_fontRender[2]->SetPosition({ wakuPosDEF_X,pos.y + wakuPosDefY * 2.0f + statusPosY });
		m_fontRender[3]->SetPosition({ wakuPosDEF_X,pos.y + wakuPosDefY * 2.0f - 15.0f });
		m_fontRender[4]->SetPosition({ wakuPosDEF_X,pos.y + wakuPosDefY + statusPosY });
		m_fontRender[5]->SetPosition({ wakuPosDEF_X,pos.y + wakuPosDefY - 15.0f });
		m_fontRender[6]->SetPosition({ wakuPosDEF_X,pos.y + statusPosY });
		m_fontRender[7]->SetPosition({ wakuPosDEF_X,pos.y - 15.0f });
		//7ばん
		pos = m_spriteRender[7]->GetPosition();
		CVector3 scl = m_spriteRender[7]->GetScale();
		if(startTimer < 54) {
			pos.y += 2.0f;
			scl.x += 0.2f;
			scl.y += 0.2f;
		}
		else if(startTimer < 60){
			pos.y -= 2.0f;
			scl.x -= (0.2f / 6.0f);
			scl.y -= (0.2f / 6.0f);
		}
		m_spriteRender[7]->SetPosition(pos);
		m_spriteRender[7]->SetScale(scl);
		if (startTimer == 71) {
			Transceiver(L"ヨウコソ\nカンソクシャ");
			CommandUpdate();
		}
	}

	//挙動
	if (startTimer >= 72 && DeleteFlag==false) {
		if (Pad(0).IsTrigger(enButtonUp)) {
			CommandNow--;
			if (CommandNow == -1) {
				CommandNow = 2;
			}
			if (startTimer > TranStart) {
				commandTren();
			}
			A_ButtonUpdate();
			CommandUpdate();
		}
		else if (Pad(0).IsTrigger(enButtonDown)) {
			CommandNow++;
			if (CommandNow == 3) {
				CommandNow = 0;
			}
			if (startTimer > TranStart) {
				commandTren();
			}
			A_ButtonUpdate();
			CommandUpdate();
		}
		else if (Pad(0).IsTrigger(enButtonA)) {
			//購入！
			//取得色々
			GameData * gamedata = GameData::GetInstance();
			SaveData * savedata = SaveData::GetInstance();
			switch (CommandNow) {
			case 0://残機
				//もしMAXなら買えない
				if (zanki_Point == -1) {
					TransceiverStandby();
					Transceiver(L"コレイジョウ\nナニヲ フヤスト\nイウノデス？");
					buruFlag = true;
					break;
				}
				//買えるか確認
				if (zanki_Point <= point) {
					//買える
					TransceiverStandby();
					Transceiver(L"アリガトウゴザイマス");
					savedata->PlusZanki_Upgrade();
					gamedata->PlusPoint(-zanki_Point);
					gamedata->PlusDEF_Zanki(Zanki_Plus);
					StatusUpTimer = 0; //ステータス上昇演出
					StatusUpAlpha = 1.0f;
					wchar_t text[256];
					//おわ
					swprintf(text, L"ざんき+%d", Zanki_Plus);
					//はい。
					m_fontRender[9]->SetText(text);
					m_fontRender[9]->SetPosition(StatusUP_DefPos);
					m_fontRender[9]->SetColor({ 1.0f,0.2f,0.2f,1.0f });
					Setting();
					CommandUpdate();
				}
				else {
					//買えない
					TransceiverStandby();
					Transceiver(L"ポイントガ タリマセン");
					buruFlag = true;
				}
				break;
			case 1://攻撃
				   //もしMAXなら買えない
				if (attack_Point == -1) {
					TransceiverStandby();
					Transceiver(L"アナタ ツヨスギデス");
					buruFlag = true;
					break;
				}
				//買えるか確認
				if (attack_Point <= point) {
					//買える
					TransceiverStandby();
					Transceiver(L"アリガトウゴザイマス");
					savedata->PlusAttack_Upgrade();
					gamedata->PlusPoint(-attack_Point);
					gamedata->PlusATK(Attack_Plus);
					StatusUpTimer = 0; //ステータス上昇演出
					StatusUpAlpha = 1.0f;
					wchar_t text[256];
					//おわ
					swprintf(text, L"こうげき+%d", Attack_Plus);
					//はい。
					m_fontRender[9]->SetText(text);
					m_fontRender[9]->SetPosition(StatusUP_DefPos);
					m_fontRender[9]->SetColor({ 1.0f,0.2f,0.2f,1.0f });
					Setting();
					CommandUpdate();
				}
				else {
					//買えない
					TransceiverStandby();
					Transceiver(L"ポイントガ タリマセン");
					buruFlag = true;
				}	
				break;
			case 2://寿命
				   //もしMAXなら買えない
				if (jyumyo_Point == -1) {
					TransceiverStandby();
					Transceiver(L"コレガ アナタノ\nゲンカイデスヨ");
					buruFlag = true;
					break;
				}
				//買えるか確認
				if (jyumyo_Point <= point) {
					//買える
					TransceiverStandby();
					Transceiver(L"アリガトウゴザイマス");
					savedata->PlusLife_Upgrade();
					gamedata->PlusPoint(-jyumyo_Point);
					gamedata->PlusLife(Life_Plus);
					StatusUpTimer = 0; //ステータス上昇演出
					StatusUpAlpha = 1.0f;
					wchar_t text[256];
					//おわ
					swprintf(text, L"じゅみょう+%d", Life_Plus);
					//はい。
					m_fontRender[9]->SetText(text);
					m_fontRender[9]->SetPosition(StatusUP_DefPos);
					m_fontRender[9]->SetColor({ 1.0f,0.2f,0.2f,1.0f });
					Setting();
					CommandUpdate();
				}
				else {
					//買えない
					TransceiverStandby();
					Transceiver(L"ポイントガ タリマセン");
					buruFlag = true;
				}	
				break;
			}

		}
		else if (Pad(0).IsTrigger(enButtonLB1)) {
			DeleteFlag = true;
			TransceiverStandby();
			ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/SE_Door.wav");
			ss->SetVolume(1.0f);
			ss->Play(false);
			Transceiver(L"マタドウゾ");
		}


	}

	//sayonara.
	if (DeleteFlag == true) {

		//トランジション
		if (DeleteTimer == 60) {
			TransitionMaker * tm = TransitionMaker::GetInstance();
			tm->TransitionSetting(TransitionMaker::Toziru, 12, 10, false);
		}

		if (DeleteTimer < 60) {
			//部屋を暗くする
			DEF_Mul -= 0.05f;
			if (DEF_Mul < 0.4f) {
				DEF_Mul = 0.4f;
			}
			m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,DEF_Mul });
			DEF_Mul2 -= 0.1f;
			if (DEF_Mul2 < 0.0f) {
				DEF_Mul2 = 0.0f;
			}
			m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,DEF_Mul2 });
			m_spriteRender[3]->SetMulColor({ 1.0f,1.0f,1.0f,DEF_Mul2 });
			m_spriteRender[4]->SetMulColor({ 0.5f,0.5f,0.5f,DEF_Mul2 });
			m_spriteRender[5]->SetMulColor({ 0.5f,0.5f,0.5f,DEF_Mul2 });
			m_spriteRender[6]->SetMulColor({ 0.5f,0.5f,0.5f,DEF_Mul2 });
			m_spriteRender[8]->SetMulColor({ 0.5f,0.5f,0.5f,DEF_Mul2 });
			m_spriteRender[9]->SetMulColor({ 0.5f,0.5f,0.5f,DEF_Mul2 });
			m_spriteRender[10]->SetMulColor({ 0.5f,0.5f,0.5f,DEF_Mul2 });
			for(int i = 0; i < 8; i++) {
				m_fontRender[i]->SetColor({ 0.5f,0.5f,0.5f,DEF_Mul2 });
			}
			CVector3 E_pos = m_spriteRender[8]->GetPosition();
			E_pos.x -= 5.0f;
			m_spriteRender[8]->SetPosition(E_pos);
		}
		else if(DeleteTimer == 84) {
			TransitionMaker * tm = TransitionMaker::GetInstance();
			tm->TransitionSetting(TransitionMaker::Toziru, 12, 10, true);
			NewGO<StageSelect>(0);
			DeleteGO(this);
		}
		DeleteTimer++;
	}

	//明かり点滅
	if (startTimer > 60 && DeleteFlag == false) {
		if (akariTimer == 6) {
			MulColor = { 1.0f,1.0f,1.0f,0.95f };
			m_spriteRender[2]->SetMulColor(MulColor);
		}if (akariTimer == 12) {
			MulColor = { 1.0f,1.0f,1.0f,1.0f };
			m_spriteRender[2]->SetMulColor(MulColor);
			akariTimer = -1;
		}
		akariTimer++;
	}

	if (jumpFlag == true) {
		CommandJump();
	}
	if (buruFlag == true) {
		CommandShake();
	}
	if (TranFlag == true) {
		if (T_Timer == 4) {
			Transceiver(L"");
			T_Timer = -1;
		}
		T_Timer++;
	}

	//ステアプ演出
	if (StatusUpTimer >= 0) {
		CVector2 UP_pos = m_fontRender[9]->GetPosition();
		UP_pos.y += 3.0f;
		m_fontRender[9]->SetPosition(UP_pos);
		if (StatusUpTimer > 12) {
			StatusUpAlpha -= 0.1f;
			if (StatusUpAlpha < 0.0f) {
				StatusUpAlpha = 0.0f;
			}
		}
		m_fontRender[9]->SetColor({ 1.0f,0.2f,0.2f,StatusUpAlpha });
		if (StatusUpTimer > 24) {
			StatusUpTimer = -2;
			m_fontRender[9]->SetPosition(StatusUP_DefPos);
		}
		StatusUpTimer++;
	}

	//Aボタン
	if (DeleteFlag == false) {
		if (A_Timer == 24) {
			m_spriteRender[10]->Init(L"sprite/A_Button2.dds", 50.0f, 50.0f);
		}
		else if (A_Timer == 48) {
			A_Timer = -1;
			m_spriteRender[10]->Init(L"sprite/A_Button.dds", 50.0f, 50.0f);
		}
		A_Timer++;
	}

	if (DeleteFlag == false) {
		CVector3 E_pos = m_spriteRender[8]->GetPosition();
		CVector3 E_pos2 = m_spriteRender[9]->GetPosition();
		if (E_MoveFlag == false) {
			E_pos.x -= 1.0f;
			E_pos2.y += 0.2f;
		}
		else {
			E_pos.x += 1.0f;
			E_pos2.y -= 0.2f;
		}
		m_spriteRender[8]->SetPosition(E_pos);
		m_spriteRender[9]->SetPosition(E_pos2);

		if (E_MoveTimer == 24) {
			E_MoveFlag = true;
		}
		else if (E_MoveTimer == 48) {
			E_MoveTimer = -1;
			E_MoveFlag = false;
		}
		E_MoveTimer++;
	}

	//ヨウコソの終焉
	if (startTimer == TranStart && DeleteFlag == false) {
		commandTren();
	}

	//うごくも
	KumoMove();

	//たいま
	startTimer++;
}

void PlayerUpgrade::CommandUpdate() {

	//ジャンプフラグをオン
	jumpFlag = true;

	//数値を更新
	Point_keisan();
	wchar_t text[256];
	swprintf(text, L"%d", point);
	m_fontRender[0]->SetText(text);
	//////
	text[256];
	swprintf(text, L"ざんき:%d", zanki);
	m_fontRender[2]->SetText(text);
	text[256];
	if (zanki_X < MAX_Upgrade) {
		swprintf(text, L"-%dpoint", zanki_Point);
	}
	else {
		zanki_Point = -1;
		swprintf(text, L"MAX");
	}
	m_fontRender[3]->SetText(text);
	text[256];
	//////
	swprintf(text, L"こうげき:%d", attack);
	m_fontRender[4]->SetText(text);
	text[256];
	if (attack_X < MAX_Upgrade) {
		swprintf(text, L"-%dpoint", attack_Point);
	}
	else {
		attack_Point = -1;
		swprintf(text, L"MAX");
	}
	m_fontRender[5]->SetText(text);
	text[256];
	//////
	swprintf(text, L"じゅみょう:%d", jyumyo);
	m_fontRender[6]->SetText(text);
	text[256];
	if (jyumyo_X < MAX_Upgrade) {
		swprintf(text, L"-%dpoint", jyumyo_Point);
	}
	else {
		jyumyo_Point = -1;
		swprintf(text, L"MAX");
	}
	m_fontRender[7]->SetText(text);

	//明るさを更新 コマンドが散らかりすぎでは？
	switch (CommandNow) {
	case 0://残機
		m_spriteRender[4]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		m_spriteRender[5]->SetMulColor({ 0.5f,0.5f,0.5f,0.5f });
		m_spriteRender[6]->SetMulColor({ 0.5f,0.5f,0.5f,0.5f });
		m_fontRender[2]->SetColor({ 1.0f,0.2f,0.2f,1.0f });
		if (zanki_Point <= point) {
			m_fontRender[3]->SetColor({ 1.0f,0.2f,0.2f,1.0f });
		}
		else {
			m_fontRender[3]->SetColor({ 0.5f,0.3f,0.3f,1.0f });
		}
		m_fontRender[4]->SetColor({ 0.5f,0.5f,0.5f,0.5f });
		m_fontRender[5]->SetColor({ 0.5f,0.5f,0.5f,0.5f });
		m_fontRender[6]->SetColor({ 0.5f,0.5f,0.5f,0.5f });
		m_fontRender[7]->SetColor({ 0.5f,0.5f,0.5f,0.5f });
		break;
	case 1://攻撃
		m_spriteRender[4]->SetMulColor({ 0.5f,0.5f,0.5f,0.5f });
		m_spriteRender[5]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		m_spriteRender[6]->SetMulColor({ 0.5f,0.5f,0.5f,0.5f });
		m_fontRender[2]->SetColor({ 0.5f,0.5f,0.5f,0.5f });
		m_fontRender[3]->SetColor({ 0.5f,0.5f,0.5f,0.5f });
		m_fontRender[4]->SetColor({ 1.0f,0.2f,0.2f,1.0f });
		if (attack_Point <= point) {
			m_fontRender[5]->SetColor({ 1.0f,0.2f,0.2f,1.0f });
		}
		else {
			m_fontRender[5]->SetColor({ 0.5f,0.3f,0.3f,1.0f });
		}
		m_fontRender[6]->SetColor({ 0.5f,0.5f,0.5f,0.5f });
		m_fontRender[7]->SetColor({ 0.5f,0.5f,0.5f,0.5f });
		break;
	case 2://寿命
		m_spriteRender[4]->SetMulColor({ 0.5f,0.5f,0.5f,0.5f });
		m_spriteRender[5]->SetMulColor({ 0.5f,0.5f,0.5f,0.5f });
		m_spriteRender[6]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		m_fontRender[2]->SetColor({ 0.5f,0.5f,0.5f,0.5f });
		m_fontRender[3]->SetColor({ 0.5f,0.5f,0.5f,0.5f });
		m_fontRender[4]->SetColor({ 0.5f,0.5f,0.5f,0.5f });
		m_fontRender[5]->SetColor({ 0.5f,0.5f,0.5f,0.5f });
		m_fontRender[6]->SetColor({ 1.0f,0.2f,0.2f,1.0f });
		if (jyumyo_Point <= point) {
			m_fontRender[7]->SetColor({ 1.0f,0.2f,0.2f,1.0f });
		}
		else {
			m_fontRender[7]->SetColor({ 0.5f,0.3f,0.3f,1.0f });
		}
		break;
	}

}
void PlayerUpgrade::CommandJump() {
	
	if (jumpTimer == 0) {//念のためリセット
		m_spriteRender[4]->SetPosition({ wakuPosDEF_X,wakuPosDefY*2.0f,0.0f });
		m_spriteRender[5]->SetPosition({ wakuPosDEF_X,wakuPosDefY ,0.0f });
		m_spriteRender[6]->SetPosition({ wakuPosDEF_X,0.0f ,0.0f });
		m_fontRender[2]->SetPosition({ wakuPosDEF_X, wakuPosDefY * 2.0f + statusPosY });
		m_fontRender[3]->SetPosition({ wakuPosDEF_X, wakuPosDefY * 2.0f - 15.0f});
		m_fontRender[4]->SetPosition({ wakuPosDEF_X, wakuPosDefY + statusPosY});
		m_fontRender[5]->SetPosition({ wakuPosDEF_X, wakuPosDefY - 15.0f});
		m_fontRender[6]->SetPosition({ wakuPosDEF_X, statusPosY });
		m_fontRender[7]->SetPosition({ wakuPosDEF_X,-15.0f });;
	}

	float hoge = 0.0f;
	if (jumpTimer < 3) {
		hoge = +2.0f;
	}
	else {
		hoge = -2.0f;
	}

	CVector3 pos = CVector3::Zero;
	CVector2 pos2 = CVector2::Zero;

	switch (CommandNow) {
	case 0://残機
		pos = m_spriteRender[4]->GetPosition();
		pos.y += hoge;
		m_spriteRender[4]->SetPosition(pos);
		pos2 = m_fontRender[2]->GetPosition();
		pos2.y += hoge;
		m_fontRender[2]->SetPosition(pos2);
		pos2 = m_fontRender[3]->GetPosition();
		pos2.y += hoge;
		m_fontRender[3]->SetPosition(pos2);
		break;
	case 1://攻撃
		pos = m_spriteRender[5]->GetPosition();
		pos.y += hoge;
		m_spriteRender[5]->SetPosition(pos);
		pos2 = m_fontRender[4]->GetPosition();
		pos2.y += hoge;
		m_fontRender[4]->SetPosition(pos2);
		pos2 = m_fontRender[5]->GetPosition();
		pos2.y += hoge;
		m_fontRender[5]->SetPosition(pos2);
		break;
	case 2://寿命
		pos = m_spriteRender[6]->GetPosition();
		pos.y += hoge;
		m_spriteRender[6]->SetPosition(pos);
		pos2 = m_fontRender[6]->GetPosition();
		pos2.y += hoge;
		m_fontRender[6]->SetPosition(pos2);
		pos2 = m_fontRender[7]->GetPosition();
		pos2.y += hoge;
		m_fontRender[7]->SetPosition(pos2);
		break;
	}

	jumpTimer++;
	if (jumpTimer == 6) {
		jumpTimer = 0;
		jumpFlag = false;
	}
}

void PlayerUpgrade::CommandShake() {

	float hoge = 0.0f;
	static int S_Timer = 0;

	if (buruTimer == 0) {//念のためリセット
		m_spriteRender[4]->SetPosition({ wakuPosDEF_X,wakuPosDefY*2.0f,0.0f });
		m_spriteRender[5]->SetPosition({ wakuPosDEF_X,wakuPosDefY ,0.0f });
		m_spriteRender[6]->SetPosition({ wakuPosDEF_X,0.0f ,0.0f });
		m_fontRender[2]->SetPosition({ wakuPosDEF_X, wakuPosDefY * 2.0f + statusPosY });
		m_fontRender[3]->SetPosition({ wakuPosDEF_X, wakuPosDefY * 2.0f - 15.0f });
		m_fontRender[4]->SetPosition({ wakuPosDEF_X, wakuPosDefY + statusPosY });
		m_fontRender[5]->SetPosition({ wakuPosDEF_X, wakuPosDefY - 15.0f });
		m_fontRender[6]->SetPosition({ wakuPosDEF_X, statusPosY });
		m_fontRender[7]->SetPosition({ wakuPosDEF_X,-15.0f });
		hoge = -4.0f;
	}
	else {
		if (S_Timer % 2 == 0) {
			//偶数
			hoge = 8.0f;
		}
		else {
			//奇数
			hoge = -8.0f;
		}
		S_Timer++;
	}

	CVector3 pos = CVector3::Zero;
	CVector2 pos2 = CVector2::Zero;

	switch (CommandNow) {
	case 0://残機
		pos = m_spriteRender[4]->GetPosition();
		pos.x += hoge;
		m_spriteRender[4]->SetPosition(pos);
		pos2 = m_fontRender[2]->GetPosition();
		pos2.x += hoge;
		m_fontRender[2]->SetPosition(pos2);
		pos2 = m_fontRender[3]->GetPosition();
		pos2.x += hoge;
		m_fontRender[3]->SetPosition(pos2);
		break;
	case 1://攻撃
		pos = m_spriteRender[5]->GetPosition();
		pos.x += hoge;
		m_spriteRender[5]->SetPosition(pos);
		pos2 = m_fontRender[4]->GetPosition();
		pos2.x += hoge;
		m_fontRender[4]->SetPosition(pos2);
		pos2 = m_fontRender[5]->GetPosition();
		pos2.x += hoge;
		m_fontRender[5]->SetPosition(pos2);
		break;
	case 2://寿命
		pos = m_spriteRender[6]->GetPosition();
		pos.x += hoge;
		m_spriteRender[6]->SetPosition(pos);
		pos2 = m_fontRender[6]->GetPosition();
		pos2.x += hoge;
		m_fontRender[6]->SetPosition(pos2);
		pos2 = m_fontRender[7]->GetPosition();
		pos2.x += hoge;
		m_fontRender[7]->SetPosition(pos2);
		break;
	}

	buruTimer++;
	if (buruTimer == 6) {
		buruTimer = 0;
		buruFlag = false;
		S_Timer = 0;
		m_spriteRender[4]->SetPosition({ wakuPosDEF_X,wakuPosDefY*2.0f,0.0f });
		m_spriteRender[5]->SetPosition({ wakuPosDEF_X,wakuPosDefY ,0.0f });
		m_spriteRender[6]->SetPosition({ wakuPosDEF_X,0.0f ,0.0f });
		m_fontRender[2]->SetPosition({ wakuPosDEF_X, wakuPosDefY * 2.0f + statusPosY });
		m_fontRender[3]->SetPosition({ wakuPosDEF_X, wakuPosDefY * 2.0f - 15.0f });
		m_fontRender[4]->SetPosition({ wakuPosDEF_X, wakuPosDefY + statusPosY });
		m_fontRender[5]->SetPosition({ wakuPosDEF_X, wakuPosDefY - 15.0f });
		m_fontRender[6]->SetPosition({ wakuPosDEF_X, statusPosY });
		m_fontRender[7]->SetPosition({ wakuPosDEF_X,-15.0f });
	}
}


//取得色々
void PlayerUpgrade::Setting() {

	GameData * gamedata = GameData::GetInstance();
	SaveData * savedata = SaveData::GetInstance();
	point = gamedata->GetPoint();
	zanki = gamedata->GetDEF_Zanki();
	attack = gamedata->GetATK();
	jyumyo = gamedata->GetDEF_Life();
	zanki_X = savedata->GetZanki_Upgrade();
	attack_X = savedata->GetAttack_Upgrade();
	jyumyo_X = savedata->GetLife_Upgrade();
	Point_keisan();

}

//引数に設定したテキストを喋るよ
void PlayerUpgrade::Transceiver(wchar_t text[256]) {

	static int len;
	if (TranTimer == 0) {//ぶっこむ
		TranFlag = true;
		for (int i = 0; i < 256; i++) {
			Message[i] = Reset[0];
		}
		len = (int)wcslen(text);
		for (int z = 0; z < len + 1; z++) {
			Message[z] = text[z];
		}
	}

	//表示
	ss = NewGO<prefab::CSoundSource>(0);
	ss->Init(L"sound/SE_Message.wav");
	ss->SetVolume(0.5f);
	ss->Play(false);
	wchar_t hoge[256] = L"";

	for (int n = 0; n < TranTimer+1; n++) {
		hoge[n] = Message[n];
	}

	swprintf(hoge, hoge);
	//はい。
	m_fontRender[8]->SetText(hoge);

	TranTimer++;
	if (TranTimer == len) {
		TranFlag = false;
		TranTimer = 0;
	}
}

void PlayerUpgrade::TransceiverStandby() {
	for (int i = 0; i < 256; i++) {
		Message[i] = Reset[0];
	}
	TranFlag = false;
	TranTimer = 0;
	T_Timer = 0;
}

void PlayerUpgrade::commandTren() {
	switch (CommandNow) {
	case 0://残機
		TransceiverStandby();
		Transceiver(L"アナタサマノ\nナカマ ヲ フヤシマス");
		break;
	case 1://攻撃
		TransceiverStandby();
		Transceiver(L"オソロシイ テキニ\nアタエル ダメージ ガ\nオオキクナリマス");
		break;
	case 2://寿命
		TransceiverStandby();
		Transceiver(L"ミジカイ イノチ ヲ\nノバシマショウ");
		break;
	}

}

void PlayerUpgrade::A_ButtonUpdate() {
	switch (CommandNow) {
	case 0://残機
		m_spriteRender[10]->SetPosition({ -130.0f,wakuPosDefY*2.0f,0.0f });
		break;
	case 1://攻撃
		m_spriteRender[10]->SetPosition({ -130.0f,wakuPosDefY,0.0f });
		break;
	case 2://寿命
		m_spriteRender[10]->SetPosition({ -130.0f, 0.0f ,0.0f });
		break;
	}

}

void PlayerUpgrade::KumoMove() {

	if (KumoTimer == 0) {
		Random = rand() % 4;
		int hoge = rand() % 2;
		if (hoge == 0) {
			KumoLimit = 60;
		}
		else if (hoge == 1) {
			KumoLimit = 30;
		}
		else if (hoge == 2) {
			KumoLimit = 12;
		}
	}
	CVector3 K_pos = m_spriteRender[11]->GetPosition();
	if (Random == 0) {//上へ
		K_pos.y += 0.2f;
		if (K_pos.y > KumoY_MAX) {
			K_pos.y = KumoY_MAX;
		}
	}
	else if (Random == 1) {//下へ
		K_pos.y -= 0.2f;
		if (K_pos.y < KumoY_MIN) {
			K_pos.y = KumoY_MIN;
		}

	}//待機

	m_spriteRender[11]->SetPosition(K_pos);

	KumoTimer++;

	if (KumoTimer == KumoLimit) {
		KumoTimer = -KumoInterval;
	}

}
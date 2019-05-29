#include "stdafx.h"
#include "WaveEffect.h"
#include "GameData.h"

WaveEffect::WaveEffect()
{

}

WaveEffect::~WaveEffect()
{

	for (int i = 0; i < m_spriteRender.size(); i++) {
		DeleteGO(m_spriteRender[i]);
	}
	for (int i = 0; i < m_fontRender.size(); i++) {
		DeleteGO(m_fontRender[i]);
	}

}

bool WaveEffect::Start() {
	//表示
	GameData * gamedata = GameData::GetInstance();
	Wave = gamedata->GetWave();
	Wave += 1;
	MaxWave = gamedata->GetMAX_WaveNo();
	if (Wave == MaxWave) {
		//0番→背景
		r = NewGO<prefab::CSpriteRender>(10);
		r->Init(L"sprite/WaveUnderBoss.dds", 1920.0f, 250.0f);
		ScaleY = 0.0f;
		r->SetScale({ 1.0f,ScaleY,1.0f });
		m_spriteRender.push_back(r);
	}
	else {
		//0番→背景
		r = NewGO<prefab::CSpriteRender>(10);
		r->Init(L"sprite/WaveUnder.dds", 1920.0f, 250.0f);
		ScaleY = 0.0f;
		r->SetScale({ 1.0f,ScaleY,1.0f });
		m_spriteRender.push_back(r);
	}
	//1番→ｱｲﾝｺｺ
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/icon.dds", 400.0f, 400.0f);
	r->SetPosition({ 300.0f,0.0f,0.0f });
	r->SetScale(CVector3::One);
	MulColor = { 1.0f,1.0f,1.0f,alf };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	
	//ボス演出の時のみ出す
	if (Wave == MaxWave) {
		prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
		//SE再生
		ss->Init(L"sound/Boss.wav");
		ss->SetVolume(1.0f);
		ss->Play(false);

		//2番→キケン1
		r = NewGO<prefab::CSpriteRender>(10);
		r->Init(L"sprite/Kiken.dds", 1280.0f, 150.0f);
		r->SetPosition({ AccX1,300.0f,0.0f });
		r->SetScale(CVector3::One);
		MulColor = { 1.0f,1.0f,1.0f,0.0f };
		r->SetMulColor(MulColor);
		m_spriteRender.push_back(r);
		//3番→キケン2
		r = NewGO<prefab::CSpriteRender>(10);
		r->Init(L"sprite/Kiken.dds", 1280.0f, 150.0f);
		r->SetPosition({ AccX2,300.0f,0.0f });
		r->SetScale(CVector3::One);
		MulColor = { 1.0f,1.0f,1.0f,0.0f };
		r->SetMulColor(MulColor);
		m_spriteRender.push_back(r);
		//4番→デンジャー1
		r = NewGO<prefab::CSpriteRender>(10);
		r->Init(L"sprite/Denger.dds", 1280.0f, 100.0f);
		r->SetPosition({ AccX3,300.0f,0.0f });
		r->SetScale(CVector3::One);
		MulColor = { 1.0f,1.0f,1.0f,0.0f };
		r->SetMulColor(MulColor);
		m_spriteRender.push_back(r);
		//5番→デンジャー2
		r = NewGO<prefab::CSpriteRender>(10);
		r->Init(L"sprite/Denger.dds", 1280.0f, 100.0f);
		r->SetPosition({ AccX4,300.0f,0.0f });
		r->SetScale(CVector3::One);
		MulColor = { 1.0f,1.0f,1.0f,0.0f };
		r->SetMulColor(MulColor);
		m_spriteRender.push_back(r);
		///////////////////////////////////////////
		//6番→キケン1
		r = NewGO<prefab::CSpriteRender>(10);
		r->Init(L"sprite/Kiken.dds", 1280.0f, 150.0f);
		r->SetPosition({ AccX1,-300.0f,0.0f });
		r->SetScale(CVector3::One);
		MulColor = { 1.0f,1.0f,1.0f,0.0f };
		r->SetMulColor(MulColor);
		m_spriteRender.push_back(r);
		//7番→キケン2
		r = NewGO<prefab::CSpriteRender>(10);
		r->Init(L"sprite/Kiken.dds", 1280.0f, 150.0f);
		r->SetPosition({ AccX2,-300.0f,0.0f });
		r->SetScale(CVector3::One);
		MulColor = { 1.0f,1.0f,1.0f,0.0f };
		r->SetMulColor(MulColor);
		m_spriteRender.push_back(r);
		//8番→デンジャー1
		r = NewGO<prefab::CSpriteRender>(10);
		r->Init(L"sprite/Denger.dds", 1280.0f, 100.0f);
		r->SetPosition({ AccX3,-300.0f,0.0f });
		r->SetScale(CVector3::One);
		MulColor = { 1.0f,1.0f,1.0f,0.0f };
		r->SetMulColor(MulColor);
		m_spriteRender.push_back(r);
		//9番→デンジャー2
		r = NewGO<prefab::CSpriteRender>(10);
		r->Init(L"sprite/Denger.dds", 1280.0f, 100.0f);
		r->SetPosition({ AccX4,-300.0f,0.0f });
		r->SetScale(CVector3::One);
		MulColor = { 1.0f,1.0f,1.0f,0.0f };
		r->SetMulColor(MulColor);
		m_spriteRender.push_back(r);
	}

	return true;
}

void WaveEffect::Update() {

	//スタンバーイ
	if (Timer == 0) {
		//Wave文字
		f = NewGO<prefab::CFontRender>(11);
		//表示
		wchar_t text[256];
		//おわ
		if (Wave == MaxWave) {
			swprintf(text, L"BOSS WAVE");
		}
		else {
			swprintf(text, L"WAVE %d", Wave);
		}
		//はい。
		f->SetText(text);
		f->SetPosition({ positionX , 20.0f });
		f->SetScale(WaveScale);
		f->SetPivot({ 0.5f,0.5f });
		m_fontRender.push_back(f);
	}

	//背景
	if (Timer < 6) {
		ScaleY += 0.1f;
	}
	else if (Timer < DeleteTimer) {
		ScaleY += 0.005f;
	}
	else {
		ScaleY -= 0.2f;
		if (ScaleY < 0.0f) {
			ScaleY = 0.0f;
		}
	}

	//文字
	if (Timer >= 6 && Timer <= 12) {
		positionX -= 160.0f;
	}
	else if (Timer < DeleteTimer) {
		positionX -= 1.0f;
	}
	else if (Timer >= DeleteTimer) {
		positionX -= 200.0f;
	}

	//画像
	if (Timer < 40) {
		alf += 0.05f;
		if (alf > 1.0f) {
			alf = 1.0f;
		}
	}
	else {
		alf -= 0.1f;
		if (alf < 0.0f) {
			alf = 0.0f;
		}
	}

	if (Wave == MaxWave) {
		//アクセサリー不透明度
		if (Timer < DeleteTimer) {
			Accalf += 0.05f;
			if (Accalf > 0.5f) {
				Accalf = 0.5f;
			}
		}
		else {
			Accalf -= 0.05f;
			if (Accalf < 0.0f) {
				Accalf = 0.0f;
			}
		}

		//アクセサリー移動処理
		AccX1 -= 5.0f;
		if (AccX1 < -1280.0f) {
			AccX1 = 1280.0f;
		}	
		AccX2 -= 5.0f;
		if (AccX2 < -1280.0f) {
			AccX2 = 1280.0f;
		}	
		AccX3 += 20.0f;
		if (AccX3 > 1280.0f) {
			AccX3 = -1280.0f;
		}
		AccX4 += 20.0f;
		if (AccX4 > 1280.0f) {
			AccX4 = -1280.0f;
		}
		//
		AccX5 += 5.0f;
		if (AccX5 > 1280.0f) {
			AccX5 = -1280.0f;
		}
		AccX6 += 5.0f;
		if (AccX6 > 1280.0f) {
			AccX6 = -1280.0f;
		}
		AccX7 -= 20.0f;
		if (AccX7 < -1280.0f) {
			AccX7 = 1280.0f;
		}
		AccX8 -= 20.0f;
		if (AccX8 < -1280.0f) {
			AccX8 = 1280.0f;
		}

		//アクセぶっぱ
		m_spriteRender[2]->SetPosition({ AccX1, 300.0f, 1.0f });
		MulColor = { 1.0f,1.0f,1.0f,Accalf };
		m_spriteRender[2]->SetMulColor(MulColor);
		m_spriteRender[3]->SetPosition({ AccX2, 300.0f, 1.0f });
		MulColor = { 1.0f,1.0f,1.0f,Accalf };
		m_spriteRender[3]->SetMulColor(MulColor);
		m_spriteRender[4]->SetPosition({ AccX3, 300.0f, 1.0f });
		MulColor = { 1.0f,1.0f,1.0f,Accalf };
		m_spriteRender[4]->SetMulColor(MulColor);
		m_spriteRender[5]->SetPosition({ AccX4, 300.0f, 1.0f });
		MulColor = { 1.0f,1.0f,1.0f,Accalf };
		m_spriteRender[5]->SetMulColor(MulColor);
		//
		m_spriteRender[6]->SetPosition({ AccX5, -300.0f, 1.0f });
		MulColor = { 1.0f,1.0f,1.0f,Accalf };
		m_spriteRender[6]->SetMulColor(MulColor);
		m_spriteRender[7]->SetPosition({ AccX6, -300.0f, 1.0f });
		MulColor = { 1.0f,1.0f,1.0f,Accalf };
		m_spriteRender[7]->SetMulColor(MulColor);
		m_spriteRender[8]->SetPosition({ AccX7, -300.0f, 1.0f });
		MulColor = { 1.0f,1.0f,1.0f,Accalf };
		m_spriteRender[8]->SetMulColor(MulColor);
		m_spriteRender[9]->SetPosition({ AccX8, -300.0f, 1.0f });
		MulColor = { 1.0f,1.0f,1.0f,Accalf };
		m_spriteRender[9]->SetMulColor(MulColor);

	}

	if (Wave != MaxWave && Timer==10) {
		prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
		//SE再生
		ss->Init(L"sound/Wave.wav");
		ss->SetVolume(1.0f);
		ss->Play(false);
	}

	//ぶっぱ
	m_fontRender[0]->SetPosition({ positionX , 20.0f });
	m_spriteRender[0]->SetScale({ 1.0f,ScaleY,1.0f });
	MulColor = { 1.0f,1.0f,1.0f,alf };
	m_spriteRender[1]->SetMulColor(MulColor);

	Timer++;

	if (Timer ==  80) {
		DeleteGO(this);
	}
}

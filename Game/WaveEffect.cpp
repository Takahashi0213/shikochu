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
	//ï\é¶
	GameData * gamedata = GameData::GetInstance();
	Wave = gamedata->GetWave();
	Wave += 1;
	MaxWave = gamedata->GetMAX_WaveNo();
	if (Wave == MaxWave) {
		//0î‘Å®îwåi
		r = NewGO<prefab::CSpriteRender>(10);
		r->Init(L"sprite/WaveUnderBoss.dds", 1920.0f, 250.0f);
		ScaleY = 0.0f;
		r->SetScale({ 1.0f,ScaleY,1.0f });
		m_spriteRender.push_back(r);
	}
	else {
		//0î‘Å®îwåi
		r = NewGO<prefab::CSpriteRender>(10);
		r->Init(L"sprite/WaveUnder.dds", 1920.0f, 250.0f);
		ScaleY = 0.0f;
		r->SetScale({ 1.0f,ScaleY,1.0f });
		m_spriteRender.push_back(r);
	}
	//1î‘Å®îwåi
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/icon.dds", 400.0f, 400.0f);
	r->SetPosition({ 300.0f,0.0f,0.0f });
	r->SetScale(CVector3::One);
	MulColor = { 1.0f,1.0f,1.0f,alf };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);

	return true;
}

void WaveEffect::Update() {

	//ÉXÉ^ÉìÉoÅ[ÉC
	if (Timer == 0) {
		//Waveï∂éö
		f = NewGO<prefab::CFontRender>(11);
		//ï\é¶
		wchar_t text[256];
		//Ç®ÇÌ
		if (Wave == MaxWave) {
			swprintf(text, L"BOSS WAVE", Wave);
		}
		else {
			swprintf(text, L"WAVE %d", Wave);
		}
		//ÇÕÇ¢ÅB
		f->SetText(text);
		f->SetPosition({ positionX , 20.0f });
		f->SetScale(WaveScale);
		f->SetPivot({ 0.5f,0.5f });
		m_fontRender.push_back(f);
	}

	//îwåi
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

	//ï∂éö
	if (Timer >= 6 && Timer <= 12) {
		positionX -= 160.0f;
	}
	else if (Timer < DeleteTimer) {
		positionX -= 1.0f;
	}
	else if (Timer >= DeleteTimer) {
		positionX -= 200.0f;
	}

	//âÊëú
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

	m_fontRender[0]->SetPosition({ positionX , 20.0f });
	m_spriteRender[0]->SetScale({ 1.0f,ScaleY,1.0f });
	MulColor = { 1.0f,1.0f,1.0f,alf };
	m_spriteRender[1]->SetMulColor(MulColor);

	Timer++;

	if (Timer ==  80) {
		DeleteGO(this);
	}
}

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
	//�\��
	GameData * gamedata = GameData::GetInstance();
	Wave = gamedata->GetWave();
	Wave += 1;
	MaxWave = gamedata->GetMAX_WaveNo();
	if (Wave == MaxWave) {
		//0�ԁ��w�i
		r = NewGO<prefab::CSpriteRender>(10);
		r->Init(L"sprite/WaveUnderBoss.dds", 1920.0f, 250.0f);
		ScaleY = 0.0f;
		r->SetScale({ 1.0f,ScaleY,1.0f });
		m_spriteRender.push_back(r);
	}
	else {
		//0�ԁ��w�i
		r = NewGO<prefab::CSpriteRender>(10);
		r->Init(L"sprite/WaveUnder.dds", 1920.0f, 250.0f);
		ScaleY = 0.0f;
		r->SetScale({ 1.0f,ScaleY,1.0f });
		m_spriteRender.push_back(r);
	}
	//1�ԁ���ݺ�
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/icon.dds", 400.0f, 400.0f);
	r->SetPosition({ 300.0f,0.0f,0.0f });
	r->SetScale(CVector3::One);
	MulColor = { 1.0f,1.0f,1.0f,alf };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	
	//�{�X���o�̎��̂ݏo��
	if (Wave == MaxWave) {
		//2�ԁ��L�P��1
		r = NewGO<prefab::CSpriteRender>(10);
		r->Init(L"sprite/Kiken.dds", 1280.0f, 150.0f);
		r->SetPosition({ AccX1,300.0f,0.0f });
		r->SetScale(CVector3::One);
		MulColor = { 1.0f,1.0f,1.0f,0.0f };
		r->SetMulColor(MulColor);
		m_spriteRender.push_back(r);
		//3�ԁ��L�P��2
		r = NewGO<prefab::CSpriteRender>(10);
		r->Init(L"sprite/Kiken.dds", 1280.0f, 150.0f);
		r->SetPosition({ AccX2,300.0f,0.0f });
		r->SetScale(CVector3::One);
		MulColor = { 1.0f,1.0f,1.0f,0.0f };
		r->SetMulColor(MulColor);
		m_spriteRender.push_back(r);
		//4�ԁ��f���W���[1
		r = NewGO<prefab::CSpriteRender>(10);
		r->Init(L"sprite/Denger.dds", 1280.0f, 100.0f);
		r->SetPosition({ AccX3,300.0f,0.0f });
		r->SetScale(CVector3::One);
		MulColor = { 1.0f,1.0f,1.0f,0.0f };
		r->SetMulColor(MulColor);
		m_spriteRender.push_back(r);
		//5�ԁ��f���W���[2
		r = NewGO<prefab::CSpriteRender>(10);
		r->Init(L"sprite/Denger.dds", 1280.0f, 100.0f);
		r->SetPosition({ AccX4,300.0f,0.0f });
		r->SetScale(CVector3::One);
		MulColor = { 1.0f,1.0f,1.0f,0.0f };
		r->SetMulColor(MulColor);
		m_spriteRender.push_back(r);
		///////////////////////////////////////////
		//6�ԁ��L�P��1
		r = NewGO<prefab::CSpriteRender>(10);
		r->Init(L"sprite/Kiken.dds", 1280.0f, 150.0f);
		r->SetPosition({ AccX1,-300.0f,0.0f });
		r->SetScale(CVector3::One);
		MulColor = { 1.0f,1.0f,1.0f,0.0f };
		r->SetMulColor(MulColor);
		m_spriteRender.push_back(r);
		//7�ԁ��L�P��2
		r = NewGO<prefab::CSpriteRender>(10);
		r->Init(L"sprite/Kiken.dds", 1280.0f, 150.0f);
		r->SetPosition({ AccX2,-300.0f,0.0f });
		r->SetScale(CVector3::One);
		MulColor = { 1.0f,1.0f,1.0f,0.0f };
		r->SetMulColor(MulColor);
		m_spriteRender.push_back(r);
		//8�ԁ��f���W���[1
		r = NewGO<prefab::CSpriteRender>(10);
		r->Init(L"sprite/Denger.dds", 1280.0f, 100.0f);
		r->SetPosition({ AccX3,-300.0f,0.0f });
		r->SetScale(CVector3::One);
		MulColor = { 1.0f,1.0f,1.0f,0.0f };
		r->SetMulColor(MulColor);
		m_spriteRender.push_back(r);
		//9�ԁ��f���W���[2
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

	//�X�^���o�[�C
	if (Timer == 0) {
		//Wave����
		f = NewGO<prefab::CFontRender>(11);
		//�\��
		wchar_t text[256];
		//����
		if (Wave == MaxWave) {
			swprintf(text, L"BOSS WAVE", Wave);
		}
		else {
			swprintf(text, L"WAVE %d", Wave);
		}
		//�͂��B
		f->SetText(text);
		f->SetPosition({ positionX , 20.0f });
		f->SetScale(WaveScale);
		f->SetPivot({ 0.5f,0.5f });
		m_fontRender.push_back(f);
	}

	//�w�i
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

	//����
	if (Timer >= 6 && Timer <= 12) {
		positionX -= 160.0f;
	}
	else if (Timer < DeleteTimer) {
		positionX -= 1.0f;
	}
	else if (Timer >= DeleteTimer) {
		positionX -= 200.0f;
	}

	//�摜
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
		//�A�N�Z�T���[�s�����x
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

		//�A�N�Z�T���[�ړ�����
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

		//�A�N�Z�Ԃ���
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

	//�Ԃ���
	m_fontRender[0]->SetPosition({ positionX , 20.0f });
	m_spriteRender[0]->SetScale({ 1.0f,ScaleY,1.0f });
	MulColor = { 1.0f,1.0f,1.0f,alf };
	m_spriteRender[1]->SetMulColor(MulColor);

	Timer++;

	if (Timer ==  80) {
		DeleteGO(this);
	}
}

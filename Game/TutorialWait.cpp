#include "stdafx.h"
#include "TutorialWait.h"
#include "StageSelect.h"
#include "Tutorial.h"
#include "TransitionMaker.h"

TutorialWait* TutorialWait::m_instance = nullptr;

TutorialWait::TutorialWait()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

}


TutorialWait::~TutorialWait()
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

bool TutorialWait::Start() {

	//0番 枠
	r = NewGO<prefab::CSpriteRender>(17);
	r->Init(L"sprite/question.dds", 575.0f, 226.0f);
	r->SetPosition({ 0.0f ,100.0f,0.0f });
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//1番 Yes
	r = NewGO<prefab::CSpriteRender>(17);
	r->Init(L"sprite/Yes.dds", 203.0f, 203.0f);
	r->SetPosition({ -200.0f ,-150.0f,0.0f });
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//2番 No
	r = NewGO<prefab::CSpriteRender>(17);
	r->Init(L"sprite/No.dds", 203.0f, 203.0f);
	r->SetPosition({ 200.0f ,-150.0f,0.0f });
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//3番 虫
	r = NewGO<prefab::CSpriteRender>(18);
	r->Init(L"sprite/icon3.dds", 200.0f, 200.0f);
	r->SetPosition({ 200.0f ,-150.0f,0.0f });
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	r->SetMulColor(MulColor);
	r->SetScale({ 10.0f,10.0f,10.0f });
	m_spriteRender.push_back(r);
	//4番 星
	r = NewGO<prefab::CSpriteRender>(18);
	r->Init(L"sprite/Star2.dds", 200.0f, 200.0f);
	r->SetPosition({ 200.0f ,-150.0f,0.0f });
	MulColor = { 1.0f,1.0f,1.0f,1.0f };
	r->SetMulColor(MulColor);
	r->SetScale({ 0.0f,0.0f,0.0f });
	m_spriteRender.push_back(r);

	//ハイスコア 0番
	f = NewGO<prefab::CFontRender>(18);
	//表示
	wchar_t text[256];
	//おわ
	swprintf(text, L"チュートリアルをみますか？");
	//はい。
	f->SetText(text);
	f->SetPosition({ 0.0f ,70.0f });
	f->SetScale(1.0f);
	MulColor = { 1.0f,1.0f,1.0f,0.0f };
	f->SetColor(MulColor);
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);

	return true;
}

void TutorialWait::Update() {

	if (Timer < 12) {//上移動
		for (int i = 0; i < 3; i++) {
			CVector3 pos = m_spriteRender[i]->GetPosition();
			pos.y += 2.0f;
			m_spriteRender[i]->SetPosition(pos);
			CVector4 col = m_spriteRender[i]->GetMulColor();
			col.a += 0.1f;
			if (col.a > 1.0f && i == 0) {
				col.a = 1.0f;
			}
			if (col.a > 0.2f && i > 0) {
				col.a = 0.2f;
			}
			m_spriteRender[i]->SetMulColor(col);
			Sentaku_Y = pos.y;
		}
		CVector2 t_pos = m_fontRender[0]->GetPosition();
		t_pos.y += 2.0f;
		m_fontRender[0]->SetPosition(t_pos);
		MulAlpha += 0.1f;
		if (MulAlpha > 1.0f) {
			MulAlpha = 1.0f;
		}
		MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
		m_fontRender[0]->SetColor(MulColor);

	}

	if ((Pad(0).IsTrigger(enButtonLeft)&& DeleteFlag ==false)|| (Pad(0).IsTrigger(enButtonRight) && DeleteFlag == false)) {//変更
		ss = NewGO<prefab::CSoundSource>(0);
		//SE再生
		ss->Init(L"sound/TitleSelect.wav");
		ss->SetVolume(1.0f);
		ss->Play(false);

		if (SelectNow == false) {
			SelectNow = true;
		}
		else if (SelectNow == true) {
			SelectNow = false;
		}
	}
	else if (Pad(0).IsTrigger(enButtonA) && Timer > 30&& DeleteFlag==false) {

		ss = NewGO<prefab::CSoundSource>(0);
		//SE再生
		ss->Init(L"sound/TitleOK.wav");
		ss->SetVolume(1.0f);
		ss->Play(false);

		DeleteFlag = true;

	}

	if (Timer > 30 && DeleteFlag == false) {
		SelectUp();
	}

	if (DeleteFlag == true) {//終了

		if (DeleteTimer == 0) {//準備
			if (SelectNow == true) {//Yes
				m_spriteRender[3]->SetPosition({ -200.0f,Sentaku_Y,0.0f });
				m_spriteRender[4]->SetPosition({ -200.0f,Sentaku_Y,0.0f });
			}
			else if (SelectNow == false) {//No
				m_spriteRender[3]->SetPosition({ 200.0f,Sentaku_Y,0.0f });
				m_spriteRender[4]->SetPosition({ 200.0f,Sentaku_Y,0.0f });
			}
		}

		//先に消去
		if (SelectNow == true) {//Yes
			CVector4 col = m_spriteRender[2]->GetMulColor();
			col.a -= 0.05f;
			if (col.a < 0.0f) {
				col.a = 0.0f;
			}
			m_spriteRender[2]->SetMulColor(col);
		}
		else if (SelectNow == false) {//No
			CVector4 col = m_spriteRender[1]->GetMulColor();
			col.a -= 0.05f;
			if (col.a < 0.0f) {
				col.a = 0.0f;
			}
			m_spriteRender[1]->SetMulColor(col);
		}

		//虫の突撃
		if (DeleteTimer < 12) {
			CVector4 m_col = m_spriteRender[3]->GetMulColor();
			m_col.a += 0.1f;
			if (m_col.a > 1.0f) {
				m_col.a = 1.0f;
			}
			m_spriteRender[3]->SetMulColor(m_col);
			CVector3 scl = m_spriteRender[3]->GetScale();
			scl *= 0.80f;
			m_spriteRender[3]->SetScale(scl);
			MulAlpha = 1.0f;
		}
		else {//消えます
			CVector3 scl = m_spriteRender[3]->GetScale();
			scl *= 1.1f;
			m_spriteRender[3]->SetScale(scl);
			scl = m_spriteRender[4]->GetScale();
			scl.x += 0.2f;
			scl.y += 0.2f;
			m_spriteRender[4]->SetScale(scl);

			CVector4 m_col = m_spriteRender[3]->GetMulColor();
			m_col.a -= 0.1f;
			if (m_col.a < 0.0f) {
				m_col.a = 0.0f;
			}
			m_spriteRender[3]->SetMulColor(m_col);
			m_col = m_spriteRender[4]->GetMulColor();
			m_col.a -= 0.05f;
			if (m_col.a < 0.0f) {
				m_col.a = 0.0f;
			}
			m_spriteRender[4]->SetMulColor(m_col);

			if (DeleteTimer > 24) {
				//不透明度
				for (int i = 0; i < 3; i++) {
					CVector4 col = m_spriteRender[i]->GetMulColor();
					col.a -= 0.1f;
					if (col.a < 0.0f) {
						col.a = 0.0f;
					}
					m_spriteRender[i]->SetMulColor(col);
				}
				MulAlpha -= 0.1f;
				if (MulAlpha < 0.0f) {
					MulAlpha = 0.0f;
				}
				MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
				m_fontRender[0]->SetColor(MulColor);
				//////移動
				for (int i = 0; i < 3; i++) {
					CVector3 pos = m_spriteRender[i]->GetPosition();
					pos.y += 2.0f;
					m_spriteRender[i]->SetPosition(pos);
				}
				CVector2 t_pos = m_fontRender[0]->GetPosition();
				t_pos.y += 2.0f;
				m_fontRender[0]->SetPosition(t_pos);
			}
		}

		if (DeleteTimer == 70) {
			if (SelectNow == true) {//Yes
				NewGO<Tutorial>(0);
			}
			else if (SelectNow == false) {//No
				NewGO<StageSelect>(0);
			}
			TransitionMaker * tm = TransitionMaker::GetInstance();
			tm->TransitionSetting(TransitionMaker::Fade, 12, 24, true);
		}
		if (DeleteTimer == 80) {
			DeleteGO(this);
		}

		DeleteTimer++;
	}


	Timer++;
}

void TutorialWait::SelectUp() {

	//本来の状態でないなら修正する
	if (SelectNow == true) {//Yes
		CVector3 pos = m_spriteRender[1]->GetPosition();
		if (pos.y < -100.0f) {
			pos.y += 5.0f;
			if (pos.y > -100.0f) {
				pos.y = -100.0f;
			}
			m_spriteRender[1]->SetPosition(pos);
		}
		CVector4 col = m_spriteRender[1]->GetMulColor();
		if (col.a < 1.0f) {
			col.a += 0.1f;
			if (col.a > 1.0f) {
				col.a = 1.0f;
			}
			m_spriteRender[1]->SetMulColor(col);
		}
		////
		pos = m_spriteRender[2]->GetPosition();
		if (pos.y > Sentaku_Y) {
			pos.y -= 5.0f;
			if (pos.y < Sentaku_Y) {
				pos.y = Sentaku_Y;
			}
			m_spriteRender[2]->SetPosition(pos);
		}
		col = m_spriteRender[2]->GetMulColor();
		if (col.a > 0.2f) {
			col.a -= 0.1f;
			if (col.a < 0.2f) {
				col.a = 0.2f;
			}
			m_spriteRender[2]->SetMulColor(col);
		}

	}
	else if (SelectNow == false) {//No

		CVector3 pos = m_spriteRender[2]->GetPosition();
		if (pos.y < -100.0f) {
			pos.y += 5.0f;
			if (pos.y > -100.0f) {
				pos.y = -100.0f;
			}
			m_spriteRender[2]->SetPosition(pos);
		}
		CVector4 col = m_spriteRender[2]->GetMulColor();
		if (col.a < 1.0f) {
			col.a += 0.1f;
			if (col.a > 1.0f) {
				col.a = 1.0f;
			}
			m_spriteRender[2]->SetMulColor(col);
		}
		////
		pos = m_spriteRender[1]->GetPosition();
		if (pos.y > Sentaku_Y) {
			pos.y -= 5.0f;
			if (pos.y < Sentaku_Y) {
				pos.y = Sentaku_Y;
			}
			m_spriteRender[1]->SetPosition(pos);
		}
		col = m_spriteRender[1]->GetMulColor();
		if (col.a > 0.2f) {
			col.a -= 0.1f;
			if (col.a < 0.2f) {
				col.a = 0.2f;
			}
			m_spriteRender[1]->SetMulColor(col);
		}
	}

}
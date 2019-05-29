#include "stdafx.h"
#include "StageWait.h"

StageWait* StageWait::m_instance = nullptr;

StageWait::StageWait()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;
}


StageWait::~StageWait()
{
	for (int i = 0; i < m_spriteRender.size(); i++) {
		DeleteGO(m_spriteRender[i]);
	}

	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;

}

void StageWait::Update() {
	if (Flag == true) {

		//装飾
		if (Timer < 60) {
			MulAlpha += 0.05f;
			if (MulAlpha > 1.0f) {
				MulAlpha = 1.0f;
			}
			MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
			m_spriteRender[0]->SetMulColor(MulColor);
			m_spriteRender[1]->SetMulColor(MulColor);
			m_spriteRender[5]->SetMulColor(MulColor);

			if (Accflag == true) {
				m_spriteRender[6]->SetMulColor(MulColor);
			}

		}
		//土台がバシュン
		if (Timer < 7) {
			CVector3 scl = m_spriteRender[1]->GetScale();
			scl.x += 0.1f;
			scl.y += 0.01f;
			m_spriteRender[1]->SetScale(scl);

			if (Accflag == true) {
				m_spriteRender[6]->SetScale(scl);
			}

		}
		else if (Timer < 13) {
			CVector3 scl = m_spriteRender[1]->GetScale();
			scl.x -= 0.12f;
			scl.y += 0.25f;
			m_spriteRender[1]->SetScale(scl);

			if (Accflag == true) {
				m_spriteRender[6]->SetScale(scl);
			}

		}
		else if (Timer < 19) {
			CVector3 scl = m_spriteRender[1]->GetScale();
			scl.x += 0.2f;
			scl.y -= 0.1f;
			m_spriteRender[1]->SetScale(scl);

			if (Accflag == true) {
				m_spriteRender[6]->SetScale(scl);
			}

		}
		else if(Timer < 60) {
			CVector3 scl = m_spriteRender[1]->GetScale();
			if (scl.x < 1.0f) {
				scl.x += 0.1f;
				if (scl.x > 1.0f) {
					scl.x = 1.0f;
				}
			}
			if (scl.x > 1.0f) {
				scl.x -= 0.1f;
				if (scl.x < 1.0f) {
					scl.x = 1.0f;
				}
			}
			//
			if (scl.y > 1.0f) {
				scl.y -= 0.1f;
				if (scl.y < 1.0f) {
					scl.y = 1.0f;
				}
			}
			if (scl.y < 1.0f) {
				scl.y += 0.1f;
				if (scl.y > 1.0f) {
					scl.y = 1.0f;
				}
			}

			m_spriteRender[1]->SetScale(scl);

			if (Accflag == true) {
				m_spriteRender[6]->SetScale(scl);
			}

		}
		//土台がムーヴヴヴ
		if (Timer < 7) {
			CVector3 pos = m_spriteRender[1]->GetPosition();
			pos.y += 0.05f;
			m_spriteRender[1]->SetPosition(pos);

			if (Accflag == true) {
				m_spriteRender[6]->SetPosition(pos);
			}

		}
		else if (Timer < 13) {
			CVector3 pos = m_spriteRender[1]->GetPosition();
			pos.y -= 0.05f;
			m_spriteRender[1]->SetPosition(pos);

			if (Accflag == true) {
				m_spriteRender[6]->SetPosition(pos);
			}

		}

		//////////////////////////////////////////////////////////////
		//文字だしマン
		if (Timer >= 60 && Timer < 90) {
			CVector3 pos = m_spriteRender[2]->GetPosition();
			pos.y += 1.0f;
			m_spriteRender[2]->SetPosition(pos);
			MulAlpha2 += 0.05f;
			if (MulAlpha2 > 1.0f) {
				MulAlpha2 = 1.0f;
			}
			MulColor = { 1.0f,1.0f,1.0f,MulAlpha2 };
			m_spriteRender[2]->SetMulColor(MulColor);
		}
		if (Timer >= 120 && Timer < 150) {
			CVector3 pos = m_spriteRender[3]->GetPosition();
			pos.y += 1.0f;
			m_spriteRender[3]->SetPosition(pos);
			MulAlpha3 += 0.05f;
			if (MulAlpha3 > 1.0f) {
				MulAlpha3 = 1.0f;
			}
			MulColor = { 1.0f,1.0f,1.0f,MulAlpha3 };
			m_spriteRender[3]->SetMulColor(MulColor);
		}	
		if (Timer >= 180 && Timer < 210) {
			CVector3 pos = m_spriteRender[4]->GetPosition();
			pos.y += 1.0f;
			m_spriteRender[4]->SetPosition(pos);
			MulAlpha4 += 0.05f;
			if (MulAlpha4 > 1.0f) {
				MulAlpha4 = 1.0f;
			}
			MulColor = { 1.0f,1.0f,1.0f,MulAlpha4 };
			m_spriteRender[4]->SetMulColor(MulColor);
		}

		if (Timer > 60) {
			JumpStart();
		}

		Timer++;
	}
	else {
		Timer = 0;
	}

	if (DeleteFlag == true) {
		if (DeleteTimer < 60) {
			MulAlpha -= 0.05f;
			MulAlphaAcc -= 0.05f;
			if (MulAlpha < 0.0f) {
				MulAlpha = 0.0f;
			}		
			if (MulAlphaAcc < 0.0f) {
				MulAlphaAcc = 0.0f;
			}
			MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
			m_spriteRender[0]->SetMulColor(MulColor);
			m_spriteRender[1]->SetMulColor(MulColor);
			m_spriteRender[2]->SetMulColor(MulColor);
			m_spriteRender[3]->SetMulColor(MulColor);
			m_spriteRender[4]->SetMulColor(MulColor);
			m_spriteRender[5]->SetMulColor(MulColor);
			MulColor = { MulAlphaAcc,MulAlphaAcc,MulAlphaAcc,1.0f };
			if (Accflag == true) {
				m_spriteRender[6]->SetMulColor(MulColor);
			}

		}
		if (DeleteTimer == 60) {
			DeleteGO(this);
		}
		JumpStart();
		DeleteTimer++;
	}

}

void StageWait::WaitSet(int stage) {

	//セッティング
	//0番 左右の飾り
	r = NewGO<prefab::CSpriteRender>(16);
	r->Init(L"sprite/loadingAcc.dds", 1280.0f, 720.0f);
	r->SetPosition({ 0.0f ,0.0f,0.0f });
	r->SetScale({ 1.0f ,1.0f,1.0f });
	r->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
	m_spriteRender.push_back(r);
	//1番 枠
	r = NewGO<prefab::CSpriteRender>(16);
	r->Init(L"sprite/loadingAcc2.dds", 1002.0f, 617.0f);
	r->SetPosition({ 0.0f ,70.0f,0.0f });
	r->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
	r->SetScale({ 0.0f ,0.0f,1.0f });
	m_spriteRender.push_back(r);
	//2番 文字1
	int X = 0 + (stage * 3);
	r = NewGO<prefab::CSpriteRender>(16);
	r->Init(Message[X], 1002.0f, 617.0f);
	r->SetPosition({ 0.0f ,50.0f,0.0f });
	r->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
	r->SetScale({ 1.0f ,1.0f,1.0f });
	m_spriteRender.push_back(r);
	X++;
	//3番 文字2
	r = NewGO<prefab::CSpriteRender>(16);
	r->Init(Message[X], 1002.0f, 617.0f);
	r->SetPosition({ 0.0f ,50.0f,0.0f });
	r->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
	r->SetScale({ 1.0f ,1.0f,1.0f });
	m_spriteRender.push_back(r);
	X++;
	//4番 文字3
	r = NewGO<prefab::CSpriteRender>(16);
	r->Init(Message[X], 1002.0f, 617.0f);
	r->SetPosition({ 0.0f ,50.0f,0.0f });
	r->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
	r->SetScale({ 1.0f ,1.0f,1.0f });
	m_spriteRender.push_back(r);
	//5番 プッシュ！
	r = NewGO<prefab::CSpriteRender>(16);
	r->Init(L"sprite/pushA.dds", 550.0f, 113.0f);
	r->SetPosition({ 0.0f ,-300.0f,0.0f });
	r->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
	r->SetScale({ 1.0f ,1.0f,1.0f });
	m_spriteRender.push_back(r);

	if (MessageAcc[stage] == true) {
		//6番 メッセージアクセサリー
		r = NewGO<prefab::CSpriteRender>(16);
		r->Init(MessageAccName[stage], 1002.0f, 617.0f);
		r->SetPosition({ 0.0f ,70.0f,0.0f });
		r->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
		r->SetScale({ 1.0f ,1.0f,1.0f });
		m_spriteRender.push_back(r);

		Accflag = true;
	}
	else {
		Accflag = false;
	}

	//フラグググ
	Flag = true;
}

void StageWait::WaitDelete() {
	DeleteFlag = true;
	Flag = false;
}

void StageWait::JumpStart() {

	if (JumpTimer >= 0 && JumpTimer < 40) {
		CVector3 pos = m_spriteRender[5]->GetPosition();
		pos.y += 1.0f;
		m_spriteRender[5]->SetPosition(pos);
	}
	else if (JumpTimer >= 0 && JumpTimer <= 45) {
		CVector3 pos = m_spriteRender[5]->GetPosition();
		pos.y -= 7.0f;
		m_spriteRender[5]->SetPosition(pos);
		CVector3 scl = m_spriteRender[5]->GetScale();
		scl.x += 0.01f;
		scl.y -= 0.05f;
		m_spriteRender[5]->SetScale(scl);
	}
	else if (JumpTimer >= 0 && JumpTimer <= 50) {
		CVector3 pos = m_spriteRender[5]->GetPosition();
		pos.y += 3.0f;
		m_spriteRender[5]->SetPosition(pos);
		CVector3 scl = m_spriteRender[5]->GetScale();
		scl.x -= 0.05f;
		scl.y += 0.1f;
		m_spriteRender[5]->SetScale(scl);
	}
	else if (JumpTimer >= 0 && JumpTimer <= 55) {
		CVector3 pos = m_spriteRender[5]->GetPosition();
		pos.y -= 2.0f;
		m_spriteRender[5]->SetPosition(pos);
		CVector3 scl = m_spriteRender[5]->GetScale();
		scl.x += 0.05f;
		scl.y -= 0.05f;
		m_spriteRender[5]->SetScale(scl);
	}
	else if (JumpTimer >= 0 && JumpTimer <= 61) {
		CVector3 scl = m_spriteRender[5]->GetScale();
		if (JumpTimer == 56) {
			JumpSclX = 1.0f - scl.x;
			JumpSclY = 1.0f - scl.y;
			JumpSclX /= 5.0f;
			JumpSclY /= 5.0f;
		}
		scl.x += JumpSclX;
		scl.y += JumpSclY;
		m_spriteRender[5]->SetScale(scl);

	}
	else if(JumpTimer == 62) {
		m_spriteRender[5]->SetPosition({ 0.0f ,-298.0f,0.0f });
		m_spriteRender[5]->SetScale({ 1.0f ,1.0f,1.0f });
		CVector3 pos = m_spriteRender[5]->GetPosition();
		CVector3 scl = m_spriteRender[5]->GetScale();
	}
	else if (JumpTimer == 63) {
		m_spriteRender[5]->SetPosition({ 0.0f ,-300.0f,0.0f });
		m_spriteRender[5]->SetScale({ 1.0f ,1.0f,1.0f });
		CVector3 pos = m_spriteRender[5]->GetPosition();
		CVector3 scl = m_spriteRender[5]->GetScale();

		JumpTimer = -60;
	}


	JumpTimer++;

}
#include "stdafx.h"
#include "OP.h"
#include "TransitionMaker.h"

OP* OP::m_instance = nullptr;

OP::OP()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;
	
	//NewGO<TransitionMaker>(0, "TransitionMaker");

}


OP::~OP()
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

bool OP::Start() {

	ss = NewGO<prefab::CSoundSource>(0);
	//SE再生
	ss->Init(L"sound/start.wav");
	ss->SetVolume(BMG_V);
	ss->Play(true);

	//0番 上部枠
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/OPED_waku.dds", 1280.0f, 720.0f);
	r->SetPosition({ 0.0f ,0.0f,0.0f });
	m_spriteRender.push_back(r);
	//1番 背景
	r = NewGO<prefab::CSpriteRender>(1);
	r->Init(L"sprite/OPED_back4.dds", 1280.0f, 720.0f);
	r->SetPosition({ 0.0f ,0.0f,0.0f });
	m_spriteRender.push_back(r);
	//2番 背景
	r = NewGO<prefab::CSpriteRender>(1);
	r->Init(L"sprite/OPED_back3.dds", 1280.0f, 720.0f);
	r->SetPosition({ 0.0f ,0.0f,0.0f });
	m_spriteRender.push_back(r);
	//3番 背景
	r = NewGO<prefab::CSpriteRender>(1);
	r->Init(L"sprite/OPED_back2.dds", 1280.0f, 720.0f);
	r->SetPosition({ 0.0f ,0.0f,0.0f });
	m_spriteRender.push_back(r);
	//4番 背景
	r = NewGO<prefab::CSpriteRender>(1);
	r->Init(L"sprite/OPED_back1.dds", 1280.0f, 720.0f);
	r->SetPosition({ 0.0f ,0.0f,0.0f });
	m_spriteRender.push_back(r);
	//5番 プレイヤー1
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/OPED_4.dds", 444.0f, 779.0f);
	r->SetPosition({ 0.0f ,180.0f + DEF_POS,0.0f });
	m_spriteRender.push_back(r);
	//6番 プレイヤー2
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/OPED_1.dds", 418.0f, 662);
	r->SetPosition({ -300.0f ,120.0f + DEF_POS,0.0f });
	m_spriteRender.push_back(r);
	//7番 プレイヤー3
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/OPED_4.dds", 444.0f, 779.0f);
	r->SetPosition({ 0.0f ,80.0f + DEF_POS,0.0f });
	m_spriteRender.push_back(r);
	//8番 ブンローグ
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/OPED_3.dds", 590.0f, 694.0f);
	r->SetPosition({ 350.0f ,280.0f + DEF_POS,0.0f });
	m_spriteRender.push_back(r);
	//9番 ネオリク
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/OPED_6.dds", 617.0f, 675.0f);
	r->SetPosition({ -350.0f ,280.0f + DEF_POS,0.0f });
	m_spriteRender.push_back(r);
	//10番 かざり
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/OPED_7.dds", 1280.0f, 920.0f);
	r->SetPosition({ 0.0f ,40.0f + DEF_POS,0.0f });
	m_spriteRender.push_back(r);
	//11番 オレ様
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/OPED_5.dds", 820.0f, 920.0f);
	r->SetPosition({ -50.0f ,60.0f + DEF_POS,0.0f });
	m_spriteRender.push_back(r);
	//12番 黒い
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/Black.dds", 1280.0f, 720.0f);
	r->SetPosition({ 0.0f ,0.0f,0.0f });
	m_spriteRender.push_back(r);
	//13番 ロゴ
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/rogo.dds", 440.0f, 245.0f);
	r->SetPosition({ 0.0f ,0.0f,0.0f });
	m_spriteRender.push_back(r);

	//テキスト 0番
	f = NewGO<prefab::CFontRender>(11);
	//表示
	wchar_t text[256];
	//おわ
	swprintf(text, L"");
	//はい。
	f->SetText(text);
	f->SetPosition({ 0.0f,-315.0f });
	f->SetScale(TextScale);
	f->SetColor({ 1.0f,1.0f,1.0f,0.0f });
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);

	return true;
}

void OP::Update() {

	switch (OP_Scene) {

	case Hazimari://はじまり
	{
		if (Timer == 12) {
			BounderSet(5);
			wchar_t text[256];
			//おわ
			swprintf(text, L"あるところに「シコウチュウ」というムシがいました");
			//はい。
			m_fontRender[0]->SetText(text);
		}

		if (Timer >= 12) {
			MulAlpha += 0.05f;
			if (MulAlpha > 1.0f) {
				MulAlpha = 1.0f;
			}
			m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,MulAlpha });
		}

		if (Timer >= Scene1_Limit) {//時間だ
			Timer = 0;
			MulAlpha = 0.0f;
			OP_Scene = Seisitu;
			UpperSet(5);
			KamisibaiSet(4);
		}
		break;
	}
	case Seisitu://性質
	{
		if (Timer < 12) {
			MulAlpha -= 0.1f;
			if (MulAlpha < 0.0f) {
				MulAlpha = 0.0f;
			}
			m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,MulAlpha });
		}

		if (Timer == 12) {//テキストA
			BounderSet(6);
			wchar_t text[256];
			//おわ
			swprintf(text, L"シコウチュウはじゅみょうがみじかく、");
			//はい。
			m_fontRender[0]->SetText(text);
		}
		if (Timer == 180) {//テキストB
			wchar_t text[256];
			//おわ
			swprintf(text, L"すぐにほしになってしまうムシでした");
			//はい。
			m_fontRender[0]->SetText(text);
		}

		if (Timer >= 12&& Timer < 60) {//テキストA表示
			MulAlpha += 0.05f;
			if (MulAlpha > 1.0f) {
				MulAlpha = 1.0f;
			}
			m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,MulAlpha });
		}
		if (Timer > 160 && Timer < 180) { //テキストA消去
			MulAlpha -= 0.1f;
			if (MulAlpha < 0.0f) {
				MulAlpha = 0.0f;
			}
			m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,MulAlpha });
		}
		if (Timer > 180 && Timer < 220) {//テキストB表示
			MulAlpha += 0.05f;
			if (MulAlpha > 1.0f) {
				MulAlpha = 1.0f;
			}
			m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,MulAlpha });
		}
		if (Timer >= 200) {

			scl = m_spriteRender[6]->GetScale();
			if (KuruTimer < 6) {
				scl.x -= 0.2f;
				if (scl.x < 0.0f) {
					scl.x = 0.0f;
				}
			}
			if (KuruTimer == 6) {
				//画像の切り替え
				m_spriteRender[6]->Init(L"sprite/OPED_2.dds", 418.0f, 662);
				pos = m_spriteRender[6]->GetPosition();
				pos.x += 35.0f;
				m_spriteRender[6]->SetPosition(pos);
			}
			if (KuruTimer > 6) {
				scl.x += 0.2f;
				if (scl.x > 1.0f) {
					scl.x = 1.0f;
				}
			}

			m_spriteRender[6]->SetScale(scl);
			KuruTimer++;
		}

		//動きます
		if (Timer < 200) {
			pos = m_spriteRender[6]->GetPosition();
			pos.x += 2.0f;
			m_spriteRender[6]->SetPosition(pos);
		}

		if (Timer >= Scene2_Limit) {//時間だ
			UpperSet(6);
			KamisibaiSet(3);
			Timer = 0;
			MulAlpha = 0.0f;
			OP_Scene = sinigami;
		}

		break;
	}
	case sinigami://性質
	{
		if (Timer < 12) {
			MulAlpha -= 0.1f;
			if (MulAlpha < 0.0f) {
				MulAlpha = 0.0f;
			}
			m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,MulAlpha });
		}

		if (Timer == 12) {//テキストA
			BounderSet(7);
			wchar_t text[256];
			//おわ
			swprintf(text, L"ちいさなムシはケツイしました");
			//はい。
			m_fontRender[0]->SetText(text);
		}
		if (Timer == 180) {//テキストB
			BounderSet(8);
			BounderSet(9);
			wchar_t text[256];
			//おわ
			swprintf(text, L"いきているうちになにかをなしとげよう、と");
			//はい。
			m_fontRender[0]->SetText(text);
		}

		if (Timer >= 12 && Timer < 60) {//テキストA表示
			MulAlpha += 0.05f;
			if (MulAlpha > 1.0f) {
				MulAlpha = 1.0f;
			}
			m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,MulAlpha });
		}
		if (Timer > 160 && Timer < 180) { //テキストA消去
			MulAlpha -= 0.1f;
			if (MulAlpha < 0.0f) {
				MulAlpha = 0.0f;
			}
			m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,MulAlpha });
		}
		if (Timer > 180 && Timer < 220) {//テキストB表示
			MulAlpha += 0.05f;
			if (MulAlpha > 1.0f) {
				MulAlpha = 1.0f;
			}
			m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,MulAlpha });
		}

		if (Timer >= Scene3_Limit) {//時間だ
			UpperSet(7);
			UpperSet(8);
			UpperSet(9);
			KamisibaiSet(2);
			Timer = 0;
			MulAlpha = 0.0f;
			OP_Scene = ganbaru;
		}

		break;
	}
	case ganbaru://がんばるぞ
	{
		if (Timer < 12) {
			MulAlpha -= 0.1f;
			if (MulAlpha < 0.0f) {
				MulAlpha = 0.0f;
			}
			m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,MulAlpha });
		}
		if (Timer == 12) {//テキストA
			BounderSet(10);
			wchar_t text[256];
			//おわ
			swprintf(text, L"シコウチュウのぼうけんがはじまります！");
			//はい。
			m_fontRender[0]->SetText(text);
		}
		if (Timer == 24) {
			BounderSet(11);
		}
		if (Timer >= 12 && Timer < 60) {//テキストA表示
			MulAlpha += 0.05f;
			if (MulAlpha > 1.0f) {
				MulAlpha = 1.0f;
			}
			m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,MulAlpha });
		}

		if (Timer > 24) {
			pos = m_spriteRender[11]->GetPosition();
			pos.y += 1.0f;
			m_spriteRender[11]->SetPosition(pos);
		}

		if (Timer >= Scene4_Limit) {//時間だ
			UpperSet(10);
			UpperSet(11);
			KamisibaiSet(1);
			Timer = 0;
			MulAlpha = 0.0f;
			OP_Scene = END;
		}

		break;
	}
	case END://がんばるぞ
	{
		if (Timer < 12) {

			MulAlpha -= 0.1f;
			if (MulAlpha < 0.0f) {
				MulAlpha = 0.0f;
			}
			m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,MulAlpha });
		}

		if (Timer == 180) {
			TransitionMaker * tm = TransitionMaker::GetInstance();
			tm->TransitionSetting(TransitionMaker::Fade, 12, 0, false);
		}

		if (Timer > 100) {
			BMG_V -= 0.01f;
			if (BMG_V < 0.0f) {
				BMG_V = 0.0f;
			}
			ss->SetVolume(BMG_V);
		}

		if (Timer >= Scene5_Limit) {//時間だ
			DeleteGO(this);
		}

		break;
	}

	}

	Bounder();
	Upper();
	Kamisibai();

	Timer++;
}

void OP::BounderSet(int x) {

	for (int i = 0; i < 5; i++) {
		if (BoundSet[i] == -1) {
			BoundSet[i] = x;
			BoundTimer[i] = 0;
			break;
		}
	}
}

void OP::Bounder() {

	//バウンドします
	for (int i = 0; i < 5; i++) {
		if (BoundSet[i] > -1) {
			int Nom = BoundSet[i];
			int Time= BoundTimer[i];
			pos = m_spriteRender[Nom]->GetPosition();

			if (Time < 24) {
				pos.y -= (DEF_POS / 24) + 5;
				//セット
				m_spriteRender[Nom]->SetPosition(pos);
			}
			else if (Time < 36) {
				pos.y += 6.0f;
				//セット
				m_spriteRender[Nom]->SetPosition(pos);
			}
			else if (Time < 48) {
				pos.y -= 4.0f;
				//セット
				m_spriteRender[Nom]->SetPosition(pos);
			}
			else {
				//終了
				BoundSet[i] = -1;
				BoundTimer[i] = -2;
			}

			BoundTimer[i]++;
		}
	}

}

void OP::UpperSet(int x) {

	for (int i = 0; i < 5; i++) {
		if (UppSet[i] == -1) {
			UppSet[i] = x;
			UpperTimer[i] = 0;
			break;
		}
	}
}

void OP::Upper() {

	//アップします
	for (int i = 0; i < 5; i++) {
		if (UppSet[i] > -1) {
			int Nom = UppSet[i];
			int Time = UpperTimer[i];
			pos = m_spriteRender[Nom]->GetPosition();

			if (Time < 12) {
				pos.y -= 5.0f;
				//セット
				m_spriteRender[Nom]->SetPosition(pos);
			}
			else if (Time < 36) {
				pos.y += (DEF_POS / 24) + 6;
				//セット
				m_spriteRender[Nom]->SetPosition(pos);
			}
			else {
				//終了
				UppSet[i] = -1;
				UpperTimer[i] = -2;
			}

			UpperTimer[i]++;
		}
	}

}

void OP::KamisibaiSet(int x) {
	KamisibaiNo = x;
	KamisibaiTimer = 0;
}

void OP::Kamisibai() {

	if (KamisibaiNo > -1) {
		pos = m_spriteRender[KamisibaiNo]->GetPosition();

		if (KamisibaiTimer < 12) {
			pos.x -= 2.0f;
			m_spriteRender[KamisibaiNo]->SetPosition(pos);
		}
		else if (KamisibaiTimer < 24) {
			pos.x += 120.0f;
			m_spriteRender[KamisibaiNo]->SetPosition(pos);
		}
		else {
			KamisibaiNo = -1;
			KamisibaiTimer = -2;
		}

		KamisibaiTimer++;
	}
}

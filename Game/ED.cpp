#include "stdafx.h"
#include "ED.h"
#include "TransitionMaker.h"

ED* ED::m_instance = nullptr;

ED::ED()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;

}


ED::~ED()
{
	for (int i = 0; i < m_spriteRender.size(); i++) {
		DeleteGO(m_spriteRender[i]);
	}
	for (int i = 0; i < m_fontRender.size(); i++) {
		DeleteGO(m_fontRender[i]);
	}

	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
}

bool ED::Start() {

	ss = NewGO<prefab::CSoundSource>(0);
	//SE�Đ�
	ss->Init(L"sound/start.wav");
	ss->SetVolume(BMG_V);
	ss->Play(true);

	//0�� �㕔�g
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/OPED_waku.dds", 1280.0f, 720.0f);
	r->SetPosition({ 0.0f ,0.0f,0.0f });
	m_spriteRender.push_back(r);
	//1�� �w�i
	r = NewGO<prefab::CSpriteRender>(1);
	r->Init(L"sprite/OPED_back4.dds", 1280.0f, 720.0f);
	r->SetPosition({ 0.0f ,0.0f,0.0f });
	m_spriteRender.push_back(r);

	//�e�L�X�g 0��
	f = NewGO<prefab::CFontRender>(11);
	//�\��
	wchar_t text[256];
	//����
	swprintf(text, L"");
	//�͂��B
	f->SetText(text);
	f->SetPosition({ 0.0f,-315.0f });
	f->SetScale(TextScale);
	f->SetColor({ 1.0f,1.0f,1.0f,0.0f });
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);
	//�X�L�b�v 1��
	f = NewGO<prefab::CFontRender>(11);
	//�\��
	text[256];
	//����
	swprintf(text, L"SELECT+START�ŃX�L�b�v");
	//�͂��B
	f->SetText(text);
	f->SetPosition({ 0.0f,330.0f });
	f->SetScale(SetumeiScale);
	f->SetColor({ 1.0f,1.0f,1.0f,0.0f });
	f->SetPivot({ 0.5f,0.5f });
	m_fontRender.push_back(f);

	return true;
}

void ED::Update() {

	switch (ED_Scene) {

	case Tobu://��֔��
	{
		if (Timer == 12) {
			BounderSet(5);
		}

		if (Timer >= Scene1_Limit) {//���Ԃ�
			Timer = 0;
			MulAlpha = 0.0f;
			ED_Scene = Utyu;
			UpperSet(5);
			KamisibaiSet(4);
		}
		break;
	}

	}

	//�X�L�b�v�L�[
	if (Pad(0).IsTrigger(enButtonA) || Pad(0).IsTrigger(enButtonB) || Pad(0).IsTrigger(enButtonX) || Pad(0).IsTrigger(enButtonY)) {
		SkipTimer = 0;
		SkipAlpha = 1.0f;
		m_fontRender[1]->SetColor({ 1.0f,1.0f,1.0f,SkipAlpha });
	}
	if (SkipTimer > -1) {

		if (SkipTimer > SkipMoziLimit - 20) {
			SkipAlpha -= 0.1f;
			if (SkipAlpha < 0.0f) {
				SkipAlpha = 0.0f;
			}
			m_fontRender[1]->SetColor({ 1.0f,1.0f,1.0f,SkipAlpha });
		}
		SkipTimer++;
		if (SkipTimer == SkipMoziLimit) {
			SkipTimer = -1;
		}
	}

	//�X�L�b�v�I
	if (Pad(0).IsPress(enButtonStart) && Pad(0).IsPress(enButtonSelect) && ED_Scene != END) {
		ED_Scene = END;
		Timer = 170; //�M���M���܂ŃX�L�b�v
	}

	Bounder();
	Upper();
	Kamisibai();

	Timer++;
}

void ED::BounderSet(int x) {

	for (int i = 0; i < 5; i++) {
		if (BoundSet[i] == -1) {
			BoundSet[i] = x;
			BoundTimer[i] = 0;
			break;
		}
	}
}

void ED::Bounder() {

	//�o�E���h���܂�
	for (int i = 0; i < 5; i++) {
		if (BoundSet[i] > -1) {
			int Nom = BoundSet[i];
			int Time = BoundTimer[i];
			pos = m_spriteRender[Nom]->GetPosition();

			if (Time < 24) {
				pos.y -= (DEF_POS / 24) + 5;
				//�Z�b�g
				m_spriteRender[Nom]->SetPosition(pos);
			}
			else if (Time < 36) {
				pos.y += 6.0f;
				//�Z�b�g
				m_spriteRender[Nom]->SetPosition(pos);
			}
			else if (Time < 48) {
				pos.y -= 4.0f;
				//�Z�b�g
				m_spriteRender[Nom]->SetPosition(pos);
			}
			else {
				//�I��
				BoundSet[i] = -1;
				BoundTimer[i] = -2;
			}

			BoundTimer[i]++;
		}
	}

}

void ED::UpperSet(int x) {

	for (int i = 0; i < 5; i++) {
		if (UppSet[i] == -1) {
			UppSet[i] = x;
			UpperTimer[i] = 0;
			break;
		}
	}
}

void ED::Upper() {

	//�A�b�v���܂�
	for (int i = 0; i < 5; i++) {
		if (UppSet[i] > -1) {
			int Nom = UppSet[i];
			int Time = UpperTimer[i];
			pos = m_spriteRender[Nom]->GetPosition();

			if (Time < 12) {
				pos.y -= 5.0f;
				//�Z�b�g
				m_spriteRender[Nom]->SetPosition(pos);
			}
			else if (Time < 36) {
				pos.y += (DEF_POS / 24) + 6;
				//�Z�b�g
				m_spriteRender[Nom]->SetPosition(pos);
			}
			else {
				//�I��
				UppSet[i] = -1;
				UpperTimer[i] = -2;
			}

			UpperTimer[i]++;
		}
	}

}

void ED::KamisibaiSet(int x) {
	KamisibaiNo = x;
	KamisibaiTimer = 0;
}

void ED::Kamisibai() {

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

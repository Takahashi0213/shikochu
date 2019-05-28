#include "stdafx.h"
#include "OP.h"
#include "TransitionMaker.h"

OP* OP::m_instance = nullptr;

OP::OP()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
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

	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
}

bool OP::Start() {

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
	//2�� �w�i
	r = NewGO<prefab::CSpriteRender>(1);
	r->Init(L"sprite/OPED_back3.dds", 1280.0f, 720.0f);
	r->SetPosition({ 0.0f ,0.0f,0.0f });
	m_spriteRender.push_back(r);
	//3�� �w�i
	r = NewGO<prefab::CSpriteRender>(1);
	r->Init(L"sprite/OPED_back2.dds", 1280.0f, 720.0f);
	r->SetPosition({ 0.0f ,0.0f,0.0f });
	m_spriteRender.push_back(r);
	//4�� �w�i
	r = NewGO<prefab::CSpriteRender>(1);
	r->Init(L"sprite/OPED_back1.dds", 1280.0f, 720.0f);
	r->SetPosition({ 0.0f ,0.0f,0.0f });
	m_spriteRender.push_back(r);
	//5�� �v���C���[1
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/OPED_4.dds", 444.0f, 779.0f);
	r->SetPosition({ 0.0f ,180.0f + DEF_POS,0.0f });
	m_spriteRender.push_back(r);
	//6�� �v���C���[2
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/OPED_1.dds", 418.0f, 662);
	r->SetPosition({ -300.0f ,120.0f + DEF_POS,0.0f });
	m_spriteRender.push_back(r);
	//7�� �v���C���[3
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/OPED_4.dds", 444.0f, 779.0f);
	r->SetPosition({ 0.0f ,80.0f + DEF_POS,0.0f });
	m_spriteRender.push_back(r);
	//8�� �u�����[�O
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/OPED_3.dds", 590.0f, 694.0f);
	r->SetPosition({ 350.0f ,280.0f + DEF_POS,0.0f });
	m_spriteRender.push_back(r);
	//9�� �l�I���N
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/OPED_6.dds", 617.0f, 675.0f);
	r->SetPosition({ -350.0f ,280.0f + DEF_POS,0.0f });
	m_spriteRender.push_back(r);
	//10�� ������
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/OPED_7.dds", 1280.0f, 920.0f);
	r->SetPosition({ 0.0f ,40.0f + DEF_POS,0.0f });
	m_spriteRender.push_back(r);
	//11�� �I���l
	r = NewGO<prefab::CSpriteRender>(3);
	r->Init(L"sprite/OPED_5.dds", 820.0f, 920.0f);
	r->SetPosition({ -50.0f ,60.0f + DEF_POS,0.0f });
	m_spriteRender.push_back(r);
	//12�� ����
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/Black.dds", 1280.0f, 720.0f);
	r->SetPosition({ 0.0f ,0.0f,0.0f });
	m_spriteRender.push_back(r);
	//13�� ���S
	r = NewGO<prefab::CSpriteRender>(0);
	r->Init(L"sprite/rogo.dds", 440.0f, 245.0f);
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

	return true;
}

void OP::Update() {

	switch (OP_Scene) {

	case Hazimari://�͂��܂�
	{
		if (Timer == 12) {
			BounderSet(5);
			wchar_t text[256];
			//����
			swprintf(text, L"����Ƃ���Ɂu�V�R�E�`���E�v�Ƃ������V�����܂���");
			//�͂��B
			m_fontRender[0]->SetText(text);
		}

		if (Timer >= 12) {
			MulAlpha += 0.05f;
			if (MulAlpha > 1.0f) {
				MulAlpha = 1.0f;
			}
			m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,MulAlpha });
		}

		if (Timer >= Scene1_Limit) {//���Ԃ�
			Timer = 0;
			MulAlpha = 0.0f;
			OP_Scene = Seisitu;
			UpperSet(5);
			KamisibaiSet(4);
		}
		break;
	}
	case Seisitu://����
	{
		if (Timer < 12) {
			MulAlpha -= 0.1f;
			if (MulAlpha < 0.0f) {
				MulAlpha = 0.0f;
			}
			m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,MulAlpha });
		}

		if (Timer == 12) {//�e�L�X�gA
			BounderSet(6);
			wchar_t text[256];
			//����
			swprintf(text, L"�V�R�E�`���E�͂���݂傤���݂������A");
			//�͂��B
			m_fontRender[0]->SetText(text);
		}
		if (Timer == 180) {//�e�L�X�gB
			wchar_t text[256];
			//����
			swprintf(text, L"�����ɂق��ɂȂ��Ă��܂����V�ł���");
			//�͂��B
			m_fontRender[0]->SetText(text);
		}

		if (Timer >= 12&& Timer < 60) {//�e�L�X�gA�\��
			MulAlpha += 0.05f;
			if (MulAlpha > 1.0f) {
				MulAlpha = 1.0f;
			}
			m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,MulAlpha });
		}
		if (Timer > 160 && Timer < 180) { //�e�L�X�gA����
			MulAlpha -= 0.1f;
			if (MulAlpha < 0.0f) {
				MulAlpha = 0.0f;
			}
			m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,MulAlpha });
		}
		if (Timer > 180 && Timer < 220) {//�e�L�X�gB�\��
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
				//�摜�̐؂�ւ�
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

		//�����܂�
		if (Timer < 200) {
			pos = m_spriteRender[6]->GetPosition();
			pos.x += 2.0f;
			m_spriteRender[6]->SetPosition(pos);
		}

		if (Timer >= Scene2_Limit) {//���Ԃ�
			UpperSet(6);
			KamisibaiSet(3);
			Timer = 0;
			MulAlpha = 0.0f;
			OP_Scene = sinigami;
		}

		break;
	}
	case sinigami://����
	{
		if (Timer < 12) {
			MulAlpha -= 0.1f;
			if (MulAlpha < 0.0f) {
				MulAlpha = 0.0f;
			}
			m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,MulAlpha });
		}

		if (Timer == 12) {//�e�L�X�gA
			BounderSet(7);
			wchar_t text[256];
			//����
			swprintf(text, L"�������ȃ��V�̓P�c�C���܂���");
			//�͂��B
			m_fontRender[0]->SetText(text);
		}
		if (Timer == 180) {//�e�L�X�gB
			BounderSet(8);
			BounderSet(9);
			wchar_t text[256];
			//����
			swprintf(text, L"�����Ă��邤���ɂȂɂ����Ȃ��Ƃ��悤�A��");
			//�͂��B
			m_fontRender[0]->SetText(text);
		}

		if (Timer >= 12 && Timer < 60) {//�e�L�X�gA�\��
			MulAlpha += 0.05f;
			if (MulAlpha > 1.0f) {
				MulAlpha = 1.0f;
			}
			m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,MulAlpha });
		}
		if (Timer > 160 && Timer < 180) { //�e�L�X�gA����
			MulAlpha -= 0.1f;
			if (MulAlpha < 0.0f) {
				MulAlpha = 0.0f;
			}
			m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,MulAlpha });
		}
		if (Timer > 180 && Timer < 220) {//�e�L�X�gB�\��
			MulAlpha += 0.05f;
			if (MulAlpha > 1.0f) {
				MulAlpha = 1.0f;
			}
			m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,MulAlpha });
		}

		if (Timer >= Scene3_Limit) {//���Ԃ�
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
	case ganbaru://����΂邼
	{
		if (Timer < 12) {
			MulAlpha -= 0.1f;
			if (MulAlpha < 0.0f) {
				MulAlpha = 0.0f;
			}
			m_fontRender[0]->SetColor({ 1.0f,1.0f,1.0f,MulAlpha });
		}
		if (Timer == 12) {//�e�L�X�gA
			BounderSet(10);
			wchar_t text[256];
			//����
			swprintf(text, L"�V�R�E�`���E�̂ڂ����񂪂͂��܂�܂��I");
			//�͂��B
			m_fontRender[0]->SetText(text);
		}
		if (Timer == 24) {
			BounderSet(11);
		}
		if (Timer >= 12 && Timer < 60) {//�e�L�X�gA�\��
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

		if (Timer >= Scene4_Limit) {//���Ԃ�
			UpperSet(10);
			UpperSet(11);
			KamisibaiSet(1);
			Timer = 0;
			MulAlpha = 0.0f;
			OP_Scene = END;
		}

		break;
	}
	case END://����΂邼
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

		if (Timer >= Scene5_Limit) {//���Ԃ�
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

	//�o�E���h���܂�
	for (int i = 0; i < 5; i++) {
		if (BoundSet[i] > -1) {
			int Nom = BoundSet[i];
			int Time= BoundTimer[i];
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

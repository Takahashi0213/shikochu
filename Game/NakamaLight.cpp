#include "stdafx.h"
#include "NakamaLight.h"
#include "GameData.h"

NakamaLight* NakamaLight::m_instance = nullptr;

NakamaLight::NakamaLight()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;
}


NakamaLight::~NakamaLight()
{
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
}

bool NakamaLight::Start() {

	r = NewGO<prefab::CSpriteRender>(5);

	return true;
}

void NakamaLight::Update() {

	if (StarTimer == 0) {//�ړ��������v�Z�`
		MoveSpeed = Star_Pos - P_Pos;
		//MoveSpeed.y += 100.0f; //�␳���Ă݂�
		MoveSpeed = MoveSpeed / (float)StarLimit;
	}

	if (StarTimer >= 0 && StarTimer < StarWaitLimit) {//�������I
		CVector3 pos = r->GetPosition();
		pos.x += MoveSpeed.x;
		pos.y += MoveSpeed.y;
		r->SetPosition(pos);

		Scale.x += 0.05f;
		Scale.y += 0.05f;
		r->SetScale(Scale);

		MulAlpha += 0.05f;
		if (MulAlpha > 1.0f) {
			MulAlpha = 1.0f;
		}
		MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
		r->SetMulColor(MulColor);

		CQuaternion RotationY;
		RotationY.SetRotationDeg(CVector3::AxisZ, -5.0f);
		CQuaternion m_rotation = r->GetRotation();
		m_rotation *= RotationY;
		r->SetRotation(m_rotation);

	}
	
	if (StarTimer == StarWaitLimit) { //�n�C�X�s�[�h����
		ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/star_02.wav");
		ss->SetVolume(0.3f);
		ss->Play(false);

		CVector3 m_pos = r->GetPosition();
		CVector2 m_Pos;
		m_Pos.x = m_pos.x;
		m_Pos.y = m_pos.y;
		MoveSpeed = Star_Pos - m_Pos;
		MoveSpeed.x *= 1.5f;
		MoveSpeed.y *= 1.5f;
		//MoveSpeed.y += 100.0f; //�␳���Ă݂�
		MoveSpeed = MoveSpeed / (float)StarLimit_High;
	}
	else if(StarTimer > StarWaitLimit) {//�͂₭������
		CVector3 pos = r->GetPosition();
		pos.x += MoveSpeed.x;
		pos.y += MoveSpeed.y;
		r->SetPosition(pos);

		Scale.x -= 0.1f;
		if (Scale.x < 0.0f) {
			Scale.x = 0.0f;
		}
		Scale.y -= 0.1f;
		if (Scale.y < 0.0f) {
			Scale.y = 0.0f;
		}
		r->SetScale(Scale);

		MulAlpha -= 0.05f;
		if (MulAlpha < 0.0f) {
			MulAlpha = 0.0f;
		}
		MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
		r->SetMulColor(MulColor);

		CQuaternion RotationY;
		RotationY.SetRotationDeg(CVector3::AxisZ, -40.0f);
		CQuaternion m_rotation = r->GetRotation();
		m_rotation *= RotationY;
		r->SetRotation(m_rotation);

	}

	if (StarTimer > -1) {

		StarTimer++;
	}

	if (StarTimer == FinalLimit) {
		ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/star_03.wav");
		ss->SetVolume(1.0f);
		ss->SetFrequencyRatio(1.5f);
		ss->Play(false);

		GraphicsEngine().GetPostEffect().GetDithering().AddPointLig(Star_Pos);
		Scale = CVector3::Zero;
		StarTimer = -1;

	}

}

void NakamaLight::NakamaPlus() {

	Star_Pos = GraphicsEngine().GetPostEffect().GetDithering().GeneratePointLigPosition();
	StarTimer = 0;

	ss = NewGO<prefab::CSoundSource>(0);
	ss->Init(L"sound/star_01.wav");
	ss->SetVolume(0.5f);
	ss->SetFrequencyRatio(2.0f);
	ss->Play(false);

	r->Init(L"sprite/Star.dds", 200, 200);
	r->SetPosition({ P_Pos.x,P_Pos.y,0.0f });
	r->SetScale(Scale);
	MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
	r->SetMulColor(MulColor);

}


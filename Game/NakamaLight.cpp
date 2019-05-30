#include "stdafx.h"
#include "NakamaLight.h"
#include "GameData.h"

NakamaLight* NakamaLight::m_instance = nullptr;

NakamaLight::NakamaLight()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;
}


NakamaLight::~NakamaLight()
{
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

bool NakamaLight::Start() {

	r = NewGO<prefab::CSpriteRender>(5);

	return true;
}

void NakamaLight::Update() {

	if (StarTimer == 0) {//移動距離を計算～
		MoveSpeed = Star_Pos - P_Pos;
		//MoveSpeed.y += 100.0f; //補正してみる
		MoveSpeed = MoveSpeed / (float)StarLimit;
	}

	if (StarTimer >= 0 && StarTimer < StarWaitLimit) {//ゆっくり！
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
	
	if (StarTimer == StarWaitLimit) { //ハイスピード準備
		CVector3 m_pos = r->GetPosition();
		CVector2 m_Pos;
		m_Pos.x = m_pos.x;
		m_Pos.y = m_pos.y;
		MoveSpeed = Star_Pos - m_Pos;
		MoveSpeed.x *= 1.5f;
		MoveSpeed.y *= 1.5f;
		//MoveSpeed.y += 100.0f; //補正してみる
		MoveSpeed = MoveSpeed / (float)StarLimit_High;
	}
	else if(StarTimer > StarWaitLimit) {//はやく動こう
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
		GraphicsEngine().GetPostEffect().GetDithering().AddPointLig(Star_Pos);
		Scale = CVector3::Zero;
		StarTimer = -1;

	}

}

void NakamaLight::NakamaPlus() {

	Star_Pos = GraphicsEngine().GetPostEffect().GetDithering().GeneratePointLigPosition();
	StarTimer = 0;

	r->Init(L"sprite/Star.dds", 200, 200);
	r->SetPosition({ P_Pos.x,P_Pos.y,0.0f });
	r->SetScale(Scale);
	MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
	r->SetMulColor(MulColor);

}


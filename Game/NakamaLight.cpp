#include "stdafx.h"
#include "NakamaLight.h"
#include "GameData.h"

NakamaLight* NakamaLight::m_instance = nullptr;

NakamaLight::NakamaLight()
{
	//if (m_instance != nullptr) {
	//	std::abort(); //すでに出ているためクラッシュ
	//}

	r = NewGO<prefab::CSpriteRender>(5);
	r2 = NewGO<prefab::CSpriteRender>(7);

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;
}


NakamaLight::~NakamaLight()
{
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

bool NakamaLight::Start() {


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
		ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/star_02.wav");
		if (OnryouMiniFlag == false) {
			ss->SetVolume(0.3f);
		}
		else {
			ss->SetVolume(0.1f);
		}
		ss->Play(false);

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

	//3Dモードかつ残り１０フレームなら…
	if (GameData::GetInstance()->GetGameMode() == GameData::Battle3D_Mode && StarTimer >= FinalLimit-10) {
		GameData * gamedata = GameData::GetInstance();
		gamedata->Star_PowerChange(1);
	}

	//スターアクセ
	if (StarAccTimer > -1 && StarAccTimer < StarAccLimit / 2) {//見える

		MulAlpha += 0.1f;
		if (MulAlpha > 1.0f) {
			MulAlpha = 1.0f;
		}
		
		MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
		r2->SetMulColor(MulColor);

	}
	else if (StarAccTimer >= StarAccLimit / 2) {//消える

		MulAlpha -= 0.1f;
		if (MulAlpha < 0.0f) {
			MulAlpha = 0.0f;
		}

		MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
		r2->SetMulColor(MulColor);

	}

	if (StarTimer > -1) {

		StarTimer++;
	}
	if (StarAccTimer > -1) {

		CQuaternion RotationY;
		RotationY.SetRotationDeg(CVector3::AxisZ, -5.0f);
		CQuaternion m_rotation = r2->GetRotation();
		m_rotation *= RotationY;
		r2->SetRotation(m_rotation);

		Scale.x += 0.1f;
		Scale.y += 0.1f;
		r2->SetScale(Scale);

		StarAccTimer++;
	}

	if (StarTimer == FinalLimit) {
		ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/star_03.wav");
		if (OnryouMiniFlag == false) {
			ss->SetVolume(1.0f);
		}
		else {
			ss->SetVolume(0.2f);
		}
		ss->SetFrequencyRatio(1.5f);
		ss->Play(false);

		GameData * gameData = GameData::GetInstance();
		int mode = gameData->GetGameMode();

		if (mode == GameData::Battle2D_Mode || mode == GameData::Tutorial) {
			GraphicsEngine().GetPostEffect().GetDithering().AddPointLig(Star_Pos);
		}

		Scale = CVector3::Zero;
		StarTimer = -1;
		MulAlpha = 0.0f;
		//
		StarAccTimer = 0;
		r2->Init(L"sprite/Star2.dds", 200, 200);
		CVector3 S_pos = CVector3::One;
		S_pos.x = Star_Pos.x;
		if (GameData::GetInstance()->GetGameMode() == GameData::Battle3D_Mode) {
			S_pos.x += 50.0f;
		}
		S_pos.y = Star_Pos.y;
		r2->SetPosition(S_pos);
		r2->SetScale(Scale);
		MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
		r2->SetMulColor(MulColor);

	}
	if (StarAccTimer == StarAccLimit) {
		StarAccTimer = -1;
		Scale = CVector3::Zero;
		MulAlpha = 0.0f;
		DeleteGO(this);
	}

}

//第一引数にtrueを入れると星が飛ぶ位置が完全ランダムになる
//第二引数にtrueを入れるとSE音量が小さくなる（一度にたくさん星を生成するときtrueにしてね）
void NakamaLight::NakamaPlus(bool randomFlag, bool SoundFlag) {

	GameData * gameData = GameData::GetInstance();
	int mode = gameData->GetGameMode();
	OnryouMiniFlag = SoundFlag;

	if (mode == GameData::Battle2D_Mode) {
		if (randomFlag == false) { //死んだときの
			Star_Pos = GraphicsEngine().GetPostEffect().GetDithering().GeneratePointLigPosition();
		}
		else { //適当な位置に飛ばすよ
			Star_Pos = GraphicsEngine().GetPostEffect().GetDithering().GeneratePointLigPosition_rand();
		}
	}
	else if (mode == GameData::Battle3D_Mode) {
		Star_Pos = { -600.0f,-50.0f };
	}

	StarTimer = 0;

	ss = NewGO<prefab::CSoundSource>(0);
	ss->Init(L"sound/star_01.wav");
	if (OnryouMiniFlag == false) {
		ss->SetVolume(0.5f);
	}
	else {
		ss->SetVolume(0.2f);
	}
	ss->SetFrequencyRatio(2.0f);
	ss->Play(false);

	//r = NewGO<prefab::CSpriteRender>(5);
	r->Init(L"sprite/Star.dds", 200, 200);
	r->SetPosition({ P_Pos.x,P_Pos.y,0.0f });
	r->SetScale(Scale);
	MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
	r->SetMulColor(MulColor);

}

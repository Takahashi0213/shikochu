#include "stdafx.h"
#include "BackGround.h"

BackGround* BackGround::m_instance = nullptr;

BackGround::BackGround()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

}


BackGround::~BackGround()
{
	DeleteGO(m_skinModelRender);
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;

}

//-100を引数に設定した場合チュートリアル用ステージを生成
void BackGround::StageMaker(int ST){

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0, "stage");

	if (ST != -100) {
		//名前を引っ張ってくる
		int len = wcslen(DetaBase[ST]);
		for (int x = 0; x < len + 1; x++) {
			ST_Name[x] = DetaBase[ST][x];
		}
	}
	else if (ST == -100) {
		//名前を引っ張ってくる
		int len = wcslen(Tutorial[0]);
		for (int x = 0; x < len + 1; x++) {
			ST_Name[x] = Tutorial[0][x];
		}
	}
	//作成
	if (animeFlag[ST] == true) {
		//アニメーションセット
		m_anim[0].Load(L"animData/Eki_Wait.tka");
		m_anim[0].SetLoopFlag(true);
		m_anim[1].Load(L"animData/Eki_Open.tka");
		m_anim[1].SetLoopFlag(false);
		m_anim[2].Load(L"animData/Eki_Close.tka");
		m_anim[2].SetLoopFlag(false);

		m_skinModelRender->Init(ST_Name, m_anim, 3);
	}
	else {
		m_skinModelRender->Init(ST_Name, nullptr, 0);
	}
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetEmissionColor(StageEmission);

	//CPhysicsStaticObjectの初期化
	if (physicsFlag[ST] == true) {
		m_physicsStaticObject.CreateMesh(m_position, CQuaternion::Identity, m_scale, m_skinModelRender);
	}
}

void BackGround::DeleteStage() {

	DeleteGO(this);

}

void BackGround::PhysicsRelease() {
	m_physicsStaticObject.SetPositionAndRotation(Re_position, CQuaternion::Identity);
}

void BackGround::PlayBG_Anime(int x) {
	m_skinModelRender->PlayAnimation(x, 0.2f);
}
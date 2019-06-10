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
	m_skinModelRender->Init(ST_Name, nullptr, 0);
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


#include "stdafx.h"
#include "UICamera.h"

UICamera* UICamera::m_instance = nullptr;

UICamera::UICamera()
{
	if (m_instance != nullptr) {
		std::abort(); //すでにカメラが出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;
}

UICamera::~UICamera()
{
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

bool UICamera::Start(){

	//遠平面を設定する
	MainCamera().SetFar(30000.0f);
	//画角を変更
	MainCamera().SetViewAngle(CMath::DegToRad(80.0f));

	//注視点を動かす
	cameraTarget.x = 0.0f;
	cameraTarget.y = 0.0f;
	cameraTarget.z = 0.0f;

	//視点をカメラに伝える
	cameraPos.x = 0.0f;
	cameraPos.y = 50.0f;
	cameraPos.z = 180.0f;

	//注視点をカメラに伝える
	MainCamera().SetTarget(cameraTarget);
	MainCamera().SetPosition(cameraPos);

	//カメラ行列を更新する
	MainCamera().Update();

	return true;

}

void UICamera::Update() {

	//注視点を動かす
	cameraTarget.x = 0.0f;
	cameraTarget.y = 0.0f;
	cameraTarget.z = 0.0f;

	if(C_Flag==false){
		//視点をカメラに伝える
		cameraPos.x = 0.0f;
		cameraPos.y = 50.0f;
		cameraPos.z = 180.0f;
	}
	else {
		//視点をカメラに伝える
		cameraPos.x = 0.0f;
		cameraPos.y = 150.0f;
		cameraPos.z = 180.0f;
	}

	//注視点をカメラに伝える
	MainCamera().SetTarget(cameraTarget);
	MainCamera().SetPosition(cameraPos);

	//カメラ行列を更新する
	MainCamera().Update();

}



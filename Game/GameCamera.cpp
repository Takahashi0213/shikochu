#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "GameData.h"

GameCamera* GameCamera::m_instance = nullptr;

GameCamera::GameCamera()
{
	if (m_instance != nullptr) {
		std::abort(); //すでにカメラが出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;
}


GameCamera::~GameCamera()
{
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

bool GameCamera::Start() {

	//遠平面を設定する
	MainCamera().SetFar(30000.0f);
	//画角を変更
	MainCamera().SetViewAngle(CMath::DegToRad(80.0f));

	Player * player = Player::GetInstance();
	CVector3 P_Position = player->Getm_Position();
	//注視点を動かす
	cameraTarget.x = P_Position.x;
	cameraTarget.y = P_Position.y;	//プレイヤーのちょっと上にする
	cameraTarget.z = P_Position.z;

	//視点をカメラに伝える
	cameraPos.x = P_Position.x;
	cameraPos.y = P_Position.y + 200.0f;	//プレイヤーのちょっと上にする
	cameraPos.z = P_Position.z - 5.0f;

	//注視点をカメラに伝える
	MainCamera().SetTarget(cameraTarget);
	MainCamera().SetPosition(cameraPos);

	//カメラ行列を更新する
	MainCamera().Update();

	return true;
}

void GameCamera::Update() {

	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();

	Player * player = Player::GetInstance();
	CVector3 P_Position = player->Getm_Position();

	if (mode==0) {
		//注視点を動かす
		cameraTarget.x = P_Position.x;
		cameraTarget.y = P_Position.y;	//プレイヤーのちょっと上にする
		cameraTarget.z = P_Position.z;

		//視点をカメラに伝える
		cameraPos.x = P_Position.x;
		cameraPos.y = P_Position.y + 200.0f;	//プレイヤーのちょっと上にする
		cameraPos.z = P_Position.z - 5.0f;
	}
	else if (mode == 1) {

		//注視点を動かす
		cameraTarget.x = P_Position.x;
		cameraTarget.y = P_Position.y;	
		cameraTarget.z = P_Position.z;

		//視点をカメラに伝える
		cameraPos.x = P_Position.x;
		cameraPos.y = P_Position.y;	//プレイヤーのちょっと上にする
		cameraPos.z = P_Position.z - 200.0f;

	}
	//注視点をカメラに伝える
	MainCamera().SetTarget(cameraTarget);
	MainCamera().SetPosition(cameraPos);

	//カメラ行列を更新する
	MainCamera().Update();

}

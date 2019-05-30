#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "GameData.h"
#include "LevelData.h"

//ボス
#include "shisokus.h"
#include "Pairodorago.h"
#include "SS_001.h"

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
	cameraPos.x = P_Position.x + camera2D_DEF.x;
	cameraPos.y = P_Position.y + camera2D_DEF.y;	//プレイヤーのちょっと上にする
	cameraPos.z = P_Position.z + camera2D_DEF.z;

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

	if (mode == 0) {
		//注視点を動かす
		cameraTarget.x = P_Position.x;
		cameraTarget.y = P_Position.y;	//プレイヤーのちょっと上にする
		cameraTarget.z = P_Position.z;

		//視点をカメラに伝える
		cameraPos.x = P_Position.x + camera2D_DEF.x;
		cameraPos.y = P_Position.y + camera2D_DEF.y;
		cameraPos.z = P_Position.z + camera2D_DEF.z;
	}
	else if (mode == 1) {

		int D_state = player->GetState3D();

		if (D_state == 1) {
			DashTimer3D++;
			if(DashTimer3D < DashTimerMAX) {
				DashHoseiZ -= 2.0f;
			}
		}
		else {
			DashTimer3D = 0;
			DashHoseiZ += 5.0f;
			if (DashHoseiZ > 0.0f) {
				DashHoseiZ = 0.0f;
			}
		}

		//注視点を動かす
		cameraTarget.x = P_Position.x;
		cameraTarget.y = P_Position.y;	
		cameraTarget.z = P_Position.z;

		//視点をカメラに伝える
		cameraPos.x = P_Position.x + camera3D_DEF.x;
		cameraPos.y = P_Position.y + camera3D_DEF.y;
		cameraPos.z = P_Position.z + camera3D_DEF.z + DashHoseiZ;

	}
	else if (mode == 2) {
		//2Dモードから3Dモードへ移行するカメラの動き
		if (swapTimer == -1) {//準備色々
			//2Dモードと3Dモードの差を計算
			swapParameter.x = camera3D_DEF.x - camera2D_DEF.x;
			swapParameter.y = camera3D_DEF.y - camera2D_DEF.y;
			swapParameter.z = camera3D_DEF.z - camera2D_DEF.z;
			//その差をフレーム数で割れば1フレームでどれだけ動かせばいいか大体わかります
			swapParameter.x = swapParameter.x / swapTimerDEF;
			swapParameter.y = swapParameter.y / swapTimerDEF;
			swapParameter.z = swapParameter.z / swapTimerDEF;
			//念のためリセット
			cameraSwap = CVector3::Zero;
			//まさかのここで再生です
			int stage = gamedata->GetStageNo();
			stage--;
			ss = NewGO<prefab::CSoundSource>(0);
			//SE再生
			ss->Init(BossBGMName[stage]);
			ss->SetVolume(BMG_V);
			ss->Play(true);
		}
		else if (swapTimer > swapWaitTimer) {
			//注視点を動かす
			cameraTarget.x = P_Position.x;
			cameraTarget.y = P_Position.y;
			cameraTarget.z = P_Position.z;

			//cameraSwapの加算
			cameraSwap.x += swapParameter.x;
			cameraSwap.y += swapParameter.y;
			cameraSwap.z += swapParameter.z;

			//視点をカメラに伝える
			cameraPos.x = P_Position.x + camera2D_DEF.x + cameraSwap.x;
			cameraPos.y = P_Position.y + camera2D_DEF.y + cameraSwap.y;
			cameraPos.z = P_Position.z + camera2D_DEF.z + cameraSwap.z;
		}

		//タイマー加算
		swapTimer++;
		if (swapTimer >= swapTimerDEF + swapWaitTimer) {
			//終了のためゲームモードを3Dにする
			gamedata->SetGameMode(GameData::Battle3D_Mode);
			swapTimer = -1; //タイマーもおしまい
		}

	}
	else if (mode == 3) {//リザルトならボスにフォーカスして回転

		//静かに～！
		BMG_V -= 0.1f;
		if (BMG_V < 0.0f) {
			BMG_V = 0.0f;
		}
		ss->SetVolume(BMG_V);

		int stage = gamedata->GetStageNo();
		stage--;
		if (stage == 0) {//シーソークスにフォーカスする	
			if (ResultCameraFlag == false) {
				shisokus * shiso = FindGO<shisokus>("shiso");
				cameraTarget = shiso->Getm_Position();
				//視点をカメラに伝える
				cameraPos.x = cameraTarget.x + targetToPos.x;
				cameraPos.y = cameraTarget.y + targetToPos.y;
				cameraPos.z = cameraTarget.z + targetToPos.z;
				ResultCameraFlag = true;
				swapTimer = -1;
			}
			else {

				if (swapTimer < 180) {

					//注視点から視点に向かうベクトルを回す
					float x;
					if (ResultCameraMoveFlag == false) {
						x = 20.0f;
						ResultCameraMoveFlag = true;
					}
					else {
						x = -0.05f;
					}
					float y = 0.0f;
					//Y軸周りの回転
					CQuaternion qRot;
					qRot.SetRotationDeg(CVector3::AxisY, 5.0f * x);
					qRot.Multiply(targetToPos);

					// X軸周りの回転
					CVector3 axisX;
					//外積を使って回転軸を求める。
					//外積は二つのベクトルを使って計算する。
					//外積の結果は新しいベクトルになる。
					// V1×V2 = V3
					//そして新しいベクトル(V3)はV1とV2に直行しているベクトルになる！！！
					axisX.Cross(CVector3::AxisY, targetToPos);
					//外積の結果は大きさ１ではないので、正規化する。　
					axisX.Normalize();
					qRot.SetRotationDeg(axisX, 5.0f*y);
					//注視点から視点に伸びるベクトルを回す。
					qRot.Multiply(targetToPos);
					//注視点から視点からに伸びるベクトルから大きさを除外して
					//方向のみのデータにする。
					CVector3 targetToPosDir = targetToPos;
					targetToPosDir.Normalize();

					//視点を動かす
					//CVector3 cameraPos;
					cameraPos = cameraTarget + targetToPos;

				}

				swapTimer++;
			}
		}
		if (stage == 1) {//パイロドラゴにフォーカスする	
			if (ResultCameraFlag == false) {
				Pairodorago * pairodorago = FindGO<Pairodorago>("Pairodorago");
				cameraTarget = pairodorago->Getm_Position();
				//視点をカメラに伝える
				cameraPos.x = cameraTarget.x + targetToPos.x;
				cameraPos.y = cameraTarget.y + targetToPos.y;
				cameraPos.z = cameraTarget.z + targetToPos.z;
				ResultCameraFlag = true;
				swapTimer = -1;
			}
			else {

				if (swapTimer < 180) {

					//注視点から視点に向かうベクトルを回す
					float x;
					if (ResultCameraMoveFlag == false) {
						x = 20.0f;
						ResultCameraMoveFlag = true;
					}
					else {
						x = -0.05f;
					}
					float y = 0.0f;
					//Y軸周りの回転
					CQuaternion qRot;
					qRot.SetRotationDeg(CVector3::AxisY, 5.0f * x);
					qRot.Multiply(targetToPos);

					// X軸周りの回転
					CVector3 axisX;
					//外積を使って回転軸を求める。
					//外積は二つのベクトルを使って計算する。
					//外積の結果は新しいベクトルになる。
					// V1×V2 = V3
					//そして新しいベクトル(V3)はV1とV2に直行しているベクトルになる！！！
					axisX.Cross(CVector3::AxisY, targetToPos);
					//外積の結果は大きさ１ではないので、正規化する。　
					axisX.Normalize();
					qRot.SetRotationDeg(axisX, 5.0f*y);
					//注視点から視点に伸びるベクトルを回す。
					qRot.Multiply(targetToPos);
					//注視点から視点からに伸びるベクトルから大きさを除外して
					//方向のみのデータにする。
					CVector3 targetToPosDir = targetToPos;
					targetToPosDir.Normalize();

					//視点を動かす
					//CVector3 cameraPos;
					cameraPos = cameraTarget + targetToPos;

				}

				swapTimer++;
			}
		}
		if (stage == 2) {//SS-001にフォーカスする	
			if (ResultCameraFlag == false) {
				SS_001 * ss_001 = FindGO<SS_001>("SS_001");
				cameraTarget = ss_001->Getm_Position();
				//視点をカメラに伝える
				cameraPos.x = cameraTarget.x + targetToPos.x;
				cameraPos.y = cameraTarget.y + targetToPos.y;
				cameraPos.z = cameraTarget.z + targetToPos.z;
				ResultCameraFlag = true;
				swapTimer = -1;
			}
			else {

				if (swapTimer < 180) {

					//注視点から視点に向かうベクトルを回す
					float x;
					if (ResultCameraMoveFlag == false) {
						x = 20.0f;
						ResultCameraMoveFlag = true;
					}
					else {
						x = -0.05f;
					}
					float y = 0.0f;
					//Y軸周りの回転
					CQuaternion qRot;
					qRot.SetRotationDeg(CVector3::AxisY, 5.0f * x);
					qRot.Multiply(targetToPos);

					// X軸周りの回転
					CVector3 axisX;
					//外積を使って回転軸を求める。
					//外積は二つのベクトルを使って計算する。
					//外積の結果は新しいベクトルになる。
					// V1×V2 = V3
					//そして新しいベクトル(V3)はV1とV2に直行しているベクトルになる！！！
					axisX.Cross(CVector3::AxisY, targetToPos);
					//外積の結果は大きさ１ではないので、正規化する。　
					axisX.Normalize();
					qRot.SetRotationDeg(axisX, 5.0f*y);
					//注視点から視点に伸びるベクトルを回す。
					qRot.Multiply(targetToPos);
					//注視点から視点からに伸びるベクトルから大きさを除外して
					//方向のみのデータにする。
					CVector3 targetToPosDir = targetToPos;
					targetToPosDir.Normalize();

					//視点を動かす
					//CVector3 cameraPos;
					cameraPos = cameraTarget + targetToPos;

				}

				swapTimer++;
			}
		}

	}

	//注視点をカメラに伝える
	MainCamera().SetTarget(cameraTarget);
	MainCamera().SetPosition(cameraPos);

	//カメラ行列を更新する
	MainCamera().Update();

}

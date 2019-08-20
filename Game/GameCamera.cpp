#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "GameData.h"
#include "LevelData.h"

//�{�X
#include "shisokus.h"
#include "Morinchu.h"
#include "Pairodorago.h"
#include "SS_001.h"
#include "Teruosuka.h"

GameCamera* GameCamera::m_instance = nullptr;

GameCamera::GameCamera()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɃJ�������o�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;
}


GameCamera::~GameCamera()
{
	if (BGM_Flag == true) {
		ss->SetVolume(0.0f);
	}

	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
}

bool GameCamera::Start() {

	//�����ʂ�ݒ肷��
	MainCamera().SetFar(30000.0f);
	//��p��ύX
	MainCamera().SetViewAngle(CMath::DegToRad(80.0f));

	Player * player = Player::GetInstance();
	CVector3 P_Position = player->Getm_Position();
	//�����_�𓮂���
	cameraTarget.x = P_Position.x;
	cameraTarget.y = P_Position.y;	//�v���C���[�̂�����Ə�ɂ���
	cameraTarget.z = P_Position.z;

	//���_���J�����ɓ`����
	cameraPos.x = P_Position.x + camera2D_DEF.x;
	cameraPos.y = P_Position.y + camera2D_DEF.y;	//�v���C���[�̂�����Ə�ɂ���
	cameraPos.z = P_Position.z + camera2D_DEF.z;

	//�����_���J�����ɓ`����
	MainCamera().SetTarget(cameraTarget);
	MainCamera().SetPosition(cameraPos);

	//�J�����s����X�V����
	MainCamera().Update();

	return true;
}

void GameCamera::Update() {

	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();

	Player * player = Player::GetInstance();
	CVector3 P_Position = player->Getm_Position();

	if (mode == GameData::Battle2D_Mode) {
		
		if (player->GetState() != Player::Estate_Death) { //����ł���Ԃ̓X���[���Ȃ��Ǝ��񂾏u�ԂɈړ����x��0�ɂȂ邩��K�N�����Ƃ��܂�
			//�v���C���[�̈ړ��x�N�g���𔽑΂ɂ��Đ��K������
			P_MoveSpeed = player->Getm_MoveSpeed();
			P_MoveSpeed.x *= -1.0f;
			P_MoveSpeed.y = 0.0f; //�O�̂���Y���[���ɂ��Ă���
			P_MoveSpeed.z *= -1.0f;
			P_MoveSpeed.Normalize();
			P_MoveSpeed.x *= DashCameraHosei;
			P_MoveSpeed.z *= DashCameraHosei;
		}

		//�����_�𓮂���
		cameraTarget.x = P_Position.x + P_MoveSpeed.x;
		cameraTarget.y = P_Position.y;
		cameraTarget.z = P_Position.z + P_MoveSpeed.z;

		//���_���J�����ɓ`����
		cameraPos.x = P_Position.x + camera2D_DEF.x + P_MoveSpeed.x;
		cameraPos.y = P_Position.y + camera2D_DEF.y;
		cameraPos.z = P_Position.z + camera2D_DEF.z + P_MoveSpeed.z;

		if (player->GetA_DashFlag() == true) { //�_�b�V�����Ȃ�J�����␳�����Z����
			//DashCameraHosei += 4.0f; //�P���ɐ��l������������@ �ȒP�����ǃX���[�Y�ł͂Ȃ�

			if (DashCameraHosei == 0.0f) { //�ړ��␳�����Ȃ疳������
				DashCameraHosei = 1.0f;
			}
			else { //�␳����Z���Ă������@
				DashCameraHosei *= MaxDashHosei_Plus;
			}
			
			if (DashCameraHosei > MaxDashHosei) { //�ł�����
				DashCameraHosei = MaxDashHosei;
			}
		}
		else { //�_�b�V�����łȂ���΃J�����␳���ɂ₩�ɖ߂�
			//DashCameraHosei -= 4.0f;

			DashCameraHosei *= MaxDashHosei_Minus; //�␳����Z���Ă������@

			if (DashCameraHosei < 1.0f) { //�␳���������Ȃ�����0�ɂ���
				DashCameraHosei = 0.0f;
			}

		}
		
	}
	else if (mode == GameData::Battle3D_Mode) {

		P_MoveSpeed = CVector3::Zero;
		int D_state = player->GetState3D();

		if (D_state == Player::Estate_Front) {
			DashTimer3D++;
			if(DashTimer3D < DashTimerMAX) {
				DashHoseiZ -= 2.0f;
			}
		}
		else if (D_state == Player::Estate_Back) {
			DashTimer3D++;
			if (DashTimer3D < DashTimerMAX) {
				DashHoseiZ += 2.0f;
			}
		}
		else {
			DashTimer3D = 0;

			if (DashHoseiZ < 0.0f) {
				DashHoseiZ += 5.0f;
				if (DashHoseiZ > 0.0f) {
					DashHoseiZ = 0.0f;
				}
			}
			if (DashHoseiZ > 0.0f) {
				DashHoseiZ -= 5.0f;
				if (DashHoseiZ < 0.0f) {
					DashHoseiZ = 0.0f;
				}
			}
	}

		//�����_�𓮂���
		cameraTarget.x = P_Position.x;
		cameraTarget.y = P_Position.y;	
		cameraTarget.z = P_Position.z;

		//���_���J�����ɓ`����
		cameraPos.x = P_Position.x + camera3D_DEF.x;
		cameraPos.y = P_Position.y + camera3D_DEF.y;
		cameraPos.z = P_Position.z + camera3D_DEF.z + DashHoseiZ;

	}
	else if (mode == 2) {
		//2D���[�h����3D���[�h�ֈڍs����J�����̓���
		if (swapTimer == -1) {//�����F�X
			//2D���[�h��3D���[�h�̍����v�Z
			swapParameter.x = camera3D_DEF.x - camera2D_DEF.x;
			swapParameter.y = camera3D_DEF.y - camera2D_DEF.y;
			swapParameter.z = camera3D_DEF.z - camera2D_DEF.z;
			//���̍����t���[�����Ŋ����1�t���[���łǂꂾ���������΂�������̂킩��܂�
			swapParameter.x = swapParameter.x / swapTimerDEF;
			swapParameter.y = swapParameter.y / swapTimerDEF;
			swapParameter.z = swapParameter.z / swapTimerDEF;
			//�O�̂��߃��Z�b�g
			cameraSwap = CVector3::Zero;
		}
		else if (swapTimer > swapWaitTimer) {
			//�����_�𓮂���
			cameraTarget.x = P_Position.x;
			cameraTarget.y = P_Position.y;
			cameraTarget.z = P_Position.z;

			//cameraSwap�̉��Z
			cameraSwap.x += swapParameter.x;
			cameraSwap.y += swapParameter.y;
			cameraSwap.z += swapParameter.z;

			//���_���J�����ɓ`����
			cameraPos.x = P_Position.x + camera2D_DEF.x + cameraSwap.x;
			cameraPos.y = P_Position.y + camera2D_DEF.y + cameraSwap.y;
			cameraPos.z = P_Position.z + camera2D_DEF.z + cameraSwap.z;
		}

		if (swapTimer == swapWaitTimer) {
			//�܂����̂����ōĐ��ł�
			int stage = gamedata->GetStageNo();
			stage--;
			ss = NewGO<prefab::CSoundSource>(0);
			//SE�Đ�
			ss->Init(BossBGMName[stage]);
			ss->SetVolume(BMG_V);
			ss->Play(true);
			BGM_Flag = true;
		}

		//�^�C�}�[���Z
		swapTimer++;
		if (swapTimer >= swapTimerDEF + swapWaitTimer) {
			//�I���̂��߃Q�[�����[�h��3D�ɂ���
			gamedata->SetGameMode(GameData::Battle3D_Mode);
			swapTimer = -1; //�^�C�}�[�������܂�
		}

	}
	else if (mode == 3) {//���U���g�Ȃ�{�X�Ƀt�H�[�J�X���ĉ�]

		//�Â��Ɂ`�I
		BMG_V -= 0.1f;
		if (BMG_V < 0.0f) {
			BMG_V = 0.0f;
		}
		ss->SetVolume(BMG_V);

		int stage = gamedata->GetStageNo();
		stage--;
		if (stage == 0) {//�V�[�\�[�N�X�Ƀt�H�[�J�X����	
			if (ResultCameraFlag == false) {
				shisokus * shiso = FindGO<shisokus>("shiso");
				cameraTarget = shiso->Getm_Position();
				//���_���J�����ɓ`����
				cameraPos.x = cameraTarget.x + targetToPos.x;
				cameraPos.y = cameraTarget.y + targetToPos.y;
				cameraPos.z = cameraTarget.z + targetToPos.z;
				ResultCameraFlag = true;
				swapTimer = -1;
			}
			else {

				if (swapTimer < 180) {

					//�����_���王�_�Ɍ������x�N�g������
					float x;
					if (ResultCameraMoveFlag == false) {
						x = 20.0f;
						ResultCameraMoveFlag = true;
					}
					else {
						x = -0.05f;
					}
					float y = 0.0f;
					//Y������̉�]
					CQuaternion qRot;
					qRot.SetRotationDeg(CVector3::AxisY, 5.0f * x);
					qRot.Multiply(targetToPos);

					// X������̉�]
					CVector3 axisX;
					//�O�ς��g���ĉ�]�������߂�B
					//�O�ς͓�̃x�N�g�����g���Čv�Z����B
					//�O�ς̌��ʂ͐V�����x�N�g���ɂȂ�B
					// V1�~V2 = V3
					//�����ĐV�����x�N�g��(V3)��V1��V2�ɒ��s���Ă���x�N�g���ɂȂ�I�I�I
					axisX.Cross(CVector3::AxisY, targetToPos);
					//�O�ς̌��ʂ͑傫���P�ł͂Ȃ��̂ŁA���K������B�@
					axisX.Normalize();
					qRot.SetRotationDeg(axisX, 5.0f*y);
					//�����_���王�_�ɐL�т�x�N�g�����񂷁B
					qRot.Multiply(targetToPos);
					//�����_���王�_����ɐL�т�x�N�g������傫�������O����
					//�����݂̂̃f�[�^�ɂ���B
					CVector3 targetToPosDir = targetToPos;
					targetToPosDir.Normalize();

					//���_�𓮂���
					//CVector3 cameraPos;
					cameraPos = cameraTarget + targetToPos;

				}

				swapTimer++;
			}
		}
		if (stage == 1) {//�������`���Ƀt�H�[�J�X����	
			if (ResultCameraFlag == false) {
				Morinchu * morinchu = FindGO<Morinchu>("Morinchu");
				cameraTarget = morinchu->Getm_Position();
				//���_���J�����ɓ`����
				cameraTarget.y += 3000.0f;
				cameraPos.x = cameraTarget.x + targetToPos.x;
				cameraPos.y = cameraTarget.y + targetToPos.y;
				cameraPos.z = cameraTarget.z + targetToPos.z;
				ResultCameraFlag = true;
				swapTimer = -1;
			}
			else {

				if (swapTimer < 180) {

					//�����_���王�_�Ɍ������x�N�g������
					float x;
					if (ResultCameraMoveFlag == false) {
						x = 20.0f;
						ResultCameraMoveFlag = true;
					}
					else {
						x = -0.05f;
					}
					float y = 0.0f;
					//Y������̉�]
					CQuaternion qRot;
					qRot.SetRotationDeg(CVector3::AxisY, 5.0f * x);
					qRot.Multiply(targetToPos);

					// X������̉�]
					CVector3 axisX;
					//�O�ς��g���ĉ�]�������߂�B
					//�O�ς͓�̃x�N�g�����g���Čv�Z����B
					//�O�ς̌��ʂ͐V�����x�N�g���ɂȂ�B
					// V1�~V2 = V3
					//�����ĐV�����x�N�g��(V3)��V1��V2�ɒ��s���Ă���x�N�g���ɂȂ�I�I�I
					axisX.Cross(CVector3::AxisY, targetToPos);
					//�O�ς̌��ʂ͑傫���P�ł͂Ȃ��̂ŁA���K������B�@
					axisX.Normalize();
					qRot.SetRotationDeg(axisX, 5.0f*y);
					//�����_���王�_�ɐL�т�x�N�g�����񂷁B
					qRot.Multiply(targetToPos);
					//�����_���王�_����ɐL�т�x�N�g������傫�������O����
					//�����݂̂̃f�[�^�ɂ���B
					CVector3 targetToPosDir = targetToPos;
					targetToPosDir.Normalize();

					//���_�𓮂���
					//CVector3 cameraPos;
					cameraPos = cameraTarget + targetToPos;

				}

				swapTimer++;
			}
		}
		if (stage == 2) {//�e�B���I�X�J�Ƀt�H�[�J�X����	
			if (ResultCameraFlag == false) {
				Teruosuka * teruosuka = FindGO<Teruosuka>("Teruosuka");
				cameraTarget = teruosuka->Getm_Position();
				//���_���J�����ɓ`����
				cameraTarget.y += 3000.0f;
				cameraPos.x = cameraTarget.x + targetToPos.x;
				cameraPos.y = cameraTarget.y + targetToPos.y - 50.0f;
				cameraPos.z = cameraTarget.z + targetToPos.z;
				ResultCameraFlag = true;
				swapTimer = -1;
			}
			else {

				if (swapTimer < 180) {

					//�����_���王�_�Ɍ������x�N�g������
					float x;
					if (ResultCameraMoveFlag == false) {
						x = 20.0f;
						ResultCameraMoveFlag = true;
					}
					else {
						x = -0.05f;
					}
					float y = 0.0f;
					//Y������̉�]
					CQuaternion qRot;
					qRot.SetRotationDeg(CVector3::AxisY, 5.0f * x);
					qRot.Multiply(targetToPos);

					// X������̉�]
					CVector3 axisX;
					//�O�ς��g���ĉ�]�������߂�B
					//�O�ς͓�̃x�N�g�����g���Čv�Z����B
					//�O�ς̌��ʂ͐V�����x�N�g���ɂȂ�B
					// V1�~V2 = V3
					//�����ĐV�����x�N�g��(V3)��V1��V2�ɒ��s���Ă���x�N�g���ɂȂ�I�I�I
					axisX.Cross(CVector3::AxisY, targetToPos);
					//�O�ς̌��ʂ͑傫���P�ł͂Ȃ��̂ŁA���K������B�@
					axisX.Normalize();
					qRot.SetRotationDeg(axisX, 5.0f*y);
					//�����_���王�_�ɐL�т�x�N�g�����񂷁B
					qRot.Multiply(targetToPos);
					//�����_���王�_����ɐL�т�x�N�g������傫�������O����
					//�����݂̂̃f�[�^�ɂ���B
					CVector3 targetToPosDir = targetToPos;
					targetToPosDir.Normalize();

					//���_�𓮂���
					//CVector3 cameraPos;
					cameraPos = cameraTarget + targetToPos;

				}

				swapTimer++;
			}
		}
		if (stage == 3) {//�p�C���h���S�Ƀt�H�[�J�X����	
			if (ResultCameraFlag == false) {
				Pairodorago * pairodorago = FindGO<Pairodorago>("Pairodorago");
				cameraTarget = pairodorago->Getm_Position();
				//���_���J�����ɓ`����
				cameraTarget.y += 3000.0f;
				cameraPos.x = cameraTarget.x + targetToPos.x;
				cameraPos.y = cameraTarget.y + targetToPos.y;
				cameraPos.z = cameraTarget.z + targetToPos.z;
				ResultCameraFlag = true;
				swapTimer = -1;
			}
			else {

				if (swapTimer < 180) {

					//�����_���王�_�Ɍ������x�N�g������
					float x;
					if (ResultCameraMoveFlag == false) {
						x = 20.0f;
						ResultCameraMoveFlag = true;
					}
					else {
						x = -0.05f;
					}
					float y = 0.0f;
					//Y������̉�]
					CQuaternion qRot;
					qRot.SetRotationDeg(CVector3::AxisY, 5.0f * x);
					qRot.Multiply(targetToPos);

					// X������̉�]
					CVector3 axisX;
					//�O�ς��g���ĉ�]�������߂�B
					//�O�ς͓�̃x�N�g�����g���Čv�Z����B
					//�O�ς̌��ʂ͐V�����x�N�g���ɂȂ�B
					// V1�~V2 = V3
					//�����ĐV�����x�N�g��(V3)��V1��V2�ɒ��s���Ă���x�N�g���ɂȂ�I�I�I
					axisX.Cross(CVector3::AxisY, targetToPos);
					//�O�ς̌��ʂ͑傫���P�ł͂Ȃ��̂ŁA���K������B�@
					axisX.Normalize();
					qRot.SetRotationDeg(axisX, 5.0f*y);
					//�����_���王�_�ɐL�т�x�N�g�����񂷁B
					qRot.Multiply(targetToPos);
					//�����_���王�_����ɐL�т�x�N�g������傫�������O����
					//�����݂̂̃f�[�^�ɂ���B
					CVector3 targetToPosDir = targetToPos;
					targetToPosDir.Normalize();

					//���_�𓮂���
					//CVector3 cameraPos;
					cameraPos = cameraTarget + targetToPos;

				}

				swapTimer++;
			}
		}
		if (stage == 4) {//SS-001�Ƀt�H�[�J�X����	
			if (ResultCameraFlag == false) {
				SS_001 * ss_001 = FindGO<SS_001>("SS_001");
				cameraTarget = ss_001->Getm_Position();
				//���_���J�����ɓ`����
				cameraPos.x = cameraTarget.x + targetToPos.x;
				cameraPos.y = cameraTarget.y + targetToPos.y;
				cameraPos.z = cameraTarget.z + targetToPos.z;
				ResultCameraFlag = true;
				swapTimer = -1;
			}
			else {

				if (swapTimer < 180) {

					//�����_���王�_�Ɍ������x�N�g������
					float x;
					if (ResultCameraMoveFlag == false) {
						x = 20.0f;
						ResultCameraMoveFlag = true;
					}
					else {
						x = -0.05f;
					}
					float y = 0.0f;
					//Y������̉�]
					CQuaternion qRot;
					qRot.SetRotationDeg(CVector3::AxisY, 5.0f * x);
					qRot.Multiply(targetToPos);

					// X������̉�]
					CVector3 axisX;
					//�O�ς��g���ĉ�]�������߂�B
					//�O�ς͓�̃x�N�g�����g���Čv�Z����B
					//�O�ς̌��ʂ͐V�����x�N�g���ɂȂ�B
					// V1�~V2 = V3
					//�����ĐV�����x�N�g��(V3)��V1��V2�ɒ��s���Ă���x�N�g���ɂȂ�I�I�I
					axisX.Cross(CVector3::AxisY, targetToPos);
					//�O�ς̌��ʂ͑傫���P�ł͂Ȃ��̂ŁA���K������B�@
					axisX.Normalize();
					qRot.SetRotationDeg(axisX, 5.0f*y);
					//�����_���王�_�ɐL�т�x�N�g�����񂷁B
					qRot.Multiply(targetToPos);
					//�����_���王�_����ɐL�т�x�N�g������傫�������O����
					//�����݂̂̃f�[�^�ɂ���B
					CVector3 targetToPosDir = targetToPos;
					targetToPosDir.Normalize();

					//���_�𓮂���
					//CVector3 cameraPos;
					cameraPos = cameraTarget + targetToPos;

				}

				swapTimer++;
			}
		}

	}

	//�����_���J�����ɓ`����
	MainCamera().SetTarget(cameraTarget);
	MainCamera().SetPosition(cameraPos);
	//�J�����s����X�V����
	MainCamera().Update();

}

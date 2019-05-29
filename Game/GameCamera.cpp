#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "GameData.h"
#include "LevelData.h"

//�{�X
#include "shisokus.h"

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

	if (mode == 0) {
		//�����_�𓮂���
		cameraTarget.x = P_Position.x;
		cameraTarget.y = P_Position.y;	//�v���C���[�̂�����Ə�ɂ���
		cameraTarget.z = P_Position.z;

		//���_���J�����ɓ`����
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
			//�܂����̂����ōĐ��ł�
			int stage = gamedata->GetStageNo();
			stage--;
			ss = NewGO<prefab::CSoundSource>(0);
			//SE�Đ�
			ss->Init(BossBGMName[stage]);
			ss->SetVolume(BMG_V);
			ss->Play(true);
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
		if (stage == 1) {//�V�[�\�[�N�X�Ƀt�H�[�J�X����	
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
	}

	//�����_���J�����ɓ`����
	MainCamera().SetTarget(cameraTarget);
	MainCamera().SetPosition(cameraPos);

	//�J�����s����X�V����
	MainCamera().Update();

}

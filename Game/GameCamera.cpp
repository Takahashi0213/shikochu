#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "GameData.h"

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

	if (mode==0 || mode == 3 ) {
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
			GameData * gamedata = GameData::GetInstance();
			gamedata->SetGameMode(GameData::Battle3D_Mode);
			swapTimer = -1; //�^�C�}�[�������܂�
		}

	}

	//�����_���J�����ɓ`����
	MainCamera().SetTarget(cameraTarget);
	MainCamera().SetPosition(cameraPos);

	//�J�����s����X�V����
	MainCamera().Update();

}

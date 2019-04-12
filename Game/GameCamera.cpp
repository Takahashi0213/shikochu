#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "GameData.h"

GameCamera::GameCamera()
{

}


GameCamera::~GameCamera()
{
}

bool GameCamera::Start() {

	//�����ʂ�ݒ肷��
	MainCamera().SetFar(30000.0f);
	//��p��ύX
	MainCamera().SetViewAngle(CMath::DegToRad(80.0f));

	Player * player = FindGO<Player>("Bug");
	CVector3 P_Position = player->Getm_Position();
	//�����_�𓮂���
	cameraTarget.x = P_Position.x;
	cameraTarget.y = P_Position.y;	//�v���C���[�̂�����Ə�ɂ���
	cameraTarget.z = P_Position.z;

	//���_���J�����ɓ`����
	cameraPos.x = P_Position.x;
	cameraPos.y = P_Position.y + 200.0f;	//�v���C���[�̂�����Ə�ɂ���
	cameraPos.z = P_Position.z - 5.0f;

	//�����_���J�����ɓ`����
	MainCamera().SetTarget(cameraTarget);
	MainCamera().SetPosition(cameraPos);

	//�J�����s����X�V����
	MainCamera().Update();

	return true;
}

void GameCamera::Update() {

	GameData * gameData = FindGO<GameData>("GameData");
	int mode = gameData->GetGameMode();

	Player * player = FindGO<Player>("Bug");
	CVector3 P_Position = player->Getm_Position();

	if (mode==0) {
		//�����_�𓮂���
		cameraTarget.x = P_Position.x;
		cameraTarget.y = P_Position.y;	//�v���C���[�̂�����Ə�ɂ���
		cameraTarget.z = P_Position.z;

		//���_���J�����ɓ`����
		cameraPos.x = P_Position.x;
		cameraPos.y = P_Position.y + 200.0f;	//�v���C���[�̂�����Ə�ɂ���
		cameraPos.z = P_Position.z - 5.0f;
	}
	else if (mode == 1) {

		//�����_�𓮂���
		cameraTarget.x = P_Position.x;
		cameraTarget.y = P_Position.y;	
		cameraTarget.z = P_Position.z;

		//���_���J�����ɓ`����
		cameraPos.x = P_Position.x;
		cameraPos.y = P_Position.y;	//�v���C���[�̂�����Ə�ɂ���
		cameraPos.z = P_Position.z - 200.0f;

	}
	//�����_���J�����ɓ`����
	MainCamera().SetTarget(cameraTarget);
	MainCamera().SetPosition(cameraPos);

	//�J�����s����X�V����
	MainCamera().Update();

}

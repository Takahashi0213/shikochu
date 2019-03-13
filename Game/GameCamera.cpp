#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

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
	//�����_�𓮂���
	cameraTarget.x = player->position.x;
	cameraTarget.y = player->position.y;	//�v���C���[�̂�����Ə�ɂ���
	cameraTarget.z = player->position.z;

	//���_���J�����ɓ`����
	cameraPos.x = player->position.x;
	cameraPos.y = player->position.y + 200.0f;	//�v���C���[�̂�����Ə�ɂ���
	cameraPos.z = player->position.z - 5.0f;

	//�����_���J�����ɓ`����
	MainCamera().SetTarget(cameraTarget);
	MainCamera().SetPosition(cameraPos);

	//�J�����s����X�V����
	MainCamera().Update();

	return true;
}

void GameCamera::Update() {

	Player * player = FindGO<Player>("Bug");
	//�����_�𓮂���
	cameraTarget.x = player->position.x;
	cameraTarget.y = player->position.y;	//�v���C���[�̂�����Ə�ɂ���
	cameraTarget.z = player->position.z;

	//���_���J�����ɓ`����
	cameraPos.x = player->position.x;
	cameraPos.y = player->position.y + 200.0f;	//�v���C���[�̂�����Ə�ɂ���
	cameraPos.z = player->position.z - 5.0f;

	//�����_���J�����ɓ`����
	MainCamera().SetTarget(cameraTarget);
	MainCamera().SetPosition(cameraPos);

	//�J�����s����X�V����
	MainCamera().Update();

}

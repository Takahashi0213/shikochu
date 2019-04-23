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

	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();

	Player * player = Player::GetInstance();
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

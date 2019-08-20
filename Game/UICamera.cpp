#include "stdafx.h"
#include "UICamera.h"

UICamera* UICamera::m_instance = nullptr;

UICamera::UICamera()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɃJ�������o�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;
}

UICamera::~UICamera()
{
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
}

bool UICamera::Start(){

	//�����ʂ�ݒ肷��
	MainCamera().SetFar(30000.0f);
	//��p��ύX
	MainCamera().SetViewAngle(CMath::DegToRad(80.0f));

	//�����_�𓮂���
	cameraTarget.x = 0.0f;
	cameraTarget.y = 0.0f;
	cameraTarget.z = 0.0f;

	//���_���J�����ɓ`����
	cameraPos.x = CameraDefPos.x;
	cameraPos.y = CameraDefPos.y;
	cameraPos.z = CameraDefPos.z;

	//�����_���J�����ɓ`����
	MainCamera().SetTarget(cameraTarget);
	MainCamera().SetPosition(cameraPos);

	//�J�����s����X�V����
	MainCamera().Update();

	return true;

}

void UICamera::Update() {

	//�����_�𓮂���
	cameraTarget.x = 0.0f;
	cameraTarget.y = 0.0f;
	cameraTarget.z = 0.0f;

	if(C_Flag==false){//�ʏ���
		//���_���J�����ɓ`����
		cameraPos.x = CameraDefPos.x;
		cameraPos.y = CameraDefPos.y;
		cameraPos.z = CameraDefPos.z;
	}
	else {//�}�ӂ��I�I�I
		//���_���J�����ɓ`����
		cameraPos.x = CameraDefPosC.x;
		cameraPos.y = CameraDefPosC.y;
		cameraPos.z = CameraDefPosC.z;
	}

	//�����_���J�����ɓ`����
	MainCamera().SetTarget(cameraTarget);
	MainCamera().SetPosition(cameraPos);

	//�J�����s����X�V����
	MainCamera().Update();

}



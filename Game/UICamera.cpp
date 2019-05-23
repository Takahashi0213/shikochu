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
	cameraPos.x = 0.0f;
	cameraPos.y = 100.0f;
	cameraPos.z = 100.0f;

	//�����_���J�����ɓ`����
	MainCamera().SetTarget(cameraTarget);
	MainCamera().SetPosition(cameraPos);

	//�J�����s����X�V����
	MainCamera().Update();

	return true;

}

void UICamera::Update() {

}


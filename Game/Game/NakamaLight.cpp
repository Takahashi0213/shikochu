#include "stdafx.h"
#include "NakamaLight.h"
#include "GameData.h"

NakamaLight* NakamaLight::m_instance = nullptr;

NakamaLight::NakamaLight()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;
}


NakamaLight::~NakamaLight()
{
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
}

bool NakamaLight::Start() {


	return true;
}

void NakamaLight::Update() {

}

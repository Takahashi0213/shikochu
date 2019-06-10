#include "stdafx.h"
#include "BackGround.h"

BackGround* BackGround::m_instance = nullptr;

BackGround::BackGround()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;

}


BackGround::~BackGround()
{
	DeleteGO(m_skinModelRender);
	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;

}

//-100�������ɐݒ肵���ꍇ�`���[�g���A���p�X�e�[�W�𐶐�
void BackGround::StageMaker(int ST){

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0, "stage");

	if (ST != -100) {
		//���O�����������Ă���
		int len = wcslen(DetaBase[ST]);
		for (int x = 0; x < len + 1; x++) {
			ST_Name[x] = DetaBase[ST][x];
		}
	}
	else if (ST == -100) {
		//���O�����������Ă���
		int len = wcslen(Tutorial[0]);
		for (int x = 0; x < len + 1; x++) {
			ST_Name[x] = Tutorial[0][x];
		}
	}
	//�쐬
	m_skinModelRender->Init(ST_Name, nullptr, 0);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetEmissionColor(StageEmission);

	//CPhysicsStaticObject�̏�����
	if (physicsFlag[ST] == true) {
		m_physicsStaticObject.CreateMesh(m_position, CQuaternion::Identity, m_scale, m_skinModelRender);
	}
}

void BackGround::DeleteStage() {

	DeleteGO(this);

}


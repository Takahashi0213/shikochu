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

void BackGround::StageMaker(Stage ST){

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0, "stage");

	//���O�����������Ă���
	int len = wcslen(DetaBase[ST]);
	for (int x = 0; x < len+1; x++) {
		ST_Name[x] = DetaBase[ST][x];
	}
	//�쐬
	m_skinModelRender->Init(ST_Name, nullptr, 0);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetEmissionColor(StageEmission);

}

void BackGround::DeleteStage() {

	DeleteGO(this);

}


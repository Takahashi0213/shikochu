#include "stdafx.h"
#include "shisokus.h"


shisokus::shisokus()
{
}


shisokus::~shisokus()
{
}

bool shisokus::Start() {

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/shisokus.cmo");
	m_skinModelRender->SetForwardRenderFlag(true);
	m_rotation.SetRotationDeg(CVector3::AxisY, -90.0f);
	m_position = { 0.0f,500.0f,3000.0f };
	m_skinModelRender->SetPosition(m_position);

	m_scale = { 10.0f,10.0f,10.0f };
	m_charaCon.Init(
		35.0f,  //�L�����N�^�[�̔��a�B
		10.0f,  //�L�����N�^�[�̍����B
		m_position //�L�����N�^�[�̏������W�B
	);

	return true;
}
void shisokus::shisoMove() {
	//�ʏ��ԁB
}
void shisokus::shisoYobi1() {

}
void shisokus::shisoAttack1() {

}
void shisokus::shisoYobi2() {

}
void shisokus::shisoAttack2() {
	
}
void shisokus::shisoDeath() {
	//�������
}


void shisokus::Update() {
	switch (m_stete) {
		case Estete_Move://�ړ�
			shisoMove();
			break;
		case Estete_Yobi1://�\������1
			shisoYobi1();
			break;
		case Estete_Attack1://�U��1
			shisoAttack1();
			break;
		case Estete_Yobi2://�\������2
			shisoYobi2();
			break;
		case Estete_Attack2://�U��2
			shisoAttack2();
			break;
		case Estete_Death://���
			shisoDeath();
			break;
	}
	//�ړ�
	m_skinModelRender->SetPosition(m_position);
	//��]
	m_skinModelRender->SetRotation(m_rotation);
	//�g�嗦
	m_skinModelRender->SetScale(m_scale);

}


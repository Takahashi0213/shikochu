#include "stdafx.h"
#include "SS_001.h"


SS_001::SS_001()
{
}


SS_001::~SS_001()
{
}

bool SS_001::Start() {

	//�A�j���[�V����
	m_animClips[enAnimationClip_move].Load(L"animData/SSwalk.tka");
	m_animClips[enAnimationClip_move].SetLoopFlag(true);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/SS_001.cmo", m_animClips, enAnimationClip_Num);
	//m_skinModelRender->SetForwardRenderFlag(true);
	m_rotation.SetRotationDeg(CVector3::AxisY, -180.0f);


	m_scale = { 10.0f,10.0f,10.0f };
	m_position = { 0.0f,500.0f,5000.0f };

	m_skinModelRender->SetPosition(m_position);

	m_charaCon.Init(
		350.0f,  //�L�����N�^�[�̔��a�B
		100.0f,  //�L�����N�^�[�̍����B
		m_position //�L�����N�^�[�̏������W�B
	);

	return true;
}

void SS_001::Update() {

	switch (m_stete) {
	case Estete_Move://�ړ�
		SSMove();
		break;
	case Estete_Yobi1://�\������1
		SSYobi1();
		break;
	case Estete_Attack1://�U��1
		SSAttack1();
		break;
	case Estete_Yobi2://�\������2
		SSYobi2();
		break;
	case Estete_Attack2://�U��2
		SSAttack2();
		break;
	case Estete_Death://���
		SSDeath();
		break;
	}
	//HP��0�Ȃ玀��
	if (NowHP == 0) {
		m_stete = Estete_Death;
	}
	//�ړ�
	m_skinModelRender->SetPosition(m_position);
	//��]
	m_skinModelRender->SetRotation(m_rotation);
	//�g�嗦
	m_skinModelRender->SetScale(m_scale);

}

void SS_001::SSMove() {

}

void SS_001::SSYobi1() {

}

void SS_001::SSAttack1() {

}

void SS_001::SSYobi2() {

}

void SS_001::SSAttack2() {

}

void SS_001::SSDeath() {

}
#include "stdafx.h"
#include "Pairodorago.h"


Pairodorago::Pairodorago()
{
}


Pairodorago::~Pairodorago()
{
}

bool Pairodorago::Start() {

	//�A�j���[�V����
	m_animClips[enAnimationClip_move].Load(L"animData/SSwalk.tka");
	m_animClips[enAnimationClip_move].SetLoopFlag(true);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/DragonTerrorBringerMesh.cmo", m_animClips, enAnimationClip_Num);
	//m_skinModelRender->SetForwardRenderFlag(true);
	m_rotation.SetRotationDeg(CVector3::AxisY, -180.0f);


	m_scale = { 10.0f,10.0f,10.0f };

	m_skinModelRender->SetPosition(m_position);

	m_charaCon.Init(
		350.0f,  //�L�����N�^�[�̔��a�B
		100.0f,  //�L�����N�^�[�̍����B
		m_position //�L�����N�^�[�̏������W�B
	);

	return true;
}

void Pairodorago::Update() {

}
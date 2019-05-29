#include "stdafx.h"
#include "Pairodorago.h"


Pairodorago::Pairodorago()
{
}


Pairodorago::~Pairodorago()
{
}

bool Pairodorago::Start() {

	//アニメーション
	m_animClips[enAnimationClip_move].Load(L"animData/SSwalk.tka");
	m_animClips[enAnimationClip_move].SetLoopFlag(true);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/DragonTerrorBringerMesh.cmo", m_animClips, enAnimationClip_Num);
	//m_skinModelRender->SetForwardRenderFlag(true);
	m_rotation.SetRotationDeg(CVector3::AxisY, -180.0f);


	m_scale = { 10.0f,10.0f,10.0f };

	m_skinModelRender->SetPosition(m_position);

	m_charaCon.Init(
		350.0f,  //キャラクターの半径。
		100.0f,  //キャラクターの高さ。
		m_position //キャラクターの初期座標。
	);

	return true;
}

void Pairodorago::Update() {

}
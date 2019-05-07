#include "stdafx.h"
#include "Neoriku.h"


Neoriku::Neoriku()
{
}


Neoriku::~Neoriku()
{
	DeleteGO(m_skinModelRender);
}

bool Neoriku::Start() {
	//アニメーションクリップをロードとループフラグ。
	m_animClips[enAnimationClip_walk].Load(L"animData/Neowalk.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);

	//m_animClips[enAnimationClip_attack1].SetLoopFlag(true);
	//スキンモデル
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/neoriku_0.cmo", m_animClips, enAnimationClip_Num);
	//m_position = { 100.0f,0.0f,0.0f };
	//m_skinModelRender->SetPosition(m_position);

	m_scale = { 2.0f,2.0f,2.0f };
	m_charaCon.Init(
		35.0f,  //キャラクターの半径。
		10.0f,  //キャラクターの高さ。
		m_position //キャラクターの初期座標。
	);


	return true;
}

void Neoriku::NeoAttack() {
	//攻撃中

}

void Neoriku::NeoMove() {
	//移動中

}
void Neoriku::NeoDeath() {
	//死んだ......ｳｯ...

}
void Neoriku::Neoyobi() {
	//予備動作


}

void Neoriku::Update() {
	switch (m_Neostete) {
	case Estete_Attack://攻撃
		NeoAttack();
		break;
	case Estete_Move://移動
		NeoMove();
		break;
	case Estete_Death:
		NeoDeath();//死
		break;
	case Estete_yobi:
		Neoyobi();//予備動作
		break;
	}
	//移動
	m_skinModelRender->SetPosition(m_position);
	//回転
	m_skinModelRender->SetRotation(m_rotation);
	//拡大率
	m_skinModelRender->SetScale(m_scale);

}



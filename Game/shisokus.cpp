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
		35.0f,  //キャラクターの半径。
		10.0f,  //キャラクターの高さ。
		m_position //キャラクターの初期座標。
	);

	return true;
}
void shisokus::shisoMove() {
	//通常状態。
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
	//ﾔﾗﾚﾀ･･･
}


void shisokus::Update() {
	switch (m_stete) {
		case Estete_Move://移動
			shisoMove();
			break;
		case Estete_Yobi1://予備動作1
			shisoYobi1();
			break;
		case Estete_Attack1://攻撃1
			shisoAttack1();
			break;
		case Estete_Yobi2://予備動作2
			shisoYobi2();
			break;
		case Estete_Attack2://攻撃2
			shisoAttack2();
			break;
		case Estete_Death://死ﾇ
			shisoDeath();
			break;
	}
	//移動
	m_skinModelRender->SetPosition(m_position);
	//回転
	m_skinModelRender->SetRotation(m_rotation);
	//拡大率
	m_skinModelRender->SetScale(m_scale);

}


#include "stdafx.h"
#include "Morikon.h"


Morikon::Morikon()
{
}


Morikon::~Morikon()
{
}

bool Morikon::Start() {

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Bat_Level_1.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);

	m_charaCon.Init(
		45.0f,  //キャラクターの半径。
		10.0f,  //キャラクターの高さ。
		m_position //キャラクターの初期座標。
	);

	return true;
}
void Morikon::Update() {

}

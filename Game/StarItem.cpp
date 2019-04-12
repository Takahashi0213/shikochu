#include "stdafx.h"
#include "StarItem.h"
#include "Player.h"
#include "GameData.h"

StarItem::StarItem()
{
}


StarItem::~StarItem()
{
	DeleteGO(m_skinModelRender);
}

bool StarItem::Start() {

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0, "item");
	m_skinModelRender->Init(L"modelData/item.cmo", nullptr, 0);

	m_position = { -200.0f,0.0f,-200.0f };
	m_skinModelRender->SetPosition(m_position);

	return true;
}

void StarItem::Update() {

	if (m_stete == Estete_Wait) {
		//接触判定
		Player * player = FindGO<Player>("Bug");
		CVector3 player_position = player->Getm_Position();
		CVector3 diff = player_position - m_position;
		itemVec = diff;

		if (diff.Length() < 60.0f) {
			m_stete = Estete_Death;
		}
	}
	else {//消滅中
		GameData * gamedata = FindGO<GameData>("GameData");
		gamedata->Star_PowerChange(1);
		m_scale -= {0.1f, 0.1f, 0.1f};
		itemTimer--;
		if (itemTimer <= 0) {
			DeleteGO(this);
		}
	}

	CQuaternion RotationY;
	RotationY.SetRotationDeg(CVector3::AxisY, -1.0f);
	//回転を加算する。
	m_rotation *= RotationY;
	//回転を設定する。
	m_skinModelRender->SetRotation(m_rotation);
	//拡大率を設定する。
	m_skinModelRender->SetScale(m_scale);


}
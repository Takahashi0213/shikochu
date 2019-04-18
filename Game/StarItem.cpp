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
	DeleteGO(m_pointLig);

}

bool StarItem::Start() {

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0, "item");
	m_skinModelRender->Init(L"modelData/item.cmo", nullptr, 0);
	m_skinModelRender->SetEmissionColor(ItemEmission);

	m_position = { -200.0f,0.0f, 200.0f };
	m_skinModelRender->SetPosition(m_position);

	m_pointLig = NewGO<prefab::CPointLight>(0, "ItemLight");
	m_pointLig->SetColor(ItemLight);
	m_pointLig->SetAttn(ItemLightAttn);

	//���C�g�������l��
	ItemEmission = ItemEmissionDEF;
	ItemLight = ItemLightDEF;
	ItemLightAttn = ItemLightAttnDEF;

	return true;
}

void StarItem::Update() {

	if (m_stete == Estete_Wait) {
		//�ڐG����
		Player * player = FindGO<Player>("Bug");
		CVector3 player_position = player->Getm_Position();
		CVector3 diff = player_position - m_position;
		itemVec = diff;
		//���������ȉ��Ȃ玩��
		if (diff.Length() < GetRange) {
			m_stete = Estete_Death;
		}
	}
	else {
		//���Œ�
		GameData * gamedata = FindGO<GameData>("GameData");
		gamedata->Star_PowerChange(1);
		m_scale -= {0.1f, 0.1f, 0.1f};//�������Ȃ�
		itemTimer--;
		if (itemTimer <= 0) {//�^�C�}�[��0�ŃC���X�^���X���폜
			DeleteGO(this);
		}
	}

	CQuaternion RotationY;
	RotationY.SetRotationDeg(CVector3::AxisY, -1.0f);
	//��]�����Z����B
	m_rotation *= RotationY;
	//��]��ݒ肷��B
	m_skinModelRender->SetRotation(m_rotation);
	//�g�嗦��ݒ肷��B
	m_skinModelRender->SetScale(m_scale);
	//���C�g
	m_pointLig->SetPosition(m_position);
	m_pointLig->SetColor(ItemLight);
	m_pointLig->SetAttn(ItemLightAttn);

}
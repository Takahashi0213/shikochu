#include "stdafx.h"
#include "StarItem.h"
#include "Player.h"
#include "GameData.h"
#include "EffectManager.h"
#include "SaveData.h"

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

	m_pointLig = NewGO<prefab::CPointLight>(0, "ItemLight");
	m_pointLig->SetColor(ItemLight);
	m_pointLig->SetAttn(ItemLightAttn);

	//���C�g�������l��
	ItemEmission = ItemEmissionDEF;
	ItemLight = ItemLightDEF;
	ItemLightAttn = ItemLightAttnDEF;

	m_skinModelRender->SetPosition(m_position);

	//Effect�Đ�
	EffectManager * effectmanager = EffectManager::GetInstance();
	effectmanager->EffectPlayer(EffectManager::ItemSpawn, m_position, EffectScale);

	return true;
}

void StarItem::Update() {

	if (m_stete == Estete_Wait) {
		//�ڐG����
		Player * player = Player::GetInstance();
		CVector3 player_position = player->Getm_Position();
		CVector3 diff = player_position - m_position;
		itemVec = diff;
		//���������ȉ��Ȃ玩��
		if (diff.Length() < GetRange && player->GetNowSkill() == -1 ) {
			prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/Item.wav");
			ss->SetVolume(1.0f);
			ss->Play(false);

			//Effect�Đ�
			EffectManager * effectmanager = EffectManager::GetInstance();
			effectmanager->EffectPlayer(EffectManager::ItemGet, m_position, EffectScale, false, false);
			//�A�C�e���J�E���g����
			GameData * gamedata = GameData::GetInstance();
			gamedata->ItemCounter();
			//state�ύX
			m_stete = Estete_Death;
		}
	}
	else if(m_stete== Estete_Death){
		//���Œ�
		GameData * gamedata = GameData::GetInstance();
		SaveData * savedata = SaveData::GetInstance();

		if (savedata->GetSkill(false) == 14 || savedata->GetSkill(true) == 14) { //�A�C�e���u�[�X�g
			gamedata->Star_PowerChange(3);
		}
		else {
			gamedata->Star_PowerChange(2);
		}

		m_scale -= {0.1f, 0.1f, 0.1f};//�������Ȃ�
		itemTimer--;
		if (itemTimer <= 0) {//�^�C�}�[��0�ŃC���X�^���X���폜
			DeleteGO(this);
		}
	}
	else if (m_stete == Estete_Death2) {
		//���Œ�
		m_scale -= {0.1f, 0.1f, 0.1f};//�������Ȃ�
		itemTimer--;
		if (itemTimer <= 0) {//�^�C�}�[��0�ŃC���X�^���X���폜
			//Effect�Đ�
			EffectManager * effectmanager = EffectManager::GetInstance();
			effectmanager->EffectPlayer(EffectManager::ItemSpawn, m_position, EffectScale);

			DeleteGO(this);
		}
	}
	else if (m_stete == Estete_Death3) {
			DeleteGO(this);
	}

	CQuaternion RotationY;
	RotationY.SetRotationDeg(CVector3::AxisY, RotItem);
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
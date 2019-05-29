#include "stdafx.h"
#include "StarItem.h"
#include "Player.h"
#include "GameData.h"
#include "EffectManager.h"

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

	//ライトを初期値に
	ItemEmission = ItemEmissionDEF;
	ItemLight = ItemLightDEF;
	ItemLightAttn = ItemLightAttnDEF;

	m_skinModelRender->SetPosition(m_position);

	//Effect再生
	EffectManager * effectmanager = EffectManager::GetInstance();
	effectmanager->EffectPlayer(EffectManager::ItemSpawn, m_position, EffectScale);

	return true;
}

void StarItem::Update() {

	if (m_stete == Estete_Wait) {
		//接触判定
		Player * player = Player::GetInstance();
		CVector3 player_position = player->Getm_Position();
		CVector3 diff = player_position - m_position;
		itemVec = diff;
		//距離が一定以下なら自死
		if (diff.Length() < GetRange) {
			prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
			ss->Init(L"sound/Item.wav");
			ss->SetVolume(1.0f);
			ss->Play(false);

			//Effect再生
			EffectManager * effectmanager = EffectManager::GetInstance();
			effectmanager->EffectPlayer(EffectManager::ItemGet, m_position, EffectScale);
			//アイテムカウント増加
			GameData * gamedata = GameData::GetInstance();
			gamedata->ItemCounter();
			//state変更
			m_stete = Estete_Death;
		}
	}
	else if(m_stete== Estete_Death){
		//消滅中
		GameData * gamedata = GameData::GetInstance();
		gamedata->Star_PowerChange(1);
		m_scale -= {0.1f, 0.1f, 0.1f};//小さくなる
		itemTimer--;
		if (itemTimer <= 0) {//タイマーが0でインスタンスを削除
			DeleteGO(this);
		}
	}
	else if (m_stete == Estete_Death2) {
		//消滅中
		m_scale -= {0.1f, 0.1f, 0.1f};//小さくなる
		itemTimer--;
		if (itemTimer <= 0) {//タイマーが0でインスタンスを削除
			//Effect再生
			EffectManager * effectmanager = EffectManager::GetInstance();
			effectmanager->EffectPlayer(EffectManager::ItemSpawn, m_position, EffectScale);

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
	//ライト
	m_pointLig->SetPosition(m_position);
	m_pointLig->SetColor(ItemLight);
	m_pointLig->SetAttn(ItemLightAttn);

}
#include "stdafx.h"
#include "AppleBomb.h"
#include "EffectManager.h"
#include "GameData.h"

AppleBomb::AppleBomb()
{
}


AppleBomb::~AppleBomb()
{
	DeleteGO(m_skinModelRender);
}

bool AppleBomb::Start() {

	m_animClips[enAnimationClip_move].Load(L"animData/Apple.tka");
	m_animClips[enAnimationClip_move].SetLoopFlag(true);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Apple.cmo", m_animClips, enAnimationClip_Num);

	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();
	if (mode == GameData::Battle3D_Mode || mode == GameData::BattleMode_Swap) {
		m_scale = { 5.0f,5.0f,5.0f };
	}
	else {
		m_scale = { 1.0f,1.0f,1.0f };
	}

	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(CQuaternion::Identity);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->PlayAnimation(enAnimationClip_move);

	return true;
}

void AppleBomb::Update() {

	GameData * gamedata = GameData::GetInstance();
	EffectManager * effectmanager = EffectManager::GetInstance();
	int mode = gamedata->GetGameMode();
	if (mode != GameData::Pause) {

		switch (m_stete) {
		case Estete_Move://移動

			AppleMove();

			break;
		case Estete_Death://死ﾇ

			 //Effect再生
			effectmanager->EffectPlayer(EffectManager::Bakuhatu, m_position, { 30.0f,30.0f,30.0f });

			DeleteGO(this);

			break;
		case Estete_Death2://死ﾇ

			DeleteGO(this);

			break;

		}

		//移動
		m_skinModelRender->SetPosition(m_position);
		//回転
		m_skinModelRender->SetRotation(CQuaternion::Identity);
		//拡大率
		m_skinModelRender->SetScale(m_scale);
	}
	if (mode == GameData::GameEnd) {
		DeleteGO(this);
	}

}

void AppleBomb::AppleMove() {

	if (Target_position.y != 0.0f) {
		//移動する
		if (Target_position.y < m_position.y) {
			m_position.y -= MoveSpeed;
			if (Target_position.y > m_position.y) {
				DeleteGO(this);
			}
		}

	}
}

//ダメージ範囲を教える関数
float AppleBomb::GetDamageLength() {

	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();
	float X;

	if (mode == GameData::Battle3D_Mode) {
		X = DamageLength * 5.0f;
	}
	else {
		X = DamageLength;
	}

	return X;
}
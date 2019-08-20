#include "stdafx.h"
#include "StarComet_Inseki.h"
#include "GameData.h"
#include "EffectManager.h"

StarComet_Inseki::StarComet_Inseki()
{
}


StarComet_Inseki::~StarComet_Inseki()
{
	DeleteGO(m_skinModelRender);
}

bool StarComet_Inseki::Start() {

	//スキンモデル
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Rock1.cmo");
	m_skinModelRender->SetPosition(m_position);

	m_scale = { 0.2f, 0.2f, 0.2 };
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetEmissionColor({ 100.0f, 20.0f,20.0f });

	EffectManager * effectmanager = EffectManager::GetInstance();
	effectmanager->EffectPlayer_Post(EffectManager::Bonus, { m_position.x,m_position.y + 50.0f,m_position.z }, { 20.0f,20.0f,20.0f }, true);

	return true;
}

void StarComet_Inseki::Update()
{

	GameData * gameData = GameData::GetInstance();

	if (gameData->GetGameMode() != GameData::Pause) { //ポーズ中は実行しない
		if (gameData->GetFinalMode() == true) {
			m_position.z += 20.0f;
		}
		else {
			m_position += MoveSpeed * MoveHosei;
		}

		CQuaternion qAddRot;
		qAddRot.SetRotationDeg(CVector3::AxisX, 0.1f);
		m_rotation *= qAddRot;

		m_skinModelRender->SetPosition(m_position);
		m_skinModelRender->SetRotation(m_rotation);
		m_skinModelRender->SetScale(m_scale);

		DeleteTimer++;
		if (DeleteTimer >= DeleteLimit) {
			DeleteGO(this);
		}
	}

}
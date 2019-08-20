#include "stdafx.h"
#include "Train2.h"
#include "GameData.h"

Train2::Train2()
{
}


Train2::~Train2()
{
	for (int i = 0; i < m_soundRender.size(); i++) {
		DeleteGO(m_soundRender[i]);
	}

	DeleteGO(m_skinModelRender);
}

bool Train2::Start() {

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Train_2.cmo");

	m_rotation.SetRotation(CVector3::AxisY, 1.575f);

	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRotation(m_rotation);

	return true;
}

void Train2::Update() {

	if (SE_Flag == true) {

		if (Timer == 0) {

			for (int i = 0; i < LoopLimit; i++) {
				ss = NewGO<prefab::CSoundSource>(0);
				ss->Init(L"sound/Train.wav", true);
				ss->SetVolume(1.0f);
				ss->Play(true);
				m_soundRender.push_back(ss);
			}

		}

		//ポジション更新
		SE_Pos = m_position;
		SE_Pos.x -= (TrainNagasa / 2.0f);
		SE_Pos.z += PosZHosei;
		for (int i = 0; i < LoopLimit / 2; i++) {
			m_soundRender[i]->SetPosition(SE_Pos);
			SE_Pos.x += TrainNagasa / ((float)LoopLimit / 2.0f);
		}
		SE_Pos = m_position;
		SE_Pos.x -= (TrainNagasa / 2.0f);
		SE_Pos.z -= PosZHosei;
		for (int i = LoopLimit / 2; i < LoopLimit; i++) {
			m_soundRender[i]->SetPosition(SE_Pos);
			SE_Pos.x += TrainNagasa / ((float)LoopLimit / 2.0f);
		}
	}

	if (GameData::GetInstance()->GetGameMode() != GameData::Pause) {

		m_skinModelRender->SetPosition(m_position);
		m_skinModelRender->SetScale(m_scale);
		m_skinModelRender->SetRotation(m_rotation);

		if (SE_Flag == true) {
			m_position.x += Speed;
		}
		else {
			m_position.x -= Speed;
		}

		Timer++;

		if (Timer == Limit) {
			DeleteGO(this);
		}
	}
}

void Train2::DeleteNow() {
	DeleteGO(this);
}
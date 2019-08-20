#include "stdafx.h"
#include "Rock.h"


Rock::Rock()
{
}


Rock::~Rock()
{
	DeleteGO(m_skinModelRender);
}

bool Rock::Start() {

	//ƒXƒLƒ“ƒ‚ƒfƒ‹
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	random = rand() % 2;
	if (random == 0) {
		m_skinModelRender->Init(L"modelData/Rock1.cmo");
	}
	else if (random == 1) {
		m_skinModelRender->Init(L"modelData/Rock2.cmo");
	}

	m_skinModelRender->SetPosition(m_position);

	random = rand() % 50;
	float Scl = (float)random / 100.0f;
	m_scale.x -= Scl;
	m_scale.y -= Scl;
	m_scale.z -= Scl;
	m_skinModelRender->SetScale(m_scale);

	random = rand() % 2;
	MoveSpeed.x += (float)random;
	random = rand() % 2;
	if (random == 1) {
		MoveSpeed.y -= 0.1f;
	}
	//€”õ
	random = rand() % 100;
	float Roll = (float)random / 100.0f;
	random = rand() % 2;
	if (random == 1) {
		random *= -1;
	}
	RollX = Roll;
	random = rand() % 100;
	Roll = (float)random / 100.0f;
	random = rand() % 2;
	if (random == 1) {
		random *= -1;
	}
	RollY = Roll;
	random = rand() % 100;
	Roll = (float)random / 100.0f;
	random = rand() % 2;
	if (random == 1) {
		random *= -1;
	}
	RollZ = Roll;

	return true;
}

void Rock::Update() {

	m_position += MoveSpeed;
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);

	CQuaternion qAddRot;
	qAddRot.SetRotationDeg(CVector3::AxisX, RollX);
	qAddRot.SetRotationDeg(CVector3::AxisY, RollY);
	qAddRot.SetRotationDeg(CVector3::AxisZ, RollZ);
	m_rotation *= qAddRot;
	m_skinModelRender->SetRotation(m_rotation);

	if (Timer == DeleteTimer) {
		DeleteGO(this);
	}

	Timer++;

}

void Rock::DeleteNow() {
	DeleteGO(this);
}
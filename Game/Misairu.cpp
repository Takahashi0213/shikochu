#include "stdafx.h"
#include "Misairu.h"
#include "Player.h"
#include "EffectManager.h"

Misairu::Misairu()
{
}


Misairu::~Misairu()
{
	DeleteGO(m_skinModelRender);
}

bool Misairu::Start() {

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Misairu.cmo");

	m_scale = { 100.0f,100.0f,100.0f };
	m_rotation.SetRotationDeg(CVector3::AxisY, -180.0f);

	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);

	return true;
}

void Misairu::Update() {

	//移動して攻撃して死ぬ

	switch (m_stete) {
	case Estete_Move://移動

		//ムーブスピード分動く
		m_position += moveSpeed;

		//もし移動時間リミットなら
		if (Timer >= MoveLimit) {
			m_stete = Estete_Attack; //攻撃！
			Timer = 0; //タイマーを0にする
		}

		break;
	case Estete_Attack://攻撃
		if (Timer >= 10 && Timer < 120) {//少し待ってから移動開始
			Player* player = FindGO<Player>("Bug");
			int state = player->GetState();
			if (state != Player::Estate_Death) {
				CVector3 P_Position = player->Getm_Position();
				CVector3 diff = P_Position - m_position;
				atmove = diff;
				atmove.Normalize();

				CVector3 enemyForward = { 0.0f, 0.0f, 1.0f };

				//　向かせたい方向のベクトルを計算する。
				CVector3 targetVector = P_Position - m_position;
				targetVector.Normalize();
				CQuaternion qRot;
				qRot.SetRotation(enemyForward, targetVector);
				m_rotation = qRot;
			}
		}

		m_position += atmove * AttackMoveSpeed;

		//もし攻撃時間リミットなら
		if (Timer >= AttackLimit) {
			m_stete = Estete_Death; //攻撃！
			Timer = 0; //タイマーを0にする
		}

		break;
	case Estete_Death://死ﾇ

		//Effect再生
		EffectManager * effectmanager = EffectManager::GetInstance();
		effectmanager->EffectPlayer(EffectManager::Bakuhatu, m_position, { 30.0f,30.0f,30.0f });

		DeleteGO(this);

		break;
	}

	//移動
	m_skinModelRender->SetPosition(m_position);
	//回転
	m_skinModelRender->SetRotation(m_rotation);
	//拡大率
	m_skinModelRender->SetScale(m_scale);
	//タイマー加算
	Timer++;

}
#include "stdafx.h"
#include "Neoriku.h"
#include "GameData.h"
#include "Player.h"
#include "Bullet.h"


Neoriku::Neoriku()
{
}


Neoriku::~Neoriku()
{
	DeleteGO(m_skinModelRender);
}

bool Neoriku::Start() {
	//アニメーションクリップをロードとループフラグ。
	m_animClips[enAnimationClip_walk].Load(L"animData/Neowalk.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);

	//m_animClips[enAnimationClip_attack1].SetLoopFlag(true);
	//スキンモデル
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/neoriku_0.cmo", m_animClips, enAnimationClip_Num);
	m_skinModelRender->SetForwardRenderFlag(true);
	//m_skinModelRender->SetEmissionColor({ 0.0f, 10.0f, 0.0f });
	m_position = { 100.0f,0.0f,0.0f };
	m_skinModelRender->SetPosition(m_position);

	m_scale = { 2.0f,2.0f,2.0f };
	m_charaCon.Init(
		35.0f,  //キャラクターの半径。
		10.0f,  //キャラクターの高さ。
		m_position //キャラクターの初期座標。
	);


	return true;
}

void Neoriku::NeoAttack() {
	//遠距離やでで
	if (count == 1) {
		NewGO<Bullet>(0, "bullet");
		count = 0;
	}
	else {
		m_stete = Estete_Move;
	}
}

void Neoriku::NeoMove() {
	//移動中
	Player * player = Player::GetInstance();
	CVector3 P_Position = player->Getm_Position();
	CVector3 diff = P_Position - m_position;
	neoVec = diff;
	//dbg::DrawVector(
	//	P_Position,
	//	m_position);
	if (diff.Length() < 400) {
		//停止＆攻撃距離
		moveVec = neoVec * Speed;
		//m_stete = Estete_yobi;
	}
	else {
		//追いかけるよ!
		neoVec.Normalize();
		moveVec = neoVec * followSpeed;
	}
	//プレイヤーの向きに回転
	CVector3 enemyForward = { -1.0f, 0.0f, 0.0f };
	diff.y = 0.0f;
	diff.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, diff);
	m_rotation = qRot;
	m_position = m_charaCon.Execute(moveVec);

}
void Neoriku::NeoDeath() {
	//死んだ......ｳｯ...
	m_position = { 1000.0f,1000.0f,-1000.0f };
	//移動
	m_skinModelRender->SetPosition(m_position);

}
void Neoriku::Neoyobi() {
	//予備動作
	/*if ( count == 0) {
		m_stete = Estete_Attack;
		count++;
	}*/
}

void Neoriku::Update() {
	switch (m_stete) {
		case Estete_Attack://攻撃
			NeoAttack();
			break;
		case Estete_Move://移動
			NeoMove();
			break;
		case Estete_Death:
			NeoDeath();//死
			break;
		case Estete_yobi:
			Neoyobi();//予備動作
			break;
	}
	//移動
	m_skinModelRender->SetPosition(m_position);
	//回転
	m_skinModelRender->SetRotation(m_rotation);
	//拡大率
	m_skinModelRender->SetScale(m_scale);

}



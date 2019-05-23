#include "stdafx.h"
#include "Player.h"
#include "soukabuto.h"


soukabuto::soukabuto()
{
}


soukabuto::~soukabuto()
{
	DeleteGO(m_skinModelRender);
}

bool soukabuto::Start() {
	m_animClips[enAnimationClip_move].Load(L"animData/Neruwalk.tka");
	m_animClips[enAnimationClip_move].SetLoopFlag(true);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/soukabuto_0.cmo");

	m_charaCon.Init(
		45.0f,  //キャラクターの半径。
		10.0f,  //キャラクターの高さ。
		m_position //キャラクターの初期座標。
	);

	return true;
}
void soukabuto::Soumove(){

	timer++;
	if(timer == randomCount){
		random = rand() % 360;//ランダムで方向を決定
		m_rotation.SetRotation(CVector3::AxisY, (float)random);
		CVector3 sou_mae = { -1.0f, 0.0f,0.0f };
		m_rotation.Multiply(sou_mae);
		moveVec = sou_mae * randomSpeed;
		movecount++;
		timer = 0;
	}
	else if (movecount >3) {
		//攻撃するよよ
		Player * player = Player::GetInstance();
		CVector3 P_Position = player->Getm_Position();
		diff = P_Position - m_position;
		attackVec = diff;
		attackVec.Normalize();

		timecount = 0;
		m_stete = Estete_Attack;
	}
	m_position = m_charaCon.Execute(moveVec);
}
void soukabuto::Souattack() {
	timecount++;
		if (timecount < waittimer) {
			//バックするよ
			moveVec = attackVec * back;

		}
		else if (timecount > waittimer) {
			//突進中
			moveVec += attackVec * rush;

		}
		if (timecount > attacktime) {
			//ランダム移動に戻る
			moveVec = attackVec * 0.0f;
			timer = 0;
			movecount = 0;
			m_stete = Estete_Move;
		}

	CVector3 enemyForward = { -1.0f, 0.0f, 0.0f };
	//プレイヤーの向きに回転
	diff.y = 0.0f;
	diff.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, diff);
	m_rotation = qRot;
	m_position = m_charaCon.Execute(moveVec);

}
void soukabuto::Soudeath() {
	DeleteGO(this);
}
void soukabuto::Update() {
	switch (m_stete) {
	case Estete_Move://移動
		Soumove();
		break;
	case Estete_Attack://攻撃1
		Souattack();
		break;
	case Estete_Death://死ﾇ
		Soudeath();
		break;
	}

	//移動
	m_skinModelRender->SetPosition(m_position);
	//回転
	m_skinModelRender->SetRotation(m_rotation);
	//拡大率
	m_skinModelRender->SetScale(m_scale);

}

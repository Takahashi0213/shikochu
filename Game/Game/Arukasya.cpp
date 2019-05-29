#include "stdafx.h"
#include "Player.h"
#include "Arukasya.h"


Arukasya::Arukasya()
{
}


Arukasya::~Arukasya()
{
}
bool Arukasya::Start() {

	//アニメーションクリップをロードとループフラグ。
	m_animClips[enAnimationClip_walk].Load(L"animData/Aruwalk.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	//予備
	m_animClips[enAnimationClip_back].Load(L"animData/Aruback.tka");

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Arukasya.cmo");
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotation);
	m_skinModelRender->SetScale(m_scale);

	m_charaCon.Init(
		45.0f,  //キャラクターの半径。
		10.0f,  //キャラクターの高さ。
		m_position //キャラクターの初期座標。
	);
	return true;
}

void Arukasya::AruAttack() {
	/*if (timecount > waittimer) {
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

	*/
}

void Arukasya::AruMove() {
	Player * player = Player::GetInstance();
	//通常状態
	CVector3 P_Position = player->Getm_Position();
	CVector3 diff = P_Position - m_position;

	count++;

	if (count == randomCount) {
		random = rand() % 360;//ランダムで方向を決定
		m_rotation.SetRotation(CVector3::AxisY, (float)random);
		CVector3 musi_mae = { 1.0f, 0.0f,0.0f };
		m_rotation.Multiply(musi_mae);
		moveVec = musi_mae * randomSpeed;
		count = 0;
		Attackcount++;
	}

	if (Attackcount > followRange) {
		//一定数以上で予備動作に移る。
		m_stete = Estete_Yobi;
	}
	if (m_stete == Estete_Move) {
		//steteがmoveのときは歩きアニメーション
		m_skinModelRender->PlayAnimation(enAnimationClip_walk);

	}

}

void Arukasya::AruYobi() {
	/*timer++;
	if (timer < waittimer) {
		//バックするよ
		moveVec = attackVec * back;
	}
	CVector3 enemyForward = { -1.0f, 0.0f, 0.0f };
	//プレイヤーの向きに回転
	diff.y = 0.0f;
	diff.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, diff);
	m_rotation = qRot;
	m_position = m_charaCon.Execute(moveVec);
	*/
}
void Arukasya::AruDeath() {
	DeleteGO(this);
}

void Arukasya::Update() {
	switch (m_stete)
	{
	case Estete_Attack:
		AruAttack();
		break;
	case Estete_Move:
		AruMove();
		break;
	case Estete_Yobi:
		AruYobi();
		break;
	case Estete_Death:
		AruDeath();
		break;
	}

	//移動
	m_skinModelRender->SetPosition(m_position);
	//回転
	m_skinModelRender->SetRotation(m_rotation);
	//拡大率
	m_skinModelRender->SetScale(m_scale);

}
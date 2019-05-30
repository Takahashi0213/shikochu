#include "stdafx.h"
#include "Fairo.h"
#include "Player.h"
#include "GameData.h"
#include "EffectManager.h"


Fairo::Fairo()
{
}


Fairo::~Fairo()
{
	DeleteGO(m_skinModelRender);
}

bool Fairo::Start() {
	//アニメーション
	m_animClips[enAnimationClip_walk].Load(L"animData/Faiwalk.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	m_animClips[enAnimationClip_dash].Load(L"animData/Faidash.tka");
	m_animClips[enAnimationClip_dash].SetLoopFlag(true);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Fairo.cmo", m_animClips, enAnimationClip_Num);
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
void Fairo::Faimove() {
	timer++;
	if (timer == randomCount) {
		random = rand() % 360;//ランダムで方向を決定
		m_rotation.SetRotation(CVector3::AxisY, (float)random);
		CVector3 sou_mae = { 0.0f, 0.0f,1.0f };
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
	if (m_stete == Estete_Move) {
		//steteがmoveのときは歩きアニメーション
		m_skinModelRender->PlayAnimation(enAnimationClip_walk);

	}

	m_position = m_charaCon.Execute(moveVec);

}
void Fairo::Faiattack() {
	timecount++;
	if (timecount < waittimer) {
		//バックするよ
		moveVec = attackVec * back;

	}
	else if (timecount > waittimer) {
		//突進中
		moveVec += attackVec * rush;
		m_skinModelRender->PlayAnimation(enAnimationClip_dash);
	}
	if (timecount > attacktime) {
		//ランダム移動に戻る
		moveVec = attackVec * 0.0f;
		timer = 0;
		movecount = 0;
		m_stete = Estete_Move;
	}

	CVector3 enemyForward = { 0.0f, 0.0f, 1.0f };
	//プレイヤーの向きに回転
	diff.y = 0.0f;
	diff.Normalize();
	CQuaternion qRot;
	qRot.SetRotation(enemyForward, diff);
	m_rotation = qRot;
	m_position = m_charaCon.Execute(moveVec);

}
void Fairo::Faideath() {
	prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
	ss->Init(L"sound/E_death.wav");
	ss->SetVolume(0.5f);
	ss->Play(false);

	EffectManager * effectmanager = EffectManager::GetInstance();
	CVector3 EF_Position = m_position;
	EF_Position.y += 50.0f;
	effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });

	GameData * gamedata = GameData::GetInstance();
	gamedata->EnemyCounterGensyou();
	DeleteGO(this);

}


void Fairo::Update() {
	
	switch (m_stete) {
	case Estete_Move://移動
		Faimove();
		break;
	case Estete_Attack://攻撃
		Faiattack();
		break;
	case Estete_Death://死ﾇ
		Faideath();
		break;
	}

	//移動
	m_skinModelRender->SetPosition(m_position);
	//回転
	m_skinModelRender->SetRotation(m_rotation);
	//拡大率
	m_skinModelRender->SetScale(m_scale);
	
}
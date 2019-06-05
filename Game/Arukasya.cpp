#include "stdafx.h"
#include "Player.h"
#include "Arukasya.h"
#include "EffectManager.h"
#include "GameData.h"

Arukasya::Arukasya()
{
}


Arukasya::~Arukasya()
{
	DeleteGO(m_skinModelRender);
}
bool Arukasya::Start() {

	//アニメーションクリップをロードとループフラグ。
	m_animClips[enAnimationClip_walk].Load(L"animData/Aruwalk.tka");
	m_animClips[enAnimationClip_walk].SetLoopFlag(true);
	//予備
	m_animClips[enAnimationClip_back].Load(L"animData/Aruback.tka");
	m_animClips[enAnimationClip_back].SetLoopFlag(true);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Arukasya.cmo", m_animClips, enAnimationClip_Num);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);

	m_charaCon.Init(
		45.0f,  //キャラクターの半径。
		10.0f,  //キャラクターの高さ。
		m_position //キャラクターの初期座標。
	);

	return true;
}

void Arukasya::AruMove() {

	timer++;
	if (timer == randomcount) {
		random = rand() % 360;//ランダムで方向を決定
		m_rotation.SetRotation(CVector3::AxisY, (float)random);
		CVector3 Aru_mae = { 0.0f, 0.0f,1.0f };
		m_rotation.Multiply(Aru_mae);
		moveVec = Aru_mae * randomSpeed;
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

		attime = 0;
		m_stete = Estete_Attack;
	}
	
	m_position = m_charaCon.Execute(moveVec);

}
void Arukasya::AruAttack() {
	attime++;
	if (attime < waittimer) {
		//バックするよ
		moveVec = attackVec * back;

	}
	else if (attime > waittimer && attime < backtime) {
		//突進中
		moveVec += attackVec * rush;

	}
	else if (attime > backtime) {
		//後退しちゃうよ
		moveVec += attackVec * backk;

	}
	if (attime > endtime) {
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


void Arukasya::AruDeath() {
	prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
	ss->Init(L"sound/E_death.wav");
	ss->SetVolume(1.0f);
	ss->Play(false);

	EffectManager * effectmanager = EffectManager::GetInstance();
	CVector3 EF_Position = m_position;
	EF_Position.y += 50.0f;
	effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f });

	GameData * gamedata = GameData::GetInstance();
	gamedata->EnemyCounterGensyou();
	DeleteGO(this);

}

void Arukasya::Update() {

	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();
	if (mode != GameData::Pause) {

		switch (m_stete)
		{
		case Estete_Attack:
			AruAttack();
			break;
		case Estete_Move:
			AruMove();
			break;
		case Estete_Death:
			AruDeath();
			break;
		case Estete_Death2:
			AruDeath2();
			break;
		}
	}
	//移動
	m_skinModelRender->SetPosition(m_position);
	//回転
	m_skinModelRender->SetRotation(m_rotation);
	//拡大率
	m_skinModelRender->SetScale(m_scale);
	
}

void Arukasya::AruDeath2() {
	DeleteGO(this);
}
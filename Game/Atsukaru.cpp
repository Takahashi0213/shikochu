#include "stdafx.h"
#include "Atsukaru.h"
#include "Player.h"
#include "GameData.h"
#include "EffectManager.h"
#include "StarComet_Inseki.h"

Atsukaru::Atsukaru()
{
}


Atsukaru::~Atsukaru()
{
	DeleteGO(m_skinModelRender);
}

bool Atsukaru::Start() {
	m_animClips[enAnimationClip_move].Load(L"animData/Atsukaru.tka");
	m_animClips[enAnimationClip_move].SetLoopFlag(true);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Atsukaru.cmo", m_animClips, enAnimationClip_Num);

	m_scale = { 3.0f,3.0f,3.0f };

	m_charaCon.Init(
		45.0f,  //キャラクターの半径。
		10.0f,  //キャラクターの高さ。
		m_position //キャラクターの初期座標。
	);

	return true;
}

void Atsukaru::Soumove() {

	timer++;
	if (timer == WaitLimit) {
		//攻撃するよよ
		Player * player = Player::GetInstance();
		CVector3 P_Position = player->Getm_Position();
		diff = P_Position - m_position;
		attackVec = diff;
		attackVec.Normalize();

		timer = 0;
		timecount = 0;
		m_stete = Estete_Attack;
	}
}

void Atsukaru::Souattack() {
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

void Atsukaru::Soudeath() {

	prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
	ss->Init(L"sound/E_death.wav");
	ss->SetVolume(1.0f);
	ss->Play(false);

	EffectManager * effectmanager = EffectManager::GetInstance();
	CVector3 EF_Position = m_position;
	EF_Position.y += 50.0f;
	effectmanager->EffectPlayer(EffectManager::enemySpawn, EF_Position, { 50.0f,50.0f,50.0f }, false, false);

	GameData * gamedata = GameData::GetInstance();
	gamedata->EnemyCounterGensyou();
	gamedata->PlusGekihaEnemy();

	DeleteGO(this);
}

void Atsukaru::Update() {

	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();
	if (mode != GameData::Pause) {

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
		case Estete_Death2://死ﾇ
			Soudeath2();
			break;

		}
	}

	//どうも隕石です
	QueryGOs<StarComet_Inseki>("StarComet_Inseki", [&](StarComet_Inseki* SCI) {
		CVector3 inseki_position = SCI->Getm_Position();
		CVector3 diff = inseki_position - m_position;
		float Langth_hoge = SCI->GetDamageLength();
		if (diff.Length() < Langth_hoge) { //隕石衝突
			SetDeath();//自分が死ぬ
			SCI->SetDeath();//隕石も死ぬ
		}
		return true;
		});

	//移動
	m_skinModelRender->SetPosition(m_position);
	//回転
	m_skinModelRender->SetRotation(m_rotation);
	//拡大率
	m_skinModelRender->SetScale(m_scale);

}

void Atsukaru::Soudeath2() {
	DeleteGO(this);
}
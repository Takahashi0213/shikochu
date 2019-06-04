#include "stdafx.h"
#include "SS_001.h"
#include "Misairu.h"
#include "EffectManager.h"
#include "GameData.h"
#include "BossHPGage.h"

SS_001::SS_001()
{
}


SS_001::~SS_001()
{
	DeleteGO(m_skinModelRender);
}

bool SS_001::Start() {

	//アニメーション
	m_animClips[enAnimationClip_move].Load(L"animData/SSwalk.tka");
	m_animClips[enAnimationClip_move].SetLoopFlag(true);
	m_animClips[enAnimationClip_wait].Load(L"animData/SSwait.tka");
	m_animClips[enAnimationClip_wait].SetLoopFlag(true);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/SS_001.cmo", m_animClips, enAnimationClip_Num);
	//m_skinModelRender->SetForwardRenderFlag(true);
	m_rotation.SetRotationDeg(CVector3::AxisY, -180.0f);


	m_scale = { 10.0f,10.0f,10.0f };
	//m_position = { 0.0f,1000.0f,5000.0f };

	m_skinModelRender->SetPosition(m_position);

	DefPos = m_position;

	//m_charaCon.Init(
	//	350.0f,  //キャラクターの半径。
	//	100.0f,  //キャラクターの高さ。
	//	m_position //キャラクターの初期座標。
	//);

	return true;
}

void SS_001::Update() {

	switch (m_stete) {
	case Estete_Move://移動
		SSMove();
		break;
	case Estete_Yobi1://予備動作1
		SSYobi1();
		break;
	case Estete_Attack1://攻撃1
		SSAttack1();
		break;
	case Estete_Yobi2://予備動作2
		SSYobi2();
		break;
	case Estete_Attack2://攻撃2
		SSAttack2();
		break;
	case Estete_Death://死ﾇ
		SSDeath();
		break;
	case Estete_Death2://死ﾇ
		SSDeath2();
		break;
	}

	//HPが0なら死ぬ
	if (NowHP == 0) {
		m_stete = Estete_Death;
	}

	//移動
	m_skinModelRender->SetPosition(m_position);
	//回転
	m_skinModelRender->SetRotation(m_rotation);
	//拡大率
	m_skinModelRender->SetScale(m_scale);

}

void SS_001::SSMove() {

	//制限時間になったとき実行
	if (AttackTimer == AttackLimit) {
		int random = rand() % 2;
		if (random == 0) {//攻撃します
			random = rand() % 2;
			//random = 1; //テスト用
			if (random == 0) {
				m_stete = Estete_Yobi1; //ミサイル
			}
			else {
				m_stete = Estete_Yobi2; //ビーム
			}
		}
		AttackTimer = 0;
	}

	AttackTimer++;
}

void SS_001::SSYobi1() {
	m_skinModelRender->PlayAnimation(enAnimationClip_wait, 0.5f);

	m_stete = Estete_Attack1; //ミサイルへ移行
}

void SS_001::SSAttack1() {

	if (MisairuTimer == 0) {
		int random = rand() % 4;
		if (random == 0) {
			MisairuMove = { 20.0f,20.0f,0.0f };
		}
		else if (random == 1) {
			MisairuMove = { -20.0f,20.0f,0.0f };
		}
		else if (random == 2) {
			MisairuMove = { 20.0f,0.0f,0.0f };
		}
		else if (random == 3) {
			MisairuMove = { -20.0f,0.0f,0.0f };
		}
		//ミサイルを撃つ回数はHPで設定する
		if (NowHP < MAXHP / 4) {
			MisairuCountMAX = 10;
		}
		else if ( NowHP < MAXHP / 2) {
			MisairuCountMAX = 8;
		}
		else {
			MisairuCountMAX = 6;
		}

		ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/missile.wav");
		ss->SetVolume(0.5f);
		ss->SetFrequencyRatio(2.0f);
		ss->Play(false);

		//ミサイル生成		
		NewGO<Misairu>(0, "Misairu");
	}

	//移動速度セット
	QueryGOs<Misairu>("Misairu", [&](Misairu* misairu) {
		if (misairu->GetFlag() == true) { //もし設定済みならスルーする～
			return true;
		}
		//設定の時間だ
		misairu->SetPosition(m_position);
		misairu->SetMoveSpeed(MisairuMove);
		misairu->SettingFlag();

		return true;
		});

	//自分の移動
	if (MisairuTimer < MisairuLimit / 4) {
		MyMove = CVector3::Zero;
		m_position -= MisairuMove * 2;
	}
	else {
		if (MyMove.x == 0.0f) {
			MyMove = DefPos - m_position;
			MyMove = MyMove / (((float)MisairuLimit / 4.0f) * 3.0f);
		}
		m_position += MyMove;
	}

	if (MisairuTimer == MisairuLimit) {
		MisairuTimer = -1;
		MisairuCounter++;
		if (MisairuCounter >= MisairuCountMAX) {
			//攻撃終了
			m_skinModelRender->PlayAnimation(enAnimationClip_move, 0.5f);
			MisairuCounter = 0;
			m_stete = Estete_Move;
		}
	}

	MisairuTimer++;

}

void SS_001::SSYobi2() {

	if (BeamYobiTimer == 0) {
		m_skinModelRender->PlayAnimation(enAnimationClip_wait, 0.5f);
		ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/beamcharge.wav");
		ss->SetVolume(0.8f);
		ss->SetFrequencyRatio(2.0f);
		ss->Play(false);

		//Effect再生
		EffectManager * effectmanager = EffectManager::GetInstance();
		effectmanager->EffectPlayer(EffectManager::Beam, { m_position.x,m_position.y,m_position.z - 2000.0f }, { 500.0f,500.0f,500.0f });
	}

	if (BeamYobiTimer >= BeamYobiLimit) {
		BeamYobiTimer = -1;
		m_stete = Estete_Attack2; //ビームへ移行
	}

	BeamYobiTimer++;

}

void SS_001::SSAttack2() {

	if (BeamTimer == 0) {
		ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/beam.wav");
		ss->SetVolume(0.5f);
		ss->Play(false);

		//Effect再生
		EffectManager * effectmanager = EffectManager::GetInstance();
		effectmanager->EffectPlayer(EffectManager::BeamHassya, { m_position.x,m_position.y,m_position.z - 2000.0f }, { 1000.0f,1000.0f,1000.0f });
	}

	if (BeamTimer < 40) {
		m_position.z += 10.0f;
	}

	if (BeamTimer > BeamLimit - 40) {
		m_position.z -= 10.0f;
	}

	if (BeamTimer >= BeamLimit) {
		//攻撃終了
		m_skinModelRender->PlayAnimation(enAnimationClip_move, 0.5f);
		BeamTimer = -1;
		m_stete = Estete_Move;
	}

	BeamTimer++;
}

void SS_001::SSDeath() {

	//ﾔﾗﾚﾀ･･･
	if (DeathTimer == 0) {
		//状態をリザルトに！
		GameData * gamedata = GameData::GetInstance();
		BossHPGage * bossHPGage = BossHPGage::GetInstance();
		gamedata->SetGameMode(GameData::Result);
		bossHPGage->DeleteGage();
	}

	if (DeathTimer == 12) {
		//Effect再生
		EffectManager * effectmanager = EffectManager::GetInstance();
		effectmanager->EffectPlayer(EffectManager::Bakuhatu, m_position, { 500.0f,500.0f,500.0f });
	}
	if (DeathTimer == 70) {
		//Effect再生
		EffectManager * effectmanager = EffectManager::GetInstance();
		effectmanager->EffectPlayer(EffectManager::Bakuhatu, m_position, { 500.0f,500.0f,500.0f });
	}
	if (DeathTimer == 160) {
		//Effect再生
		EffectManager * effectmanager = EffectManager::GetInstance();
		effectmanager->EffectPlayer(EffectManager::Bakuhatu, m_position, { 500.0f,500.0f,500.0f });
	}
	if (DeathTimer == 230) {
		//Effect再生
		EffectManager * effectmanager = EffectManager::GetInstance();
		effectmanager->EffectPlayer(EffectManager::Bakuhatu, { m_position.x + 500.0f,m_position.y, m_position.z - 2000.0f }, { 1000.0f,1000.0f,1000.0f });
	}


	if (ToumeiTimeMAX == DeathTimer) {
		prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/Boss_death.wav");
		ss->SetVolume(0.5f);
		ss->SetFrequencyRatio(0.5f);
		ss->Play(false);

		m_scale = CVector3::Zero;
	}

	if (DeathTimeMAX == DeathTimer) {
		GameData * gamedata = GameData::GetInstance();
		gamedata->EnemyCounterGensyou();
		DeleteGO(this);
	}

	DeathTimer++;

}

void SS_001::SSDeath2() {

	DeleteGO(this);
}


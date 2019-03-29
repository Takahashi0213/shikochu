#include "stdafx.h"
#include "Player.h"
#include "tkEngine/character/tkCharacterController.h"
#include "GameData.h"

Player::Player()
{
}

Player::~Player()
{
	DeleteGO(m_skinModelRender);
}

bool Player::Start() {

	//キャラクターコントローラーを初期化。
	m_charaCon.Init(30, 100, position);

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0,"Bug");
	m_skinModelRender->Init(L"modelData/bug.cmo", nullptr, 0);

	//ゲームデータから最大寿命を引っ張ってくる
	GameData * gamedata = FindGO<GameData>("GameData");
	m_Life = gamedata->GetDEF_Life();

	return true;
}

void Player::Update() {

	switch (player_state) {

	case Estate_Stay://待機
		//移動
		if (Pad(0).IsPress(enButtonUp)) {
			m_moveSpeed.z += moveCrossKey;
		}
		if (Pad(0).IsPress(enButtonDown)) {
			m_moveSpeed.z -= moveCrossKey;
		}
		if (Pad(0).IsPress(enButtonRight)) {
			m_moveSpeed.x += moveCrossKey;
		}
		if (Pad(0).IsPress(enButtonLeft)) {
			m_moveSpeed.x -= moveCrossKey;
		}

		CVector3 stick = CVector3::Zero;
		stick.x = Pad(0).GetLStickXF();
		stick.y = 0.0f;
		stick.z = Pad(0).GetLStickYF();
		m_moveSpeed += stick * playerMoveSpeed;
		//スティック入力されてなければ緩やかストップ
		if (stick.x == 0.0f) {
			m_moveSpeed.x /= 1.2f;
		}
		if (stick.z == 0.0f) {
			m_moveSpeed.z /= 1.2f;
		}
		//移動速度上限
		if (m_moveSpeed.x > moveSpeedMAX) {
			m_moveSpeed.x = moveSpeedMAX;
		}
		else if (m_moveSpeed.x < -moveSpeedMAX) {
			m_moveSpeed.x = -moveSpeedMAX;

		}
		if (m_moveSpeed.z > moveSpeedMAX) {
			m_moveSpeed.z = moveSpeedMAX;
		}
		else if (m_moveSpeed.z < -moveSpeedMAX) {
			m_moveSpeed.z = -moveSpeedMAX;

		}

		//ダッシュ機能
		if (Pad(0).IsTrigger(enButtonA)) {

			CVector3 Dash_Speed = m_moveSpeed;
			Dash_Speed.Normalize();
			Dash_Speed *= 1000.0f;
			m_moveSpeed += Dash_Speed;

			m_Life -= 5;
			if (m_Life < 0) {
				m_Life = 0; //0より小さくしない
			}
		}
		break;
	//case Estate_Dash://ダッシュ
	//	break;
	//case Estate_Death://死んでいる
	//	break;
	}

	//寿命減少
	m_LifeCounter++;
	if (m_LifeCounter > m_LifeSpeed) {
		m_LifeCounter = 0;
		m_Life -= 1;
		if (m_Life < 0) {
			m_Life = 0; //0より小さくしない
		}
	}

	position = m_charaCon.Execute(m_moveSpeed);

	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		//わからん
	}
	float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
	rotation.SetRotation(CVector3::AxisY, angle);

	//敵との距離を計算
	Enemy * enemy = FindGO<Enemy>("Enemy");
	CVector3 enemy_position = enemy->Getm_Position();
	CVector3 diff = enemy_position - position;
	playerVec = diff;

	if (diff.Length() < 80.0f) {
		m_Life = 0;//敵にぶつかった
		int EState = enemy->GetEState();
		if (EState != 0) {//敵が攻撃中の時でない
			enemy->SetDeath();
		}
	}

	//寿命だ…
	if (m_Life == 0) {
		//ここで死ぬ
		PlayerReset();
	}

	//反映
	m_skinModelRender->SetPosition(position);
	m_skinModelRender->SetRotation(rotation);
	m_skinModelRender->SetScale(m_scale);

}

void Player::PlayerReset() {

	if (ResetTimer == 0) {
		player_state = Estate_Death;
		m_scale = CVector3::Zero;
		m_skinModelRender->SetScale(m_scale);

	}
	if (ResetTimer == 120) {
		//ゲームデータから最大寿命を引っ張ってくる
		GameData * gamedata = FindGO<GameData>("GameData");
		m_Life = gamedata->GetDEF_Life();
		ResetTimer = -1;
		gamedata->SetZanki(-1);
		player_state = Estate_Stay;
		//元に戻す
		position = { 0.0f,0.0f,0.0f };
		rotation = CQuaternion::Identity;
		m_scale = CVector3::One;
		m_moveSpeed = CVector3::Zero;
		m_skinModelRender->SetPosition(position);
		m_skinModelRender->SetRotation(rotation);
		m_skinModelRender->SetScale(m_scale);
	}
	ResetTimer++;

}
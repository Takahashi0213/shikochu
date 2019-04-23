#include "stdafx.h"
#include "Player.h"
#include "tkEngine/character/tkCharacterController.h"
#include "GameData.h"

Player* Player::m_instance = nullptr;

Player::Player()
{
	if (m_instance != nullptr) {
		std::abort(); //すでにプレイヤーが出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

}

Player::~Player()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(m_pointLig);

	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

bool Player::Start() {

	//キャラクターコントローラーを初期化。
	m_charaCon.Init(30, 100, position);

	//ライトの数値を初期化
	LightReset();

	//出現
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0,"Bug");
	m_skinModelRender->Init(L"modelData/bug.cmo", nullptr, 0);
	m_skinModelRender->SetEmissionColor(PlayerEmission);

	//ゲームデータから最大寿命を引っ張ってくる
	GameData * gamedata = GameData::GetInstance();
	m_Life = gamedata->GetDEF_Life();

	m_pointLig = NewGO<prefab::CPointLight>(0, "StarLight");
	m_pointLig->SetColor(PlayerLight);
	m_pointLig->SetAttn(PlayerLightAttn);

	return true;
}

void Player::Update() {

	//現在モード
	GameData * gameData = FindGO<GameData>("GameData");
	int mode = gameData->GetGameMode();

	if (mode == 0) {

		switch (player_state) {

		case Estate_Stay://待機
		{
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

			//流星ダッシュ
			if (Pad(0).IsTrigger(enButtonY)) {
				GameData * gamedata = GameData::GetInstance();
				//ゲージの色々を取得する
				int Now_Star_Power = gamedata->GetStar_Power();
				int MAX_Star_Power = gamedata->GetMAXStar_Power();
				//ゲージがMAXなら
				if (Now_Star_Power == MAX_Star_Power) {
					//ダッシュ状態になるぞ！！！！！！
					m_LifeSpeed = 1;
					player_state = Estate_Dash;
				}
			}
		}
		break;
		case Estate_Dash://ダッシュ

			CVector3 Dash_Speed = m_moveSpeed;
			Dash_Speed.Normalize();
			Dash_Speed *= dashSpeed2D;
			m_moveSpeed += Dash_Speed;
			//流星ゲージが減る
			GameData * gamedata = GameData::GetInstance();
			gamedata->Star_PowerChange(-DashLifeSpeed);
			//もし流星ゲージが0なら死ぬ
			int NowStarPower = gamedata->GetStar_Power();
			if (NowStarPower == 0) {
				m_Life = 0;
			}
		
		break;
		//case Estate_Death://死んでいる

		//break;
		}

		//寿命減少
		m_LifeCounter++;
		if (m_LifeCounter > m_LifeSpeed) {
			m_LifeCounter = 0;
			m_Life -= m_Life_Decrease;
			if (player_state == Estate_Dash) {
				if (m_Life < DashLife) {
					m_Life = DashLife; //DashLifeより小さくしない
				}
			}
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

		PlayerJudge();

	}
	else if (mode == 1) {

		switch (player_state) {

		case Estate_Stay://待機
		{
			//移動
			if (Pad(0).IsPress(enButtonUp)) {
				m_moveSpeed.y += moveCrossKey;
			}
			if (Pad(0).IsPress(enButtonDown)) {
				m_moveSpeed.y -= moveCrossKey;
			}
			if (Pad(0).IsPress(enButtonRight)) {
				m_moveSpeed.x += moveCrossKey;
			}
			if (Pad(0).IsPress(enButtonLeft)) {
				m_moveSpeed.x -= moveCrossKey;
			}

			CVector3 stick = CVector3::Zero;
			stick.x = Pad(0).GetLStickXF();
			stick.y = Pad(0).GetLStickYF();
			stick.z = 0.0f;
			m_moveSpeed += stick * playerMoveSpeed;
			//スティック入力されてなければ緩やかストップ
			if (stick.x == 0.0f) {
				m_moveSpeed.x /= 1.2f;
			}
			if (stick.y == 0.0f) {
				m_moveSpeed.y /= 1.2f;
			}
			//移動速度上限
			if (m_moveSpeed.x > moveSpeedMAX) {
				m_moveSpeed.x = moveSpeedMAX;
			}
			else if (m_moveSpeed.x < -moveSpeedMAX) {
				m_moveSpeed.x = -moveSpeedMAX;

			}
			if (m_moveSpeed.y > moveSpeedMAX) {
				m_moveSpeed.y = moveSpeedMAX;
			}
			else if (m_moveSpeed.y < -moveSpeedMAX) {
				m_moveSpeed.y = -moveSpeedMAX;

			}

			//加速減速
			if (Pad(0).IsTrigger(enButtonA)) {
				//加速状態に
				Dash_state3D = Estate_Front;
			}
			else if (Pad(0).IsTrigger(enButtonB)) {
				//減速状態に
				Dash_state3D = Estate_Back;
			}
			else {
				//通常状態に
				Dash_state3D = Estate_DEF;
			}

			//流星ダッシュ
			if (Pad(0).IsTrigger(enButtonY)) {
				GameData * gamedata = GameData::GetInstance();
				//ゲージの色々を取得する
				int Now_Star_Power = gamedata->GetStar_Power();
				int MAX_Star_Power = gamedata->GetMAXStar_Power();
				//ゲージがMAXなら
				if (Now_Star_Power == MAX_Star_Power) {
					//ダッシュ状態になるぞ！！！！！！
					m_LifeSpeed = 1;
					player_state = Estate_Dash;
				}
			}
		}
		//自動前進
		switch (Dash_state3D) {
		case Estate_DEF:
			m_moveSpeed.z = Advance3D;
			break;
		case Estate_Front:
			m_moveSpeed.z = Advance3D + Advance3D_PM;
			break;
		case Estate_Back:
			m_moveSpeed.z = Advance3D - Advance3D_PM;
			break;
		}
			break;
		case Estate_Dash://ダッシュ

			m_moveSpeed.z = dashSpeed3D; //全速前進！
			//流星ゲージが減る
			GameData * gamedata = GameData::GetInstance();
			gamedata->Star_PowerChange(-DashLifeSpeed);
			//もし流星ゲージが0なら死ぬ
			int NowStarPower = gamedata->GetStar_Power();
			if (NowStarPower == 0) {
				m_Life = 0;
			}

			break;
			//case Estate_Death://死んでいる
			//	break;
		}

		//寿命減少
		m_LifeCounter++;
		if (m_LifeCounter > m_LifeSpeed) {
			m_LifeCounter = 0;
			m_Life -= m_Life_Decrease;
			if (player_state == Estate_Dash) {
				if (m_Life < DashLife) {
					m_Life = DashLife; //DashLifeより小さくしない
				}
			}
			if (m_Life < 0) {
				m_Life = 0; //0より小さくしない
			}
		}

		position = m_charaCon.Execute(m_moveSpeed);

		PlayerJudge();

	}

	//死んでいなければ光る
	if (player_state != Estate_Death) {

		//発光具合を寿命に応じて調整する
		int LightLoop = (int)GetLifePercent(1);
		int LoopX = 0;
		float LightX = LightXDEF;//上昇値
		float AttnX = AttnXDEF;
		LightReset();
		for (; LightLoop > 0; LightLoop--) {
			PlayerLight.x = PlayerLight.x + LightX;
			PlayerLight.y = PlayerLight.y + LightX;
			PlayerLight.z = PlayerLight.z + LightX;
			PlayerLightAttn.x = PlayerLightAttn.x + AttnX;

			LoopX++;

			LightX = LightXDEF;//上昇値
			AttnX = AttnXDEF;
			LightX += (float)(LoopX * LoopX / LightSpeed);
			AttnX += (float)(LoopX * LoopX / AttnSpeed);

		}

	}

	//無敵時間中なら実行
	if (MutekiTimer >= 0) {
		MutekiSupporter();
	}

	//ライト
	m_pointLig->SetPosition(position);
	m_pointLig->SetColor(PlayerLight);
	m_pointLig->SetAttn(PlayerLightAttn);
	//反映
	m_skinModelRender->SetPosition(position);
	m_skinModelRender->SetRotation(rotation);
	m_skinModelRender->SetScale(m_scale);

}

void Player::PlayerJudge(){

	//敵との距離を計算
	Enemy * enemy = FindGO<Enemy>("Enemy");
	CVector3 enemy_position = enemy->Getm_Position();
	CVector3 diff = enemy_position - position;
	playerVec = diff;

	//死んでいなければ接触判定
	if (player_state != Estate_Dash) {
		if (diff.Length() < 80.0f) {
			//もし無敵時間中でないなら
			if (MutekiTimer == -1) {
				m_Life = 0;//敵にぶつかった
				int EState = enemy->GetEState();
				if (EState != 0) {//敵が攻撃中の時でない
					enemy->SetDeath();
			}
			}
		}
	}

	//寿命だ…
	if (m_Life == 0) {
		//ダッシュ中なら流星ゲージを0にする
		if (player_state == Estate_Dash) {
			GameData * gamedata = GameData::GetInstance();
			gamedata->StarPowerZero();
		}
		//ここで死ぬ
		PlayerReset();
	}
}

void Player::PlayerReset() {

	if (ResetTimer == 0) {

		//しんでしまった！
		player_state = Estate_Death;
		
		//移動停止
		m_moveSpeed = CVector3::Zero;

		//無敵時間の準備！
		MutekiTimer = 0;

	}
	
	//死んで発光する時間
	if (ResetTimer <= DeathLightTime/2){
		//死の発光
		PlayerEmission *= DeathLight;
		PlayerLight *= DeathLight;
	}
	else if (ResetTimer < DeathLightTime) {
		//死の発光減少
		PlayerEmission *= DeathLight_Syusoku;
		PlayerLight *= DeathLight_Syusoku;
	}
	else if (ResetTimer == DeathLightTime) {

		//ライト戻す
		LightReset();

		//m_scaleをゼロにして死んだように見せかける
		m_scale = CVector3::Zero;
		m_skinModelRender->SetScale(m_scale);

	}
	//
	//インターバル終了
	//
	if (ResetTimer == ResetAverage) {
		//ゲームデータから最大寿命を引っ張ってくる
		GameData * gamedata = GameData::GetInstance();
		m_Life = gamedata->GetDEF_Life();
		ResetTimer = -1;
		gamedata->SetZanki(-1);//残機減少
		//状態を戻す
		player_state = Estate_Stay;
		//寿命減少速度も戻す
		LifeSpeedReset();
		//あれもこれも戻す
		position = { 0.0f,0.0f,0.0f };
		rotation = CQuaternion::Identity;
		m_scale = CVector3::One;
		//はい。
		m_skinModelRender->SetPosition(position);
		m_skinModelRender->SetRotation(rotation);
		m_skinModelRender->SetScale(m_scale);
	}

	ResetTimer++;

}

float Player::GetLifePercent(int x){//x=0で割合を、x=1で減少値を返す

	//ゲームデータから最大寿命を引っ張ってくる
	GameData * gamedata = GameData::GetInstance();
	int DEF_Life = gamedata->GetDEF_Life();

	if (x == 0) {
		float player_percent = (float)m_Life / DEF_Life;
		return player_percent;
	}
	else if (x == 1) {
		int player_Gensyou = DEF_Life - m_Life;
		return (float)player_Gensyou;
	}

}

void Player::MutekiSupporter() {

	//タイマー加算
	MutekiTimer++;

	//ここで点滅処理


	//時間切れ
	if (MutekiTimer >= MutekiAverage) {
		MutekiTimer = -1; //無敵を戻す
	}
}
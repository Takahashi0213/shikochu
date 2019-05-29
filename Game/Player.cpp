#include "stdafx.h"
#include "Player.h"
#include "tkEngine/character/tkCharacterController.h"
#include "GameData.h"
#include "EffectManager.h"
#include "Bullet.h"
#include "Radar.h"
//Enemy
#include "Neoriku.h"
#include "Neruk.h"
#include "shisokus.h"
#include "soukabuto.h"
#include "Nerubikkuri.h"
#include "Bunbogu.h"
#include "Ekku.h"
#include "Pi_rabi.h"
#include "Fairo.h"
#include "Pairodorago.h"
#include "Morikon.h"
#include "Riritto.h"
#include "Arukasya.h"
#include "SS_001.h"

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
	if (LaderFlag == false) {
		DeleteGOs("Radar");
	}

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

	NewGO<Radar>(0, "Radar");

	return true;
}

void Player::Update() {

	//現在モード
	GameData * gameData = GameData::GetInstance();
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
			m_moveSpeed *= 0.98f;
			/*if (stick.x == 0.0f) {
				m_moveSpeed.x /= 1.2f;
			}
			if (stick.z == 0.0f) {
				m_moveSpeed.z /= 1.2f;
			}*/
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

				prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
				//SE再生
				ss->Init(L"sound/dash.wav");
				ss->SetVolume(1.0f);
				ss->Play(false);

				CVector3 Dash_Speed = m_moveSpeed;
				Dash_Speed.Normalize();
				Dash_Speed *= A_DashSpeed;
				m_moveSpeed += Dash_Speed;

				//ダッシュフラグセット
				DashFlag = true;
				if (DashTimeCount == -1) {
					DashTimeCount = 0;
				}

				m_Life -= Dash_LifeGensyo;
				if (m_Life < 0) {
					m_Life = 0; //0より小さくしない
				}
			}

			//ダッシュ状態カウント
			if (DashTimeCount >= -1) {
				DashTimeCount++;
				if (DashTimeCount >= DashTimeMAX) { //ダッシュ状態が時間切れなら
					DashTimeCount = -1;
					DashFlag = false;
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
					DashFlag = true;
					DashTimeCount = -2; //解除されないダッシュ状態になる
				}
			}
		}
		break;
		case Estate_Dash://ダッシュ

			EffectManager * effectmanager = EffectManager::GetInstance();
			effectmanager->EffectPlayer(EffectManager::star, position, SpawnEffectScale/2);
			effectmanager->EffectPlayer(EffectManager::star, position, SpawnEffectScale / 2);
			effectmanager->EffectPlayer(EffectManager::star, position, SpawnEffectScale / 2);
			effectmanager->EffectPlayer(EffectManager::star, position, SpawnEffectScale / 2);

			//移動
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

		//無敵時間中なら実行
		if (MutekiTimer >= 0) {
			//無敵状態は敵を貫通したいので、キャラコンを使わずに動かす。

			CVector3 addPos = m_moveSpeed * GameTime().GetFrameDeltaTime();
			position += addPos;
			//キャラコンも追従させておかないと、無敵時間が終わったときに戻されてしまうので
			//キャラコンに座標を設定しておく。
			m_charaCon.SetPosition(position);
		}
		else {
			position = m_charaCon.Execute(m_moveSpeed);
		}
		if (fabsf(m_moveSpeed.x) < 0.001f
			&& fabsf(m_moveSpeed.z) < 0.001f) {
			//わからん
		}
		float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
		rotation.SetRotation(CVector3::AxisY, angle);

		PlayerJudge();

	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	else if (mode == 1) {

		switch (player_state) {

		case Estate_Stay://待機
		{
			//移動
			if (Pad(0).IsPress(enButtonUp)) {
				m_moveSpeed.y += moveCrossKey * (Advance3D_Move + Advance3D_Move);
			}
			if (Pad(0).IsPress(enButtonDown)) {
				m_moveSpeed.y -= moveCrossKey * (Advance3D_Move + Advance3D_Move);
			}
			if (Pad(0).IsPress(enButtonRight)) {
				m_moveSpeed.x += moveCrossKey * (Advance3D_Move + Advance3D_Move);
			}
			if (Pad(0).IsPress(enButtonLeft)) {
				m_moveSpeed.x -= moveCrossKey * (Advance3D_Move + Advance3D_Move);
			}

			CVector3 stick = CVector3::Zero;
			stick.x = Pad(0).GetLStickXF();
			stick.y = Pad(0).GetLStickYF();
			stick.z = 0.0f;
			m_moveSpeed += stick * (playerMoveSpeed*Advance3D_Move);
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
			if (Pad(0).IsPress(enButtonA)) {
				//加速状態に
				m_Life -= 2;
				DashFlag = true;
				Dash_state3D = Estate_Front;
			}
			else if (Pad(0).IsPress(enButtonB)) {
				//減速状態に
				DashFlag = false;
				Dash_state3D = Estate_Back;
			}
			else {
				//通常状態に
				DashFlag = false;
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
					m_LifeSpeed = 2;
					DashFlag = true;
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
			m_moveSpeed.z = Advance3D + Advance3D_PM * Advance3D_FrontHosei;
			break;
		case Estate_Back:
			m_moveSpeed.z = Advance3D - Advance3D_PM;
			break;
		}
			break;
		case Estate_Dash://ダッシュ

			EffectManager * effectmanager = EffectManager::GetInstance();
			CVector3 ef_position = position;
			ef_position.z += 200.0f;
			effectmanager->EffectPlayer(EffectManager::star, ef_position, SpawnEffectScale / 2);
			effectmanager->EffectPlayer(EffectManager::star, ef_position, SpawnEffectScale / 2);
			effectmanager->EffectPlayer(EffectManager::star, ef_position, SpawnEffectScale / 2);
			effectmanager->EffectPlayer(EffectManager::star, ef_position, SpawnEffectScale / 2);

			m_moveSpeed.z = Advance3D + Advance3D_PM * (Advance3D_FrontHosei*dashSpeed3D); //全速前進！
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

		//無敵時間中なら実行
		if (MutekiTimer >= 0) {
			//無敵状態は敵を貫通したいので、キャラコンを使わずに動かす。
			CVector3 addPos = m_moveSpeed * GameTime().GetFrameDeltaTime();
			position += addPos;
			//キャラコンも追従させておかないと、無敵時間が終わったときに戻されてしまうので
			//キャラコンに座標を設定しておく。
			m_charaCon.SetPosition(position);
		}
		else {
			position = m_charaCon.Execute(m_moveSpeed);
		}

		//地面に埋まらないようにする
		if (position.y < PosY_Min3D) {
			position.y = PosY_Min3D;
		}

		PlayerJudge();

	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	else if (mode == 2) {

		PlayerJudge();

		}
	else if (mode == 3) {

		//なんもせんで
		SetActiveFlag(false);
		//m_scaleをゼロにして死んだように見せかける
		m_scale = CVector3::Zero;
		position = { 10000.0f,10000.0f,0.0f };

	}
	//死んでいなければ光る
	if (player_state != Estate_Death) {

		//発光具合を寿命に応じて調整する
		GameData * gamedata = GameData::GetInstance();
		int LightLoop = (int)gamedata->GetLifePercent(1);
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

	//モードに応じてライト処理を変えます
	if (mode == 0 || mode == 3) {
		CVector3 pos = position;
		pos.y += LightPosHosei;
		m_pointLig->SetPosition(pos);
		m_pointLig->SetColor(PlayerLight * LightHosei);
		m_pointLig->SetAttn(PlayerLightAttn);
		m_skinModelRender->SetEmissionColor(EmissionColorDEF);
		GraphicsEngine().GetTonemap().SetLuminance(0.56f);
	}
	else if (mode == 1) {
		CVector3 pos = position;
		pos.z += LightPosHoseiZ;
		m_pointLig->SetPosition(pos);
		m_pointLig->SetColor(PlayerLight * LightHosei);
		m_pointLig->SetAttn(PlayerLightAttn);
		m_skinModelRender->SetEmissionColor(EmissionColorDEF);
		GraphicsEngine().GetTonemap().SetLuminance(0.28f);
	}
	/////////////////////////////////////////////
	if (mode == 3) {//リザルト中は絶対死なない！
		//ゲームデータから最大寿命を引っ張ってくる
		GameData * gamedata = GameData::GetInstance();
		m_Life = gamedata->GetDEF_Life();
	}
	/////////////////////////////////////////////

	//これもライト
	if (player_state != Estate_Death) {
		LightStatusSupporter(); //死んでないときだけね
	}
	//反映
	m_skinModelRender->SetPosition(position);
	m_skinModelRender->SetRotation(rotation);
	m_skinModelRender->SetScale(m_scale);

}

//判定を色々
void Player::PlayerJudge() {

	//ブンボーグとの距離を計算
	QueryGOs<Bunbogu>("bun", [&](Bunbogu* bunbogu) {
		if (bunbogu->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 enemy_position = bunbogu->Getm_Position();
		CVector3 diff = enemy_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = bunbogu->GetDamageLength();
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					m_Life = 0;

					int EState = bunbogu->GetEState();
					if (EState != 0 && DashFlag == true || player_state==Estate_Dash) {//敵が攻撃中の時でない＆ダッシュ状態なら…

						bunbogu->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::spawn, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}
				}
			}
		}
		return true;
		});

	//玉との距離を計算
	QueryGOs<Bullet>("bullet", [&](Bullet* bullet) {
		CVector3 bullet_position = bullet->Getm_Position();
		CVector3 diff = bullet_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = bullet->GetDamageLength();
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1 || player_state != Estate_Dash) {

					//寿命をゼロに
					m_Life = 0;

					bullet->SetDeath();//お前も死ね

				}
			}
		}
		return true;
		});

	//ネオリクとの距離を計算
	QueryGOs<Neoriku>("neo", [&](Neoriku* neoriku) {
		if (neoriku->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 neoriku_position = neoriku->Getm_Position();
		CVector3 diff = neoriku_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = neoriku->GetDamageLength();
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					m_Life = 0;

					if (DashFlag == true) {//ダッシュ状態なら…

						neoriku->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::spawn, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//シーソークスとの距離を計算
	QueryGOs<shisokus>("shiso", [&](shisokus* Shisok) {
		if (Shisok->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 Shisok_position = Shisok->Getm_Position();
		CVector3 diff = Shisok_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = Shisok->GetDamageLength();
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ダメージを前もって計算
					GameData * gamedata = GameData::GetInstance();
					bool dash;
					if (player_state == Estate_Dash) {
						dash = true;
					}
					else {
						dash = false;
					}
					int Damage = (int)gamedata->DamageKeisan(dash);

					//寿命をゼロに
					m_Life = 0;

					int EState = Shisok->GetEState();
					if (EState != 1 && DashFlag == true || player_state == Estate_Dash) {//敵が攻撃中の時でない＆ダッシュ状態なら…

						prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
						ss->Init(L"sound/damage.wav");
						ss->SetVolume(0.5f);
						ss->Play(false);

						//オラァ！
						Shisok->Damage(Damage);

					}


				}
			}
		}
		return true;
		});

	//ネルクとの距離を計算
	QueryGOs<Neruk>("neru", [&](Neruk* neruk) {
		if (neruk->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 neruk_position = neruk->Getm_Position();
		CVector3 diff = neruk_position - position;

		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = neruk->GetDamageLength();
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1 || player_state != Estate_Dash) {

					//寿命をゼロに
					m_Life = 0;

					neruk->SetDeath();//お前も死ね

				}
				if (player_state == Estate_Dash) {
					neruk->SetDeath();//お前も死ね
				}
			}
		}
		return true;
		});

	//ソウカブトとの距離を計算
	QueryGOs<soukabuto>("sou", [&](soukabuto* souka) {
		if (souka->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 souka_position = souka->Getm_Position();
		CVector3 diff = souka_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = souka->GetDamageLength();
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					m_Life = 0;

					if (DashFlag == true) {//ダッシュ状態なら…

						souka->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::spawn, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//エックとの距離を計算
	QueryGOs<Ekku>("Ekku", [&](Ekku* ekku) {
		if (ekku->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 souka_position = ekku->Getm_Position();
		CVector3 diff = souka_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = ekku->GetDamageLength();
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					m_Life = 0;

					if (DashFlag == true) {//ダッシュ状態なら…

						ekku->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::spawn, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//ピーラビとの距離を計算
	QueryGOs<Pi_rabi>("Pi_rabi", [&](Pi_rabi* pi_rabi) {
		if (pi_rabi->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 souka_position = pi_rabi->Getm_Position();
		CVector3 diff = souka_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = pi_rabi->GetDamageLength();
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					m_Life = 0;

					if (DashFlag == true) {//ダッシュ状態なら…

						pi_rabi->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::spawn, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//ファイロとの距離を計算
	QueryGOs<Fairo>("Fairo", [&](Fairo* fairo) {
		if (fairo->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 souka_position = fairo->Getm_Position();
		CVector3 diff = souka_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = fairo->GetDamageLength();
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					m_Life = 0;

					if (DashFlag == true) {//ダッシュ状態なら…

						fairo->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::spawn, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//パイロドラゴとの距離を計算
	QueryGOs<Pairodorago>("Pairodorago", [&](Pairodorago* pairodorago) {
		if (pairodorago->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 Shisok_position = pairodorago->Getm_Position();
		CVector3 diff = Shisok_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = pairodorago->GetDamageLength();
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ダメージを前もって計算
					GameData * gamedata = GameData::GetInstance();
					bool dash;
					if (player_state == Estate_Dash) {
						dash = true;
					}
					else {
						dash = false;
					}
					int Damage = (int)gamedata->DamageKeisan(dash);

					//寿命をゼロに
					m_Life = 0;

					int EState = pairodorago->GetEState();
					if (EState != 1 && DashFlag == true || player_state == Estate_Dash) {//敵が攻撃中の時でない＆ダッシュ状態なら…

						prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
						ss->Init(L"sound/damage.wav");
						ss->SetVolume(0.5f);
						ss->Play(false);

						//オラァ！
						pairodorago->Damage(Damage);

					}


				}
			}
		}
		return true;
		});

	//モリコンとの距離を計算
	QueryGOs<Morikon>("Morikon", [&](Morikon* morikon) {
		if (morikon->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 souka_position = morikon->Getm_Position();
		CVector3 diff = souka_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = morikon->GetDamageLength();
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					m_Life = 0;

					if (DashFlag == true) {//ダッシュ状態なら…

						morikon->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::spawn, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//リリットとの距離を計算
	QueryGOs<Riritto>("Riritto", [&](Riritto* riritto) {
		if (riritto->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 souka_position = riritto->Getm_Position();
		CVector3 diff = souka_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = riritto->GetDamageLength();
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					m_Life = 0;

					if (DashFlag == true) {//ダッシュ状態なら…

						riritto->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::spawn, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//アルカシャとの距離を計算
	QueryGOs<Arukasya>("Arukasya", [&](Arukasya* arukasya) {
		if (arukasya->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 souka_position = arukasya->Getm_Position();
		CVector3 diff = souka_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = arukasya->GetDamageLength();
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					m_Life = 0;

					if (DashFlag == true) {//ダッシュ状態なら…

						arukasya->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::spawn, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//SS-001との距離を計算
	QueryGOs<SS_001>("SS_001", [&](SS_001* ss_001) {
		if (ss_001->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 souka_position = ss_001->Getm_Position();
		CVector3 diff = souka_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = ss_001->GetDamageLength();
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					m_Life = 0;

					if (DashFlag == true) {//ダッシュ状態なら…

						ss_001->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::spawn, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

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

	GameData * gamedata = GameData::GetInstance();

	if (ResetTimer == 0) {

		prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
		//SE再生
		ss->Init(L"sound/P_death.wav");
		ss->SetVolume(0.5f);
		ss->Play(false);

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

	//もし残機が１ならおしまいですよ
	int zanki = gamedata->GetZanki();
	if (zanki == 1 && ResetTimer == DeathLightTime) {
		gamedata->SetZanki(-1);//残機減少
		gamedata->SetGameMode(GameData::GameOver);
		MutekiTimer = -1;
		m_skinModelRender->SetActiveFlag(false);
		DeleteGOs("Radar");
		LaderFlag = true;
	}
	else if (zanki == 0) {
		ResetTimer = 0;
	}

	//
	//インターバル終了
	//
	if (ResetTimer == ResetAverage) {
		//ゲームデータから最大寿命を引っ張ってくる
		m_Life = gamedata->GetDEF_Life();
		int mode = gamedata->GetGameMode();
			//あ～～～～～～
			ResetTimer = -1;
			gamedata->SetZanki(-1);//残機減少
			 //状態を戻す
			player_state = Estate_Stay;
			//寿命減少速度も戻す
			LifeSpeedReset();
			//あれもこれも戻す
			position = CVector3::Zero;
			m_charaCon.SetPosition(position); //キャラコンも戻すぞ
			rotation = CQuaternion::Identity;
			m_scale = CVector3::One;
			LightStatus = LightStatusDEF;
			//はい。
			m_skinModelRender->SetPosition(position);
			m_skinModelRender->SetRotation(rotation);
			m_skinModelRender->SetScale(m_scale);
			//移動が終わったのでエフェクトを再生（移動後にやらないと死んだ場所で再生されてしまうので）
			EffectManager * effectmanager = EffectManager::GetInstance();
			if (mode == 0) {
				effectmanager->EffectPlayer(EffectManager::spawn, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale);
			}
			else if (mode == 1) {
				effectmanager->EffectPlayer(EffectManager::spawn, { position.x,position.y,position.z + SpawnEffectY }, SpawnEffectScale);
			}

		//臨時モードチェンジ
		//gamedata->SwapGameMode();

	}

	ResetTimer++;

}

void Player::MutekiSupporter() {

	//現在モード
	GameData * gameData = GameData::GetInstance();
	int mode = gameData->GetGameMode();

	//タイマー加算
	MutekiTimer++;

	if (MutekiTimer >= ResetAverage && mode != 2) {
		//ここで点滅処理
		static int TenmetuTimer = 0;
		if (TenmetuTimer % 2 == 0) {
			//偶数
			m_skinModelRender->SetActiveFlag(true);
		}
		else {
			//奇数
			m_skinModelRender->SetActiveFlag(false);
		}
		TenmetuTimer++;
	}

	//時間切れ
	if (MutekiTimer >= MutekiAverage) {
		MutekiTimer = -1; //無敵を戻す
		m_skinModelRender->SetActiveFlag(true);
	}
}

void Player::LightStatusSupporter() {

	//呼び出し
	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();
	float RightHosei = 1.0f - gamedata->ZankiWariai(); //逆だ…
	float range = minRange * (1.0f - RightHosei) + maxRange * RightHosei;

	//LightStatusの値を設定
	float LightX = gamedata->GetLifePercent(0);
	LightX = 1.0f - LightX; //これで割合がわかります！！！！
	LightStatus = LightStatusMAX * LightX;
	range += LightStatus;

	//ふははは
	if (mode == 1) {
		LightStatus *= LightHosei3D;
	}

	//セット(^_-)-☆
	SetSpecialLigRange(range);

}
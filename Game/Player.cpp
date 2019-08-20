#include "stdafx.h"
#include "Player.h"
#include "tkEngine/character/tkCharacterController.h"
#include "GameData.h"
#include "EffectManager.h"
#include "Bullet.h"
#include "Bullet2.h"
#include "Bullet3.h"
#include "Bullet4.h"
#include "Bullet5.h"
#include "Bullet6.h"
#include "Radar.h"
#include "NakamaLight.h"
#include "SaveData.h"
#include "SkillData.h"
#include "StarComet.h"

//Enemy
#include "Neoriku.h"
#include "Neruk.h"
#include "shisokus.h"
#include "soukabuto.h"
#include "Nerubikkuri.h"
#include "Bunbogu.h"
#include "Benite.h"
#include "Nibo.h"
#include "Sekuteimu.h"
#include "Ekku.h"
#include "Pi_rabi.h"
#include "Fairo.h"
#include "Pairodorago.h"
#include "Morikon.h"
#include "Riritto.h"
#include "Arukasya.h"
#include "SS_001.h"
#include "Misairu.h"
#include "Kikochu.h"
#include "Uminoushi.h"
#include "Akoyadokari.h"
#include "Morinchu.h"
#include "Kirabi.h"
#include "Suteira.h"
#include "Idando.h"
#include "Kodan.h"
#include "Taidol.h"
#include "Suroku.h"
#include "Mimitto.h"
#include "Tizutyo.h"
#include "Kuubo.h"
#include "Toripipi.h"
#include "Teruosuka.h"
#include "Atsukaru.h"
#include "Metoporisu.h"

//ギミック
#include "AppleBomb.h"
#include "Train1.h"
#include "Train2.h"

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
	//DeleteGOs("NakamaLight");
	DeleteGOs("StarComet");

	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

bool Player::Start() {

	SoundEngine().SetListenerFront({0.0f, 0.0f, 1.0f});
	SoundEngine().SetListenerUp({ 0.0f, 1.0f, 0.0f });

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

	SaveData * savedata = SaveData::GetInstance();
	if (savedata->GetSkill(false) == 18) { //カミカゼバトル
		m_LifeSpeed = m_LifeSpeedDEF / 2;
	}
	else {
		m_LifeSpeed = m_LifeSpeedDEF;
	}

	NewGO<Radar>(0, "Radar");
	NewGO<StarComet>(0, "StarComet");
	//NewGO<NakamaLight>(0, "NakamaLight");

	return true;
}

void Player::Update() {

	//現在モード
	GameData * gameData = GameData::GetInstance();
	SaveData * savedata = SaveData::GetInstance();
	int mode = gameData->GetGameMode();

	if (mode == 0) {

		switch (player_state) {

		case Estate_Stay://待機
		{
			//移動
			float Hosei = 0.0f;
			if (NowSkillNo == 8) { //ナガレボシ中なら補正を設定する
				Hosei += Nagareboshi;
			}
			if (savedata->GetSkill(false) == 18) { //カミカゼバトル
				Hosei += Kamikaze;
			}
			if (savedata->GetSkill(false) == 19) { //アクム
				Hosei += Akumu;
			}

			if (Pad(0).IsPress(enButtonUp)) {
				m_moveSpeed.z += (moveCrossKey + Hosei);
			}
			if (Pad(0).IsPress(enButtonDown)) {
				m_moveSpeed.z -= (moveCrossKey + Hosei);
			}
			if (Pad(0).IsPress(enButtonRight)) {
				m_moveSpeed.x += (moveCrossKey + Hosei);
			}
			if (Pad(0).IsPress(enButtonLeft)) {
				m_moveSpeed.x -= (moveCrossKey + Hosei);
			}

			CVector3 stick = CVector3::Zero;
			stick.x = Pad(0).GetLStickXF();
			stick.y = 0.0f;
			stick.z = Pad(0).GetLStickYF();

			m_moveSpeed += stick * (playerMoveSpeed + Hosei);

			m_moveSpeed *= 0.98f;

			//スティック入力されてなければ緩やかストップ
			if (NowSkillNo == 8) {
				//移動速度上限
				if (m_moveSpeed.Length() > moveSpeedMAX * 2.0f) {
					m_moveSpeed.Normalize();
					m_moveSpeed *= (moveSpeedMAX * 2.0f);
				}
			}
			else {
				//移動速度上限
				if (m_moveSpeed.Length() > moveSpeedMAX) {
					m_moveSpeed.Normalize();
					m_moveSpeed *= moveSpeedMAX;
				}
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

				CVector3 E_Pos = position;
				E_Pos.y += SpawnEffectY;
				EffectManager * effectmanager = EffectManager::GetInstance();
				effectmanager->EffectPlayer(EffectManager::Dash, E_Pos, DashEffectScale, true);
				effectmanager->EffectPlayer(EffectManager::Dash2, E_Pos, DashEffectScale, true, true);

				//ダッシュフラグセット
				DashFlag = true;
				A_DashFlag = true;
				if (DashTimeCount == -1) {
					DashTimeCount = 0;
				}

				if (savedata->GetSkill(false) == 15 || savedata->GetSkill(true) == 15) { //セツヤク
					m_Life -= Dash_LifeGensyo / 2;
				}
				else {
					m_Life -= Dash_LifeGensyo;
				}

				if (savedata->GetSkill(false) == 16 || savedata->GetSkill(true) == 16) { //イノチカンゲン
					if (NowSkillNo == -1) {
						gameData->Star_PowerChange(1);
					}
				}

				if (m_Life < 0) {
					m_Life = 0; //0より小さくしない
				}
				if (NowSkillNo == 7 && m_Life < 1) {
					m_Life = 1; //1より小さくしない
				}

			}

			//ダッシュ状態カウント
			if (DashTimeCount > -1) {
				DashTimeCount++;

				if (DashTimeCount >= DashTimeMAX) { //ダッシュ状態が時間切れなら
					DashTimeCount = -1;
					DashFlag = false;
					A_DashFlag = false;
				}
			}

			//スキル
			if (Pad(0).IsTrigger(enButtonY)) {
				//コメットキャノン中なら発射する
				if (NowSkillNo == 10) {
					StarComet * starComet = StarComet::GetInstance();
					starComet->Comet_Hassya(m_moveSpeed, position);
					gameData->Star_PowerChange(-10);
					SkillTimer += 10;
				}

				GameData * gamedata = GameData::GetInstance();
				//色々を取得する
				int Now_Star_Power = gamedata->GetStar_Power();
				int SkillNo = savedata->GetSkill(false);
				int SkillCost = Skill_Data[SkillNo].StarPower;
				//int MAX_Star_Power = gamedata->GetMAXStar_Power();
				if (SkillCost > 0 && Now_Star_Power >= SkillCost && NowSkillNo == -1) { //発動型かつスターゲージが足りているなら発動
					SkillYobidashi(SkillNo);
				}
				else {
					//ちがうならブリップ
					prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
					ss->Init(L"sound/blip.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);
				}
			}
			//スキル
			if (Pad(0).IsTrigger(enButtonX)) {
				//コメットキャノン中なら発射する
				if (NowSkillNo == 10) {
					StarComet * starComet = StarComet::GetInstance();
					starComet->Comet_Hassya(m_moveSpeed, position);
					gameData->Star_PowerChange(-10);
					SkillTimer += 10;
				}

				GameData * gamedata = GameData::GetInstance();
				//色々を取得する
				int Now_Star_Power = gamedata->GetStar_Power();
				int SkillNo = savedata->GetSkill(true);
				int SkillCost = Skill_Data[SkillNo].StarPower;
				//int MAX_Star_Power = gamedata->GetMAXStar_Power();
				if (SkillCost > 0 && Now_Star_Power >= SkillCost && NowSkillNo == -1) { //発動型かつスターゲージが足りているなら発動
					SkillYobidashi(SkillNo);
				}
				else {
					//ちがうならブリップ
					prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
					ss->Init(L"sound/blip.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);
				}
			}

		}break;
		case Estate_Dash://ダッシュ
		{
			EffectManager * effectmanager = EffectManager::GetInstance();
			effectmanager->EffectPlayer(EffectManager::star, position, SpawnEffectScale / 2);
			effectmanager->EffectPlayer(EffectManager::star, position, SpawnEffectScale / 2);
			effectmanager->EffectPlayer(EffectManager::star, position, SpawnEffectScale / 2);
			effectmanager->EffectPlayer(EffectManager::star, position, SpawnEffectScale / 2);
			effectmanager->EffectPlayer(EffectManager::StarDash, position, DashEffectScale, true, true);
			effectmanager->EffectPlayer(EffectManager::Dash2, position, DashEffectScale, true, true);

			//移動
			CVector3 Dash_Speed = m_moveSpeed;
			Dash_Speed.Normalize();
			Dash_Speed *= dashSpeed2D;
			m_moveSpeed += Dash_Speed;

			//すいせいダッシュなら操作可能
			if (NowSkillNo == 2) {
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
				//移動速度上限
				if (m_moveSpeed.Length() > moveSpeedMAX) {
					m_moveSpeed.Normalize();
					m_moveSpeed *= moveSpeedMAX;
				}
			}

			//流星ゲージが減る
			GameData * gamedata = GameData::GetInstance();
			gamedata->Star_PowerChange(-DashLifeSpeed);
			//もし流星ゲージが0なら死ぬ
			int NowStarPower = gamedata->GetStar_Power();
			if (NowStarPower == 0) {
				effectmanager->EffectPlayer(EffectManager::Bonus, position, SpawnEffectScale);
				m_Life = 0;
			}

		}break;
		//case Estate_Death://死んでいる

		//break;
		case Estate_Frea://ソウルフレア！
		{
			//移動はできないけど減速はします
			m_moveSpeed *= 0.98f;

			SoulFlareTimer++;

			if (SoulFlareTimer == SoulFlareLimit) { //どっかーん
				EffectManager * effectmanager = EffectManager::GetInstance();
				effectmanager->EffectPlayer_Post(EffectManager::Bakuhatu, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale, true);

				DashFlag = true;
				SoulFlareFlag = true;
				MutekiTimer = -1; //無敵解除しないとダメージを与えられないんですわ
				DashTimeCount = -2; //解除されないダッシュ状態になる
			}
			else if (SoulFlareTimer == SoulFlareLimit + 1) { //ソウルフレア終了なのでしにまーす
				DashFlag = false;
				SoulFlareFlag = false;
				SoulFlareTimer = 0;
				m_Life = 0;
			}

		}break;
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
			if (NowSkillNo == 7 && m_Life < 1) {
				m_Life = 1; //1より小さくしない
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
			//return;
		}
		float angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
		rotation.SetRotation(CVector3::AxisY, angle);

		PlayerJudge();
		SkillUpdate();

		//プレイヤーの座標を正規化座標系に変換する。
		CVector2 playerPosInSeikika;
		MainCamera().CalcScreenPositionFromWorldPosition(playerPosInSeikika, position);
		playerPosInSeikika.x /= (float)GraphicsEngine().Get2DSpaceScreenWidth() * 0.5f;
		playerPosInSeikika.y /= (float)GraphicsEngine().Get2DSpaceScreenHeight() * 0.5f;
		GraphicsEngine().GetPostEffect().GetDithering().SetPlayerPosition(playerPosInSeikika);

	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	else if (mode == 1) {

		switch (player_state) {

		case Estate_Stay://待機
		{

			//移動
			float Hosei = 0.0f;
			if (NowSkillNo == 8) { //ナガレボシ中なら補正を設定する
				Hosei += Nagareboshi;
			}
			if (savedata->GetSkill(false) == 18) { //カミカゼバトル
				Hosei += Kamikaze;
			}
			if (savedata->GetSkill(false) == 19) { //アクム
				Hosei += Akumu;
			}

			if (Pad(0).IsPress(enButtonUp)) {
				m_moveSpeed.y += moveCrossKey * (Advance3D_Move + Advance3D_Move + Hosei);
			}
			if (Pad(0).IsPress(enButtonDown)) {
				m_moveSpeed.y -= moveCrossKey * (Advance3D_Move + Advance3D_Move + Hosei);
			}
			if (Pad(0).IsPress(enButtonRight)) {
				m_moveSpeed.x += moveCrossKey * (Advance3D_Move + Advance3D_Move + Hosei);
			}
			if (Pad(0).IsPress(enButtonLeft)) {
				m_moveSpeed.x -= moveCrossKey * (Advance3D_Move + Advance3D_Move + Hosei);
			}

			CVector3 stick = CVector3::Zero;
			stick.x = Pad(0).GetLStickXF();
			stick.y = Pad(0).GetLStickYF();
			stick.z = 0.0f;
			m_moveSpeed += stick * (playerMoveSpeed*Advance3D_Move + Hosei);

			//スティック入力されてなければ緩やかストップ

			m_moveSpeed.x *= 0.98f;
			m_moveSpeed.y *= 0.98f;

			if (NowSkillNo == 8) {
				//移動速度上限
				if (m_moveSpeed.Length() > moveSpeedMAX * 2.0f) {
					m_moveSpeed.Normalize();
					m_moveSpeed *= (moveSpeedMAX * 2.0f);
				}
			}
			else {
				//移動速度上限
				if (m_moveSpeed.Length() > moveSpeedMAX) {
					m_moveSpeed.Normalize();
					m_moveSpeed *= moveSpeedMAX;
				}
			}

			//加速減速
			if (Pad(0).IsPress(enButtonA)) {
				//加速状態に
				m_Life -= 2;
				if (NowSkillNo == 7 && m_Life < 1) {
					m_Life = 1; //1より小さくしない
				}
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

			//スキル
			if (Pad(0).IsTrigger(enButtonY)) {
				//コメットキャノン中なら発射する
				if (NowSkillNo == 10) {
					StarComet * starComet = StarComet::GetInstance();
					starComet->Comet_Hassya({ 0.0f , 0.0f , 0.0f }, position);
					gameData->Star_PowerChange(-10);
					SkillTimer += 10;
				}

				GameData * gamedata = GameData::GetInstance();
				//色々を取得する
				int Now_Star_Power = gamedata->GetStar_Power();
				int SkillNo = savedata->GetSkill(false);
				int SkillCost = Skill_Data[SkillNo].StarPower;
				//int MAX_Star_Power = gamedata->GetMAXStar_Power();
				if (SkillCost > 0 && Now_Star_Power >= SkillCost && NowSkillNo == -1) { //発動型かつスターゲージが足りているなら発動
					SkillYobidashi(SkillNo);
				}
				else {
					//ちがうならブリップ
					prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
					ss->Init(L"sound/blip.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);
				}
			}
			//スキル
			if (Pad(0).IsTrigger(enButtonX)) {
				//コメットキャノン中なら発射する
				if (NowSkillNo == 10) {
					StarComet * starComet = StarComet::GetInstance();
					starComet->Comet_Hassya({ 0.0f , 0.0f , 0.0f }, position);
					gameData->Star_PowerChange(-10);
					SkillTimer += 10;
				}

				GameData * gamedata = GameData::GetInstance();
				//色々を取得する
				int Now_Star_Power = gamedata->GetStar_Power();
				int SkillNo = savedata->GetSkill(true);
				int SkillCost = Skill_Data[SkillNo].StarPower;
				//int MAX_Star_Power = gamedata->GetMAXStar_Power();
				if (SkillCost > 0 && Now_Star_Power >= SkillCost && NowSkillNo == -1) { //発動型かつスターゲージが足りているなら発動
					SkillYobidashi(SkillNo);
				}
				else {
					//ちがうならブリップ
					prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
					ss->Init(L"sound/blip.wav");
					ss->SetVolume(1.0f);
					ss->Play(false);
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
			m_moveSpeed.z = Advance3D - Advance3D_PM - Advance3D_Back;
			break;
		}
			break;
		case Estate_Dash://ダッシュ
		{
			EffectManager * effectmanager = EffectManager::GetInstance();
			CVector3 ef_position = position;
			ef_position.z += 200.0f;
			effectmanager->EffectPlayer(EffectManager::star, ef_position, SpawnEffectScale / 2);
			effectmanager->EffectPlayer(EffectManager::star, ef_position, SpawnEffectScale / 2);
			effectmanager->EffectPlayer(EffectManager::star, ef_position, SpawnEffectScale / 2);
			effectmanager->EffectPlayer(EffectManager::star, ef_position, SpawnEffectScale / 2);

			m_moveSpeed.z = Advance3D + Advance3D_PM * (Advance3D_FrontHosei*dashSpeed3D); //全速前進！

			//すいせいダッシュなら操作可能
			if (NowSkillNo == 2) {
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
			}

			//流星ゲージが減る
			GameData * gamedata = GameData::GetInstance();
			gamedata->Star_PowerChange(-DashLifeSpeed);
			//もし流星ゲージが0なら死ぬ
			int NowStarPower = gamedata->GetStar_Power();
			if (NowStarPower == 0) {
				m_Life = 0;
			}

		}break;
		//case Estate_Death://死んでいる
		//	break;
		case Estate_Frea://ソウルフレア！
		{
			SoulFlareTimer++;

			if (SoulFlareTimer == SoulFlareLimit) { //どっかーん
				EffectManager * effectmanager = EffectManager::GetInstance();
				effectmanager->EffectPlayer_Post(EffectManager::Bakuhatu, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale, true);

				DashFlag = true;
				SoulFlareFlag = true;
				MutekiTimer = -1; //無敵解除しないとダメージを与えられないんですわ
				DashTimeCount = -2; //解除されないダッシュ状態になる
			}
			else if (SoulFlareTimer == SoulFlareLimit + 1) { //ソウルフレア終了なのでしにまーす
				DashFlag = false;
				SoulFlareFlag = false;
				SoulFlareTimer = 0;
				m_Life = 0;
			}

		}break;
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
			if (NowSkillNo == 7 && m_Life < 1) {
				m_Life = 1; //1より小さくしない
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
		SkillUpdate();

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

	//現在モードが0か1ならゲージ上昇
	if (mode == GameData::Battle2D_Mode || mode == GameData::Battle3D_Mode) {
		StarPointTimer++;
		if (StarPointTimer >= StarPointLimit && NowSkillNo== -1 ) { //スキル発動中は増えません
			if (savedata->GetSkill(false) != 20 && savedata->GetSkill(true) != 20) { //キョウフスキル装備中は増えない
				gameData->Star_PowerChange(1);
			}
			StarPointTimer = 0;
		}
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
		if (GameData::GetInstance()->GetStageNo() == 5) {
			GraphicsEngine().GetTonemap().SetLuminance(0.05f);
		}
		else if (GameData::GetInstance()->GetStageNo() == 2) {
			GraphicsEngine().GetTonemap().SetLuminance(0.1f);
		}
		else {
			GraphicsEngine().GetTonemap().SetLuminance(DEFAULT_LUMINANCE);
		}
	}
	else if (mode == 1) {
		CVector3 pos = position;
		pos.z += LightPosHoseiZ;
		m_pointLig->SetPosition(pos);
		m_pointLig->SetColor(PlayerLight * LightHosei);
		m_pointLig->SetAttn(PlayerLightAttn);
		m_skinModelRender->SetEmissionColor(EmissionColorDEF);
		if (GameData::GetInstance()->GetStageNo() == 5) {
			GraphicsEngine().GetTonemap().SetLuminance(0.1f, 0.5f);
		}
		else if (GameData::GetInstance()->GetStageNo() == 2) {
			GraphicsEngine().GetTonemap().SetLuminance(0.1f, 0.5f);
		}
		else {
			GraphicsEngine().GetTonemap().SetLuminance(DEFAULT_LUMINANCE, 0.5f);
		}
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

	SoundEngine().SetListenerPosition(position * 0.01f);

}

//判定を色々
void Player::PlayerJudge() {

	SaveData * savedata = SaveData::GetInstance();

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
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					int EState = bunbogu->GetEState();
					if ((EState != Bunbogu::Estete_Attack && DashFlag == true )|| player_state==Estate_Dash || player_state == Estate_Frea) {//敵が攻撃中の時でない＆ダッシュ状態なら…

						bunbogu->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { enemy_position.x,enemy_position.y + SpawnEffectY,enemy_position.z }, SpawnEffectScale);
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
				if (MutekiTimer == -1 && player_state != Estate_Dash) {

					//寿命をゼロに
					if (player_state != Estate_Dash) {
						if (savedata->GetSkill(false) == 17 || savedata->GetSkill(true) == 17) { //ハガネノカラダ
							m_Life -= 20;
							if (m_Life < 0) {
								m_Life = 0;
							}
						}
						else {
							m_Life = 0;
						}
					}

					bullet->SetDeath();//お前も死ね

				}
			}
		}
		return true;
		});
	QueryGOs<Bullet2>("bullet2", [&](Bullet2* bullet2) {
		CVector3 bullet_position = bullet2->Getm_Position();
		CVector3 diff = bullet_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = bullet2->GetDamageLength();
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1 && player_state != Estate_Dash) {

					//寿命をゼロに
					if (player_state != Estate_Dash) {
						if (savedata->GetSkill(false) == 17 || savedata->GetSkill(true) == 17) { //ハガネノカラダ
							m_Life -= 20;
							if (m_Life < 0) {
								m_Life = 0;
							}
						}
						else {
							m_Life = 0;
						}
					}

					bullet2->SetDeath();//お前も死ね

				}
			}
		}
		return true;
		});
	QueryGOs<Bullet3>("bullet3", [&](Bullet3* bullet3) {
		CVector3 bullet_position = bullet3->Getm_Position();
		CVector3 diff = bullet_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = bullet3->GetDamageLength();
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1 && player_state != Estate_Dash) {

					//寿命をゼロに
					if (player_state != Estate_Dash) {
						if (savedata->GetSkill(false) == 17 || savedata->GetSkill(true) == 17) { //ハガネノカラダ
							m_Life -= 20;
							if (m_Life < 0) {
								m_Life = 0;
							}
						}
						else {
							m_Life = 0;
						}
					}

					bullet3->SetDeath();//お前も死ね

				}
			}
		}
		return true;
		});
	QueryGOs<Bullet4>("bullet4", [&](Bullet4* bullet4) {
		CVector3 bullet_position = bullet4->Getm_Position();
		CVector3 diff = bullet_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = bullet4->GetDamageLength();
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1 && player_state != Estate_Dash) {

					//寿命をゼロに
					if (player_state != Estate_Dash) {
						if (savedata->GetSkill(false) == 17 || savedata->GetSkill(true) == 17) { //ハガネノカラダ
							m_Life -= 20;
							if (m_Life < 0) {
								m_Life = 0;
							}
						}
						else {
							m_Life = 0;
						}
					}

					bullet4->SetDeath();//お前も死ね

				}
			}
		}
		return true;
		});
	QueryGOs<Bullet5>("bullet5", [&](Bullet5* bullet5) {
		CVector3 bullet_position = bullet5->Getm_Position();
		CVector3 diff = bullet_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = bullet5->GetDamageLength();
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1 && player_state != Estate_Dash) {

					//寿命をゼロに
					if (player_state != Estate_Dash) {
						if (savedata->GetSkill(false) == 17 || savedata->GetSkill(true) == 17) { //ハガネノカラダ
							m_Life -= 20;
							if (m_Life < 0) {
								m_Life = 0;
							}
						}
						else {
							m_Life = 0;
						}
					}

					bullet5->SetDeath();//お前も死ね

				}
			}
		}
		return true;
		});
	QueryGOs<Bullet6>("bullet6", [&](Bullet6* bullet6) {
		CVector3 bullet_position = bullet6->Getm_Position();
		CVector3 diff = bullet_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = bullet6->GetDamageLength();
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1 && player_state != Estate_Dash) {

					//寿命をゼロに
					if (player_state != Estate_Dash) {
						if (savedata->GetSkill(false) == 17 || savedata->GetSkill(true) == 17) { //ハガネノカラダ
							m_Life -= 20;
							if (m_Life < 0) {
								m_Life = 0;
							}
						}
						else {
							m_Life = 0;
						}
					}

					bullet6->SetDeath();//お前も死ね

				}
			}
		}
		return true;
		});

	//ミサイルとの距離を計算
	QueryGOs<Misairu>("Misairu", [&](Misairu* misairu) {
		CVector3 bullet_position = misairu->Getm_Position();
		CVector3 diff = bullet_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = misairu->GetDamageLength();
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//寿命をゼロに
					if (player_state != Estate_Dash) {
						if (savedata->GetSkill(false) == 17 || savedata->GetSkill(true) == 17) { //ハガネノカラダ
							m_Life -= 20;
							if (m_Life < 0) {
								m_Life = 0;
							}
						}
						else {
							m_Life = 0;
						}
					}

					misairu->SetDeath();//お前も死ね

				}
			}
		}
		return true;
		});

	//リンゴボムとの距離を計算
	QueryGOs<AppleBomb>("AppleBomb", [&](AppleBomb* appleBomb) {
		if (appleBomb->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 bullet_position = appleBomb->Getm_Position();
		CVector3 diff = bullet_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = appleBomb->GetDamageLength();
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//寿命をゼロに
					if (player_state != Estate_Dash) {
						m_Life = 0;
						GameData * gamedata = GameData::GetInstance();
						gamedata->SetBombFlag();
					}

					appleBomb->SetDeath();//お前も死ね

				}
			}
		}
		return true;
		});

	//電車との距離を計算
	QueryGOs<Train1>("Train1", [&](Train1* train1) {
		if (train1->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 bullet_position = train1->Getm_Position();
		CVector3 diff = bullet_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = train1->GetDamageLength();
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//寿命をゼロに
					if (player_state != Estate_Dash) {
						m_Life = 0;
						GameData * gamedata = GameData::GetInstance();
						gamedata->SetDensyaFlag();
					}

				}
			}
		}
		return true;
		});
	QueryGOs<Train2>("Train2", [&](Train2* train2) {
		if (train2->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 bullet_position = train2->Getm_Position();
		CVector3 diff = bullet_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = train2->GetDamageLength();
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//寿命をゼロに
					if (player_state != Estate_Dash) {
						m_Life = 0;
						GameData * gamedata = GameData::GetInstance();
						gamedata->SetDensyaFlag();
					}

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
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
							m_moveSpeed.x *= -1.0f;
							m_moveSpeed.y *= -1.0f;
							m_moveSpeed.z *= -1.0f;
						}
						else {
							m_Life = 0;
						}
					}

					if (DashFlag == true) {//ダッシュ状態なら…

						neoriku->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { neoriku_position.x,neoriku_position.y + SpawnEffectY,neoriku_position.z }, SpawnEffectScale);
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
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
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
					if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
						m_moveSpeed.x *= -Zonbi_Handou_Boss;
						m_moveSpeed.y *= -Zonbi_Handou_Boss;
						m_moveSpeed.z *= -Zonbi_Handou_Boss;
					}
					else {
						if (player_state != Estate_Frea) {
							m_Life = 0;
						}
					}

					int EState = Shisok->GetEState();
					if (EState != shisokus::Estete_Attack1 && (DashFlag == true || player_state == Estate_Dash || player_state == Estate_Frea)) {//敵が攻撃中の時でない＆ダッシュ状態なら…

						prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
						ss->Init(L"sound/damage.wav");
						ss->SetVolume(0.5f);
						ss->Play(false);

						//オラァ！
						Shisok->Damage(Damage);
						gamedata->PlusBossDamage();

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
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//寿命をゼロに
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

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
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}			
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					if (DashFlag == true) {//ダッシュ状態なら…

						souka->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { souka_position.x,souka_position.y + SpawnEffectY,souka_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//キコウチュウとの距離を計算
	QueryGOs<Kikochu>("Kikochu", [&](Kikochu* kikochu) {
		if (kikochu->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 souka_position = kikochu->Getm_Position();
		CVector3 diff = souka_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = kikochu->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					if (DashFlag == true) {//ダッシュ状態なら…

						kikochu->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { souka_position.x,souka_position.y + SpawnEffectY,souka_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//ウミノウシとの距離を計算
	QueryGOs<Uminoushi>("Uminoushi", [&](Uminoushi* uminoushi) {
		if (uminoushi->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 souka_position = uminoushi->Getm_Position();
		CVector3 diff = souka_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = uminoushi->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					if (DashFlag == true) {//ダッシュ状態なら…

						uminoushi->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { souka_position.x,souka_position.y + SpawnEffectY,souka_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//アコヤドカリとの距離を計算
	QueryGOs<Akoyadokari>("Akoyadokari", [&](Akoyadokari* akoyadokari) {
		if (akoyadokari->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 enemy_position = akoyadokari->Getm_Position();
		CVector3 diff = enemy_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = akoyadokari->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					int EState = akoyadokari->GetEState();
					if (EState != 0 && DashFlag == true || player_state == Estate_Dash || player_state == Estate_Frea) {//敵が攻撃中の時でない＆ダッシュ状態なら…

						akoyadokari->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { enemy_position.x,enemy_position.y + SpawnEffectY,enemy_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}
				}
			}
		}
		return true;
		});

	//ベニテーとの距離を計算
	QueryGOs<Benite>("Benite", [&](Benite* benite) {
		if (benite->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 enemy_position = benite->Getm_Position();
		CVector3 diff = enemy_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = benite->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					int EState = benite->GetEState();
					if (EState != Benite::Estete_Attack && DashFlag == true || player_state == Estate_Dash || player_state == Estate_Frea) {//敵が攻撃中の時でない＆ダッシュ状態なら…

						benite->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { enemy_position.x,enemy_position.y + SpawnEffectY,enemy_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}
				}
			}
		}
		return true;
		});

	//ニーボーとの距離を計算
	QueryGOs<Nibo>("Nibo", [&](Nibo* nibo) {
		if (nibo->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 enemy_position = nibo->Getm_Position();
		CVector3 diff = enemy_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = nibo->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					int EState = nibo->GetEState();
					if ((EState != Benite::Estete_Attack && DashFlag == true) || player_state == Estate_Dash || player_state == Estate_Frea) {//敵が攻撃中の時でない＆ダッシュ状態なら…

						nibo->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { enemy_position.x,enemy_position.y + SpawnEffectY,enemy_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}
				}
			}
		}
		return true;
		});

	//セクティムとの距離を計算
	QueryGOs<Sekuteimu>("Sekuteimu", [&](Sekuteimu* sekuteimu) {
		if (sekuteimu->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 souka_position = sekuteimu->Getm_Position();
		CVector3 diff = souka_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = sekuteimu->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					if (DashFlag == true) {//ダッシュ状態なら…

						sekuteimu->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { souka_position.x,souka_position.y + SpawnEffectY,souka_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//キラビンとの距離を計算
	QueryGOs<Kirabi>("Kirabi", [&](Kirabi* kirabi) {
		if (kirabi->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 enemy_position = kirabi->Getm_Position();
		CVector3 diff = enemy_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = kirabi->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					int EState = kirabi->GetEState();
					if ( (EState != Benite::Estete_Attack && DashFlag == true ) || player_state == Estate_Dash || player_state == Estate_Frea) {//敵が攻撃中の時でない＆ダッシュ状態なら…

						kirabi->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { enemy_position.x,enemy_position.y + SpawnEffectY,enemy_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}
				}
			}
		}
		return true;
		});

	//スティラとの距離を計算
	QueryGOs<Suteira>("Suteira", [&](Suteira* suteira) {
		if (suteira->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 souka_position = suteira->Getm_Position();
		CVector3 diff = souka_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = suteira->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					if (DashFlag == true) {//ダッシュ状態なら…

						suteira->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { souka_position.x,souka_position.y + SpawnEffectY,souka_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//モリンチュとの距離を計算
	QueryGOs<Morinchu>("Morinchu", [&](Morinchu* morinchu) {
		if (morinchu->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 Shisok_position = morinchu->Getm_Position();
		Shisok_position.y += 2000.0f;
		Shisok_position.z += 500.0f;
		CVector3 diff = Shisok_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = morinchu->GetDamageLength();
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
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
					if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
						m_moveSpeed.x *= -Zonbi_Handou_Boss;
						m_moveSpeed.y *= -Zonbi_Handou_Boss;
						m_moveSpeed.z *= -Zonbi_Handou_Boss;
					}
					else {
						if (player_state != Estate_Frea) {
							m_Life = 0;
						}
					}

					int EState = morinchu->GetEState();
					if ((EState != Morinchu::Estete_Attack1 && DashFlag == true )|| player_state == Estate_Dash || player_state == Estate_Frea) {//敵が攻撃中の時でない＆ダッシュ状態なら…

						prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
						ss->Init(L"sound/damage.wav");
						ss->SetVolume(0.5f);
						ss->Play(false);

						//オラァ！
						morinchu->Damage(Damage);
						gamedata->PlusBossDamage();

					}


				}
			}
		}
		return true;
		});

	//チズチョウとの距離を計算
	QueryGOs<Tizutyo>("Tizutyo", [&](Tizutyo* tizutyo) {
		if (tizutyo->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 souka_position = tizutyo->Getm_Position();
		CVector3 diff = souka_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = tizutyo->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					if (DashFlag == true) {//ダッシュ状態なら…

						tizutyo->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { souka_position.x,souka_position.y + SpawnEffectY,souka_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//クーボとの距離を計算
	QueryGOs<Kuubo>("Kuubo", [&](Kuubo* kuubo) {
		if (kuubo->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 enemy_position = kuubo->Getm_Position();
		CVector3 diff = enemy_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = kuubo->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					int EState = kuubo->GetEState();
					if ((EState != Kuubo::Estete_Attack && DashFlag == true) || player_state == Estate_Dash || player_state == Estate_Frea) {//敵が攻撃中の時でない＆ダッシュ状態なら…

						kuubo->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { enemy_position.x,enemy_position.y + SpawnEffectY,enemy_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}
				}
			}
		}
		return true;
		});

	//トリピピとの距離を計算
	QueryGOs<Toripipi>("Toripipi", [&](Toripipi* toripipi) {
		if (toripipi->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 enemy_position = toripipi->Getm_Position();
		CVector3 diff = enemy_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = toripipi->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					if (DashFlag == true) {//ダッシュ状態なら…

						toripipi->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { enemy_position.x,enemy_position.y + SpawnEffectY,enemy_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}
				}
			}
		}
		return true;
		});

	//ティルオスカとの距離を計算
	QueryGOs<Teruosuka>("Teruosuka", [&](Teruosuka* teruosuka) {
		if (teruosuka->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 Shisok_position = teruosuka->Getm_Position();

		if (teruosuka->GetTeruMode() == Teruosuka::Tank) {

		}else if (teruosuka->GetTeruMode() == Teruosuka::Plane) {
			Shisok_position.z -= 1700.0f;
		}
		else if (teruosuka->GetTeruMode() == Teruosuka::Human) {
			Shisok_position.y += 3000.0f;
			Shisok_position.z += 200.0f;
		}

		//Shisok_position.y += 2000.0f;
		//Shisok_position.z += 500.0f;
		CVector3 diff = Shisok_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = teruosuka->GetDamageLength();
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
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

					if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
						m_moveSpeed.x *= -Zonbi_Handou_Boss;
						m_moveSpeed.y *= -Zonbi_Handou_Boss;
						m_moveSpeed.z *= -Zonbi_Handou_Boss;
					}
					else {
						if (player_state != Estate_Frea) {
							m_Life = 0;
						}
					}

					int EState = teruosuka->GetEState();
					if ((EState != Teruosuka::Estete_HumanAttack && DashFlag == true) || player_state == Estate_Dash || player_state == Estate_Frea) {//敵が攻撃中の時でない＆ダッシュ状態なら…

						prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
						ss->Init(L"sound/damage.wav");
						ss->SetVolume(0.5f);
						ss->Play(false);

						//オラァ！
						teruosuka->Damage(Damage);
						gamedata->PlusBossDamage();

					}


				}
			}
		}
		return true;
		});

	//アツカルとの距離を計算
	QueryGOs<Atsukaru>("Atsukaru", [&](Atsukaru* atsukaru) {
		if (atsukaru->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 enemy_position = atsukaru->Getm_Position();
		CVector3 diff = enemy_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = atsukaru->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					if (DashFlag == true) {//ダッシュ状態なら…

						atsukaru->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { enemy_position.x,enemy_position.y + SpawnEffectY,enemy_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}
				}
			}
		}
		return true;
		});

	//メトポリスとの距離を計算
	QueryGOs<Metoporisu>("Metoporisu", [&](Metoporisu* metoporisu) {
		if (metoporisu->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 enemy_position = metoporisu->Getm_Position();
		CVector3 diff = enemy_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = metoporisu->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					if (DashFlag == true) {//ダッシュ状態なら…

						metoporisu->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { enemy_position.x,enemy_position.y + SpawnEffectY,enemy_position.z }, SpawnEffectScale);
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
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					int EState = ekku->GetEState();
					if ((EState != Ekku::Estete_Attack && DashFlag == true) || player_state == Estate_Dash || player_state == Estate_Frea) {//敵が攻撃中の時でない＆ダッシュ状態なら…

						ekku->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { souka_position.x,souka_position.y + SpawnEffectY,souka_position.z }, SpawnEffectScale);
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
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					int EState = pi_rabi->GetEState();
					if ((EState != Pi_rabi::Estete_Attack && DashFlag == true) || player_state == Estate_Dash || player_state == Estate_Frea) {//敵が攻撃中の時でない＆ダッシュ状態なら…

						pi_rabi->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { souka_position.x,souka_position.y + SpawnEffectY,souka_position.z }, SpawnEffectScale);
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
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					if (DashFlag == true) {//ダッシュ状態なら…

						fairo->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { souka_position.x,souka_position.y + SpawnEffectY,souka_position.z }, SpawnEffectScale);
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
		//Shisok_position.z = Shisok_position.z - 800.0f;
		Shisok_position.y = Shisok_position.y + 2000.0f;
		CVector3 diff = Shisok_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = pairodorago->GetDamageLength();
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
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
					if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
						m_moveSpeed.x *= -Zonbi_Handou_Boss;
						m_moveSpeed.y *= -Zonbi_Handou_Boss;
						m_moveSpeed.z *= -Zonbi_Handou_Boss;
					}
					else {
						if (player_state != Estate_Frea) {
							m_Life = 0;
						}
					}
					
					if (DashFlag == true || player_state == Estate_Dash || player_state == Estate_Frea) {//敵が攻撃中の時でない＆ダッシュ状態なら…

						prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
						ss->Init(L"sound/damage.wav");
						ss->SetVolume(0.5f);
						ss->Play(false);

						//オラァ！
						pairodorago->Damage(Damage);
						gamedata->PlusBossDamage();

					}


				}
			}
		}
		return true;
		});

	//イーダンドとの距離を計算
	QueryGOs<Idando>("Idando", [&](Idando* idando) {
		if (idando->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 enemy_position = idando->Getm_Position();
		CVector3 diff = enemy_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = idando->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					int EState = idando->GetEState();
					if ((EState != Idando::Estete_Attack && DashFlag == true) || player_state == Estate_Dash || player_state == Estate_Frea) {//敵が攻撃中の時でない＆ダッシュ状態なら…

						idando->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { enemy_position.x,enemy_position.y + SpawnEffectY,enemy_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}
				}
			}
		}
		return true;
		});

	//コダンとの距離を計算
	QueryGOs<Kodan>("Kodan", [&](Kodan* kodan) {
		if (kodan->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 souka_position = kodan->Getm_Position();
		CVector3 diff = souka_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = kodan->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					if (DashFlag == true) {//ダッシュ状態なら…

						kodan->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { souka_position.x,souka_position.y + SpawnEffectY,souka_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//タイドルとの距離を計算
	QueryGOs<Taidol>("Taidol", [&](Taidol* taidol) {
		if (taidol->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 enemy_position = taidol->Getm_Position();
		CVector3 diff = enemy_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = taidol->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					int EState = taidol->GetEState();
					if ((EState != Taidol::Estete_Attack && DashFlag == true) || player_state == Estate_Dash || player_state == Estate_Frea) {//敵が攻撃中の時でない＆ダッシュ状態なら…

						taidol->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { enemy_position.x,enemy_position.y + SpawnEffectY,enemy_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
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
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					int EState = morikon->GetEState();
					if ((EState != Morikon::Estete_Attack && DashFlag == true) || player_state == Estate_Dash || player_state == Estate_Frea) {//敵が攻撃中の時でない＆ダッシュ状態なら…

						morikon->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { souka_position.x,souka_position.y + SpawnEffectY,souka_position.z }, SpawnEffectScale);
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
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					if (DashFlag == true) {//ダッシュ状態なら…

						riritto->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { souka_position.x,souka_position.y + SpawnEffectY,souka_position.z }, SpawnEffectScale);
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
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					if (DashFlag == true) {//ダッシュ状態なら…

						arukasya->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { souka_position.x,souka_position.y + SpawnEffectY,souka_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//スロークとの距離を計算
	QueryGOs<Suroku>("Suroku", [&](Suroku* suroku) {
		if (suroku->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 souka_position = suroku->Getm_Position();
		CVector3 diff = souka_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = suroku->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					if (DashFlag == true) {//ダッシュ状態なら…

						suroku->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { souka_position.x,souka_position.y + SpawnEffectY,souka_position.z }, SpawnEffectScale);
							//gamedata->TestMessage();
						}
					}


				}
			}
		}
		return true;
		});

	//ミミットとの距離を計算
	QueryGOs<Mimitto>("Mimitto", [&](Mimitto* mimitto) {
		if (mimitto->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 souka_position = mimitto->Getm_Position();
		CVector3 diff = souka_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = mimitto->GetDamageLength();
			if (player_state == Estate_Dash) {
				Langth_hoge *= StarRange;
			}
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
			//距離判定
			if (diff.Length() < Langth_hoge) {
				//もし無敵時間中でないなら
				if (MutekiTimer == -1) {

					//ギリギリボーナスが成立するか確認
					GameData * gamedata = GameData::GetInstance();
					bool Hantei = gamedata->GiriBonusKeisan();

					//寿命をゼロに
					if (player_state != Estate_Dash && player_state != Estate_Frea) {
						if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
							m_moveSpeed.x *= -Zonbi_Handou_Normal;
							m_moveSpeed.y *= -Zonbi_Handou_Normal;
							m_moveSpeed.z *= -Zonbi_Handou_Normal;
						}
						else {
							m_Life = 0;
						}
					}

					if (DashFlag == true) {//ダッシュ状態なら…

						mimitto->SetDeath();//お前も死ね

						if (Hantei == true) {
							//ギリギリボーナスカウントを+1
							gamedata->GiriCounter();
							//ボーナス成立のエフェクトを表示
							EffectManager * effectmanager = EffectManager::GetInstance();
							effectmanager->EffectPlayer(EffectManager::Bonus, { souka_position.x,souka_position.y + SpawnEffectY,souka_position.z }, SpawnEffectScale);
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
		CVector3 Shisok_position = ss_001->Getm_Position();
		CVector3 diff = Shisok_position - position;
		playerVec = diff;
		//死んでいなければ接触判定
		if (player_state != Estate_Death) {
			//＊ダメージレンジは どこだ。
			float Langth_hoge = ss_001->GetDamageLength();
			if (SoulFlareFlag == true) {
				Langth_hoge *= FlareRange;
			}
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
					if (NowSkillNo == 7) { //ゾンビタイム中は死なずに反動でぶっとぶ
						m_moveSpeed.x *= -Zonbi_Handou_Boss;
						m_moveSpeed.y *= -Zonbi_Handou_Boss;
						m_moveSpeed.z *= -Zonbi_Handou_Boss;
						}
					else {
						if (player_state != Estate_Frea) {
							m_Life = 0;
						}
					}

					if (DashFlag == true || player_state == Estate_Dash || player_state == Estate_Frea) {//敵が攻撃中の時でない＆ダッシュ状態なら…

						prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
						ss->Init(L"sound/damage.wav");
						ss->SetVolume(0.5f);
						ss->Play(false);

						//オラァ！
						ss_001->Damage(Damage);
						gamedata->PlusBossDamage();

					}


				}
			}

			//ビーム判定！
			int EState = ss_001->GetEState();
			if (EState == SS_001::Estete_Attack2) {//ビームなう
				float X_MAX = Shisok_position.x + ss_001->GetBeamRange();
				float X_MIN = Shisok_position.x - ss_001->GetBeamRange();
				float Y_MAX = Shisok_position.y + ss_001->GetBeamRange();
				float Y_MIN = Shisok_position.y - ss_001->GetBeamRange();
				//今、審判の時
				if (X_MAX > position.x && X_MIN < position.x && Y_MAX > position.y && Y_MIN < position.y) {
					//寿命をゼロに
					m_Life = 0;
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
	SaveData * savedata = SaveData::GetInstance();

	if (ResetTimer == 0) {

		prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
		//SE再生
		ss->Init(L"sound/P_death.wav");
		ss->SetVolume(0.5f);
		ss->Play(false);

		//しんでしまった！
		player_state = Estate_Death;
		
		DashTimeCount = -1;
		DashFlag = false;
		A_DashFlag = false;
		DashTimeCount = -1;
		NowSkillReset();

		if (savedata->GetSkill(false) == 18) { //カミカゼバトル
			m_LifeSpeed = m_LifeSpeedDEF / 2;
		}
		else {
			m_LifeSpeed = m_LifeSpeedDEF;
		}

		//移動停止
		m_moveSpeed = CVector3::Zero;

		//無敵時間の準備！
		MutekiTimer = 0;
	}

	if (GameData::GetInstance()->GetGameMode() == GameData::Battle2D_Mode && ResetTimer == 5) {
		//星が増えるのは2Dモードだけ。
		if (savedata->GetSkill(false) != 21 && savedata->GetSkill(true) != 21) { //ナミダスキル装備中は増えない
			NakamaLight * nakamaLight = NewGO<NakamaLight>(0);
			//NakamaLight * nakamaLight = NakamaLight::GetInstance();
			nakamaLight->NakamaPlus(false, false);
		}
	}
	if (GameData::GetInstance()->GetGameMode() == GameData::Battle3D_Mode && ResetTimer == 5) {
		//3Dモードなら流星ゲージ上昇
		if (savedata->GetSkill(false) != 21 && savedata->GetSkill(true) != 21) { //ナミダスキル装備中は増えない
			NakamaLight * nakamaLight = NewGO<NakamaLight>(0);
			//NakamaLight * nakamaLight = NakamaLight::GetInstance();
			nakamaLight->NakamaPlus(false, false);
		}
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
		//あ～～～～～～
			ResetTimer = -1;
			gamedata->SetZanki(-1);//残機減少
			 //状態を戻す
			player_state = Estate_Stay;
			//寿命減少速度も戻す
			LifeSpeedReset();
			//あれもこれも戻す
			if (GameData::GetInstance()->GetStageNo() == 3 && GameData::GetInstance()->GetGameMode() == GameData::Battle3D_Mode) {
				position = P_Pos_Metoro3D;
			}
			else {
				position = CVector3::Zero;
			}
			m_charaCon.SetPosition(position); //キャラコンも戻すぞ
			rotation = CQuaternion::Identity;
			m_scale = CVector3::One;
			LightStatus = LightStatusDEF;
			m_moveSpeed = DeathMove;
			//はい。
			m_skinModelRender->SetPosition(position);
			m_skinModelRender->SetRotation(rotation);
			m_skinModelRender->SetScale(m_scale);
			/*
			if (GameData::GetInstance()->GetGameMode() == GameData::Battle2D_Mode) {
				//星が増えるのは2Dモードだけ。
				GraphicsEngine().GetPostEffect().GetDithering().AddPointLig();
			}
			*/
			//移動が終わったのでエフェクトを再生（移動後にやらないと死んだ場所で再生されてしまうので）
			EffectManager * effectmanager = EffectManager::GetInstance();
			int mode = gamedata->GetGameMode();
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
	SaveData * savedata = SaveData::GetInstance();
	int mode = gameData->GetGameMode();

	//タイマー加算
	if (mode != GameData::Pause && player_state != Estate_Frea) { //ポーズ中とソウルフレア中は実行しない！
		MutekiTimer++;
	}

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

	int Hosei = 0;
	
	if (savedata->GetSkill(false) == 13 || savedata->GetSkill(true) == 13) { //ムテキノバシ
		Hosei = 60;
	}

	//時間切れ

	if (MutekiTimer >= MutekiAverage + Hosei) {
		MutekiTimer = -1; //無敵を戻す
		m_skinModelRender->SetActiveFlag(true);
	}
}

void Player::LightStatusSupporter() {

	//呼び出し
	GameData * gamedata = GameData::GetInstance();
	int mode = gamedata->GetGameMode();
	float RightHosei = 1.0f - gamedata->ZankiWariai(); //逆だ…
	float range;
	if (GameData::GetInstance()->GetGameMode() == GameData::Battle2D_Mode) {
		//2Dモードでは仲間はポイントライトになる。
		range = minRange;
	}
	else {
		//それ以外(3Dモードなど)では、世界全体を照らす。
		range = minRange * (1.0f - RightHosei) + maxRange * RightHosei;
	}
	
	//LightStatusの値を設定
	float LightX = gamedata->GetLifePercent(0);
	LightX = 1.0f - LightX; //これで割合がわかります！！！！
	LightStatus = LightStatusMAX * LightX;
	range += LightStatus;

	//ふははは
	if (mode == GameData::Battle3D_Mode) {
		LightStatus *= LightHosei3D;
	}

	if (NowSkillNo == 4) { //カガヤキノウミ
		range *= 4.0f;
	}

	//セット(^_-)-☆
	SetSpecialLigRange(range, 0.2f);

}

void Player::SkillYobidashi(int SkillNo) {

	//発動中スキルNoを設定
	NowSkillNo = SkillNo;
	GameData * gameData = GameData::GetInstance();
	EffectManager * effectmanager = EffectManager::GetInstance();

	if (SkillNo == 0) {//流星ダッシュ
		prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/stardash.wav");
		ss->SetVolume(1.0f);
		ss->Play(false);

		//ダッシュ状態になるぞ！！！！！！
		m_LifeSpeed = 1;
		player_state = Estate_Dash;
		DashFlag = true;
		DashTimeCount = -2; //解除されないダッシュ状態になる
	}
	else if (SkillNo == 1) { //こんぺいとうダッシュ
		prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/stardash.wav");
		ss->SetVolume(1.0f);
		ss->Play(false);

		//ダッシュ状態になるぞ！！！！！！
		m_LifeSpeed = 1;
		player_state = Estate_Dash;
		DashFlag = true;
		DashTimeCount = -2; //解除されないダッシュ状態になる
	}
	else if (SkillNo == 2) { //すいせいダッシュ
		prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/stardash.wav");
		ss->SetVolume(1.0f);
		ss->Play(false);

		//ダッシュ状態になるぞ！！！！！！
		m_LifeSpeed = 1;
		player_state = Estate_Dash;
		DashFlag = true;
		DashTimeCount = -2; //解除されないダッシュ状態になる
	}
	else if (SkillNo == 3) { //スタードロップ
		NakamaLight * stardrop = NewGO<NakamaLight>(0);
		stardrop->NakamaPlus(true,false);

		effectmanager->EffectPlayer_Post(EffectManager::Bonus, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale);

	}
	else if (SkillNo == 4) { //カガヤキノウミ
		//効果音だけ
		prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/stardash.wav");
		ss->SetVolume(1.0f);
		ss->Play(false);

		effectmanager->EffectPlayer_Post(EffectManager::Bonus, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale);

	}
	else if (SkillNo == 5) { //スターフィーバー
		NakamaLight * starFi1 = NewGO<NakamaLight>(0);
		starFi1->NakamaPlus(true,true);
		NakamaLight * starFi2 = NewGO<NakamaLight>(0);
		starFi2->NakamaPlus(true,true);
		NakamaLight * starFi3 = NewGO<NakamaLight>(0);
		starFi3->NakamaPlus(true,true);

		effectmanager->EffectPlayer_Post(EffectManager::Bonus, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale);

	}
	else if (SkillNo == 6) { //ミルキーウェイ
		NakamaLight * starMil1 = NewGO<NakamaLight>(0);
		starMil1->NakamaPlus(true, true);
		NakamaLight * starMil2 = NewGO<NakamaLight>(0);
		starMil2->NakamaPlus(true, true);
		NakamaLight * starMil3 = NewGO<NakamaLight>(0);
		starMil3->NakamaPlus(true, true);
		NakamaLight * starMil4 = NewGO<NakamaLight>(0);
		starMil4->NakamaPlus(true, true);
		NakamaLight * starMil5 = NewGO<NakamaLight>(0);
		starMil5->NakamaPlus(true, true);
		NakamaLight * starMil6 = NewGO<NakamaLight>(0);
		starMil6->NakamaPlus(true, true);
		NakamaLight * starMil7 = NewGO<NakamaLight>(0);
		starMil7->NakamaPlus(true, true);
		NakamaLight * starMil8 = NewGO<NakamaLight>(0);
		starMil8->NakamaPlus(true, true);
		NakamaLight * starMil9 = NewGO<NakamaLight>(0);
		starMil9->NakamaPlus(true, true);
		NakamaLight * starMil10 = NewGO<NakamaLight>(0);
		starMil10->NakamaPlus(true, true);

		effectmanager->EffectPlayer_Post(EffectManager::Bonus, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale);

	}
	else if (SkillNo == 7) { //ゾンビタイム
		//効果音だけ
		prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/ZonbiTime.wav");
		ss->SetVolume(0.5f);
		ss->Play(false);

		effectmanager->EffectPlayer_Post(EffectManager::Bonus, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale);

	}
	else if (SkillNo == 8) { //ナガレボシ
		//効果音だけ
		prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/Nagareboshi.wav");
		ss->SetVolume(0.5f);
		ss->Play(false);

		effectmanager->EffectPlayer_Post(EffectManager::Bonus, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale);

	}
	else if (SkillNo == 9) { //ソウルフレア
		prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/beamcharge.wav");
		ss->SetVolume(0.8f);
		ss->SetFrequencyRatio(1.5f);
		ss->Play(false);

		//Effect再生
		effectmanager->EffectPlayer_Post(EffectManager::Beam, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale, true);

		MutekiTimer = 0; //無敵になる（しかもソウルフレア発動中は永続だ！）
		m_LifeSpeed = 99999; //さらに自動寿命減少もしないのだ！
		player_state = Estate_Frea;
	}
	else if (SkillNo == 10) { //すたこめ
		prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/Stacco.wav");
		ss->SetVolume(1.0f);
		ss->Play(false);

		effectmanager->EffectPlayer_Post(EffectManager::Bonus, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale);

	}
	else if (SkillNo == 11) { //生命力ぅ…ですかねぇ
		prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/ZankiKaihuku.wav");
		ss->SetVolume(1.0f);
		ss->Play(false);

		//残機加算
		int MAX_Zanki = gameData->GetDEF_Zanki();
		float PlusZanki = (float)MAX_Zanki * 0.1f;
		gameData->SetZanki((int)PlusZanki);

		effectmanager->EffectPlayer_Post(EffectManager::Bonus, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale);

	}
	else if (SkillNo == 22) { //キコサーチ
		prefab::CSoundSource* ss = NewGO<prefab::CSoundSource>(0);
		ss->Init(L"sound/ZankiKaihuku.wav");
		ss->SetVolume(1.0f);
		ss->Play(false);

		effectmanager->EffectPlayer_Post(EffectManager::Bonus, { position.x,position.y + SpawnEffectY,position.z }, SpawnEffectScale);

	}

}

void Player::NowSkillReset() { //死んだら発動終了するスキルはここよ

	if (NowSkillNo == 0) {//流星ダッシュ
		NowSkillNo = -1;
	}else if (NowSkillNo == 1) {//こんぺいとうダッシュ
		NowSkillNo = -1;
	}
	else if (NowSkillNo == 2) {//すいせいダッシュ
		NowSkillNo = -1;
	}
	else if (NowSkillNo == 7) {//ゾンビタイム
		NowSkillNo = -1; //敵に当たっても死なないけど弾や電車に当たったらここに行くぞ
	}
	else if (NowSkillNo == 9) {//ソウルフレア
		NowSkillNo = -1;
	}
	else if (NowSkillNo == 10) {//スターコメット
		NowSkillNo = -1;
	}


}

void Player::SkillUpdate() { //時間が経てば終了するスキルはここよ

	if (NowSkillNo == -1) {
		SkillTimer = 0;
		SkillTimer2 = 0;
		SoulStarFlag = false;

	}

	if (NowSkillNo == 3) {//スタードロップ中
		GameData * gamedata = GameData::GetInstance();
		gamedata->Star_PowerChange(-5);		//流星ゲージ減少
		SkillTimer += 5;
		if (SkillTimer >= Skill_Data[3].StarPower) { //はい終了
			NowSkillNo = -1;
			SkillTimer = 0;
		}
	}
	else if (NowSkillNo == 4) { //カガヤキノウミ
		GameData * gamedata = GameData::GetInstance();
		SkillTimer2++;
		if (SkillTimer2 == 5) {
			gamedata->Star_PowerChange(-1);
			SkillTimer += 1;
			SkillTimer2 = 0;
		}
		if (SkillTimer >= Skill_Data[4].StarPower) { //はい終了
			NowSkillNo = -1;
			SkillTimer = 0;
		}
	}
	else if (NowSkillNo == 5) {//スターフィーバー中
		GameData * gamedata = GameData::GetInstance();
		gamedata->Star_PowerChange(-10);		//流星ゲージ減少
		SkillTimer += 10;
		if (SkillTimer >= Skill_Data[5].StarPower) { //はい終了
			NowSkillNo = -1;
			SkillTimer = 0;
		}
	}
	else if (NowSkillNo == 6) {//ミルキーウェイ中
		GameData * gamedata = GameData::GetInstance();
		gamedata->Star_PowerChange(-10);		//流星ゲージ減少
		SkillTimer += 10;
		if (SkillTimer >= Skill_Data[6].StarPower) { //はい終了
			NowSkillNo = -1;
			SkillTimer = 0;
		}
	}
	else if (NowSkillNo == 7) {//ゾンビタイム中
		GameData * gamedata = GameData::GetInstance();
		SkillTimer2++;
		if (SkillTimer2 == Zonbi_Gensyo_Limit) {
			gamedata->Star_PowerChange(-1);
			SkillTimer += 1;
			SkillTimer2 = 0;
		}
		if (SkillTimer >= Skill_Data[7].StarPower) { //はい終了
			NowSkillNo = -1;
			SkillTimer = 0;
			m_Life = 0;
		}
	}
	else if (NowSkillNo == 8) {//ナガレボシ中
		GameData * gamedata = GameData::GetInstance();
		SkillTimer2++;
		if (SkillTimer2 == 5) {
			gamedata->Star_PowerChange(-1);
			SkillTimer += 1;
			SkillTimer2 = 0;
		}
		if (SkillTimer >= Skill_Data[7].StarPower) { //はい終了
			NowSkillNo = -1;
			SkillTimer = 0;
		}
	}
	else if (NowSkillNo == 9) {//ソウルフレア
		GameData * gamedata = GameData::GetInstance();
		if (SoulStarFlag == false) {
			gamedata->Star_PowerChange(-10);		//流星ゲージ減少
			SkillTimer += 10;
		}
		if (SkillTimer >= Skill_Data[9].StarPower) { //はい終了
			SoulStarFlag = true;
			SkillTimer = 0;
		}
	}
	else if (NowSkillNo == 10) {//スターコメット
		GameData * gamedata = GameData::GetInstance();
		SkillTimer2++;
		if (SkillTimer2 == 5) {
			gamedata->Star_PowerChange(-1);
			SkillTimer += 1;
			SkillTimer2 = 0;
		}
		if (SkillTimer >= Skill_Data[10].StarPower) { //はい終了
			NowSkillNo = -1;
			SkillTimer = 0;
		}
	}
	else if (NowSkillNo == 11) {//生命力
		GameData * gamedata = GameData::GetInstance();
		gamedata->Star_PowerChange(-10);		//流星ゲージ減少
		SkillTimer += 10;
		if (SkillTimer >= Skill_Data[11].StarPower) { //はい終了
			NowSkillNo = -1;
			SkillTimer = 0;
		}
	}
	else if (NowSkillNo == 22) {//キコサーチ
		GameData * gamedata = GameData::GetInstance();
		SkillTimer2++;
		if (SkillTimer2 == 5) {
			gamedata->Star_PowerChange(-1);
			SkillTimer += 1;
			SkillTimer2 = 0;
		}
		if (SkillTimer >= Skill_Data[22].StarPower) { //はい終了
			NowSkillNo = -1;
			SkillTimer = 0;
		}
	}



}
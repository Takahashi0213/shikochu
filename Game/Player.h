#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"
#include "tkEngine/light/tkPointLight.h"

class Player : public IGameObject
{
	static Player* m_instance;
public:

	enum Player_State {
		Estate_Stay, //待機
		Estate_Dash, //ダッシュ
		Estate_Death, //死亡
		Estate_Frea, //ソウルフレア
	};
	//3Dモードでの加速減速ステート
	enum Dash_State3D{
		Estate_DEF, //通常
		Estate_Front, //加速
		Estate_Back, //減速
	};

	Player();
	~Player();
	bool Start();
	void Update();

	//寿命を返す関数
	int Player::GetLife() {

		return m_Life;
	}

	//ポジションを返す関数
	CVector3 Player::Getm_Position() {
		return position;
	}

	//回転を返す関数
	CQuaternion Player::GetRotation() {
		return rotation;
	}

	//移動速度を返す関数
	CVector3 Player::Getm_MoveSpeed() {
		return m_moveSpeed;
	}

	//ステートを返す関数
	int Player::GetState() {
			return player_state;
	}

	//3Dステートを返す関数
	int Player::GetState3D() {
		return Dash_state3D;
	}

	//Aダッシュフラグを返す関数
	bool Player::GetA_DashFlag() {
		return A_DashFlag;
	}

	//引数分寿命減少
	void Player::SetLife(int x) {
		m_Life -= x;
		if (m_Life < 0) {
			m_Life = 0;
		}
	}

	//無敵時間中ならtrue、そうでなければfalseを返す
	bool Player::MutekiChecker() {
		//無敵時間タイマーを参照
		if (MutekiTimer >= 0) {			
			return true; //無敵時間
		}
		else {
			return false; //無敵でない
		}
	}

	//現在のスキル発動状況を返す
	int Player::GetNowSkill() {
		return NowSkillNo;
	}

	//インスタンスの取得
	static Player* Player::GetInstance(){
		return m_instance;
	}

private:

	//寿命減少速度リセット
	void LifeSpeedReset() {
		m_LifeSpeed = m_LifeSpeedDEF;
	}

	//ライトを初期値にする関数
	void LightReset() {
		PlayerEmission = PlayerEmissionDEF;
		PlayerLight = PlayerLightDEF;
		PlayerLightAttn = PlayerLightAttnDEF;
	}

	void PlayerReset(); //死んだときに色々初期化します
	void PlayerJudge(); //死亡判定色々
	void MutekiSupporter(); //無敵時間中に実行するぜ～～～～～
	void LightStatusSupporter(); //呼ぶだけ明かり更新ちゃん
	void SkillYobidashi(int SkillNo); //スキルを強制実行！
	void NowSkillReset(); //死んだときに実行 スキルフラグを初期化したりする
	void SkillUpdate(); //スキルフラグ初期化（常時実行）

	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	CVector3 position = CVector3::Zero;
	CQuaternion rotation = CQuaternion::Identity;
	CVector3 m_scale = CVector3::One; //拡大率

	CVector3 m_moveSpeed = CVector3::Zero;	//移動速度。
	CCharacterController m_charaCon;		//キャラクターコントローラー。
	
	Player_State player_state = Estate_Stay;		 //状態
	Dash_State3D Dash_state3D = Estate_DEF;			 //3Dでの前進状態

	bool LaderFlag = false;

	//距離算出用
	CVector3 playerVec;
	const float PosY_Min3D = -350.0f; //3Dモード時、地面に埋まらないようにするので
	//移動速度
	const float moveCrossKey = 14.0f; //十字キー入力時の最高速度
	const float moveSpeedMAX = 600.0f; //普段の最高速度
	const float playerMoveSpeed = 14.0f; //ここの数値をいじると移動速度変わる
	const float dashSpeed2D = 50.0f; //2Dモード時の流星ダッシュ速度
	const float dashSpeed3D = 2.0f; //3Dモード時の流星ダッシュ速度
	const float Advance3D = 200.0f; //3Dモード時のデフォルト前進速度
	const float Advance3D_PM = 100.0f; //3Dモード時の加速減速量
	const float Advance3D_Back = 50.0f; //3Dモード時の減速補正
	const float Advance3D_FrontHosei = 10.0f; //3Dモード時の加速補正
	const float Advance3D_Move = 6.0f; //3Dモード時の移動補正
	const float A_DashSpeed = 2000.0f; //Aダッシュの速さだ
	const float Nagareboshi = 6.0f; //ナガレボシ中の最高速度加算
	const float Kamikaze = 10.0f; //カミカゼバトルの最高速度加算
	const float Akumu = -8.0f; //アクムの最高速度減算
	//寿命
	int m_Life = 0; //自分の寿命
	int m_LifeCounter = 0; //寿命減少カウンター
	const int m_Life_Decrease = 1; //減少値
	int m_LifeSpeed = 5; //ここをいじると寿命減少速度変わる
	const int m_LifeSpeedDEF = 5; //デフォルト寿命減少速度
	const int DashLife = 2; //ダッシュ中は寿命が0にならないようにする、その最小値
	const int DashLifeSpeed = 2; //ダッシュ中の寿命減少速度
	const int Dash_LifeGensyo = 10; //ダッシュ時の寿命減少値
	//Aダッシュ絡み
	bool DashFlag = false; //ダッシュだよ
	int DashTimeCount = -1; //ダッシュタイムを数えるよ
	const int DashTimeMAX = 40; //ダッシュが切れるフレーム
	bool A_DashFlag = false; //Aダッシュのフラグ（流星ダッシュには反応しない）
	//リセット用
	int ResetTimer = 0; //リセット用タイマー。そのままの意味
	const int ResetAverage = 60; //自分がリスポーンする間隔
	//光関連
	prefab::CPointLight* m_pointLig;	//点光源。
	CVector3 PlayerEmission = CVector3::One; //自分の発光具合
	CVector3 PlayerLight = CVector3::One; //周囲の光
	CVector3 PlayerLightAttn = CVector3::One; //減衰
	const float LightPosHosei = 30.0f; //ポイントライトのY軸補正（2Dモード）
	const float LightPosHoseiZ = -30.0f; //ポイントライトのZ軸補正（3Dモード）
	const float LightHosei = 0.01f; //僅かに光る
	const CVector3 PlayerEmissionDEF = { 0.1f, 0.1f, 0.1f }; //自分の発光具合デフォ
	const CVector3 PlayerLightDEF = { 500.0f, 500.0f, 500.0f }; //周囲の光デフォ
	const CVector3 PlayerLightAttnDEF = { 50.0f, 2.0f, 0.0f }; //減衰デフォ
	const CVector3 EmissionColorDEF{ 2.0f,2.0f,2.0f }; //モデルの光デフォ
	const float LightXDEF = 500000.0f;//上昇値
	const float AttnXDEF = 0.2f;//上昇値
	const float LightSpeed = 5.0f; //光が強くなるスピード 小さくすると強く光るようになる
	const float AttnSpeed = 10000.0f;//光る範囲が広くなるスピード 小さくすると強く光るようになる
	const float DeathLight = 1.5f; //死んだ瞬間にドカンと光る倍率
	const float DeathLight_Syusoku = 0.8f; //死んだ瞬間の光が収束する倍率
	const int DeathLightTime = 12; //死んだ瞬間に光る時間
	//周囲の光
	const float LightStatusDEF = 0.5f; //明かりデフォルト
	const float LightStatusMAX = 0.4f; //寿命によって明るさに補正がかかる、その最大値
	float LightStatus = LightStatusDEF; //少しずつ光る
	const float LightHosei3D = 4.0f; //3Dモードでの補正だぜ
	float Light_Nakama = 4.0f; //仲間が死んだときのライト補正の大きさ
	float minRange = 0.3f; //最小範囲
	float maxRange = 2.0f; //DEF最大範囲 すなわちザンキゼロかつ寿命MAXの時の明るさ範囲
	//無敵時間
	const int MutekiAverage = 60 + ResetAverage; //無敵解除までの時間（リスポーン間隔も含む）
	int MutekiTimer = -1; //無敵時間タイマー 0以上ならカウント開始するので普段は-1
	const CVector3 DeathMove = { 0.0f,0.0f,0.01f }; //死んだときのごく微量移動
	//エフェクト関連
	const CVector3 SpawnEffectScale = { 40.0f,40.0f,40.0f }; //スポーンエフェクトの大きさ
	const CVector3 DashEffectScale = { 20.0f,20.0f,20.0f }; //ダッシュエフェクトの大きさ
	const float SpawnEffectY = 50.0f;//スポーンエフェクトのY補正
	//ネルク
	bool bikkuriflag = false;
	//
	const float StarRange = 2.0f; //流星ダッシュ中の当たり判定拡張倍率
	//スキル設定
	int NowSkillNo = -1; //発動中のスキルNo（-1なら未）
	short SkillTimer = 0; //スキル発動時間のタイマー
	short SkillTimer2 = 0; //スキル発動時間のタイマー
	//ソウルフレア
	short SoulFlareTimer = 0; //タイマー
	const short SoulFlareLimit = 120; //爆発までの時間
	const float FlareRange = 4.0f; //ソウルフレア当たり判定拡張倍率
	bool SoulFlareFlag = false; //ソウルフレア発生中！
	bool SoulStarFlag = false;
	//ゾンビタイム
	const float Zonbi_Handou_Normal = 1.0f; //通常敵の反動
	const float Zonbi_Handou_Boss = 3.0f; //ボスの反動
	const int Zonbi_Gensyo_Limit = 5; //数字が小さいほど早く終了する

	int StarPointTimer = 0; //スターゲージ上昇タイマー
	const int StarPointLimit = 60; //スターゲージの上昇制限時間
	CVector3 P_Pos_Metoro3D = { 0.0f,0.0f,-3000.0f }; //UGメトロ3Dモード用ポジション
};


#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"
#include "tkEngine/light/tkPointLight.h"
#include "Enemy.h"

class Player : public IGameObject
{
public:

	enum Player_State {
		Estate_Stay, //待機
		Estate_Dash, //ダッシュ
		Estate_Death, //死亡
	};

	Player();
	~Player();
	bool Start();
	void Update();
	float Player::GetLifePercent(int x); 	//現在の寿命割合をfloatで返すぞ！

	//寿命を返す関数
	int Player::GetLife() {

		return m_Life;
	}

	//ポジションを返す関数
	CVector3 Player::Getm_Position() {
		return position;
	}

	//ステートを返す関数
	int Player::GetState() {
			return player_state;
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

	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	CVector3 position = CVector3::Zero;
	CQuaternion rotation = CQuaternion::Identity;
	CVector3 m_scale = CVector3::One; //拡大率

	CVector3 m_moveSpeed = CVector3::Zero;	//移動速度。
	CCharacterController m_charaCon;		//キャラクターコントローラー。
	
	Player_State player_state = Estate_Stay;		 //状態

	//距離算出用
	CVector3 playerVec;
	//移動速度
	const float moveCrossKey = 20.0f; //十字キー入力時の最高速度
	const float moveSpeedMAX = 1000.0f; //普段の最高速度
	const float playerMoveSpeed = 4.0f; //ここの数値をいじると移動速度変わる
	const float dashSpeed2D = 100.0f; //2Dモード時の前進速度
	const float dashSpeed3D = 10.0f; //3Dモード時の前進速度
	//寿命
	int m_Life = 0; //自分の寿命
	int m_LifeCounter = 0; //寿命減少カウンター
	const int m_Life_Decrease = 1; //減少値
	int m_LifeSpeed = 5; //ここをいじると寿命減少速度変わる
	const int m_LifeSpeedDEF = 5; //デフォルト寿命減少速度
	const int DashLife = 2; //ダッシュ中は寿命が0にならないようにする、その最小値
	const int DashLifeSpeed = 2; //ダッシュ中の寿命減少速度
	//リセット用
	int ResetTimer = 0; //リセット用タイマー。そのままの意味
	const int ResetAverage = 60; //自分がリスポーンする間隔
	//光関連
	prefab::CPointLight* m_pointLig;	//点光源。
	CVector3 PlayerEmission = CVector3::One; //自分の発光具合
	CVector3 PlayerLight = CVector3::One; //周囲の光
	CVector3 PlayerLightAttn = CVector3::One; //減衰
	const CVector3 PlayerEmissionDEF = { 0.1f, 0.1f, 0.1f }; //自分の発光具合デフォ
	const CVector3 PlayerLightDEF = { 500.0f, 500.0f, 500.0f }; //周囲の光デフォ
	const CVector3 PlayerLightAttnDEF = { 50.0f, 2.0f, 0.0f }; //減衰デフォ
	const float LightXDEF = 100.0f;//上昇値
	const float AttnXDEF = 1.0f;//上昇値
	const float LightSpeed = 50.0f; //光が強くなるスピード 小さくすると強く光るようになる
	const float AttnSpeed = 5000.0f;//光る範囲が広くなるスピード 小さくすると強く光るようになる

};


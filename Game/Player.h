#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"

#include "Enemy.h"

class Player : public IGameObject
{
public:

	enum Player_State2D {
		Estate_Stay, //待機
		Estate_Dash, //ダッシュ
		Estate_Death, //死亡
	};
	enum Player_State3D {
		Estate_Stay2, //待機
		Estate_Dash2, //ダッシュ
		Estate_Death2, //死亡
	};

	Player();
	~Player();
	bool Start();
	void Update();
	void PlayerReset();//死んだときに色々初期化します

	int Player::GetLife() {

		return m_Life;
	}

	//ポジションを返す関数
	CVector3 Player::Getm_Position() {
		return position;
	}

private:

	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	CVector3 position = CVector3::Zero;
	CQuaternion rotation = CQuaternion::Identity;
	CVector3 m_scale = CVector3::One; // 拡大率。

	CVector3 m_moveSpeed = CVector3::Zero;	//移動速度。
	CCharacterController m_charaCon;		//キャラクターコントローラー。
	
	Player_State2D player_state = Estate_Stay;		 //状態
	Player_State3D player_state2 = Estate_Stay2;		 //3D状態

	//距離算出用
	CVector3 playerVec;
	//移動速度
	const float moveCrossKey = 20.0f; //十字キー入力時の最高速度
	const float moveSpeedMAX = 1000.0f; //普段の最高速度
	const float playerMoveSpeed = 4.0f;//ここの数値をいじると移動速度変わる
	//寿命
	int m_Life = 0; //自分の寿命
	int m_LifeCounter = 0; //寿命減少カウンター
	const int m_LifeSpeed = 5; //ここをいじると寿命減少速度変わる
	//リセット用
	int ResetTimer = 0;
};


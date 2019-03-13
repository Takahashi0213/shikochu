#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"

class Player : public IGameObject
{
public:

	enum Player_State {
		Estate_Stay, //待機
		Estate_Move, //移動
		Estate_Dash, //ダッシュ
		Estate_Death, //死亡
	};

	const float moveCrossKey = 10.0f; //十字キー入力時の最高速度
	const float moveSpeedMAX = 200.0f; //普段の最高速度

	Player();
	~Player();
	bool Start();
	void Update();
	int GetLife();

	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	CVector3 position = CVector3::Zero;
	CQuaternion rotation = CQuaternion::Identity;

	CVector3 m_moveSpeed = CVector3::Zero;	//移動速度。
	CCharacterController m_charaCon;		//キャラクターコントローラー。

private:
	//寿命
	int m_Life = 0; //自分の寿命
};


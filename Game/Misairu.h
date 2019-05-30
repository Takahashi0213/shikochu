#pragma once
class Misairu : public IGameObject
{
public:
	Misairu();
	~Misairu();
	bool Start();
	void Update();

	enum Estete {
		Estete_Move,	//移動
		Estete_Attack,  //攻撃
		Estete_Death	 //死ﾇ
	};

	//移動速度を設定する関数
	void Misairu::SetMoveSpeed(CVector3 move) {
		moveSpeed = move;
	}

	//フラグの管理
	void Misairu::SettingFlag() {
		SetFlag = true;
	}
	bool Misairu::GetFlag() {
		return SetFlag;
	}

	//ポジションを設定する関数
	void Misairu::SetPosition(CVector3 pos) {
		m_position = pos;
	}

	//ポジションを返す関数
	CVector3 Misairu::Getm_Position() {
		return m_position;
	}
	//ステートを返す関数
	int Misairu::GetEState() {
		return m_stete;
	}
	//ダメージ範囲を教える関数
	float GetDamageLength() {
		return DamageLength;
	}

	//自分が死ぬ関数
	int Misairu::SetDeath() {
		m_stete = Estete_Death;
		return 0;
	}

private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダラー。
	CVector3 m_position = CVector3::Zero; // 座標。
	CQuaternion m_rotation = CQuaternion::Identity; //回転。
	CVector3 m_scale = CVector3::One; // 拡大率。

	CVector3 moveSpeed = CVector3::Zero;

	Estete m_stete = Estete_Move; //状態

	const float DamageLength = 100.0f; //ダメメージを受けけるは範囲だだよ

	CVector3 atmove = CVector3::Zero;
	bool SetFlag = false;

	//タイマー
	int Timer = 0;
	//
	const int MoveLimit = 120; //移動の制限時間
	const int AttackLimit = 300; //攻撃の制限時間
	//
	const float AttackMoveSpeed = 30.0f; //攻撃の移動速度
};


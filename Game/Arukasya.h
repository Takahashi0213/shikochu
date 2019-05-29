#pragma once
class Arukasya : public IGameObject
{
public:
	enum Estete {
		Estete_Attack,  //攻撃
		Estete_Move, //移動
		Estete_Yobi, //予備
		Estete_Death, //死
	};
	enum EnAnimationClip {
		enAnimationClip_walk, //歩き
		enAnimationClip_back, //後退
		enAnimationClip_Num,  //アニメーションクリップ
	};

	Arukasya();
	~Arukasya();

	void AruAttack();
	void AruMove();
	void AruYobi();
	void AruDeath();

	bool Start();
	void Update();

private:
	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダラー。
	CVector3 m_position = CVector3::Zero; // 座標。
	CQuaternion m_rotation = CQuaternion::Identity; //回転。
	CVector3 m_scale = { 30.0f,30.0f,30.0f }; // 拡大率。

	Estete m_stete = Estete_Move; //状態
	CCharacterController m_charaCon; //キャラコン

	CVector3 moveVec;
	//移動関連
	int count = 0;
	int random = 0;
	const float randomCount = 60.0f;
	const float randomSpeed = 30.0f;
	const float followRange = 4.0f;
	int Attackcount = 0;
	//予備関連

	//攻撃関連
	int timer = 0;
	const float waittimer = 30.0f;
};


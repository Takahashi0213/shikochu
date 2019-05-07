#pragma once
class Neoriku : public IGameObject
{
public:
	Neoriku();
	~Neoriku();

	enum Estete {
		Estete_Attack,  //攻撃
		Estete_Move, //移動
		Estete_Death, //死
		Estete_yobi	//予備動作
	};

	enum EnAnimationClip {
		enAnimationClip_walk, //歩き
		enAnimationClip_move, //動作
		enAnimationClip_attack, //攻撃
		enAnimationClip_Num,  //アニメーションクリップ

	};

	bool Start();
	void Update();

	void NeoAttack();
	void NeoMove();
	void NeoDeath();
	void Neoyobi();


private:
	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダラー。
	CVector3 m_position = CVector3::Zero; // 座標。
	CQuaternion m_rotation = CQuaternion::Identity; //回転。
	CVector3 m_scale = CVector3::One; // 拡大率。

	Estete m_Neostete = Estete_Move; //状態
	CCharacterController m_charaCon; //キャラコン

};


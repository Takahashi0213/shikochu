#pragma once
class SS_001 : public IGameObject
{
public:
	SS_001();
	~SS_001();
	bool Start();
	void Update();

	enum Estete {
		Estete_Move,	//移動
		Estete_Attack1,  //攻撃1
		Estete_Yobi1,	//予備動作1
		Estete_Attack2,  //攻撃2
		Estete_Yobi2,	//予備動作2
		Estete_Death	 //死ﾇ

	};

	enum EnAnimationClip {
		enAnimationClip_move, //動作
		enAnimationClip_Num,  //アニメーションクリップ
	};

private:

	/*
	攻撃1→ミサイル
	攻撃2→ビーム！
	*/

	void SSMove();
	void SSYobi1();
	void SSAttack1();
	void SSYobi2();
	void SSAttack2();
	void SSDeath();

	CAnimationClip m_animClips[enAnimationClip_Num];
	prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダラー。
	CVector3 m_position = CVector3::Zero; // 座標。
	CQuaternion m_rotation = CQuaternion::Identity; //回転。
	CVector3 m_scale = CVector3::One; // 拡大率。

	Estete m_stete = Estete_Move; //状態
	CCharacterController m_charaCon; //キャラコン

	int waveNo = 0; //自分が属するWaveの番号

	const int MAXHP = 500; //最大HP
	int NowHP = MAXHP; //現在HP

};


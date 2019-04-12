#pragma once
class StarItem : public IGameObject
{
public:

	enum Estete {
		Estete_Wait,  //待機
		Estete_Death, //死
	};

	StarItem();
	~StarItem();
	bool Start();
	void Update();

private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	CVector3 m_position = CVector3::Zero; // 座標。
	CQuaternion m_rotation = CQuaternion::Identity; //回転。
	CVector3 m_scale = CVector3::One; // 拡大率。
	//距離算出用
	CVector3 itemVec;
	//消滅時間のタイマー
	int itemTimer = 10;//これが0になったら消滅

	Estete m_stete = Estete_Wait;		 //状態

};


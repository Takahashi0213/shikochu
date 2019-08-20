#pragma once
class StarItem : public IGameObject
{
public:

	enum Estete {
		Estete_Wait,  //待機
		Estete_Death, //死
		Estete_Death2, //取得されずに死んだ
		Estete_Death3, //だまって死ね
	};

	//座標を設定。
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	//ポジションを返す関数
	CVector3 StarItem::Getm_Position() {
		return m_position;
	}

	//所属Waveをセット
	void SetWave(int x) {
		waveNo = x;
	}
	//所属Waveを返す
	int GetWave() {
		return waveNo;
	}

	//さよならアイテム
	void DeleteItem() {
		m_stete = Estete_Death2;
	}

	//さよならアイテム
	void DeleteItem2() {
		m_stete = Estete_Death3;
	}

	StarItem();
	~StarItem();
	bool Start();
	void Update();

private:

	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	CVector3 m_position = CVector3::Zero; // 座標。
	CQuaternion m_rotation = CQuaternion::Identity; //回転。
	CVector3 m_scale = { 2.0f,2.0f,2.0f }; // 拡大率。
	//距離算出用
	CVector3 itemVec;
	//消滅時間のタイマー
	int itemTimer = 10;//これが0になったら消滅、100にすると即満タンになるチートアイテムになります

	Estete m_stete = Estete_Wait;	//状態

	const float GetRange = 80.0f;	//取得する範囲
	const CVector3 EffectScale = { 30.0f,30.0f,30.0f }; //取得時のエフェクトの大きさ
	
	//光関連
	prefab::CPointLight* m_pointLig;	//点光源。
	CVector3 ItemEmission = CVector3::One; //自分の発光具合
	CVector3 ItemLight = CVector3::One; //周囲の光
	CVector3 ItemLightAttn = CVector3::One; //減衰
	const CVector3 ItemEmissionDEF = { 1.0f, 1.0f, 1.0f }; //自分の発光具合デフォ
	const CVector3 ItemLightDEF = { 200.0f, 200.0f, 200.0f }; //周囲の光デフォ
	const CVector3 ItemLightAttnDEF = { 50.0f, 2.0f, 0.0f }; //減衰デフォ

	int waveNo = 0; //自分が属するWaveの番号

	const float RotItem = 1.0f; //回る速度や方向
};


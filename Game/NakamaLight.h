#pragma once
class NakamaLight : public IGameObject
{
	static NakamaLight* m_instance;
public:
	NakamaLight();
	~NakamaLight();
	bool Start();
	void Update();
	void NakamaPlus(); //実行されたら仲間の光！

	//インスタンスの取得
	static NakamaLight* NakamaLight::GetInstance() {
		return m_instance;
	}

private:

	std::vector<prefab::CSpriteRender*> m_spriteRender;
	prefab::CSoundSource* ss;
	prefab::CSpriteRender* r;

	const CVector2 P_Pos = CVector2::Zero; //基点
	CVector2 Star_Pos = CVector2::Zero; //目標地点
	CVector2 MoveSpeed = CVector2::Zero; //移動距離

	CVector3 Scale = CVector3::Zero;
	CVector3 ScaleSpeed = CVector3::Zero;

	float MulAlpha = 0.0f;
	CVector4 MulColor{ 1.0f,1.0f,1.0f,1.0f };

	int StarTimer = -1;
	const int StarLimit = 120; //星の移動速度（ゆっくり）
	const int StarLimit_High = 24; //星の移動速度（はやく！）
	const int StarWaitLimit = 36; //星がゆっくり動く制限時間
	const int FinalLimit = StarWaitLimit + StarLimit_High;

};


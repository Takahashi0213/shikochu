#pragma once
class BackGround : public IGameObject
{
	static BackGround* m_instance;
public:

	//ステージ名

	BackGround();
	~BackGround();
	void StageMaker(int ST);
	void DeleteStage();

	//インスタンスの取得
	static BackGround* BackGround::GetInstance() {
		return m_instance;
	}

private:

	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	CPhysicsStaticObject m_physicsStaticObject;				//静的物理オブジェクト。

	//ステージファイル名
	wchar_t DetaBase[5][30]{
	{ L"modelData/stage1.cmo" },
	{ L"modelData/stage2.cmo" },
	{ L"modelData/stage3.cmo" },

	};

	//trueに設定したステージでは静的物理オブジェクトを設定する
	bool physicsFlag[5]{
		false,
		true,
		false,
	};

	wchar_t ST_Name[30] = { L"" };	//ステージ名保管用

	const CVector3 m_position = { 0.0f,-1000.0f,0.0f };//場所
	const CVector3 m_scale = { 25.0f,25.0f,25.0f };//大きさ

	const float Emission = 0.4f; //わざわざ調整するのが面倒なので
	const CVector3 StageEmission = { Emission,Emission,Emission }; //自分の発光具合

};


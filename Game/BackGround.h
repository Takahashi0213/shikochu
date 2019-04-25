#pragma once
class BackGround : public IGameObject
{
	static BackGround* m_instance;
public:

	//ステージ名
	enum Stage {
		Stage_1,
		Stage_2,
		Stage_3,
		Stage_4,
		Stage_5,
	};

	BackGround();
	~BackGround();
	void StageMaker(Stage stage);
	void DeleteStage();

	//インスタンスの取得
	static BackGround* BackGround::GetInstance() {
		return m_instance;
	}

private:

	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。

																//エフェクトファイル名
	wchar_t DetaBase[5][30]{
	{ L"modelData/stage1.cmo" },
	};

	Stage m_stete = Stage_1;		 //ステージ状態
	wchar_t ST_Name[30] = { L"" };	//ステージ名保管用

	const CVector3 m_position = { 0.0f,-1000.0f,0.0f };//場所
	const CVector3 m_scale = { 25.0f,25.0f,25.0f };//大きさ

	const float Emission = 0.5f; //わざわざ調整するのが面倒なので
	const CVector3 StageEmission = { Emission,Emission,Emission }; //自分の発光具合

};


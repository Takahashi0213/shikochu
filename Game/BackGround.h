#pragma once
class BackGround : public IGameObject
{
	static BackGround* m_instance;
public:

	enum EnAnimationClip {
		enAnimationClip_A,  //アニメーションクリップ
		enAnimationClip_B,  //アニメーションクリップ	
		enAnimationClip_C,  //アニメーションクリップ
	};

	//ステージ名

	BackGround();
	~BackGround();
	void StageMaker(int ST);
	void DeleteStage();
	void PhysicsRelease();

	//インスタンスの取得
	static BackGround* BackGround::GetInstance() {
		return m_instance;
	}

	void BackGround::PlayBG_Anime(int x);

private:

	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
	CPhysicsStaticObject m_physicsStaticObject;				//静的物理オブジェクト。

	//ステージファイル名
	wchar_t DetaBase[5][30]{
	{ L"modelData/stage1.cmo" },
	{ L"modelData/forest.cmo" },
	{ L"modelData/Metolo.cmo" },
	{ L"modelData/stage2.cmo" },
	{ L"modelData/stage3.cmo" },

	};

	wchar_t Tutorial[1][30]{
	{ L"modelData/Tutorial.cmo" },
	};

	//trueに設定したステージでは静的物理オブジェクトを設定する
	bool physicsFlag[5]{
		false,
		true,
		true,
		true,
		false,
	};

	//trueに設定したステージではアニメーションを設定する
	bool animeFlag[5]{
		false,
		false,
		true,
		false,
		false,
	};

	CAnimationClip m_anim[3];

	wchar_t ST_Name[30] = { L"" };	//ステージ名保管用

	const CVector3 m_position = { 0.0f,-1000.0f,0.0f };//場所
	const CVector3 m_scale = { 25.0f,25.0f,25.0f };//大きさ
	const CVector3 Re_position = { 0.0f,-10000.0f,0.0f }; //当たり判定が消えたように見せかける用

	const float Emission = 0.4f; //わざわざ調整するのが面倒なので
	const CVector3 StageEmission = { Emission,Emission,Emission }; //自分の発光具合

};


#pragma once

class Train1;
class Train2;
class StageGimmick : public IGameObject
{
	static StageGimmick* m_instance;
public:
	StageGimmick();
	~StageGimmick();
	bool Start();
	void Update();

	//インスタンスの取得
	static StageGimmick* StageGimmick::GetInstance() {
		return m_instance;
	}

private:
	CSkinModelData trainModelData1;
	CSkinModelData trainModelData2;
	CPhysicsStaticObject m_physicsStaticObject;				//静的物理オブジェクト。

	std::vector<prefab::CSpriteRender*> m_spriteRender;
	std::vector<prefab::CSkinModelRender*> m_skinModelRender;
	prefab::CSoundSource* ss;
	prefab::CSpriteRender* r;
	prefab::CSkinModelRender* e;

	const CVector3 m_position = CVector3::Zero;//場所
	const CVector3 m_scale = CVector3::One;//大きさ

	int timer = 0;

	//電車
	bool TrainFlag = false;
	Train1*train1 = nullptr;
	Train2*train2 = nullptr;

	//定数
	int TrainLimit = 720; //初回は720固定
	const float TrainX = 20000.0f;
};


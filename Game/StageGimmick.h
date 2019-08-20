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

	//�C���X�^���X�̎擾
	static StageGimmick* StageGimmick::GetInstance() {
		return m_instance;
	}

private:
	CSkinModelData trainModelData1;
	CSkinModelData trainModelData2;
	CPhysicsStaticObject m_physicsStaticObject;				//�ÓI�����I�u�W�F�N�g�B

	std::vector<prefab::CSpriteRender*> m_spriteRender;
	std::vector<prefab::CSkinModelRender*> m_skinModelRender;
	prefab::CSoundSource* ss;
	prefab::CSpriteRender* r;
	prefab::CSkinModelRender* e;

	const CVector3 m_position = CVector3::Zero;//�ꏊ
	const CVector3 m_scale = CVector3::One;//�傫��

	int timer = 0;

	//�d��
	bool TrainFlag = false;
	Train1*train1 = nullptr;
	Train2*train2 = nullptr;

	//�萔
	int TrainLimit = 720; //�����720�Œ�
	const float TrainX = 20000.0f;
};


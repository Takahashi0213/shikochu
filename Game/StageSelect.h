#pragma once
class StageSelect : public IGameObject
{
	static StageSelect* m_instance;
public:
	enum EnAnimationClip {
		enAnimationClip_motion1, //動く1
		enAnimationClip_motion2, //動く2
		enAnimationClip_Num,  //アニメーションクリップ
	};

	StageSelect();
	~StageSelect();
	bool Start();
	void Update();

	//インスタンスの取得
	static StageSelect* StageSelect::GetInstance() {
		return m_instance;
	}

private:

	CAnimationClip m_animClips[enAnimationClip_Num];
	//prefab::CSkinModelRender* m_skinModelRender = nullptr;	//スキンモデルレンダラー。
	CVector3 m_position = CVector3::Zero; // 座標。
	CQuaternion m_rotation = CQuaternion::Identity; //回転。
	CVector3 m_scale = CVector3::One; // 拡大率。

	std::vector<prefab::CSpriteRender*> m_spriteRender;
	std::vector<prefab::CFontRender*> m_fontRender;
	std::vector<prefab::CSkinModelRender*> m_skinModelRender;
	prefab::CSpriteRender* r;
	prefab::CFontRender* f;
	prefab::CSkinModelRender* e;

	int SelectStageNow = 0; //現在選択中のステージ

};


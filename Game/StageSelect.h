#pragma once
class StageSelect : public IGameObject
{
	static StageSelect* m_instance;
public:
	enum EnAnimationClip {
		enAnimationClip_motion1, //����1
		enAnimationClip_motion2, //����2
		enAnimationClip_Num,  //�A�j���[�V�����N���b�v
	};

	StageSelect();
	~StageSelect();
	bool Start();
	void Update();

	//�C���X�^���X�̎擾
	static StageSelect* StageSelect::GetInstance() {
		return m_instance;
	}

private:

	CAnimationClip m_animClips[enAnimationClip_Num];
	//prefab::CSkinModelRender* m_skinModelRender = nullptr;	//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero; // ���W�B
	CQuaternion m_rotation = CQuaternion::Identity; //��]�B
	CVector3 m_scale = CVector3::One; // �g�嗦�B

	std::vector<prefab::CSpriteRender*> m_spriteRender;
	std::vector<prefab::CFontRender*> m_fontRender;
	std::vector<prefab::CSkinModelRender*> m_skinModelRender;
	prefab::CSpriteRender* r;
	prefab::CFontRender* f;
	prefab::CSkinModelRender* e;

	int SelectStageNow = 0; //���ݑI�𒆂̃X�e�[�W

};


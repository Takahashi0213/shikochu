#pragma once
class Zukan : public IGameObject
{
	static Zukan* m_instance;
public:
	enum EnAnimationClip {
		enAnimationClip_Num,  //�A�j���[�V�����N���b�v
	};

	Zukan();
	~Zukan();
	bool Start();
	void Update();

	//�C���X�^���X�̎擾
	static Zukan* Zukan::GetInstance() {
		return m_instance;
	}
private:

	void KoumokuUpdate();

	CAnimationClip m_mo0anim[1];
	CAnimationClip m_mo1anim[1];
	CAnimationClip m_mo2anim[1];
	CAnimationClip m_mo3anim[1];
	CAnimationClip m_mo4anim[1];

	CVector3 m_position = CVector3::Zero; // ���W�B
	CQuaternion m_rotation = CQuaternion::Identity; //��]�B
	CQuaternion m_rotation2 = CQuaternion::Identity; //��]�B
	CVector3 m_scale = CVector3::One; // �g�嗦�B

	std::vector<prefab::CSpriteRender*> m_spriteRender;
	std::vector<prefab::CFontRender*> m_fontRender;
	std::vector<prefab::CSkinModelRender*> m_skinModelRender;
	prefab::CSoundSource* ss;
	prefab::CSpriteRender* r;
	prefab::CFontRender* f;
	prefab::CSkinModelRender* e;

	float BMG_V = 1.0f;

	//���s�p
	float MulAlpha = 1.0f;
	float MulAlpha2 = 0.0f;
	CVector4 MulColor{ 1.0f,1.0f,1.0f,1.0f };

	int Timer = 0;
	bool DeleteFlag = false;
	
	//Exit���o
	int E_MoveTimer = 0;
	bool E_MoveFlag = false;

	//���O
	wchar_t ModelName[255] = { L"" };	//���f�����ۊǗp

	//���݂̍���
	int SelectNow = 0;

	//�萔
	const wchar_t Reset[1] = L"";

};


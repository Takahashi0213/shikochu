#pragma once
class Zukan : public IGameObject
{
	static Zukan* m_instance;
public:
	enum EnAnimationClip {
		enAnimationClip_Num,  //�A�j���[�V�����N���b�v
		enAnimationClip_ATK,  //�A�j���[�V�����N���b�v
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
	void AttackAnime(int i);
	void YazirusiUpdate(); //�㉺�ړ�������̕s�����x�ύX

	CAnimationClip m_mo0anim[2];
	CAnimationClip m_mo1anim[2];
	CAnimationClip m_mo2anim[2];
	CAnimationClip m_mo3anim[2];
	CAnimationClip m_mo4anim[2];
	CAnimationClip m_mo5anim[2];
	CAnimationClip m_mo6anim[2];
	CAnimationClip m_mo7anim[2];
	CAnimationClip m_mo8anim[2];
	CAnimationClip m_mo9anim[2];
	CAnimationClip m_mo10anim[2];
	CAnimationClip m_mo11anim[2];
	CAnimationClip m_mo12anim[2];
	CAnimationClip m_mo13anim[2];
	CAnimationClip m_mo14anim[2];
	CAnimationClip m_mo15anim[2];
	CAnimationClip m_mo16anim[2];
	CAnimationClip m_mo17anim[2];
	CAnimationClip m_mo18anim[2];
	CAnimationClip m_mo19anim[2];
	CAnimationClip m_mo20anim[2];
	CAnimationClip m_mo21anim[2];
	CAnimationClip m_mo22anim[2];
	CAnimationClip m_mo23anim[2];
	CAnimationClip m_mo24anim[2];
	CAnimationClip m_mo25anim[2];
	CAnimationClip m_mo26anim[2];
	CAnimationClip m_mo27anim[2];
	CAnimationClip m_mo28anim[2];
	CAnimationClip m_mo29anim[2];
	CAnimationClip m_mo30anim[2];
	CAnimationClip m_mo31anim[2];
	CAnimationClip m_mo32anim[2];

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

	//�U���A�j��
	bool AttackAnimeFlag = false;

	//�萔
	const wchar_t Reset[1] = L"";

	//���㉺
	bool Ya_UpDownFlag = false;
	int Ya_UpDownTimer = 0;

};


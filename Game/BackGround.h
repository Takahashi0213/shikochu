#pragma once
class BackGround : public IGameObject
{
	static BackGround* m_instance;
public:

	enum EnAnimationClip {
		enAnimationClip_A,  //�A�j���[�V�����N���b�v
		enAnimationClip_B,  //�A�j���[�V�����N���b�v	
		enAnimationClip_C,  //�A�j���[�V�����N���b�v
	};

	//�X�e�[�W��

	BackGround();
	~BackGround();
	void StageMaker(int ST);
	void DeleteStage();
	void PhysicsRelease();

	//�C���X�^���X�̎擾
	static BackGround* BackGround::GetInstance() {
		return m_instance;
	}

	void BackGround::PlayBG_Anime(int x);

private:

	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	CPhysicsStaticObject m_physicsStaticObject;				//�ÓI�����I�u�W�F�N�g�B

	//�X�e�[�W�t�@�C����
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

	//true�ɐݒ肵���X�e�[�W�ł͐ÓI�����I�u�W�F�N�g��ݒ肷��
	bool physicsFlag[5]{
		false,
		true,
		true,
		true,
		false,
	};

	//true�ɐݒ肵���X�e�[�W�ł̓A�j���[�V������ݒ肷��
	bool animeFlag[5]{
		false,
		false,
		true,
		false,
		false,
	};

	CAnimationClip m_anim[3];

	wchar_t ST_Name[30] = { L"" };	//�X�e�[�W���ۊǗp

	const CVector3 m_position = { 0.0f,-1000.0f,0.0f };//�ꏊ
	const CVector3 m_scale = { 25.0f,25.0f,25.0f };//�傫��
	const CVector3 Re_position = { 0.0f,-10000.0f,0.0f }; //�����蔻�肪�������悤�Ɍ���������p

	const float Emission = 0.4f; //�킴�킴��������̂��ʓ|�Ȃ̂�
	const CVector3 StageEmission = { Emission,Emission,Emission }; //�����̔����

};


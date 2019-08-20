#pragma once
class ED
{
	static ED* m_instance;
public:
	ED();
	~ED();
	bool Start();
	void Update();

	//�C���X�^���X�̎擾
	static ED* ED::GetInstance() {
		return m_instance;
	}

private:

	void BounderSet(int x);
	void Bounder();
	//
	void UpperSet(int x);
	void Upper();
	//
	void KamisibaiSet(int x);
	void Kamisibai();

	//ED�V�[��
	enum ed_Scene {
		Tobu,
		Utyu,
		Otiru,
		Saigo,
		END,
	};

	std::vector<prefab::CSpriteRender*> m_spriteRender;
	std::vector<prefab::CFontRender*> m_fontRender;
	prefab::CSoundSource* ss;
	prefab::CSpriteRender* r;
	prefab::CFontRender* f;
	ed_Scene ED_Scene = Tobu;		 //���

	int Timer = 0;
	CVector3 pos = CVector3::Zero;
	CVector3 scl = CVector3::One;

	//�o�E���_�[
	int BoundSet[5]{
		{ -1 },
	{ -1 },
	{ -1 },
	{ -1 },
	{ -1 },
	};
	int BoundTimer[5]{
		{ -1 },
	{ -1 },
	{ -1 },
	{ -1 },
	{ -1 },
	};

	//�A�b�p�[
	int UppSet[5]{
		{ -1 },
	{ -1 },
	{ -1 },
	{ -1 },
	{ -1 },
	};
	int UpperTimer[5]{
		{ -1 },
	{ -1 },
	{ -1 },
	{ -1 },
	{ -1 },
	};

	float BMG_V = 0.8f;

	//���ŋ�
	int KamisibaiNo = -1;
	int KamisibaiTimer = -1;

	//������p
	int KuruTimer = 0;

	//���s�p
	float MulAlpha = 0.0f;
	CVector4 MulColor{ 1.0f,1.0f,1.0f,1.0f };

	//�X�L�b�v�p
	int SkipTimer = -1; //���i��-1
	float SkipAlpha = 1.0f;

	//�萔
	const float DEF_POS = 720.0f;//�f�t�H�p���Z�萔

	const float TextScale = 1.3f;
	const float SetumeiScale = 1.0f; //�X�L�b�v�������̑傫��

	const int Scene1_Limit = 180; //�V�[��1�̃^�C�����~�b�g

	const int SkipMoziLimit = 120; //�X�L�b�v��������������܂ł̎���
};


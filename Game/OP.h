#pragma once
class OP : public IGameObject
{
	static OP* m_instance;
public:
	OP();
	~OP();
	bool Start();
	void Update();

	//�C���X�^���X�̎擾
	static OP* OP::GetInstance() {
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

	//OP�V�[��
	enum op_Scene {
		Hazimari,
		Seisitu,
		sinigami,
		ganbaru,
		END,
	};

	std::vector<prefab::CSpriteRender*> m_spriteRender;
	std::vector<prefab::CFontRender*> m_fontRender;
	prefab::CSoundSource* ss;
	prefab::CSpriteRender* r;
	prefab::CFontRender* f;
	op_Scene OP_Scene = Hazimari;		 //���

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

	//�萔
	const float DEF_POS = 720.0f;//�f�t�H�p���Z�萔

	const float TextScale = 1.3f;

	const int Scene1_Limit = 180; //�V�[��1�̃^�C�����~�b�g
	const int Scene2_Limit = 360; //�V�[��2�̃^�C�����~�b�g
	const int Scene3_Limit = 360; //�V�[��3�̃^�C�����~�b�g
	const int Scene4_Limit = 180; //�V�[��4�̃^�C�����~�b�g
	const int Scene5_Limit = 200; //�V�[��5�̃^�C�����~�b�g


};


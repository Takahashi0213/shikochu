#pragma once
class Title : public IGameObject
{
	static Title* m_instance;
public:
	Title();
	~Title();
	enum Estete {
		NewGame,	//���߂���
		LoadGame,	//��������
		Exit,		//�I��
	};
	enum Newmove {
		NewUp,
		Newloop,
		NewDisappear,
	};
	enum Loadmove {
		LoadDown,
		Loadloop,
		LoadUp,
	};

	enum Exitmove {
		Exitdown1,	
		Exitloop,	
		Exitdown2,		
	};


	bool Start();
	void Update();

	void GameStart();
	void GameMore();
	void GameEnd();


	void NewMove();
	void LoadMove();
	void ExitMove();

	void minimusi();
	void minimove();

private:

	std::vector<prefab::CSpriteRender*> m_spriteRender;
	prefab::CSpriteRender* r;
	prefab::CSoundSource* ss;

	CVector4 MulColor{ 1.0f,1.0f,1.0f,1.0f };

	Estete m_stete = NewGame;//���
	Newmove m_new = NewUp;//���
	Loadmove m_load = LoadDown;//���
	Exitmove m_exit= Exitdown1;//���
	//�~�j���֘A
	int timer = 0;
	CVector3 minipos = {0.0f,-70.0f,0.0f};
	bool miniflag = false;
	bool minimoveflag = false;
	int movetimer = 0;
	//���ʂ��Ďg�p
	CVector3 musi = { 0.0f,0.0f,0.0f };
	CVector3 diff;
	CVector3 scalediff;
	const float movecount = 12;			//�������p
	int down1timer = 0;
	int down2timer = 0;
	const float loop_1y = 100.0f;		//�e�N�X�`���̍����Œ�
	const float loop_2y = 100.0f;		//�e�N�X�`���̍����Œ�

	//New�֘A
	const float hoge1posX = 800.0f;
	const float hoge1posY = -800.0f;
	CVector3 musi1up = { -150.0f,2000.0f,0.0f };//��������W�i��ʊO�j
	const float loop_11y = -100.0f;		//�e�N�X�`���̍����Œ�
	const float loop_12y = -100.0f;		//�e�N�X�`���̍����Œ�
	CVector3 misi1setscale = { 2.5f,2.5f,2.5f };
	CVector3 misi1upscale = { 3.0f,3.0f,3.0f };
	CVector3 misi1scale = { 1.0f,1.0f,1.0f };

	//Load�֘A
	const float hoge2posX = 200.0f;
	const float hoge2posY = 600.0f;
	CVector3 misi2setscale = { 0.0f,0.0f,0.0f };
	CVector3 misi2scale = { 1.0f,1.0f,1.0f };
	CVector3 misi2bigscale = { 3.0f,3.0f,3.0f };
	CVector3 musi2up = { 0.0f,1000.0f,0.0f };//��������W�i��ʊO�j
	bool selectflag = false;
	//Exit�֘A
	const float hogeposY = 700.0f;		//�������W�i��ʊO�j
	CVector3 musidown = { 0.0f,-700.0f,0.0f };//��������W�i��ʊO�j
	float Feathertoumaina = 1.0f;		//�����x�p
	bool Featherflag = false;
	//loop�֘A
	float setloop1_1x = 200.0f;
	float setloop1_2x = -800.0f;

	float setloop2_1x = 200.0f;
	float setloop2_2x = -800.0f;

	float setloop3_1x = 200.0f;
	float setloop3_2x = -800.0f;

	float BGM_V = 1.0f;
	int Timer = 0;
};


#pragma once
class NerukGenerator : public  IGameObject
{
	static NerukGenerator* m_instance;

public:
	NerukGenerator();
	~NerukGenerator();
	void Update();

	//�����_���̐��l��Ԃ��֐�
	/*int NerukGenerator::GetMoverandom(int moverandom) {
		return moverandom;
	}
	int NerukGenerator::GetAnirandom(int animesionrandom) {
		return animesionrandom;
	}*/
	int  moverandom = 0; //�����ꏊ�����p
	int  animesionrandom = 0; //�A�j���[�V���������p
	//�C���X�^���X�̎擾
	static NerukGenerator* NerukGenerator::GetInstance() {
		return m_instance;
	}

private:
	//����
	int timer = 0;	//�l���N�̐����p
	int oldmovecount = 3;
	const float newtimer = 90.0f;//���������܂ł̎���

	int timer1 = 0;	//�l���N�̐����p
	int oldmovecount1 = 3;
	const float newtimer1 = 90.0f;//���������܂ł̎���
	
	bool flag = false;
	
};


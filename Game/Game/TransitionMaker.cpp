#include "stdafx.h"
#include "TransitionMaker.h"

TransitionMaker* TransitionMaker::m_instance = nullptr;

TransitionMaker::TransitionMaker()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;
}


TransitionMaker::~TransitionMaker()
{
	for (int i = 0; i < m_spriteRender.size(); i++) {
		DeleteGO(m_spriteRender[i]);
	}

	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;
}

bool TransitionMaker::Start() {

	//0�� �t�F�[�h�p
	r = NewGO<prefab::CSpriteRender>(15);
	r->Init(L"sprite/Black.dds", 1280.0f, 720.0f);
	r->SetPosition({ 0.0f ,0.0f,0.0f });
	MulAlpha = 0.0f;
	MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//1�� ����p1
	r = NewGO<prefab::CSpriteRender>(15);
	r->Init(L"sprite/Black.dds", 1280.0f, 720.0f);
	r->SetPosition({ 0.0f ,720.0f,0.0f });
	MulAlpha = 0.0f;
	MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);
	//2�� ����p2
	r = NewGO<prefab::CSpriteRender>(15);
	r->Init(L"sprite/Black.dds", 1280.0f, 720.0f);
	r->SetPosition({ 0.0f ,-720.0f,0.0f });
	MulAlpha = 0.0f;
	MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
	r->SetMulColor(MulColor);
	m_spriteRender.push_back(r);

	return true;
}

void TransitionMaker::Update() {

	if (TransitionTimer >= 0) { //�^�C�}�[��0�ȏ�Ȃ���s
		if (TransitionTimer >= TransitionWait) { //�E�F�C�g�Ȃ�҂�
			/////////////////���̒��Ńg�����W�V�����I�I�I�I�I�I�I�I///////////////////
			if (TransitionFlag == false) {//�\��////////////////////////////////////////////////
				if (TransitionNo == 0) {
					float hoge = 1.0f / (float)TransitionFrame;
					MulAlpha += hoge;
					MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
					m_spriteRender[0]->SetMulColor(MulColor);
				}
				else if (TransitionNo == 1) {
					float hoge = 360.0f / (float)TransitionFrame;
					CVector3 pos = m_spriteRender[1]->GetPosition();
					pos.y -= hoge;
					m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
					m_spriteRender[1]->SetPosition(pos);
					hoge = 360.0f / (float)TransitionFrame;
					pos = m_spriteRender[2]->GetPosition();
					pos.y += hoge;
					m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
					m_spriteRender[2]->SetPosition(pos);
				}
			}
			else if (TransitionFlag == true) {//����///////////////////////////////////////////
				if (TransitionNo == 0) {
					float hoge = 1.0f / (float)TransitionFrame;
					MulAlpha -= hoge;
					MulColor = { 1.0f,1.0f,1.0f,MulAlpha };
					m_spriteRender[0]->SetMulColor(MulColor);
				}
				else if (TransitionNo == 1) {
					float hoge = 360.0f / (float)TransitionFrame;
					CVector3 pos = m_spriteRender[1]->GetPosition();
					pos.y += hoge;
					m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
					m_spriteRender[1]->SetPosition(pos);
					hoge = 360.0f / (float)TransitionFrame;
					pos = m_spriteRender[2]->GetPosition();
					pos.y -= hoge;
					m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
					m_spriteRender[2]->SetPosition(pos);
				}

			}
			//////////////////////////////////////////////////////////////////////////
			//���Ԑ؂�Ȃ炨���܂�
			if (TransitionTimer > TransitionLimit) {
				if (TransitionFlag == true && TransitionNo == 1) {
					m_spriteRender[1]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
					m_spriteRender[2]->SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
				}
				TransitionTimer = -2;
			}
		}
		TransitionTimer++;
	}
}

//�g�����W�V������u���܂�
//���������g�����W�V�����̎��
//���������g�����W�V�����̎��s����
//��O�������g�����W�V�������n�܂�܂ł̃E�F�C�g
//��l������false�Ȃ�\���Atrue�Ȃ���������
//���ӁI�I�\���Ə����̃g�����W�V�����̎�ނ͓�������Ȃ��ƃo�O���
void TransitionMaker::TransitionSetting(Transition tran, int frame, int wait,bool flag) {

	//�ݒ�
	TransitionNo = tran;
	TransitionTimer = 0; //�^�C�}�[��0��
	TransitionFrame = frame;
	TransitionWait = wait;
	TransitionLimit = frame + wait;
	TransitionFlag = flag;

}


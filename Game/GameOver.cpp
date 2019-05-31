#include "stdafx.h"
#include "GameOver.h"
#include "GameData.h"
#include "TransitionMaker.h"

GameOver* GameOver::m_instance = nullptr;

GameOver::GameOver()
{
	if (m_instance != nullptr) {
		std::abort(); //���łɏo�Ă��邽�߃N���b�V��
	}

	//���̃C���X�^���X��B��̃C���X�^���X�Ƃ��ċL�^����
	m_instance = this;

}


GameOver::~GameOver()
{
	for (int i = 0; i < m_spriteRender.size(); i++) {
		DeleteGO(m_spriteRender[i]);
	}
	for (int i = 0; i < m_fontRender.size(); i++) {
		DeleteGO(m_fontRender[i]);
	}

	//�C���X�^���X���j�����ꂽ�̂ŁAnullptr����
	m_instance = nullptr;

}

bool GameOver::Start() {

	//0�ԁ��w�i
	r = NewGO<prefab::CSpriteRender>(10);
	r->Init(L"sprite/gameover.dds", 880.0f, 320.0f);
	r->SetPosition({ 0.0f,100.0f,0.0f });
	m_spriteRender.push_back(r);

	//�A�h�o�C�X
	f = NewGO<prefab::CFontRender>(10);
	//�\��
	GameData * gamedata = GameData::GetInstance();
	bool mode = gamedata->GetFinalMode();
	int stage = gamedata->GetStageNo();

	if (mode == false) {
		int random = rand() % 4;
		int len = (int)wcslen(Setumei_2D[random]);
		for (int z = 0; z < len + 1; z++) {
			HogeText[z] = Setumei_2D[random][z];
		}
	}else if (mode == true) {
		stage--;
		int len = (int)wcslen(Setumei_3D[stage]);
		for (int z = 0; z < len + 1; z++) {
			HogeText[z] = Setumei_3D[stage][z];
		}
	}

	swprintf(HogeText, HogeText);
	//�͂��B
	f->SetText(HogeText);
	f->SetPivot({ 0.0f,1.0f });
	f->SetPosition({ -400.0f,-100.0f });
	f->SetScale(1.0f);
	f->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	m_fontRender.push_back(f);

	return true;
}

void GameOver::Update() {

	if (Pad(0).IsTrigger(enButtonA) || Pad(0).IsTrigger(enButtonB) || Pad(0).IsTrigger(enButtonY) || Pad(0).IsTrigger(enButtonX)) {
		if (DeleteFlag == false) {
			TransitionMaker * tm = TransitionMaker::GetInstance();
			tm->TransitionSetting(TransitionMaker::Fade, 12, 0, false);
			DeleteFlag = true;
		}
	}

	if (DeleteFlag == true) {

		if (DeleteTimer == 60) {
			TransitionMaker * tm = TransitionMaker::GetInstance();
			tm->TransitionSetting(TransitionMaker::Fade, 12, 20, true);
			
			GameData * gamedata = GameData::GetInstance();
			gamedata->SetGameMode(GameData::GameEnd);
			DeleteGO(this);

		}

		DeleteTimer++;
	}


}
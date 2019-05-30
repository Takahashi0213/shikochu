#include "stdafx.h"
#include "Player.h"
#include "Nerubikkuri.h"
#include "Neruk.h"
#include "Misairu.h"

Nerubikkuri* Nerubikkuri::m_instance = nullptr;

Nerubikkuri::Nerubikkuri()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;

}


Nerubikkuri::~Nerubikkuri()
{
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
	DeleteGO(bikkuri);
}
bool Nerubikkuri::Start() {
	bikkuri = NewGO<prefab::CSpriteRender>(0);
	bikkuri->Init(L"sprite/bikkuri.dds", 300.0f, 300.0f);
	
	bikkuri->SetScale({0.5f,0.5f,0.5f });
	bikkuri->SetActiveFlag(false);
	return true;
}
void Nerubikkuri::Update()
{
	static CVector3 hoge = { 0.0f,100.0f,0.0f };
	bikkuri->SetPosition(hoge);
	Player* player = FindGO<Player>("Bug");
	bikkuri->SetActiveFlag(false);
	//ネルクとの距離を計算
	QueryGOs<Neruk>("neru", [&](Neruk* neruk) {
		if (neruk->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 neruk_position = neruk->Getm_Position();
		CVector3 diff = neruk_position - player->Getm_Position();
	
		if (diff.z < 800.0f && diff.z > 0.0f) {
			diff.z = 0.0f;
			if (diff.Length() < 200.0f) {
				bikkuri->SetActiveFlag(true);
			}

		}
		return true;
		});

	//ミサイルとの距離を計算
	QueryGOs<Misairu>("Misairu", [&](Misairu* misairu) {
		if (misairu->IsActive() == false) {
			//Activeじゃない。
			return true;
		}
		CVector3 neruk_position = misairu->Getm_Position();
		CVector3 diff = neruk_position - player->Getm_Position();

		if (diff.z < 800.0f && diff.z > 0.0f) {
			diff.z = 0.0f;
			if (diff.Length() < 200.0f) {
				bikkuri->SetActiveFlag(true);
			}

		}
		return true;
		});


}


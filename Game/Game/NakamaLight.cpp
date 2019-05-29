#include "stdafx.h"
#include "NakamaLight.h"
#include "GameData.h"

NakamaLight* NakamaLight::m_instance = nullptr;

NakamaLight::NakamaLight()
{
	if (m_instance != nullptr) {
		std::abort(); //すでに出ているためクラッシュ
	}

	//このインスタンスを唯一のインスタンスとして記録する
	m_instance = this;
}


NakamaLight::~NakamaLight()
{
	//インスタンスが破棄されたので、nullptrを代入
	m_instance = nullptr;
}

bool NakamaLight::Start() {


	return true;
}

void NakamaLight::Update() {

}

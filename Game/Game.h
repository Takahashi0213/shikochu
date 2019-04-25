#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"

class Game : public IGameObject
{
	static Game* m_instance;
public:
	Game();
	~Game();
	bool Start();
	void Update();

	//�C���X�^���X�̎擾
	static Game* Game::GetInstance() {
		return m_instance;
	} 

private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	CQuaternion rotation = CQuaternion::Identity;
	prefab::CDirectionLight* m_directionLig = nullptr;
	float m_tonemapDisableTimer = 1.0f;

};


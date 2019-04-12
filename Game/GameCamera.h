#pragma once
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	CVector3 cameraTarget;
	CVector3 cameraPos;
};


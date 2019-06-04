#pragma once

class EffectPlay : public IGameObject
{
public:
	EffectPlay();
	~EffectPlay();
	bool Start();
	void Update();

	void SetAnimation(std::wstring Animetion) {
		animation = Animetion;
	}
	void SetPosition(CVector3 Position) {
		position = Position;
	}
	void SetScale(CVector3 Scale) {
		scale = Scale;
	}

	void SetTuibiFlag(bool flag) {
		P_TuibiFlag = flag;
	}

private:
	std::wstring animation;
	CVector3 scale;
	CVector3 position;
	prefab::CEffect* effect;

	bool P_TuibiFlag = false;

};

#pragma once
class StarComet : public IGameObject
{
	static StarComet* m_instance;
public:
	StarComet();
	~StarComet();

	//隕石発射ァ！
	//第一引数にプレイヤーの移動速度をぶっこみます
	//第二引数にプレイヤーの現在座標をつっこみます
	void Comet_Hassya(CVector3 PlayerMoveSpeed, CVector3 Player_Pos);

	//インスタンスの取得
	static StarComet* StarComet::GetInstance() {
		return m_instance;
	}

};


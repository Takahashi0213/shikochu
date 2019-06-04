#pragma once
class NakamaLight : public IGameObject
{
	static NakamaLight* m_instance;
public:
	NakamaLight();
	~NakamaLight();
	bool Start();
	void Update();
	void NakamaPlus(); //���s���ꂽ�璇�Ԃ̌��I

	//�C���X�^���X�̎擾
	static NakamaLight* NakamaLight::GetInstance() {
		return m_instance;
	}

private:

	std::vector<prefab::CSpriteRender*> m_spriteRender;
	prefab::CSoundSource* ss;
	prefab::CSpriteRender* r;
	prefab::CSpriteRender* r2;

	const CVector2 P_Pos = CVector2::Zero; //��_
	CVector2 Star_Pos = CVector2::Zero; //�ڕW�n�_
	CVector2 MoveSpeed = CVector2::Zero; //�ړ�����

	CVector3 Scale = CVector3::Zero;
	CVector3 ScaleSpeed = CVector3::Zero;

	float MulAlpha = 0.0f;
	CVector4 MulColor{ 1.0f,1.0f,1.0f,1.0f };

	int StarTimer = -1;
	int StarAccTimer = -1;

	const int StarLimit = 120; //���̈ړ����x�i�������j
	const int StarLimit_High = 24; //���̈ړ����x�i�͂₭�I�j
	const int StarWaitLimit = 36; //����������蓮����������
	const int FinalLimit = StarWaitLimit + StarLimit_High;

	const int StarAccLimit = 24; //���G�t�F�N�g��������܂ł̎���
};


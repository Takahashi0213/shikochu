#pragma once
class Player_Status : public IGameObject
{
public:
	Player_Status();
	~Player_Status();

	bool Start();
	void Update();
	std::vector<prefab::CSpriteRender*> m_spriteRender;
	std::vector<prefab::CSpriteRender*> m_spriteRenderHP;

private:
	prefab::CFontRender* m_fontRender;
	const CVector2 LifePivot = { 0.5f, 0.1f };//HP�̊�_
	const CVector2 StarPivot = { 0.5f, 0.0f };//�����o�[�̊�_

	bool StarMaxFlag = false; //�}�b�N�X�A�C�R���\���t���O
	float StarMaxColor = 1.0f; //�}�b�N�X�A�C�R���̔���
	bool StarMaxColorFlag = false; //�}�b�N�X�A�C�R���̐F�����������[�v����̂�
	float StarMaxScale = 1.0f; //�}�b�N�X�A�C�R���̊g�嗦

	const CVector2 ZankiPos = { -645.0f, 255.0f }; //�c�@���\���ʒu
	const float ZankiPosXHosei = 40.0f; //�c�@���P���̎�X�ʒu��␳
	CVector4 LifeColor = { 1.0f,1.0f,1.0f,1.0f }; //HP�o�[�̐F
	CVector4 StarColor = { 1.0f,1.0f,1.0f,1.0f }; //�����o�[�̐F
	const float ZankiScale = 3.0f; //�c�@���\���T�C�Y

};


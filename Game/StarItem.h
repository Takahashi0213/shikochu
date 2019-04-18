#pragma once
class StarItem : public IGameObject
{
public:

	enum Estete {
		Estete_Wait,  //�ҋ@
		Estete_Death, //��
	};

	StarItem();
	~StarItem();
	bool Start();
	void Update();

private:
	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero; // ���W�B
	CQuaternion m_rotation = CQuaternion::Identity; //��]�B
	CVector3 m_scale = CVector3::One; // �g�嗦�B
	//�����Z�o�p
	CVector3 itemVec;
	//���Ŏ��Ԃ̃^�C�}�[
	int itemTimer = 10;//���ꂪ0�ɂȂ�������ŁA100�ɂ���Ƒ����^���ɂȂ�`�[�g�A�C�e���ɂȂ�܂�

	Estete m_stete = Estete_Wait;	//���

	const float GetRange = 40.0f;	//�擾����͈�

	//���֘A
	prefab::CPointLight* m_pointLig;	//�_�����B
	CVector3 ItemEmission = CVector3::One; //�����̔����
	CVector3 ItemLight = CVector3::One; //���͂̌�
	CVector3 ItemLightAttn = CVector3::One; //����
	const CVector3 ItemEmissionDEF = { 1.0f, 1.0f, 1.0f }; //�����̔�����f�t�H
	const CVector3 ItemLightDEF = { 200.0f, 200.0f, 200.0f }; //���͂̌��f�t�H
	const CVector3 ItemLightAttnDEF = { 50.0f, 2.0f, 0.0f }; //�����f�t�H
};


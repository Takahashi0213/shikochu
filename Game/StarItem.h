#pragma once
class StarItem : public IGameObject
{
public:

	enum Estete {
		Estete_Wait,  //�ҋ@
		Estete_Death, //��
		Estete_Death2, //�擾���ꂸ�Ɏ���
	};

	//���W��ݒ�B
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	//����Wave���Z�b�g
	void SetWave(int x) {
		waveNo = x;
	}
	//����Wave��Ԃ�
	int GetWave() {
		return waveNo;
	}

	//����Ȃ�A�C�e��
	void DeleteItem() {
		m_stete = Estete_Death2;
	}

	StarItem();
	~StarItem();
	bool Start();
	void Update();

private:

	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
	CVector3 m_position = CVector3::Zero; // ���W�B
	CQuaternion m_rotation = CQuaternion::Identity; //��]�B
	CVector3 m_scale = { 2.0f,2.0f,2.0f }; // �g�嗦�B
	//�����Z�o�p
	CVector3 itemVec;
	//���Ŏ��Ԃ̃^�C�}�[
	int itemTimer = 10;//���ꂪ0�ɂȂ�������ŁA100�ɂ���Ƒ����^���ɂȂ�`�[�g�A�C�e���ɂȂ�܂�

	Estete m_stete = Estete_Wait;	//���

	const float GetRange = 80.0f;	//�擾����͈�
	const CVector3 EffectScale = { 30.0f,30.0f,30.0f }; //�擾���̃G�t�F�N�g�̑傫��
	
	//���֘A
	prefab::CPointLight* m_pointLig;	//�_�����B
	CVector3 ItemEmission = CVector3::One; //�����̔����
	CVector3 ItemLight = CVector3::One; //���͂̌�
	CVector3 ItemLightAttn = CVector3::One; //����
	const CVector3 ItemEmissionDEF = { 1.0f, 1.0f, 1.0f }; //�����̔�����f�t�H
	const CVector3 ItemLightDEF = { 200.0f, 200.0f, 200.0f }; //���͂̌��f�t�H
	const CVector3 ItemLightAttnDEF = { 50.0f, 2.0f, 0.0f }; //�����f�t�H

	int waveNo = 0; //������������Wave�̔ԍ�

};


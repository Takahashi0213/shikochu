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
	int itemTimer = 10;//���ꂪ0�ɂȂ��������

	Estete m_stete = Estete_Wait;		 //���

};


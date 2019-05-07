#pragma once
class BackGround : public IGameObject
{
	static BackGround* m_instance;
public:

	//�X�e�[�W��
	enum Stage {
		Stage_1,
		Stage_2,
		Stage_3,
		Stage_4,
		Stage_5,
	};

	BackGround();
	~BackGround();
	void StageMaker(Stage stage);
	void DeleteStage();

	//�C���X�^���X�̎擾
	static BackGround* BackGround::GetInstance() {
		return m_instance;
	}

private:

	prefab::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B

																//�G�t�F�N�g�t�@�C����
	wchar_t DetaBase[5][30]{
	{ L"modelData/stage1.cmo" },
	};

	Stage m_stete = Stage_1;		 //�X�e�[�W���
	wchar_t ST_Name[30] = { L"" };	//�X�e�[�W���ۊǗp

	const CVector3 m_position = { 0.0f,-1000.0f,0.0f };//�ꏊ
	const CVector3 m_scale = { 25.0f,25.0f,25.0f };//�傫��

	const float Emission = 0.4f; //�킴�킴��������̂��ʓ|�Ȃ̂�
	const CVector3 StageEmission = { Emission,Emission,Emission }; //�����̔����

};


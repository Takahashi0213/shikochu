#pragma once

const int Stage = 2; //�X�e�[�W��

//�e�X�e�[�W��Wave��
const int Stage_Wave[Stage]{
	2,
	4,
};

//���x���t�@�C����
//�e�X�g�v���C�p���x������level/level_Test.tkl
const wchar_t LevelName[10][255]{
{ L"level/level_Test.tkl" },
{ L"level/level_03.tkl" },
{ L"level/level_02.tkl" },
{ L"level/level_03.tkl" }, //Boss
{ L"level/level_Test.tkl" },//��������X�e�[�W�Q

};

//�X�e�[�W�ʃ{�X��
const wchar_t BossName[Stage][128]{
{ L"�V�[�\�[�N�X" },

};

//�X�e�[�W��
const wchar_t StageName[Stage][128]{
	{ L"�C�t�F�}�����E�f�B�[�v�V�[" },
	{ L"�w�C�����E�w����" },

};

//���������X�e�[�W�̃t�@�C����
const wchar_t StageMiniName[Stage][255]{
	{ L"modelData/StageMini1.cmo" },
	{ L"modelData/StageMini2.cmo" },
};
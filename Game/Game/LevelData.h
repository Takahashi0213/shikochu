#pragma once

const int Stage = 2; //�X�e�[�W��

//�e�X�e�[�W��Wave��
const int Stage_Wave[Stage]{
	4,
	4,
};

//���x���t�@�C����
//�e�X�g�v���C�p���x������level/level_Test.tkl
const wchar_t LevelName[10][255]{
{ L"level/level_00.tkl" },
{ L"level/level_01.tkl" },
{ L"level/level_02.tkl" },
{ L"level/level_03.tkl" }, //Boss
{ L"level/level_Test.tkl" },//��������X�e�[�W�Q
{ L"level/level_Test.tkl" },//��������X�e�[�W�Q
{ L"level/level_Test.tkl" },//��������X�e�[�W�Q
{ L"level/level_03.tkl" },//��������X�e�[�W�Q

};

//�X�e�[�W�ʃ{�X��
const wchar_t BossName[Stage][128]{
{ L"�V�[�\�[�N�X" },
{ L"�i�i�V�m�S���x�G" },

};

//�X�e�[�W��
const wchar_t StageName[Stage][128]{
	{ L"�u�C�t�F�}�����E�f�B�[�v�V�[�v" },
	{ L"�u�w�C�����E�w�����v" },

};

//���������X�e�[�W�̃t�@�C����
const wchar_t StageMiniName[Stage][255]{
	{ L"modelData/StageMini1.cmo" },
	{ L"modelData/StageMini2.cmo" },
};

//BGM�̃t�@�C����
const wchar_t BGMName[Stage][255]{
{ L"sound/sea.wav" },
{ L"sound/iseki.wav" },
};

//�{�XBGM�̃t�@�C����
const wchar_t BossBGMName[Stage][255]{
{ L"sound/seaSokus.wav" },
{ L"sound/iseki.wav" },
};
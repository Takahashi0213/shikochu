#pragma once

const int Stage = 5; //�X�e�[�W��

//�e�X�e�[�W��Wave��
const int Stage_Wave[Stage]{
	4,
	4,
	4,
	4,
	4,
};

//���x���t�@�C����
//�e�X�g�v���C�p���x������level/level_Test.tkl
const wchar_t LevelName[20][255]{
{ L"level/level_00.tkl" },	//�X�e�[�W�P
{ L"level/level_01.tkl" },
{ L"level/level_02.tkl" },
{ L"level/level_03.tkl" },	//Boss1
{ L"level/level_12.tkl" },//�X�e�[�W�Q
{ L"level/level_13.tkl" },
{ L"level/level_14.tkl" },
{ L"level/level_15.tkl" },//Boss2
{ L"level/level_16.tkl" },	//�X�e�[�W�R
{ L"level/level_17.tkl" },
{ L"level/level_18.tkl" },
{ L"level/level_19.tkl" },	//Boss3
{ L"level/level_04.tkl" },	//�X�e�[�W�S
{ L"level/level_05.tkl" },
{ L"level/level_06.tkl" },
{ L"level/level_07.tkl" },	//Boss4
{ L"level/level_08.tkl" },	//�X�e�[�W�T
{ L"level/level_09.tkl" },
{ L"level/level_10.tkl" },
{ L"level/level_11.tkl" },	//Boss5

};

/*
{ L"level/level_12.tkl" },//�X�e�[�W�Q
{ L"level/level_13.tkl" },
{ L"level/level_14.tkl" },
*/


//�n�[�h���[�h�p���x���t�@�C����
//�e�X�g�v���C�p���x������level/level_Test.tkl
const wchar_t LevelName_Hard[20][255]{
{ L"level/level_00_h.tkl" },	//�X�e�[�W�P
{ L"level/level_01_h.tkl" },
{ L"level/level_02_h.tkl" },
{ L"level/level_03.tkl" },	//Boss1
{ L"level/level_12_h.tkl" },//�X�e�[�W�Q
{ L"level/level_13_h.tkl" },
{ L"level/level_14_h.tkl" },
{ L"level/level_15.tkl" },//Boss2
{ L"level/level_16_h.tkl" },	//�X�e�[�W�R
{ L"level/level_17_h.tkl" },
{ L"level/level_18_h.tkl" },
{ L"level/level_19.tkl" },	//Boss3
{ L"level/level_04_h.tkl" },	//�X�e�[�W�S
{ L"level/level_05_h.tkl" },
{ L"level/level_06_h.tkl" },
{ L"level/level_07.tkl" },	//Boss4
{ L"level/level_08_h.tkl" },	//�X�e�[�W�T
{ L"level/level_09_h.tkl" },
{ L"level/level_10_h.tkl" },
{ L"level/level_11.tkl" },	//Boss5

};

//�X�e�[�W�ʃ{�X��
const wchar_t BossName[Stage][128]{
{ L"�V�[�\�[�N�X" },
{ L"�������`��" },
{ L"�e�B���I�X�J" },
{ L"�p�C���h���S" },
{ L"SS-001" },

};

//�X�e�[�W��
const wchar_t StageName[Stage][128]{
{ L"�u�C�t�F�}�����E�f�B�[�v�V�[�v" },
{ L"�u�e�����Y�t�H���X�g�v" },
{ L"�uUG���g���v" },
{ L"�u�w�C�����E�w�����v" },
{ L"�u�K���N�V�A�v" },

};

//���������X�e�[�W�̃t�@�C����
const wchar_t StageMiniName[Stage][255]{
	{ L"modelData/StageMini1.cmo" },
	{ L"modelData/StageMini4.cmo" },
	{ L"modelData/StageMini5.cmo" },
	{ L"modelData/StageMini2.cmo" },
	{ L"modelData/StageMini3.cmo" },

};

//BGM�̃t�@�C����
const wchar_t BGMName[Stage][255]{
{ L"sound/sea.wav" },
{ L"sound/Mori.wav" },
{ L"sound/UGMetoro.wav" },
{ L"sound/iseki.wav" },
{ L"sound/ikukan.wav" },
};

//�{�XBGM�̃t�@�C����
const wchar_t BossBGMName[Stage][255]{
{ L"sound/seaSokus.wav" },
{ L"sound/MoriB.wav" },
{ L"sound/Teruosuka.wav" },
{ L"sound/pairodorago.wav" },
{ L"sound/SS_001.wav" },
};
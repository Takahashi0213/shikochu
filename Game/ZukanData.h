#pragma once

//�}�ӂ̃f�[�^�x�[�X

const int Monster = 13; //���ڐ�

//���f��
const wchar_t MonsterModel[Monster][128]{
{ L"modelData/bunbo-gu0.cmo" },
{ L"modelData/neoriku_0.cmo" },
{ L"modelData/soukabuto_0.cmo" },
{ L"modelData/Neruk.cmo" },
{ L"modelData/shisokus.cmo" },
{ L"modelData/Ekku.cmo" },
{ L"modelData/Rabbit_Level_1.cmo" },
{ L"modelData/Fairo.cmo" },
{ L"modelData/DragonTerrorBringerMesh.cmo" },
{ L"modelData/Bat_Level_1.cmo" },
{ L"modelData/Riritto.cmo" },
{ L"modelData/Arukasya.cmo" },
{ L"modelData/SS_001.cmo" },

};

//�A�j���[�V����
const wchar_t MonsterAnime[Monster][128]{
{ L"animData/walk.tka" },
{ L"animData/Neowalk.tka" },
{ L"animData/souwalk.tka" },
{ L"animData/Neruwalk.tka" },
{ L"animData/sisowalk.tka" },
{ L"animData/Ekwalk.tka" },
{ L"animData/P_idel.tka" },
{ L"animData/Faiwalk.tka" },
{ L"animData/piro_Bigidle.tka" },
{ L"animData/Mori_idel.tka" },
{ L"animData/Ririwalk.tka" },
{ L"animData/Aruwalk.tka" },
{ L"animData/SSwalk.tka" },

};

//�����X�^�[��
const wchar_t MonsterName[Monster][128]{
{ L"�u�����[�O" },
{ L"�l�I���N" },
{ L"�\�E�J�u�g" },
{ L"�l���N" },
{ L"�V�[�\�[�N�X" },
{ L"�G�b�N" },
{ L"�s�[���r" },
{ L"�t�@�C��" },
{ L"�p�C���h���S" },
{ L"�����R��" },
{ L"�����b�g" },
{ L"�A���J�V��" },
{ L"SS-001" },

};

//������ 1�s14�����܂ł����傤�ǂ���
const wchar_t Setumei[Monster][255]{
{ L"�u�����[�O�̂��߂�" },
{ L"�l�I���N�̂��߂�" },
{ L"�\�E�J�u�g�̂���" },
{ L"�l���N�̃A��" },
{ L"�V�[�\�[�N�X�́`" },
{ L"�����������������ق�����\n�݂�\n������������������" },
{ L"�΂���낤" },
{ L"�Ȃ�́H" },
{ L"�����������I�I�H�H\n�����H�H�H�H\n�قققق�" },
{ L"����������" },
{ L"�ӂ͂�" },
{ L"�A���J�V���`" },
{ L"���I���I����������" },

};

//�}�ӗp�X�P�[��
const CVector3 M_Scale[Monster]{
	{ 2.0f,2.0f,2.0f },
	{ 2.0f,2.0f,2.0f },
	{ 2.0f,2.0f,2.0f },
	{ 2.0f,2.0f,2.0f },
	{ 0.5f,0.5f,0.5f },
	{ 2.0f,2.0f,2.0f },
	{ 30.0f,30.0f,30.0f },
	{ 1.0f,1.0f,1.0f },
	{ 20.0f, 20.0f, 20.0f },
{ 20.0f, 20.0f, 20.0f },
{ 1.0f,1.0f,1.0f },
{ 2.0f,2.0f,2.0f },
{ 0.5f,0.5f,0.5f },

};

//�}�ӗpX�␳
const float X_Hosei[Monster]{
	{ 0.0f },
{ 0.0f },
{ 50.0f },
{ 0.0f },
{ 0.0f },
{ 50.0f },
{ 20.0f },
{ 20.0f },
{ 20.0f },
{ 50.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },

};

//�}�ӗpY�␳
const float Y_Hosei[Monster]{
	{ 0.0f },
	{ 0.0f },
	{ -60.0f },
	{ 0.0f },
	{ 0.0f },
	{ -50.0f },
	{ -50.0f },
	{ -50.0f },
	{ -100.0f },
{ -160.0f },
{ 0.0f },
{ -60.0f },
{ 0.0f },

};

//�}�ӗpZ�␳
const float Z_Hosei[Monster]{
	{ 0.0f },
{ 0.0f },
{ -100.0f },
{ 0.0f },
{ 0.0f },
{ -100.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },
{ 0.0f },

};
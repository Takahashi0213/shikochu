#pragma once

const int SkillKazu = 24; //�X�L����

const struct _Skill { //�X�L���f�[�^�p�\����
	wchar_t SkillName[128]; //�X�L����
	wchar_t SkillHint[255]; //�����莞�̃q���g
	wchar_t SkillSetumei[255]; //�X�L������
	int StarPower; //������Q�[�W 0�̏ꍇ�p�b�V�u�X�L���Ƃ��Ĉ���
	wchar_t SkillIcon[255]; //�X�L���摜
	wchar_t SkillTran[255]; //�g�����V�[�o�[�̃Z���t

};

const struct _Skill Skill_Data[SkillKazu]{ //�X�L���f�[�^
	{ L"��イ�����_�b�V��" , L"�������傩�� �����Ă���", L"�Ă��� ���������\n�Ƃ���������肾��" , 100 , L"sprite/skillicon_1.dds",L"�C�m�`�K�P �m\n�g�b�V�� �R�E�Q�L �f�X" },
	{ L"����؂��Ƃ��_�b�V��" , L"�V�[�\�[�N�X�� ��������", L"�Ă��� ���������\n�Ƃ���������肾��" , 50 , L"sprite/skillicon_2.dds",L"�����E�Z�C�_�b�V�� ����\n�R���p�N�g�i �^�C�v�f�X" },
	{ L"���������_�b�V��", L"STAGE1��HARD��\nS�����N�� �����Ƃ����悤" , L"�X���C�h�p�b�h�łق�������\n���傤���� �ł��邼" , 100 , L"sprite/skillicon_3.dds",L"�\�E�T�J�m�E �i\n�����E�Z�C�_�b�V��\n�f�X�l" },
	{ L"�X�^�[�h���b�v" , L"�L�R�E�`���E�}�[�N��\n1�� ���߂悤", L"�͂ǂ������ �ق���\n1�� �łĂ���" , 50 , L"sprite/skillicon_4.dds",L"�K������ �X�R�V\n�A�J���N �f�L�}�X" },
	{ L"�J�K���L�m�E�~" , L"�L�R�E�`���E�}�[�N��\n3�� ���߂悤", L"�͂ǂ����イ�� �܂�肪\n�ƂĂ������邭�Ȃ�" , 75 , L"sprite/skillicon_5.dds",L"�V�o���N �g�e��\n�A�J���N �i���}�X��" },
	{ L"�X�^�[�t�B�[�o�[" , L"�L�R�E�`���E�}�[�N��\n5�� ���߂悤", L"�͂ǂ������ �ق���\n3�� �łĂ���" , 100 , L"sprite/skillicon_6.dds" ,L"�K������ �\���i���j\n�A�J���N �f�L�}�X" },
	{ L"�~���L�[�E�F�C" , L"�L�R�E�`���E�}�[�N��\n����� ���߂悤", L"�͂ǂ������ �ق���\n10�� �łĂ���" , 100 , L"sprite/skillicon_7.dds",L"�K������ �g�e��\n�A�J���N �f�L�}�X" },
	{ L"�]���r�^�C��" , L"STAGE4��\n�A�C�e���� 15���Ђ남��", L"�͂ǂ����イ�� �Ă���\n�������Ă� ���ȂȂ�" , 100 , L"sprite/skillicon_8.dds",L"�e�L�m �R�E�Q�L�n\n���R�E�J �f�L�}�Z����" },
	{ L"�i�K���{�V" , L"STAGE2��\nS�����N�� �����Ƃ����悤", L"�͂ǂ����イ��\n���ǂ������� �A�b�v�I" , 75 , L"sprite/skillicon_9.dds",L"�V�o���N �g�e��\n�E�S�L���X�N �i���}�X" },
	{ L"�\�E���t���A" , L"STAGE2�ł΂������\n�����炸�N���A���悤", L"���΂炭�`���[�W����\n�����΂��͂� ����" , 100 , L"sprite/skillicon_10.dds",L"�V���E�C�m �e�L��\n�C�b�L�j �^�I�Z�}�X" },
	{ L"�R���b�g�L���m��" , L"STAGE3�łł񂵂��\n�Ђ��ꂸ�N���A���悤", L"�͂ǂ����イ��\n���񂹂����͂�����ł���" , 100 , L"sprite/skillicon_11.dds",L"�Z�b�e�C�V�^ �X�L���m\n�{�^���f �C���Z�L��\n�g�o�V�}�X" },
	{ L"�����߂���傭" , L"STAGE3��HARD��\nS�����N�� �����Ƃ����悤", L"���悤����� ���񂫂�\n�����������ӂ���" , 100 , L"sprite/skillicon_12.dds" ,L"�C�m�`�� �t���X�i���e\n�Y���N�i�C�f�X�J" },
	{ L"�A�^�b�N�A�b�v" , L"�Ă����邢����\n10���� ��������", L"����������傭�� ������" , 0 , L"sprite/skillicon_13.dds",L"�C�c�f��\n�R�E�Q�L�����N\n1.2�o�C �f�X�I" },
	{ L"���e�L�m�o�V" , L"�Ă����邢����\n30���� ��������", L"�ނĂ�������\n�Ȃ����Ȃ�" , 0 , L"sprite/skillicon_14.dds" ,L"���e�L�W�J�� �K\n2�o�C �j�i���}�X" },
	{ L"�A�C�e���u�[�X�g" , L"�Ă����邢����\n50���� ��������", L"�A�C�e�����Ђ�����Ƃ���\n�Q�[�W���傤���傤��傤+" , 0 , L"sprite/skillicon_15.dds",L"�X�L���� �^�N�T��\n�c�J�C�^�C �A�i�^�j\n�I�X�X���f�X" },
	{ L"�Z�c���N" , L"�Ă����邢����\n70���� ��������", L"�_�b�V���������Ƃ���\n����݂傤���񂵂傤1/2" , 0 , L"sprite/skillicon_16.dds",L"�n���N �n���N\n�n�V���^�C �A�i�^�j\n�I�X�X���f�X" },
	{ L"�C�m�`�J���Q��" , L"�Ă����邢����\n100���� ��������", L"�_�b�V�������邾����\n�Q�[�W���������ӂ���" , 0 , L"sprite/skillicon_17.dds",L"�z���g�E�j �X�R�V�f�X�K\n�I�g�N �f�X���l" },
	{ L"�n�K�l�m�J���_" , L"�Ă����邢����\n150���� ��������", L"�Ă��̂��܂� �������Ă�\n���ȂȂ��Ȃ�" , 0 , L"sprite/skillicon_18.dds" ,L"�J�����j �W���~���E �K\n�X�R�V �w���}�X�K..." },
	{ L"�J�~�J�[�o�g��" , L"��イ�����_�b�V����\n�{�X�Ƀg�h����5����������", L"����݂傤�� �͂₭�ւ邪\n���������Ƃ��ǂ�������+" , 0 , L"sprite/skillicon_19.dds",L"�M���M���m �o�g����\n�^�m�V�~�^�C �A�i�^�j\n�I�X�X���f�X" },
	{ L"�A�N��" , L"�n�[�h���[�h��1����\n�N���A���悤", L"���ǂ������ǂ������邪\n�����Ƃ��X�R�A1.5�΂�" , 0 , L"sprite/skillicon_20.dds",L"�_�b�V���f �C�h�E\n�X���m�K �_�C�W�f�X" },
	{ L"�L���E�t" , L"�n�[�h���[�h��3����\n�N���A���悤", L"�Q�[�W�������Ăɂӂ��Ȃ�\n�����Ƃ��X�R�A1.5�΂�" , 0 , L"sprite/skillicon_21.dds",L"�A�C�e���� �^�N�T��\n�A�c���i�N�e�n..." },
	{ L"�i�~�_" , L"�n�[�h���[�h��5����\n�N���A���悤", L"�ق� ���łȂ���\n�����Ƃ��X�R�A2.0�΂�" , 0 , L"sprite/skillicon_22.dds",L"�N���C �N���C\n���~�m �Z�J�C�f�X" },
	{ L"�L�R�T�[�`" , L"STAGE5��HARD��\nS�����N�� �����Ƃ����悤", L"�L�R�E�`���E��\n���[�_�[�ɂ���" , 50 , L"sprite/skillicon_23.dds",L"�A�m���V��\n�~�c�P�^�C �A�i�^�j\n�I�X�X���f�X" },
	{ L"�A�C�e�����[�_�[" , L"???????", L"�A�C�e�����˂�\n���[�_�[�ɂ���" , 0 , L"sprite/skillicon_24.dds",L"�R���f �X�L���K\n�_�V�z�E�_�C�I\n...�f�X�J�l�H" },

};
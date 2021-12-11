#include "Menu.h"

namespace Game {
	Menu::Menu() {
		button1 = Button(4);
		button1.SetGroup(1, 0);
		button1.SetButton(0, 155, 230, 155, 40);
		button1.SetButton(1, 155, 330, 155, 40);
		button1.SetButton(2, 155, 430, 155, 40);
		button1.SetButton(3, 905, 570, 210, 40);
		button2 = Button(2);
		button2.SetGroup(0, 1);
		button2.SetButton(0, 560, 400, 68, 40);
		button2.SetButton(1, 650, 400, 97, 40);
		button2.SetSelection(1);
	}

	int Menu::MakeSaveData(int i) {
		std::ofstream ofs;

		// �Z�[�u�f�[�^�쐬
		if (i < 0 || i > MAX_SAVE - 1) {
			return -1;
		}
		saveData[i].saveTime = time(NULL);
		saveData[i].saveCount++;
		saveData[i].index_place = index_place;
		for (int j = 0; j < FLAG_MAX; ++j) {
			saveData[i].flag[j] = flag[j];
		}

		// �Z�[�u�t�@�C���쐬
		try {
			js_saveFile[i] = json::object();
			js_saveFile[i]["header"]["soft"]["name"] = ansi_to_utf8(SOFT_NAME);
			js_saveFile[i]["header"]["soft"]["ver"] = ansi_to_utf8(SOFT_VER);
			js_saveFile[i]["header"]["game"]["name"] = ansi_to_utf8(strGameName);
			js_saveFile[i]["header"]["game"]["ver"] = ansi_to_utf8(strGameVersion);
			js_saveFile[i]["save"]["time"] = saveData[i].saveTime;
			js_saveFile[i]["save"]["count"] = saveData[i].saveCount;
			js_saveFile[i]["save"]["data"]["index_place"] = saveData[i].index_place;
			for (int j = 0; j < FLAG_MAX; ++j) {
				js_saveFile[i]["save"]["data"]["flag"][j] = saveData[i].flag[j];
			}
		}
		catch (...) {
			// �G���[�����������ɓ����H
			return -1;
		}

		// �t�@�C����������
		struct stat statBuf;
		if (stat("save", &statBuf) != 0) {
			if (_mkdir("Save") != 0) {
				return -1;
			}
		}
		ofs = std::ofstream("save/save" + std::to_string(i + 1) + ".json");
		if (ofs) {
			ofs << js_saveFile[i];
			ofs.close();
			return 0;
		}

		return -1;		// �t�@�C���o�͎��s
	}

	void Menu::Reset() {
		button1.SetSelection(0);
		button2.SetSelection(1);
		onTitle = false;
	}

	int Menu::Main() {
		int res = 0;

		// ���j���[�J�m�F
		if (onMenuAllow && !onMenu && GetSingleCancel()) {		// �I�����E���j���[�Ȃ��E�L�����Z���L�[
			// ���j���[�I�[�v��SE
			onMenu = true;
		}
		else if (onMenu && !onTitle && GetSingleCancel()) {	// ���j���[���E�^�C�g���߂�m�F�Ȃ��E�L�����Z���L�[
			PlaySoundMem(sh_cancel, DX_PLAYTYPE_BACK);
			onMenu = false;
		}
		else if (!onMenu) {
			return -1;						// ���������A���j���[�Ȃ��E�L�����Z���L�[�Ȃ�
		}

		// �`�揈��(���j���[�{��)
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 230);
		DrawBox(100, 100, 1180, 650, 0x007DDA, TRUE);
		DrawBoxAA(100.f, 100.f, 1180.f, 650.f, 0x004070, FALSE, 3.5f);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		// �I���{�b�N�X
		opt = button1.Main(onTitle);

		// �����`��
		DrawStringToHandle(560, 160, "�`�Z�[�u�`", 0xFFFFFF, font3);
		DrawStringToHandle(160, 240, "�E�Z�[�u�P", 0xFFFFFF, font3);
		DrawStringToHandle(160, 340, "�E�Z�[�u�Q", 0xFFFFFF, font3);
		DrawStringToHandle(160, 440, "�E�Z�[�u�R", 0xFFFFFF, font3);
		DrawStringToHandle(910, 580, "�^�C�g���ɖ߂�", 0xFFFFFF, font3);

		DrawLine(160, 550, 1120, 550, 0xFFFFFF);

		for (int i = 0; i < 3; ++i) {
			if (saveData[i].saveCount != 0) {
				struct tm local;
				localtime_s(&local, &saveData[i].saveTime);
				int year = local.tm_year + 1900;
				int month = local.tm_mon + 1;
				int day = local.tm_mday;
				int hour = local.tm_hour;
				int min = local.tm_min;
				char min2[3];
				if (min < 10) {
					sprintf_s(min2, 3, "0%d", min);
				}
				else {
					sprintf_s(min2, 3, "%d", min);
				}

				DrawFormatStringToHandle(160, 280 + 100 * i, 0xFFFFFF, font3, "�@�ŏI�Z�[�u�F%d�N%d��%d���@%d��%s���@�Z�[�u�񐔁F%d��",
					year, month, day, hour, min2, saveData[i].saveCount);
			}
		}

		if (onTitle) {
			DrawBox(WIDTH / 2 - 200, HEIGHT / 2 - 70, WIDTH / 2 + 200, HEIGHT / 2 + 130, 0xFFCC00, TRUE);

			opt_title = button2.GetSelection();

			color_t yes, no;
			if (opt_title == 0) {
				yes = 0xFF0000;
				no = 0x000000;
			}
			else {
				yes = 0x000000;
				no = 0xFF0000;
			}

			switch (button2.Main(false))
			{
			case 0:
				PlaySoundMem(sh_decide, DX_PLAYTYPE_BACK);
				res = 1;
				break;
			case 1:
				PlaySoundMem(sh_cancel, DX_PLAYTYPE_BACK);
				onTitle = false;
				button2.SetSelection(1);
				break;
			case -2:
				PlaySoundMem(sh_cancel, DX_PLAYTYPE_BACK);
				onTitle = false;
				button2.SetSelection(1);
				break;
			}

			DrawStringToHandle(475, 345, "�^�C�g���ɖ߂�܂����H", 0x000000, font3);
			DrawStringToHandle(565, 410, "�͂�", yes, font3);
			DrawStringToHandle(655, 410, "������", no, font3);
		}
		else {
			switch (opt)
			{
			case 0:
			case 1:
			case 2:
				if (MakeSaveData(opt) == 0) {
					PlaySoundMem(sh_success, DX_PLAYTYPE_BACK);
				}
				else {
					PlaySoundMem(sh_fail, DX_PLAYTYPE_BACK);
				}
				break;
			case 3:
				PlaySoundMem(sh_decide, DX_PLAYTYPE_BACK);
				onTitle = true;
				break;
			}
		}

		return res;
	}
}
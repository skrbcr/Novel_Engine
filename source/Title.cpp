#include "Title.h"

namespace Game {
	Title::Title(string_view strBackImgFile, string_view strBgmFile, double bgmVol, bool showVer) {
		gh_back = LoadGraph(strBackImgFile.data());
		if (gh_back == -1) {
			ErrorLog(ER_IMG_LOAD, strBackImgFile.data());
		}
		sh_bgm = LoadSoundMem(strBgmFile.data());
		if (sh_bgm == -1) {
			ErrorLog(ER_SND_LOAD, strBgmFile.data());
		}
		else {
			this->bgmVol = bgmVol;
		}

		showVerFlag = showVer;

		width_hajime = GetDrawStringWidthToHandle("�͂��߂���", static_cast<int>(strlen("�͂��߂���")), font6);
		width_tuduki = GetDrawStringWidthToHandle("�Â�����", static_cast<int>(strlen("�Â�����")), font6);

		button_title.SetGroup(1, 0);
		button_title.AddButton((WIDTH - width_hajime) / 2, 518, width_hajime, 50);
		button_title.AddButton((WIDTH - width_tuduki) / 2, 595, width_tuduki, 50);

		button_load.SetGroup(1, 0, 0xCCCCFF);
		button_load.AddButton(160, 230, 960, 85);
		button_load.AddButton(160, 330, 960, 85);
		button_load.AddButton(160, 430, 960, 85);
		button_load.AddButton(905, 570, GetDrawStringWidthToHandle("�^�C�g���ɖ߂�", static_cast<int>(strlen("�^�C�g���ɖ߂�")), font3) + 10, 40);
	}

	int Title::Main() {
		int res = 0;

		switch (nPage)
		{
		case 0:		// �N�����Ȃ�
			// �w�i
			DrawGraph(0, 0, gh_back, FALSE);

			if (fcounter == 0) {
				// �Z�[�u�f�[�^�ǂݍ���
				std::ifstream ifs;
				for (int i = 0; i < MAX_SAVE; ++i) {
					ifs = std::ifstream("save/save" + std::to_string(i + 1) + ".dat", std::ios::binary);
					if (ifs) {
						ifs.read(reinterpret_cast<char*>(&saveData[i]), sizeof(SaveData));
						ifs.close();
						//if (strcmp(saveData[i].strheader, GAME_HEADER) && strcmp(saveData[i].strgm, GAME_NAME)) {
						opt_title = 1;
						button_title.SetSelection(1);
						//}
						//else {
						//	saveData[i] = SaveData();
						//}
					}
				}
			}
			if (fcounter <= 30) {
				// ��ʉ��o
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255 - 255 * fcounter / 30.0));
				DrawBox(0, 0, WIDTH, HEIGHT, 0x000000, TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

				// ���o�I���EBGM�Đ��J�n
				if (fcounter == 30) {
					// BGM�J�n
					bgm.Play(sh_bgm, DX_PLAYTYPE_LOOP, bgmVol, TRUE);
					nPage = 1;
					fcounter = -1;
				}
			}
			break;
		case 1:		// �^�C�g�����
			// �`��
			DrawGraph(0, 0, gh_back, FALSE);

			// �͂��߂���E�Â�����
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
			DrawBox((WIDTH - 250) / 2, 500, (WIDTH + 250) / 2, 660, 0x999999, TRUE);
			DrawBoxAA((WIDTH - 250) / 2, 500, (WIDTH + 250) / 2, 660, 0xAAAAAA, FALSE, 2.f);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			button_title.Main(false);
			DrawStringToHandle((WIDTH - width_hajime) / 2, 528, "�͂��߂���", 0x000000, font6);
			DrawStringToHandle((WIDTH - width_tuduki) / 2, 605, "�Â�����", 0x000000, font6);

			// �o�[�W�������
			if (showVerFlag) {
				DrawStringToHandle(WIDTH - 20 - GetDrawStringWidthToHandle(strGameVersion.c_str(), static_cast<int>(strGameVersion.size()), font2),
					HEIGHT - 30, strGameVersion.c_str(), 0x000000, font2);
			}

			//DrawGraph(62, 92, gh_logo, TRUE);

			// �L�[����
			if (GetSingleUp() || GetSingleDown()) {
				PlaySoundMem(sh_cursor, DX_PLAYTYPE_BACK);
				if (opt_title == 0) {
					opt_title = 1;
				}
				else {
					opt_title = 0;
				}
			}
			if (GetSingleOk()) {
				PlaySoundMem(sh_decide, DX_PLAYTYPE_BACK);
				if (opt_title == 0) {		// �J�n�����J�n
					nPage = 3;
					fcounter = -1;
					bgm.SetEffect(BGM_effct::FADE_OUT, 120);
				}
				else {
					nPage = 2;
					fcounter = -1;
				}
			}
			break;
		case 2:		// ���[�h�I��
			// �w�i
			DrawGraph(0, 0, gh_back, FALSE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
			DrawBox(0, 0, WIDTH, HEIGHT, 0xFFFFFF, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			// �{�^������
			opt_load = button_load.Main(false);
			switch (opt_load)
			{
			case 0:
			case 1:
			case 2:
				if (saveData[opt_load].saveCount != 0) {
					PlaySoundMem(sh_decide, DX_PLAYTYPE_BACK);
					nPage = 4;
					fcounter = -1;
					bgm.SetEffect(BGM_effct::FADE_OUT, 120);
				}
				else {
					PlaySoundMem(sh_fail, DX_PLAYTYPE_BACK);
				}
				break;
			case 3:
			case -2:
				PlaySoundMem(sh_cancel, DX_PLAYTYPE_BACK);
				nPage = 1;
				fcounter = -1;
				break;
			}

			// �����`��
			DrawStringToHandle(430, 160, "�`���[�h����t�@�C����I���`", 0x000000, font3);
			DrawStringToHandle(160, 240, "�E�Z�[�u�P", 0x000000, font3);
			DrawStringToHandle(160, 340, "�E�Z�[�u�Q", 0x000000, font3);
			DrawStringToHandle(160, 440, "�E�Z�[�u�R", 0x000000, font3);
			DrawLine(160, 550, 1120, 550, 0x000000);
			DrawStringToHandle(910, 580, "�^�C�g���ɖ߂�", 0x000000, font3);

			for (int i = 0; i < 3; ++i) {
				if (saveData[i].saveCount != 0) {
					struct tm local;
					time_t timer = time(NULL);
					//localtime_s(&local, &timer);
					localtime_s(&local, &saveData[i].saveTime);
					int year = static_cast<long long>(local.tm_year) + 1900;
					int month = local.tm_mon + 1;
					int day = local.tm_mday;
					int hour = local.tm_hour;
					int min = local.tm_min;
					string strMin = "";
					//char min2[3];
					if (min < 10) {
						strMin = "0";
						strMin += std::to_string(min);
						//sprintf_s(min2, 3, "0%d", min);
					}
					else {
						strMin = std::to_string(min);
						//sprintf_s(min2, 3, "%d", min);
					}
					DrawFormatStringToHandle(160, 280 + 100 * i, 0x000000, font3, "�@�ŏI�Z�[�u�F%d�N%d��%d���@%d��%s���@�Z�[�u�񐔁F%d��", year, month, day, hour, strMin.c_str(), saveData[i].saveCount);
				}
			}
			break;
		case 3:		// �^�C�g�����Q�[��
			// �`��
			DrawGraph(0, 0, gh_back, FALSE);

			// �͂��߂���E�Â�����
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
			DrawBox((WIDTH - 250) / 2, 500, (WIDTH + 250) / 2, 660, 0x999999, TRUE);
			DrawBoxAA((WIDTH - 250) / 2, 500, (WIDTH + 250) / 2, 660, 0xAAAAAA, FALSE, 2.f);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			button_title.Main(true);
			DrawStringToHandle((WIDTH - width_hajime) / 2, 528, "�͂��߂���", 0x000000, font6);
			DrawStringToHandle((WIDTH - width_tuduki) / 2, 605, "�Â�����", 0x000000, font6);

			// �o�[�W�������
			if (showVerFlag) {
				DrawStringToHandle(WIDTH - 20 - GetDrawStringWidthToHandle(strGameVersion.c_str(), static_cast<int>(strGameVersion.size()), font2),
					HEIGHT - 30, strGameVersion.c_str(), 0x000000, font2);
			}

			// ���o
			if (fcounter < 90) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255.0 * fcounter / 90.0));
				DrawBox(0, 0, WIDTH, HEIGHT, 0x000000, TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				fcounter++;
			}
			else if (fcounter < 150) {
				DrawBox(0, 0, WIDTH, HEIGHT, 0x000000, TRUE);
			}
			else {
				DrawBox(0, 0, WIDTH, HEIGHT, 0x000000, TRUE);
				res = 1;
			}
			break;
		case 4:		// ���[�h���Q�[��
			// �w�i
			DrawGraph(0, 0, gh_back, FALSE);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
			DrawBox(0, 0, WIDTH, HEIGHT, 0xFFFFFF, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			// �{�^��
			button_load.Main(true);

			// �����`��
			DrawStringToHandle(430, 160, "�`���[�h����t�@�C����I���`", 0x000000, font3);
			DrawStringToHandle(160, 240, "�E�Z�[�u�P", 0x000000, font3);
			DrawStringToHandle(160, 340, "�E�Z�[�u�Q", 0x000000, font3);
			DrawStringToHandle(160, 440, "�E�Z�[�u�R", 0x000000, font3);
			DrawLine(160, 550, 1120, 550, 0x000000);
			DrawStringToHandle(910, 580, "�^�C�g���ɖ߂�", 0x000000, font3);
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
					if (min < 10) sprintf_s(min2, 3, "0%d", min);
					else sprintf_s(min2, 3, "%d", min);

					DrawFormatStringToHandle(160, 280 + 100 * i, 0x000000, font3, "�@�ŏI�Z�[�u�F%d�N%d��%d���@%d��%s���@�Z�[�u�񐔁F%d��", year, month, day, hour, min2, saveData[i].saveCount);
				}
			}

			// ���o
			if (fcounter < 90) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255.0 * fcounter / 90.0));
				DrawBox(0, 0, WIDTH, HEIGHT, 0x000000, TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			else if (fcounter < 150) {
				DrawBox(0, 0, WIDTH, HEIGHT, 0x000000, TRUE);
			}
			else {
				DrawBox(0, 0, WIDTH, HEIGHT, 0x000000, TRUE);
				res = 10 + opt_load;
			}
			break;
		default:
			break;
		}

		fcounter++;

		return res;
	}
}
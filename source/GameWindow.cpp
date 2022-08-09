#include "GameWindow.h"

namespace Game {
	GameWindow::GameWindow() {
		/* �E�B���h�E�ݒ� */
		SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);	// DxLib�֐��̕���������Ɏg�p���镶���R�[�h�̐ݒ�
		LoadConfig();
		SetMainWindowText(strGameName.c_str());	// �^�C�g���e�L�X�g�̐ݒ�
		SetMainWindowClassName(SOFT_NAME);		// �E�B���h�E�N���X����o�^
		SetAlwaysRunFlag(TRUE);							// ��A�N�e�B�u�������s
		//SetWindowIconID(1);							// �A�C�R���i.ico�t�@�C����icon.rc���K�v�B������icon.rc�Őݒ肵���C�ӂ̃A�C�R��ID�j
		//SetOutApplicationLogValidFlag(FALSE);			// ���O���o�͂��Ȃ�
		ChangeWindowMode(TRUE);							// �t���X�N���[���ɂ��Ȃ�
		SetGraphMode(1280, 720, 32);					// �E�B���h�E�T�C�Y�ƐF�r�b�g���̎w��
		SetWindowSizeExtendRate(1.0);					// ���ۂɕ\������E�B���h�E�T�C�Y�ɕύX

		if (DxLib_Init() == -1) {
			throw runtime_error("Error: Failed to initialize DxLib.");
		}
		SetDrawScreen(DX_SCREEN_BACK);				// �_�u���o�b�t�@�̎g�p

		MakeHandles();

		vfont = vector<Font>();
	}
	GameWindow::~GameWindow() {
		DeleteHandles();
		DxLib_End();
	}
	void GameWindow::SetKey(const char* key) {
		okPress = cancelPress = singleOk = singleCancel = skipPress = false;
		upPress = downPress = rightPress = leftPress = singleUp = singleDown = singleRight = singleLeft = autoSkip = false;
		if (key[KEY_INPUT_RETURN] || key[KEY_INPUT_Z] || key[KEY_INPUT_SPACE]) okPress = true;
		if (key[KEY_INPUT_ESCAPE] || key[KEY_INPUT_X]) cancelPress = true;
		if (key[KEY_INPUT_UP]) upPress = true;
		if (key[KEY_INPUT_DOWN]) downPress = true;
		if (key[KEY_INPUT_RIGHT]) rightPress = true;
		if (key[KEY_INPUT_LEFT]) leftPress = true;
		if (key[KEY_INPUT_S]) skipPress = true;

		if (okPress && singleOkFlag) {
			singleOk = true;
			singleOkFlag = false;
		}
		else if (!okPress && !singleOkFlag) singleOkFlag = true;
		if (cancelPress && singleCancelFlag) {
			singleCancel = true;
			singleCancelFlag = false;
		}
		else if (!cancelPress && !singleCancelFlag) singleCancelFlag = true;
		if (upPress && singleUpFlag) {
			singleUp = true;
			singleUpFlag = false;
		}
		else if (!upPress && !singleUpFlag) singleUpFlag = true;
		if (downPress && singleDownFlag) {
			singleDown = true;
			singleDownFlag = false;
		}
		else if (!downPress && !singleDownFlag) singleDownFlag = true;
		if (rightPress && singleRightFlag) {
			singleRight = true;
			singleRightFlag = false;
		}
		else if (!rightPress && !singleRightFlag) singleRightFlag = true;
		if (leftPress && singleLeftFlag) {
			singleLeft = true;
			singleLeftFlag = false;
		}
		else if (!leftPress && !singleLeftFlag) singleLeftFlag = true;
		if (skipPress && autoSkipCount % 4 == 0) {
			autoSkip = true;
			autoSkipCount++;
		}
		else if (skipPress) autoSkipCount++;
		else autoSkipCount = 0;
	}
	bool GameWindow::GetSingleOk() {
		return singleOk;
	}
	bool GameWindow::GetSingleCancel() {
		return singleCancel;
	}
	bool GameWindow::GetSingleUp() {
		return singleUp;
	}
	bool GameWindow::GetSingleDown() {
		return singleDown;
	}
	bool GameWindow::GetSingleRight() {
		return singleRight;
	}
	bool GameWindow::GetSingleLeft() {
		return singleLeft;
	}
	bool GameWindow::GetAutoSkip() {
		return autoSkip;
	}
	void GameWindow::LoadConfig() {
		ifstream ifs = ifstream("data/data/config.json");
		if (ifs) {
			try {
				ifs >> js_cfg;
			}
			catch (...) {
				throw runtime_error("Error: Cannot oepn \"data/data/config.json\"");
			}
		}
		else {
			throw runtime_error("Error: Not found \"data/data/config.json\"");
		}

		// �Q�[���^�C�g���̐ݒ�
		if (js_cfg["game"].is_object()) {
			if (js_cfg["game"]["title"].is_string()) {
				strGameName = js_cfg["game"]["title"];
			}
			if (js_cfg["game"]["version"].is_string()) {
				strGameVersion = js_cfg["game"]["version"];
			}
		}
	}
	void GameWindow::MakeHandles() {
		SetFontCharCodeFormat(DX_CHARCODEFORMAT_UTF8);
		font1 = CreateFontToHandle((const char*)u8"������", 24, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
		font2 = CreateFontToHandle((const char*)u8"������", 18, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
		font3 = CreateFontToHandle((const char*)u8"������", 20, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
		font4 = CreateFontToHandle((const char*)u8"������", 48, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
		font5 = CreateFontToHandle((const char*)u8"������", 12, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
		font6 = CreateFontToHandle((const char*)u8"������", 30, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
	}
	void GameWindow::DeleteHandles() {
		DeleteFontToHandle(font1);
		DeleteFontToHandle(font2);
		DeleteFontToHandle(font3);
		DeleteFontToHandle(font4);
		DeleteFontToHandle(font5);

		for (auto& f : vfont) {
			DeleteFontToHandle(f.fh);
		}
	}
}

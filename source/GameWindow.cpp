#include "GameWindow.h"

namespace Game {
	GameWindow::GameWindow() {
		/* ウィンドウ設定 */
		SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);	// DxLib関数の文字列引数に使用する文字コードの設定
		LoadConfig();
		SetMainWindowText(strGameName.c_str());	// タイトルテキストの設定
		SetMainWindowClassName(SOFT_NAME);		// ウィンドウクラス名を登録
		SetAlwaysRunFlag(TRUE);							// 非アクティブ時も実行
		//SetWindowIconID(1);							// アイコン（.icoファイルとicon.rcが必要。引数はicon.rcで設定した任意のアイコンID）
		//SetOutApplicationLogValidFlag(FALSE);			// ログを出力しない
		ChangeWindowMode(TRUE);							// フルスクリーンにしない
		SetGraphMode(1280, 720, 32);					// ウィンドウサイズと色ビット数の指定
		SetWindowSizeExtendRate(1.0);					// 実際に表示するウィンドウサイズに変更

		if (DxLib_Init() == -1) {
			throw runtime_error("Error: Failed to initialize DxLib.");
		}
		SetDrawScreen(DX_SCREEN_BACK);				// ダブルバッファの使用

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

		// ゲームタイトルの設定
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
		font1 = CreateFontToHandle((const char*)u8"游明朝", 24, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
		font2 = CreateFontToHandle((const char*)u8"游明朝", 18, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
		font3 = CreateFontToHandle((const char*)u8"游明朝", 20, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
		font4 = CreateFontToHandle((const char*)u8"游明朝", 48, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
		font5 = CreateFontToHandle((const char*)u8"游明朝", 12, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
		font6 = CreateFontToHandle((const char*)u8"游明朝", 30, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
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

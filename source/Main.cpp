// skrbcr/Novel_Engine（https://github.com/skrbcr/Novel_Engine）
// DXライブラリ使用のノベルゲームエンジン？のアルファ版 ver.0.2.0（予定）
// 
// 配布ソースコードの一部に、以下のライブラリを含みます
// 著作権表示の詳細は、"./nlohmann/json.hpp" や "../README.md" をご覧ください
// ・nlohmann/json（ https://github.com/nlohmann/json ）version 3.9.1
// 
// また、本ソフトは DXライブラリ（Ver3.23 https://dxlib.xsrv.jp/ ）も使用していますが
// 配布ソースコードには含んでおりません
// ですから、ビルドされる方は、ご自身でのダウンロードや設定等をお願いいたします
// 

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include "DxLib.h"
#include "nlohmann/json.hpp"
#include "Global.h"
#include "Menu.h"
#include "Place.h"
#include "Choice.h"
#include "Button.h"
#include "BGM.h"
#include "Title.h"

namespace Game {
	static Title title;		// タイトル

	// 各種ハンドルの作成
	static void MakeHandles();

	// 各種ハンドルの削除
	static void DeleteHandles();

	// Config.jsonの読み込み・ウィンドウの設定
	static void LoadConfig();

	// Config.json の適用
	static void SetConfig();

	// ゲームのメインループ処理
	static void GameMain();

	// ゲームの初期化。本編移行前に行う
	static void GameInit();

	// ゲーム本編
	static int GamePlay();
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	/* デバッグ用（メモリリーク検知） */
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	//int* a = new int();		// メモリリークのサンプル（deleteを呼ばない）

	/* ウィンドウ設定 */
	SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);	// DxLib関数の文字列引数に使用する文字コードの設定
	Game::LoadConfig();
	SetMainWindowText(Game::strGameName.c_str());	// タイトルテキストの設定
	SetMainWindowClassName(Game::SOFT_NAME);		// ウィンドウクラス名を登録
	SetAlwaysRunFlag(TRUE);							// 非アクティブ時も実行
	//SetWindowIconID(1);							// アイコン（.icoファイルとicon.rcが必要。引数はicon.rcで設定した任意のアイコンID）
	//SetOutApplicationLogValidFlag(FALSE);			// ログを出力しない
	ChangeWindowMode(TRUE);							// フルスクリーンにしない
	SetGraphMode(1280, 720, 32);					// ウィンドウサイズと色ビット数の指定
	SetWindowSizeExtendRate(1.0);					// 実際に表示するウィンドウサイズに変更

	/* 初期化 */
	if (DxLib_Init() == -1) {
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);				// ダブルバッファの使用

	char key[256];								// キー入力配列

	Game::MakeHandles();
	Game::SetConfig();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll(key) == 0) {
		Game::SetKey(key);
		Game::GameMain();
	}

	Game::DeleteHandles();

	/* 終了処理 */
	DxLib_End();

	return 0;
}

namespace Game {
	static int status = 0;				// ステータス番号
	static int counter = 0;				// フレームカウンタ
	static int snum = 0;				// シーン管理番号
	static int resEvent = 0;			// イベント返り値
	static int resEvDet = 0;			// イベント返り値詳細
	static bool playFinFlag = false;	// ゲーム本編終了フラグ

	static Menu menu;			// メニュー
	static Place place;			// 場所インスタンス

	static json js_cfg = json();		// Config.json

	void MakeHandles() {
		// フォント作成
		SetFontCharCodeFormat(DX_CHARCODEFORMAT_UTF8);
		font1 = CreateFontToHandle((const char*)u8"游明朝", 24, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
		font2 = CreateFontToHandle((const char*)u8"游明朝", 18, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
		font3 = CreateFontToHandle((const char*)u8"游明朝", 20, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
		font4 = CreateFontToHandle((const char*)u8"游明朝", 48, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
		font5 = CreateFontToHandle((const char*)u8"游明朝", 12, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
		font6 = CreateFontToHandle((const char*)u8"游明朝", 30, -1, DX_FONTTYPE_ANTIALIASING_16X16, DX_CHARCODEFORMAT_UTF8);
	}

	void DeleteHandles() {
		DeleteFontToHandle(font1);
		DeleteFontToHandle(font2);
		DeleteFontToHandle(font3);
		DeleteFontToHandle(font4);
		DeleteFontToHandle(font5);
	}

	void LoadConfig() {
		ifstream ifs = ifstream("data/data/config.json");
		if (ifs) {
			try {
				ifs >> js_cfg;
			}
			catch (...) {
				ErrorLog(ER_JSON_SYNTAX, "data/data/config.json");
				return;
			}
		}
		else {
			ErrorLog(ER_JSON_OPEN, "data/data/config.json");
			return;
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

	void SetConfig() {
		// システムSEの読み込み
		if (js_cfg["se"].is_object()) {
			se.ApplayConfig(js_cfg["se"]);
		}
		// ダイアログ
		if (js_cfg["dialog"].is_object()) {
			Dialog::ApplyConfig(js_cfg["dialog"]);
		}
		// キャラクター画像
		if (js_cfg["chara"].is_object()) {
			if (js_cfg["chara"]["img"].is_array()) {
				size_t n = js_cfg["chara"]["img"].size();
				place.InitChara(n);
				for (size_t i = 0; i < n; ++i) {
					if (js_cfg["chara"]["img"][i].is_array() && js_cfg["chara"]["img"][i][0].is_string()
						&& js_cfg["chara"]["img"][i][1].is_number() && js_cfg["chara"]["img"][i][2].is_number()) {
						place.SetChara(i, js_cfg["chara"]["img"][i][0],
							js_cfg["chara"]["img"][i][1], js_cfg["chara"]["img"][i][2]);
					}
				}
			}
		}
		// タイトル画面の設定
		if (js_cfg["title"].is_object()) {
			title.ApplyConfig(js_cfg["title"]);
		}
	}

	void GameMain() {
		switch (status)
		{
		case 0:					// タイトル画面
		{
			int i = title.Main();
			if (i == 1) {
				GameInit();
				place.SetGeneral();
				status = 10;
			}
			else if (i >= 10 && i <= 12) {
				i -= 10;
				GameInit();
				index_place = saveData[i].index_place;
				for (int k = 0; k < FLAG_MAX; ++k) {
					flag[k] = saveData[i].flag[k];
				}
				place.SetGeneral();
				status = 10;
			}
		}
		break;
		case 10:				// ゲーム本編
			if (GamePlay() == 1) {
				counter = -1;
				status = 0;
				title.Init();
			}
			break;
		}

		bgm.Main();

		counter++;
	}

	void GameInit() {
		snum = 0;
		for (int i = 0; i < FLAG_MAX; ++i) {
			flag[i] = false;
		}
		place.Init();
		//choice = Choice();
		menu = Menu();
		index_place = 0;

		onMenu = false;
		onEvent = false;
	}

	int GamePlay() {
		// メインの処理
		place.Main(resEvent, resEvDet);

		// ゲーム終了
		if (flag[1]) {
			snum = 0;
			playFinFlag = true;
		}

		// メニュー
		switch (menu.Main())
		{
		case 1:
			playFinFlag = true;
			bgm.SetEffect(BGM_effct::FADE_OUT, 20);
		}

		// 終了フラグが立っているとき、お片付け！
		if (playFinFlag) {
			playFinFlag = false;
			return 1;
		}

		return 0;
	}
}
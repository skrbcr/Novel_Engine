// skrbcr/Novel_Engine ver.0.1.0（https://github.com/skrbcr/Novel_Engine）
// DXライブラリ使用のノベルゲームエンジン？のアルファ版
// 
// 配布ソースコードの一部に、以下のライブラリを含みます
// 著作権表示等の詳細は、README.mdをご覧ください
// ・nlohmann/json（ https://github.com/nlohmann/json ）version 3.9.1
// ・javacommons/strconv（ https://github.com/javacommons/strconv ）v1.8.10
// 
// また、本ソフトは DXライブラリ（Ver3.23 https://dxlib.xsrv.jp/ ）も使用していますが
// 配布ソースコードには含んでおりませんので、ビルドされる方は、各位でのダウンロードや設定等をお願いいたします
// 

#include "DxLib.h"
#include "nlohmann/json.hpp"
#include "javacommons/strconv.h"
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

	// Config.json の読み込み・タイトル画面も設定
	static void LoadConfig();

	// ゲームのメインループ処理
	static void GameMain();

	// ゲームの初期化。本編移行前に行う
	static void GameInit();

	// ゲーム本編
	static int GamePlay();
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	/* ウィンドウ設定 */
	SetWindowText("Novel Game");				// ウィンドウ名
	SetMainWindowClassName(Game::GAME_CLASS);	// ウィンドウクラス名を登録
	SetAlwaysRunFlag(TRUE);						// 非アクティブ時も実行
	//SetWindowIconID(1);							// アイコン（.icoファイルとicon.rcが必要。引数はicon.rcで設定した任意のアイコンID）
	//SetOutApplicationLogValidFlag(FALSE);		// ログを出力しない
	ChangeWindowMode(TRUE);						// フルスクリーンにしない
	SetGraphMode(1280, 720, 32);				// ウィンドウサイズと色ビット数の指定
	SetWindowSizeExtendRate(1.0);				// 実際に表示するウィンドウサイズに変更

	/* 初期化 */
	if (DxLib_Init() == -1) {
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);				// ダブルバッファの使用

	char key[256];								// キー入力配列

	Game::MakeHandles();

	Game::effect = Game::Effect();
	Game::bgm = Game::BGM();

	Game::LoadConfig();

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
	static Choice choice;		// 選択インスタンス

	void MakeHandles() {
		// フォント作成
		font1 = CreateFontToHandle("游明朝", 24, -1, DX_FONTTYPE_ANTIALIASING_16X16);
		font2 = CreateFontToHandle("游明朝", 18, -1, DX_FONTTYPE_ANTIALIASING_16X16);
		font3 = CreateFontToHandle("游明朝", 20, -1, DX_FONTTYPE_ANTIALIASING_16X16);
		font4 = CreateFontToHandle("游明朝", 48, -1, DX_FONTTYPE_ANTIALIASING_16X16);
		font5 = CreateFontToHandle("游明朝", 12, -1, DX_FONTTYPE_ANTIALIASING_16X16);
		font6 = CreateFontToHandle("游明朝", 30, -1, DX_FONTTYPE_ANTIALIASING_16X16);

		// ダイアログボックス画像読み込み
		Dialog::gh_box = LoadGraph("data/picture/[自作]dialog.png");
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
		json js = json();
		if (ifs) {
			try {
				ifs >> js;
			}
			catch (...) {
				ErrorLog(ER_JSON_SYNTAX, "data/data/config.json");
				return;
			}
			ifs.close();
		}
		else {
			ErrorLog(ER_JSON_OPEN, "data/data/config.json");
			return;
		}
		// ゲームタイトルの設定
		if (js["game"].is_object()) {
			if (js["game"]["name"].is_string()) {
				strGameName = utf8_to_ansi(js["game"]["name"]);
				SetWindowTextA(strGameName.c_str());
			}
			if (js["game"]["version"].is_string()) {
				strGameVersion = utf8_to_ansi(js["game"]["version"]);
			}
		}
		// システムSEの読み込み
		if (js["se"].is_object()) {
			if (js["se"]["cursor"].is_string()) {
				sh_cursor = LoadSoundMem(utf8_to_ansi(js["se"]["cursor"]).c_str());
			}
			if (js["se"]["decide"].is_string()) {
				sh_decide = LoadSoundMem(utf8_to_ansi(js["se"]["decide"]).c_str());
			}
			if (js["se"]["cancel"].is_string()) {
				sh_cancel = LoadSoundMem(utf8_to_ansi(js["se"]["cancel"]).c_str());
			}
			if (js["se"]["success"].is_string()) {
				sh_success = LoadSoundMem(utf8_to_ansi(js["se"]["success"]).c_str());
			}
			if (js["se"]["fail"].is_string()) {
				sh_fail = LoadSoundMem(utf8_to_ansi(js["se"]["fail"]).c_str());
			}
		}

		// タイトル画面の設定
		string strBack = "";
		string strBgm = "";
		double bgmVol = 1.0;
		bool showVer = false;
		if (js["title"].is_object()) {
			if (js["title"]["back"].is_array()) {
				if (js["title"]["back"][0].is_string()) {
					strBack = js["title"]["back"][0];
					strBack = utf8_to_ansi(strBack);
				}
			}
			if (js["title"]["bgm"].is_array()) {
				if (js["title"]["bgm"][0].is_string()) {
					strBgm = js["title"]["bgm"][0];
					strBgm = utf8_to_ansi(strBgm);
				}
				if (js["title"]["bgm"][1].is_number()) {
					bgmVol = js["title"]["bgm"][1];
				}
			}
			if (js["title"]["version"].is_boolean()) {
				showVer = js["title"]["version"];
			}
		}
		title = Title(strBack, strBgm, bgmVol, showVer);
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
		place = Place();
		choice = Choice();
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
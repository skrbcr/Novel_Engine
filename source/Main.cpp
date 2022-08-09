// skrbcr/Novel_Engine（https://github.com/skrbcr/Novel_Engine）
// DXライブラリ使用のノベルゲームエンジン？のアルファ版 ver.0.2.0
// 
// 配布ソースコードの一部に、以下のライブラリを含みます
// 著作権表示の詳細は、"./nlohmann/json.hpp" や "../README.md" をご覧ください
// ・nlohmann/json（https://github.com/nlohmann/json）version 3.9.1
// 
// また、本ソフトは DXライブラリ（Ver3.23 https://dxlib.xsrv.jp/）も使用していますが
// 配布ソースコードには含んでおりません
// ですから、ビルドされる方は、ご自身でのダウンロードや設定等をお願いいたします
// 

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include "DxLib.h"
#include "Global.h"
#include "GameWindow.h"
#include "GameControl.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	/* デバッグ用（メモリリーク検知） */
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	//int* a = new int();		// メモリリークのサンプル（deleteを呼ばない）
	
	try {
		//Game::gw = Game::GameWindow();
		Game::GameControl gc = Game::GameControl();
		char key[256];		// キー入力配列

		while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll(key) == 0) {
			Game::gw.SetKey(key);
			gc.GameMain();
		}
	}
	catch (const std::exception&) {
		return -1;		// あとでエラー処理を書いておく
	}

	return 0;
}

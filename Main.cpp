#include "DxLib.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	/* ウィンドウ設定 */
	SetWindowText("");				// ウィンドウ名
	SetAlwaysRunFlag(TRUE);						// 非アクティブ時も実行
	//SetWindowIconID();							// アイコン（.icoファイルとicon.rcが必要。引数はicon.rcで設定した任意のアイコンID）
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

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll(key) == 0) {
		
	}

	/* 終了処理 */
	DxLib_End();

	return 0;
}

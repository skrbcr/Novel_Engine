#pragma once
#include "nlohmann/json.hpp"
#include "Global.h"
#include "Title.h"
#include "Menu.h"
#include "Place.h"
#include "Choice.h"
#include "Button.h"
#include "BGM.h"

using std::runtime_error;

namespace Game {
	class GameWindow {
	private:
		json js_cfg = json();	// Config.json
		Title title;			// タイトル画面
		Menu menu;				// メニュー
		Place place;			// 場所インスタンス

		int status = 0;				// ステータス番号
		int counter = 0;			// フレームカウンタ
		int snum = 0;				// シーン管理番号
		int resEvent = 0;			// イベント返り値
		int resEvDet = 0;			// イベント返り値詳細
		bool playFinFlag = false;	// ゲーム本編終了フラグ

	public:
		GameWindow();
		~GameWindow();
		void GameMain();			// ゲームのメインループ処理
		int GamePlay();				// ゲーム本編

	private:
		void GameInit();			// ゲームの初期化。本編移行前に行う
		void MakeHandles();			// 各種ハンドルの作成
		void DeleteHandles();		// 各種ハンドルの削除
		void LoadConfig();			// Config.jsonの読み込み・ウィンドウの設定
		void SetConfig();			// Config.json の適用
	};
}

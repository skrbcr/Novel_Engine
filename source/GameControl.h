#pragma once
#include "GameWindow.h"
#include "Title.h"
#include "Menu.h"
#include "Place.h"
#include "Choice.h"
#include "Button.h"
#include "BGM.h"

namespace Game {
	class GameControl {
	private:
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
		GameControl();
		void GameInit();			// ゲームの初期化。本編移行前に行う
		void GameMain();			// ゲームのメインループ処理
		int GamePlay();				// ゲーム本編
		void SetConfig();			// Config.json の適用
	};
}

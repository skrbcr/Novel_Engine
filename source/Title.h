#pragma once
#include <fstream>
#include <map>
#include "DxLib.h"
#include "Global.h"
#include "Button.h"

namespace Game {
	class Title
	{
	private:
		int nPage = 0;			// タイトルのページ番号
		int fcounter = 0;		// フレームカウンタ

		int gh_back = 0;		// 背景画像 グラフィックハンドル
		int width_hajime = 0;	// "はじめから"の幅
		int width_tuduki = 0;	// "つづきから"の幅
		bool showVerFlag = false;		// バージョン情報をタイトル画面に表示するか

		int sh_bgm = 0;			// BGM サウンドハンドル
		double bgmVol = 1.0;	// BGM 音量
		std::map<const char*, int> mapSe;
		
		Button button_title = Button();		// タイトル画面のボタン
		Button button_load = Button();		// ロード画面のボタン
		int opt_title = 0;		// タイトル画面のボタンの選択中番号
		int opt_load = 0;		// ロード画面のボタンの選択番号

	public:
		Title() {

		}

		~Title() {

		}

		/// <summary>
		/// 設定の適用
		/// </summary>
		/// <param name="js">json["title"]</param>
		void ApplyConfig(json& js);

		/// <summary>
		/// 
		/// </summary>
		/// <returns>0: 通常 1: ゲーム本編へ 10~: 10引いたindexのセーブを読み込んで本編へ</returns>
		int Main();

		void Init() {
			nPage = 0;
			fcounter = 0;
		}
	};
}

// メモ・nPage
// 0: 起動時
// 1: タイトル
// 2: ロード選択
// 3: タイトル→ゲーム開始
// 4: ロード→ゲーム開始

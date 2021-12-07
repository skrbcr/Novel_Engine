#pragma once
#include <string>
#include <ctime>
#include <direct.h>
#include <fstream>
#include "nlohmann/json.hpp"
#include "javacommons/strconv.h"
#include "Global.h"
#include "Button.h"

using std::string;
using nlohmann::json;

namespace Game {
	class Menu
	{
	private:
		int opt = 0;
		int opt_title = 0;
		bool onTitle = false;

		Button button1 = Button();
		Button button2 = Button();


	private:
		/// <summary>
		/// セーブファイル作成・出力
		/// </summary>
		/// <param name="i">ファイル番号</param>
		/// <returns>0:成功 -1:失敗</returns>
		int MakeSaveData(int i);


	public:
		Menu();


		~Menu() {

		}

		/// <summary>
		/// 選択番号・フレームカウンタ・フラグをリセット
		/// </summary>
		void Reset();

		/// <summary>
		/// メニュー本体
		/// </summary>
		/// <returns>-1:メニューなし 0:メニュー・通常 1:本編終了の合図</returns>
		int Main();
	};
}

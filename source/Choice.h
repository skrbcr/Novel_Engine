#pragma once
#include <string>
//#include <string_view>
#include <vector>
#include "Global.h"
#include "Dialog.h"
#include "Button.h"

using std::string;
using std::vector;

namespace Game {
	class Choice
	{
	private:
		vector<string> strOptList;			// 選択肢文字列配列
		Button button = Button();
		int num = 0;				// 選択肢個数
		int count = 0;				// 現在選択番号
		int width = 0;				// 選択ボックス幅

	public:

		Choice() {

		}

		~Choice() {

		}

		/// <summary>
		/// メイン関数
		/// </summary>
		/// <returns>-1:通常 0~:ボタン決定</returns>
		int Main();

		/// <summary>
		/// 設定
		/// </summary>
		/// <param name="strList">選択肢文字列</param>
		void Set(vector<string>& strList);
	};
}


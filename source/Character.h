#pragma once
#include <vector>
#include <string>
#include "Global.h"

using std::vector;
using std::string_view;

namespace Game {
	class Character
	{
	private:
		int gh_body = 0;		// body グラフィックハンドル
		int gh_face = 0;		// face グラフィックハンドル

	public:
		static vector<vector<int>> vpos;		// 画像配置座標

	public:
		Character() {

		}

		~Character() {

		}

		/// <summary>
		/// body 画像を設定
		/// </summary>
		/// <param name="gh"></param>
		/// <param name="strPos"></param>
		void SetBody(int gh, string_view strPos);

	};
}


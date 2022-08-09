#include "Choice.h"

namespace Game {
	int Choice::iSeDecide = 0;
	void Choice::ApplyConfig(json& js) {
		if (js["se"].is_object()) {
			if (js["se"]["decide"].is_number_integer()) {
				iSeDecide = js["se"]["decide"];
			}
		}
	}
	int Choice::Main() {
		// 背景
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 245);
		DrawBox(Dialog::msgwnd_left + Dialog::msgwnd_width - width - 40, Dialog::msgwnd_top - 65 - 50 * num,
			Dialog::msgwnd_left + Dialog::msgwnd_width , Dialog::msgwnd_top - 20, 0x007DDA, TRUE);
		DrawBoxAA(static_cast<float>(Dialog::msgwnd_left + Dialog::msgwnd_width - width - 40), static_cast<float>(Dialog::msgwnd_top - 65 - 50 * num),
			static_cast<float>(Dialog::msgwnd_left + Dialog::msgwnd_width), static_cast<float>(Dialog::msgwnd_top - 20), 0x004070, FALSE, 3.5f);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		// 選択肢表示
		for (int i = 0; i < num; ++i) {
			DrawStringToHandle(Dialog::msgwnd_left + Dialog::msgwnd_width - width - 15, Dialog::msgwnd_top - 30 - 50 * (num - i),
				strOptList[i].data(), 0xFFFFFF, gw.font1);
		}

		count = button.Main(onMenu);
		if (count >= 0) {
			se.Play(iSeDecide);
		}

		return count;
	}

	void Choice::Set(vector<string>& strList) {
		num = static_cast<int>(strList.size());
		count = 0;
		width = 0;
		strOptList = vector<string>(num);

		// 選択肢文字列を取得
		int width_tmp = 0;
		for (int i = 0; i < num; ++i) {
			strOptList[i] = strList[i];
			width_tmp = GetDrawStringWidthToHandle(strOptList[i].c_str(), static_cast<int>(strOptList[i].size()), gw.font1);
			if (width_tmp > width) {
				width = width_tmp;
			}
		}

		// 最長文字列に余白ができるように
		width += 10;

		// ボタンを設定
		button = Button(num);
		button.SetGroup(1, 0);
		for (int i = 0; i < num; ++i) {
			button.SetButton(i, Dialog::msgwnd_left + Dialog::msgwnd_width - width - 20, Dialog::msgwnd_top - 40 - 50 * (num - i), width, 45);
		}
	}
}
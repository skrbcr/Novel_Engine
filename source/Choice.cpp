#include "Choice.h"

namespace Game {
	int Choice::Main() {
		// 背景
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 245);
		DrawBox(DLGBOX_LEFT + DLGBOX_WIDTH - width - 40, DLGBOX_TOP - 65 - 50 * num,
			DLGBOX_LEFT + DLGBOX_WIDTH, DLGBOX_TOP - 20, 0x007DDA, TRUE);
		DrawBoxAA(static_cast<float>(DLGBOX_LEFT + DLGBOX_WIDTH - width - 40), static_cast<float>(DLGBOX_TOP - 65 - 50 * num),
			static_cast<float>(DLGBOX_LEFT + DLGBOX_WIDTH), static_cast<float>(DLGBOX_TOP - 20), 0x004070, FALSE, 3.5f);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		// 選択肢表示
		for (int i = 0; i < num; ++i) {
			DrawStringToHandle(DLGBOX_LEFT + DLGBOX_WIDTH - width - 15, DLGBOX_TOP - 30 - 50 * (num - i),
				strOptList[i].data(), 0xFFFFFF, font1);
		}

		count = button.Main(onMenu);
		if (count >= 0) {
			PlaySoundMem(sh_decide, DX_PLAYTYPE_BACK, TRUE);
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
			width_tmp = GetDrawStringWidthToHandle(strOptList[i].c_str(), static_cast<int>(strOptList[i].size()), font1);
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
			button.SetButton(i, DLGBOX_LEFT + DLGBOX_WIDTH - width - 20, DLGBOX_TOP - 40 - 50 * (num - i), width, 45);
		}
	}
}
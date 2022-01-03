#include "Dialog.h"

namespace Game {
	int Dialog::gh_box = 0;
	int Dialog::msgwnd_left = 0;
	int Dialog::msgwnd_top = 0;
	int Dialog::msgwnd_width = 0;
	int Dialog::msgwnd_height = 0;
	int Dialog::msgspk_left = 0;
	int Dialog::msgspk_top = 0;
	int Dialog::msgtxt_left = 0;
	int Dialog::msgtxt_top = 0;

	void Dialog::Set(string_view speaker, string_view content) {
		strSpeaker = speaker;
		strContent = content;
		nLenSpeaker = speaker.size();
		status = 0;
		strContDisp = "";
		index_strCont = 0;
		nWordContnet = strcount_utf8(strContent.c_str());
		fcounter = 0;
	}

	void Dialog::Draw() {
		// メッセージボックス画像の描画
		DrawGraph(msgwnd_left, msgwnd_top, gh_box, TRUE);

		// 話者の描画
		DrawStringToHandle(msgwnd_left + msgspk_left, msgwnd_top + msgspk_top, strSpeaker.c_str(), 0xFFFF00, font1);

		switch (status)
		{
		case 0:			// （予約済み）ダイアログスキンの出現演出用→使わない
			status = 1;
		case 1:			// 文字表示演出
			if (fcounter % 2 == 0) {
				index_strCont += 2;
			}
			if (index_strCont <= nWordContnet) {
				strContDisp = strextract_utf8(strContent.c_str(), index_strCont);
				fcounter++;
			}
			else {
				strContDisp = strContent;
				index_strCont = nWordContnet;
				status = 2;
			}
			break;
		case 2:
			strContDisp = strContent;
			index_strCont = nWordContnet;
			break;
		default:
			break;
		}

		nLenContent = strContDisp.size();

		// 内容の描画
		int nLine = 0;
		int drawX = msgwnd_left + msgtxt_left;
		int drawY = msgwnd_top + msgtxt_top;
		int drawY_span = 50;
		color_t color_now = 0xFFFFFF;
		int fh_now = font1;
		size_t i;
		size_t j = (size_t)0;		// 描画開始位置

		for (i = (size_t)0; i < nLenContent; ++i) {
			if (strContDisp[i] == '\n') {
				DrawStringToHandle(drawX, drawY + nLine * drawY_span, strContDisp.substr(j, i - j).c_str(), color_now, fh_now);
				j = i + 1;
				nLine++;
				drawX = msgwnd_left + msgtxt_left;
			}
			else if (strContDisp[i] == '\\' && i + 3 < nLenContent && strContDisp[i + 3] == '\\') {
				switch (strContDisp[i + 1])
				{
				case 's':			// サイズ変更
					switch (strContDisp[i + 2])
					{
					case '0':
						fh_now = font1;
						drawY = msgwnd_top + msgtxt_top;
						if (drawY_span < 50) {
							drawY_span = 50;
						}
						break;
					case '1':
						fh_now = font4;
						drawY = msgwnd_top + msgtxt_top + 10;
						if (drawY_span < 100) {
							drawY_span = 100;
						}
						break;
					case '2':
						fh_now = font5;
						drawY = msgwnd_top + msgtxt_top;
						if (drawY_span < 25 || i == 0) {
							drawY_span = 25;
						}
						break;
					}
					j += 4;
					break;
				case 'c':
					if (strContDisp[i + 2] >= 0x30 && strContDisp[i + 2] <= 0x39) {
						// ここまでの文字列をまず描画
						DrawStringToHandle(drawX, drawY + nLine * drawY_span, strContDisp.substr(j, i - j).c_str(), color_now, fh_now);

						// 描画x座標に加える
						drawX += GetDrawStringWidthToHandle(strContDisp.substr(j, i - j).c_str(), static_cast<int>(i - j), fh_now);

						color_now = colorList[strContDisp[i + 2] - 48];
						j += i - j + 4;
					}
					break;
				}
			}
		}

		// 残りの文字を描画
		DrawStringToHandle(drawX, drawY + nLine * drawY_span, strContent.substr(j, i - j).c_str(), color_now, fh_now);
	}

	int Dialog::Main(int mode) {
		switch (mode)
		{
		case 0:
			if (onDisplay) {
				Draw();

				// 入力の処理
				if (GetSingleOk()) {
					if (status == 1) {
						status = 2;
					}
					else if (status == 2) {
						return 0;
					}
				}
				else if (GetSingleCancel()) {
					onDisplay = false;
				}
			}
			else {
				if (GetSingleCancel()) {
					onDisplay = true;
				}
			}
			return status;
		case 1:
		{
			Draw();

			int res = status;

			// 入力の処理
			if (GetSingleOk()) {
				if (status == 1) {
					status = 2;
				}
			}
			return res;
		}
		}

		return status;
	}
}

#include "Global.h"

namespace Game {
	string strGameName = "";
	string strGameVersion = "";

	/* キー操作 */

	static bool singleOk = false;			// OKキー単押し
	static bool singleCancel = false;		// キャンセルキー単押し
	static bool singleUp = false;			// 上キー単押し
	static bool singleDown = false;			// 下キー単押し
	static bool singleRight = false;		// 右キー単押し
	static bool singleLeft = false;			// 左キー単押し
	static bool autoSkip = false;			// スキップキー自動

	static bool okPress = false;			// キー入力（OK）
	static bool cancelPress = false;		// キー入力（キャンセル)
	static bool singleOkFlag = false;		// 決定単押しフラグ
	static bool singleCancelFlag = false;	// キャンセル単押しフラグ）
	static bool upPress = false;			// 上キー入力
	static bool downPress = false;			// 下キー入力
	static bool rightPress;					// 右クリック
	static bool leftPress;					// 左クリック
	static bool singleUpFlag = false;		// 上キー単押しフラグ
	static bool singleDownFlag = false;		// 下キー単押しフラグ
	static bool singleRightFlag;			// 右キー単押しフラグ
	static bool singleLeftFlag;				// 左キー単押しフラグ
	static bool skipPress = false;			// キー入力(スキップ)
	static int autoSkipCount = 0;			// スキップオートカウンタ


	/* SE */
	//int sh_cursor = 0;
	//int sh_decide = 0;
	//int sh_cancel = 0;
	//int sh_success = 0;
	//int sh_fail = 0;

	/* フォント */
	int font1 = 0;
	int font2 = 0;
	int font3 = 0;
	int font4 = 0;
	int font5 = 0;
	int font6 = 0;

	bool onMenu = false;
	bool onEvent = false;
	bool onMenuAllow = false;

	class Effect effect = Effect();
	class BGM bgm = BGM();
	class SE se = SE();
	vector<Font> vfont = vector<Font>();

	int index_place = 0;

	void SetKey(const char* key) {
		okPress = cancelPress = singleOk = singleCancel = skipPress = false;
		upPress = downPress = rightPress = leftPress = singleUp = singleDown = singleRight = singleLeft = autoSkip = false;
		if (key[KEY_INPUT_RETURN] || key[KEY_INPUT_Z] || key[KEY_INPUT_SPACE]) okPress = true;
		if (key[KEY_INPUT_ESCAPE] || key[KEY_INPUT_X]) cancelPress = true;
		if (key[KEY_INPUT_UP]) upPress = true;
		if (key[KEY_INPUT_DOWN]) downPress = true;
		if (key[KEY_INPUT_RIGHT]) rightPress = true;
		if (key[KEY_INPUT_LEFT]) leftPress = true;
		if (key[KEY_INPUT_S]) skipPress = true;

		if (okPress && singleOkFlag) {
			singleOk = true;
			singleOkFlag = false;
		}
		else if (!okPress && !singleOkFlag) singleOkFlag = true;
		if (cancelPress && singleCancelFlag) {
			singleCancel = true;
			singleCancelFlag = false;
		}
		else if (!cancelPress && !singleCancelFlag) singleCancelFlag = true;
		if (upPress && singleUpFlag) {
			singleUp = true;
			singleUpFlag = false;
		}
		else if (!upPress && !singleUpFlag) singleUpFlag = true;
		if (downPress && singleDownFlag) {
			singleDown = true;
			singleDownFlag = false;
		}
		else if (!downPress && !singleDownFlag) singleDownFlag = true;
		if (rightPress && singleRightFlag) {
			singleRight = true;
			singleRightFlag = false;
		}
		else if (!rightPress && !singleRightFlag) singleRightFlag = true;
		if (leftPress && singleLeftFlag) {
			singleLeft = true;
			singleLeftFlag = false;
		}
		else if (!leftPress && !singleLeftFlag) singleLeftFlag = true;
		if (skipPress && autoSkipCount % 4 == 0) {
			autoSkip = true;
			autoSkipCount++;
		}
		else if (skipPress) autoSkipCount++;
		else autoSkipCount = 0;
	}

	bool GetSingleOk() {
		return singleOk;
	}

	bool GetSingleCancel() {
		return singleCancel;
	}

	bool GetSingleUp() {
		return singleUp;
	}

	bool GetSingleDown() {
		return singleDown;
	}

	bool GetSingleRight() {
		return singleRight;
	}

	bool GetSingleLeft() {
		return singleLeft;
	}

	bool GetAutoSkip() {
		return autoSkip;
	}

	void ErrorLog(int ER_TYPE, string_view state1, string_view state2) {
		ofstream ofs = ofstream("!Error log.txt", std::ios::app);
		if (ofs) {
			switch (ER_TYPE)
			{
			case ER_JSON_OPEN:
				ofs << (const char*)u8"Catastrophic: JSONファイルが開けません！\n" << "\tファイル名: " << state1 << endl;
				break;
			case ER_JSON_SYNTAX:
				ofs << (const char*)u8"Catastrophic: JSONファイルの中身が異常です！\n" << "\tファイル名: " << state1 <<
					(const char*)u8"\n\t詳細: JSONファイルに記述ミスがあります。あるいは、エンコードが間違っています、UTF-8でエンコードしてください。" << endl;
				break;
			case ER_JSON_RULE:
				ofs << (const char*)u8"Catastrophic: JSONファイルがゲーム製作の仕様書に従っていません！\n" << (const char*)u8"\tファイル名: " << state1 <<
					(const char*)u8"\n\t詳細: ゲーム制作の仕様書を見直してください。" << state2 << endl;
				break;
			case ER_PLC_SET:
				ofs << (const char*)u8"Catastrophic: Placeの設定でエラーが発生しました！\n" << (const char*)u8"\tPlace no: " << state1 <<
					(const char*)u8"\n\t詳細: このエラーが発生した場合、原因は様々考えられます。例えば、JSONの記述やプログラムのエラーなど。\n"
					<< state2 << endl;
				break;
			case ER_IMG_LOAD:
				ofs << (const char*)u8"Mild: 画像を読み込めませんでした！\n" << (const char*)u8"ファイル名: " << state1 <<
					(const char*)u8"\n\t詳細: 当該の画像ファイルを読み込めませんでした。ファイルが存在しているか、あるいは、JSONファイルで正しいファイル名を指定しているか確認してください" << endl;
				break;
			case ER_SND_LOAD:
				ofs << (const char*)u8"Mild: 音声を読み込めませんでした！\n" << (const char*)u8"ファイル名: " << state1 <<
					(const char*)u8"\n\t詳細: 当該の音声ファイルを読み込めませんでした。ファイルが存在しているか、あるいは、JSONファイルで正しいファイル名を指定しているか確認してください" << endl;
				break;
			default:
				ofs << (const char*)u8"Unknown: 正体不明のエラーが発生しました！\n" <<
					(const char*)u8"\t詳細: エラー番号が正しく指定されていないです。なぜエラーが起きたのか、そもそも本当にエラーが発生したのかも不明です。" <<
					(const char*)u8"\n\tエラー内容1: " << state1 << "\n\tエラー内容2: " << state2 << endl;
				break;
			}
			ofs.close();
		}
	}
}
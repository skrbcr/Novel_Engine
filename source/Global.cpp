#include "Global.h"

namespace Game {
	bool onMenu = false;
	bool onEvent = false;
	bool onMenuAllow = false;

	class GameWindow gw = GameWindow();

	class Effect effect = Effect();
	class BGM bgm = BGM();
	class SE se = SE();

	int index_place = 0;

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
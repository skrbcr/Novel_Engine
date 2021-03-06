#pragma once
#include <vector>
#include <string>
#include <string_view>
#include <fstream>
#include "nlohmann/json.hpp"
#include "Global.h"
#include "BackImage.h"
#include "Dialog.h"
#include "Choice.h"
#include "Effect.h"
#include "Image.h"
#include "Character.h"

using std::vector;
using std::string;
using std::string_view;
using std::ifstream;
using std::to_string;
using json = nlohmann::json;

namespace Game {
	/// <summary>
	/// イベント構造体
	/// </summary>
	struct Event
	{
		bool available = true;		// イベントが利用可能か

		int gh_obj = 0;				// オブジェクト画像 グラフィックハンドル
		int x_obj = 0;				// オブジェクト画像 x座標
		int y_obj = 0;				// オブジェクト画像 y座標
		int width_obj = 0;			// オブジェクト画像 幅
		int height_obj = 0;			// オブジェクト画像 高さ

		int gh_ev = 0;				// イベントで表示する画像
		int x_ev = 0;				// イベントで表示する画像
		int y_ev = 0;				// イベントで表示する画像
		int nFactor = 0;			// イベント内の項目数

		vector<Image> vImage = vector<Image>();		// Image配列
	};

	/// <summary>
	/// 場所クラス
	/// </summary>
	class Place
	{
	private:
		json js_gen = json();		// PlaceNoteのJSON
		int nPlace = 0;				// Placeファイルの数

		int gh_back = 0;					// 背景画像
		double drawX = 0.0;					// 背景画像の描画x座標
		double drawY = 0.0;					// 背景画像の描画y座標
		BackImage backImg = BackImage();	// 背景

		int sh_bgm = 0;						// BGMのサウンドハンドル
		int type_bgm = DX_PLAYTYPE_LOOP;	// BGMの再生方法
		double vol_bgm = 1.0;				// BGMの音量

		bool onEffect = false;			// エフェクト中フラグ
		bool onNext = false;			// 次の項目に移るフラグ
		bool useDlg = false;			// ダイアログを使っているかフラグ
		bool onChoice = false;			// 選択肢イベント中
		bool onPlaceChange = false;		// Place変更フラグ
		int nTmpNextPlace = 0;			// 次のPlaceのファイル

		json js = json();			// JSONファイル
		int nEvent = 0;				// イベント数
		//Event* events = nullptr;	// イベントリスト
		vector<Event> events;		// イベントリスト
		int index_event = 0;		// 現在実行中のイベントのインデックス
		int index_factor = 0;		// 現在実行中のイベントのcontentのインデックス
		Dialog dialog = Dialog();	// ダイアログインスタンス
		Choice choice = Choice();	// 選択肢インスタンス
		Character chara = Character();	// キャラクタークラス

	public:
		Place() {

		}

		~Place() {

		}

		void Init() {
			js_gen = json();		// PlaceNoteのJSON
			nPlace = 0;				// Placeファイルの数

			gh_back = 0;					// 背景画像
			drawX = 0.0;					// 背景画像の描画x座標
			drawY = 0.0;					// 背景画像の描画y座標
			backImg = BackImage();	// 背景

			sh_bgm = 0;						// BGMのサウンドハンドル
			type_bgm = DX_PLAYTYPE_LOOP;	// BGMの再生方法
			vol_bgm = 1.0;				// BGMの音量

			onEffect = false;			// エフェクト中フラグ
			onNext = false;			// 次の項目に移るフラグ
			useDlg = false;			// ダイアログを使っているかフラグ
			onChoice = false;			// 選択肢イベント中
			onPlaceChange = false;		// Place変更フラグ
			nTmpNextPlace = 0;			// 次のPlaceのファイル

			js = json();			// JSONファイル
			nEvent = 0;				// イベント数
			//Event* events = nullptr;	// イベントリスト
			events = vector<Event>();		// イベントリスト
			index_event = 0;		// 現在実行中のイベントのインデックス
			index_factor = 0;		// 現在実行中のイベントのcontentのインデックス
			Dialog dialog = Dialog();	// ダイアログインスタンス
			Choice choice = Choice();	// 選択肢インスタンス
		}

	public:
		void SetGeneral();

		/// <summary>
		/// Placeの登録
		/// </summary>
		/// <param name="strFilepath">Placeデータファイルパス</param>
		void Set(string_view strFilepath);
				
		/// <summary>
		/// メイン関数
		/// </summary>
		/// <param name="resEvent">返り値（イベント番号）</param>
		/// <param name="resDetail">返り値（詳細）</param>
		void Main(int& resEvent, int& resDetail);

		void ChangePlace(int index);

		/// <summary>
		/// イベントの"available"を変更
		/// </summary>
		/// <param name="index">イベント番号</param>
		/// <param name="available">bool値</param>
		void ChangeEventAvailable(int index, bool available);

		/// <summary>
		/// イベント要素をセット
		/// </summary>
		void SetFactor();

		void InitChara(size_t n) {
			chara = Character(n);
		}

		void SetChara(size_t i, string_view strPos, int x, int y) {
			chara.SetCharaPos(i, strPos, x, y);
		}
	};
}

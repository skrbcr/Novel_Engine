#pragma once
#include <string>
#include "DxLib.h"
#include "Global.h"

using std::string;

namespace Game {
	enum class BGM_effct
	{
		NO_EFFECT,		// エフェクトなし
		FADE_OUT,		// フェードアウト
		FADE_IN,		// フェードイン
		CHANGE_VOL,		// 音量変更
	};

	class BGM
	{
	private:
		int sh = 0;							// BGMサウンドハンドル
		string filepath = "";				// ファイルパス
		int playType = DX_PLAYTYPE_LOOP;	// 再生方法
		int volume = 255;					// 音量(0~255)
		double volume_gen = 1;				// 音量(全体設定 0~1.0)
		int duration = 0;					// フレーム数
		int frame = 0;						// フレームカウンタ
		bool onPlay = false;				// 再生中フラグ
		bool onChange = false;				// 変項中フラグ
		BGM_effct effectMode = BGM_effct::NO_EFFECT;	// 現在のエフェクト

	private:

	public:
		BGM() {

		}

		void Main();

		/// <summary>
		/// 再生開始
		/// </summary>
		/// <param name="from_zero">先頭から再生するか</param>
		void Play(int from_zero);

		/// <summary>
		/// 再生開始
		/// </summary>
		/// <param name="filepath">サウンドハンドル</param>
		/// <param name="playType">再生方法(DX_PLAYTYPE_XXX)</param>
		/// <param name="volume">音量(0~1.0)</param>
		/// <param name="from_zero">先頭から再生するか</param>
		void Play(int sh, int playType, double volume, int from_zero);
		//void Play(string_view filepath, int playType, double volume);

		/// <summary>
		/// 再生停止
		/// </summary>
		void Pause();

		/// <summary>
		/// 効果を設定
		/// </summary>
		/// <param name="effectType">効果の種類(BGM_effect enum class)</param>
		/// <param name="arg">引数</param>
		void SetEffect(BGM_effct effectType, double arg);

		/// <summary>
		/// BGM全体の音量設定の変更を適用
		/// </summary>
		/// <param name="volume">音量(0~1.0)</param>
		void SetGeneralVolume(double volume);
	};
}

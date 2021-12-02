#pragma once
#include "DxLib.h"
#include "Global.h"

/* Effectクラスの使い方
 * FADE_OUT後は解除しないとエフェクトが掛かり続ける
 */

using color_t = unsigned int;

namespace Game {
	/// <summary>
	/// 描画効果列挙型
	/// </summary>
	enum class effectType
	{
		NO_EFFECT,		// 効果なし（通常）
		FADE_OUT,		// フェードアウト
		FADE_IN,		// フェードイン
		FLASH,			// 点滅
		WAIT,			// 待機
	};

	class Effect
	{
	private:
		effectType eType = effectType::NO_EFFECT;		// エフェクト種類
		int frame = 0;									// 所要フレーム
		int frame_after = 0;							// エフェクト後待機フレーム
		color_t color = 0x000000;						// エフェクト色

		int fcount = 0;			// フレームカウンタ

	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		Effect() {

		}

		/// <summary>
		/// エフェクトの設定
		/// </summary>
		/// <param name="eType">種類</param>
		/// <param name="frame">所要フレーム</param>
		/// <param name="frame_after">エフェクト後フレーム</param>
		/// <param name="color">色</param>
		void Set(effectType eType, int frame, int frame_after, color_t color);

		/// <summary>
		/// エフェクトの実行
		/// </summary>
		/// <returns>true:実行中 false:なし</returns>
		bool Main();
	};
}

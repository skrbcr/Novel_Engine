#include "Effect.h"

namespace Game {
	void Effect::Set(effectType eType, int frame, int frame_after, color_t color) {
		this->eType = eType;
		this->frame = frame;
		this->frame_after = frame_after;
		this->color = color;

		fcount = 0;
	}

	bool Effect::Main() {
		if (eType == effectType::NO_EFFECT) {
			// ‰½‚à‚µ‚È‚¢
			return false;
		}
		else if (fcount <= frame) {
			switch (eType)
			{
			case effectType::FADE_OUT:
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(256.0 * fcount / frame));
				DrawBox(0, 0, WIDTH, HEIGHT, color, TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				break;
			case effectType::FADE_IN:
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(256.0 - 256.0 * fcount / frame));
				DrawBox(0, 0, WIDTH, HEIGHT, color, TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				break;
			case effectType::FLASH:
				if (fcount < frame * 0.5) {
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(512.0 * fcount / frame));
					DrawBox(0, 0, WIDTH, HEIGHT, color, TRUE);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				}
				else {
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(512.0 * (1.0 - static_cast<double>(fcount) / static_cast<double>(frame))));
					DrawBox(0, 0, WIDTH, HEIGHT, color, TRUE);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				}
				break;
			}
			fcount++;
			return true;
		}
		else if (fcount < frame + frame_after) {
			if (eType == effectType::FADE_OUT) {
				DrawBox(0, 0, WIDTH, HEIGHT, color, TRUE);
			}
			fcount++;
			return true;
		}
		else {
			if (eType == effectType::FADE_OUT) {		// Fade out‚Ì‚Æ‚«AŽc‚ç‚È‚¢‚æ‚¤‚É
				DrawBox(0, 0, WIDTH, HEIGHT, color, TRUE);
			}
			return false;
		}
	}
}
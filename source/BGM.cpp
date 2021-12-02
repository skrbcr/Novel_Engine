#include "BGM.h"

namespace Game {
	void BGM::Main()
	{
		switch (effectMode)
		{
			//case BGM_effct::NO_EFFECT:
				//break;
		case BGM_effct::FADE_OUT:
			if (frame < duration) {
				ChangeVolumeSoundMem((int)(volume * (1.0 - (double)frame / (double)duration)), sh);
				frame++;
			}
			else if (frame == duration) {
				if (CheckSoundMem(sh) == 1) {
					StopSoundMem(sh);
					ChangeVolumeSoundMem((int)(volume * 1.0), sh);
				}
				onPlay = false;
				effectMode = BGM_effct::NO_EFFECT;
			}
			break;
		case BGM_effct::FADE_IN:
			if (frame < duration) {
				ChangeVolumeSoundMem((int)(volume * ((double)frame / (double)duration)), sh);
				frame++;
			}
			else if (frame == duration) {
				ChangeVolumeSoundMem(volume, sh);
				effectMode = BGM_effct::NO_EFFECT;
			}
			break;
			//case BGM_effct::CHANGE_VOL:
				//break;
		}
	}

	void BGM::Play(int from_zero)
	{
		if (CheckSoundMem(sh) == 0) {
			ChangeVolumeSoundMem(volume, sh);		// 元の音量に戻して再生
			PlaySoundMem(sh, playType, from_zero);
			onPlay = true;
		}
	}

	void BGM::Play(int sh, int playType, double volume, int from_zero)
	{
		// 既に再生されているBGMがあれば、停止
		if (CheckSoundMem(this->sh) == 1) {
			StopSoundMem(this->sh);
		}

		// サウンドハンドルを取得
		this->sh = sh;
		if (sh == -1) {
			ErrorLog(ER_SND_LOAD, filepath);
		}

		// 音量設定
		if (volume >= 0 && volume <= 1.0) {
			this->volume = (int)(255 * volume_gen * volume);
		}
		ChangeVolumeSoundMem(this->volume, this->sh);

		// 再生
		PlaySoundMem(this->sh, playType, from_zero);
		onPlay = true;
	}

	void BGM::Pause()
	{
		if (CheckSoundMem(sh) == 1) {
			StopSoundMem(sh);
		}
		onPlay = false;
	}

	void BGM::SetEffect(BGM_effct effectType, double arg)
	{
		switch (effectType)
		{
		case BGM_effct::FADE_OUT:
			duration = (int)arg;
			effectMode = effectType;
			break;
		case BGM_effct::FADE_IN:
			duration = (int)arg;
			effectMode = effectType;
			break;
		case BGM_effct::CHANGE_VOL:
			volume = (int)(255 * volume_gen * arg);
			ChangeVolumeSoundMem(volume, sh);
			break;
		}
		frame = 0;
	}

	void BGM::SetGeneralVolume(double volume)
	{
		// 現在のBGMへ反映
		this->volume = (int)(this->volume * volume / volume_gen);
		ChangeVolumeSoundMem(this->volume, sh);

		// 全体に反映
		volume_gen = volume;
	}
}

#include "SE.h"

namespace Game {
	void SE::ApplayConfig(json& js) {
		if (js["volume"].is_number()) {
			vol = js["volume"];
		}
		if (js["sound"].is_array()) {
			size_t n = js["sound"].size();
			vsh = vector<int>(n);
			for (int i = 0; i < n; ++i) {
				if (js["sound"][i].is_string()) {
					string tmp = js["sound"][i];
					if (!tmp.empty()) {
						vsh[i] = LoadSoundMem(tmp.c_str());
						if (vsh[i] == 0 || vsh[i] == -1) {
							vsh[i] = 0;
							ErrorLog(ER_SND_LOAD, tmp);
						}
					}
					else {
						vsh[i] = 0;
					}
				}
			}
		}
	}

	void SE::ChangeVolume(double volume) {
		if (volume <= 0.0) {
			vol = 0.0;
		}
		else if (volume >= 1.0) {
			vol = 1.0;
		}
		else {
			vol = volume;
		}
	}

	void SE::Play(int i) {
		try {
			PlaySoundMem(vsh.at(i), DX_PLAYTYPE_BACK);
		}
		catch (const std::out_of_range&) {
			ErrorLog(ER_JSON_RULE, (const char*)u8"SE再生で指定されたインデックスが配列の範囲外です。");
		}
	}
}
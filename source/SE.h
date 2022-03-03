#pragma once
#include <vector>
#include <string>
#include "DxLib.h"
#include "nlohmann/json.hpp"
#include "Global.h"

using std::string;
using std::vector;
using nlohmann::json;

namespace Game {
	class SE {
	private:
		vector<int> vsh;
		double vol;

	public:
		SE() {
			vsh = vector<int>();
			vol = 0.0;
		}

		~SE() {

		}

		void ApplayConfig(json& js);

		void ChangeVolume(double volume) {
			vol = volume;
		}

		void Play(int i);
	};
}

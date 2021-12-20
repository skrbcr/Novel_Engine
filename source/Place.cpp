#include "Place.h"

namespace Game {
	void Place::SetGeneral() {
		string str_file = STR_JSON_DIRECTORY;
		str_file += "PlaceNote.json";
		ifstream ifs = ifstream(str_file);
		if (ifs) {
			try {
				ifs >> js_gen;
			}
			catch (...) {
				ErrorLog(ER_JSON_SYNTAX, str_file);
				return;
			}
			ifs.close();
		}
		else {
			ErrorLog(ER_JSON_OPEN, str_file);
			return;
		}

		if (js_gen.is_array()) {
			nPlace = static_cast<int>(js_gen.size());
		}
		else {
			ErrorLog(ER_JSON_RULE, "PlaceNote.json", "PlaceNote.json ���z��ɂȂ��Ă��܂���B���̃t�@�C���͔z��ō\������Ă���K�v������܂��B");
			return;
		}

		if (nPlace > 0 && index_place >= 0 && index_place < nPlace) {
			if (js_gen[index_place]["file"].is_string()) {
				str_file = STR_JSON_DIRECTORY;
				str_file += js_gen[index_place]["file"];
				Set(str_file);
			}
		}
		else {
			ErrorLog(ER_PLC_SET,
				"PlaceNote.json", to_string(nPlace) + ", index_place: " + to_string(index_place) + "�̂����ꂩ���s���ł��B");
			return;
		}
	}

	void Place::Set(string_view strFilepath) {
		// ������
		nEvent = 0;
		index_event = 0;
		index_factor = 0;
		onEffect = false;
		onNext = false;
		useDlg = false;

		// JSON�t�@�C���ǂݍ���
		ifstream ifs = ifstream(strFilepath.data());
		if (ifs) {
			try {
				ifs >> js;
			}
			catch (...) {
				ErrorLog(ER_JSON_SYNTAX, strFilepath.data());
				return;
			}
			ifs.close();
		}
		else {
			ErrorLog(ER_JSON_OPEN, strFilepath.data());
			return;
		}

		// �w�i�ݒ�
		if (js["back"].is_array()) {
			gh_back = 0;
			drawX = 0;
			drawY = 0;

			if (js["back"][0].is_string()) {
				string str = js["back"][0];
				gh_back = LoadGraph(str.c_str());
				if (gh_back == -1) {
					ErrorLog(ER_IMG_LOAD, str);
				}
			}
			if (js["back"][1].is_number()) {
				drawX = js["back"][1];
			}
			if (js["back"][2].is_number()) {
				drawY = js["back"][2];
			}

			backImg.Set(gh_back, drawX, drawY);
		}

		// BGM�ݒ�
		if (js["bgm"].is_array()) {
			sh_bgm = 0;
			type_bgm = DX_PLAYTYPE_BACK;
			vol_bgm = 1.0;

			if (js["bgm"][0].is_string()) {
				string str = js["bgm"][0];
				sh_bgm = LoadSoundMem(str.c_str());
			}
			if (js["bgm"][1].is_boolean()) {
				type_bgm = DX_PLAYTYPE_LOOP;
			}
			if (js["bgm"][2].is_number()) {
				vol_bgm = js["bgm"][2];
			}
		}

		// BGS�ݒ�


		// �C�x���g�ݒ�
		if (js["event"].is_array()) {
			// �C�x���g�����擾
			nEvent = static_cast<int>(js["event"].size());

			// �C�x���g���X�g�̏�����
			if (nEvent > 0) {
				events = vector<Event>(nEvent);
			}
			else {
				ErrorLog(ER_PLC_SET, to_string(index_place), "�C�x���g�ݒ�Ɏ��s�B�C�x���g�����ُ�ł��BnEvent: " + to_string(nEvent));
				return;
			}

			// �C�x���g���X�g�̐ݒ�
			for (int i = 0; i < nEvent; ++i) {
				// available �t���O
				if (js["event"][i]["available"].is_boolean()) {
					events[i].available = js["event"][i]["available"];
				}
				else {
					events[i].available = true;
				}

				// Image
				if (js["event"][i]["image"].is_array()) {
					for (const auto& js_img : js["event"][i]["image"]) {
						if (js_img[0].is_number_integer()) {
							switch (static_cast<int>(js_img[0])) {
							case 0:
								if (js_img[1].is_string() && js_img[2].is_number_integer() && js_img[3].is_number_integer()) {
									if (js_img[4].is_number()) {
										events[i].vImage.push_back(Image(js_img[1], js_img[2], js_img[3], js_img[4]));
									}
									else {
										events[i].vImage.push_back(Image(js_img[1], js_img[2], js_img[3], 1.0));
									}
								}
								break;
							}
						}
					}
				}

				// �C�x���g���̍��ڐ����擾
				if (js["event"][i]["content"].is_array()) {
					events[i].nFactor = static_cast<int>(js["event"][i]["content"].size());
					if (events[i].nFactor < 0) {
						ErrorLog(ER_PLC_SET, to_string(index_place),
							"�C�x���g���X�g�̐ݒ�ŃG���[�B" + to_string(i) + "�Ԗڂ̃C�x���g�̍��ڐ����ُ�l " + to_string(events[i].nFactor) + " �ł��B");
					}
				}
			}
		}

		// �t���O�̎��O����
		if (js["pre-flag"].is_array()) {
			for (const auto& js_flag : js["pre-flag"]) {
				if (js_flag.is_array()) {
					if (js_flag[0].is_number_integer() && js_flag[1].is_boolean()
						&& js_flag[2].is_number_integer() && js_flag[3].is_boolean()) {
						if (js_flag[0] >= 0 && js_flag[0] < FLAG_MAX && js_flag[2] >= 0 && js_flag[2] < nEvent) {
							if (flag[js_flag[0]] == js_flag[1]) {
								events[js_flag[2]].available = js_flag[3];
							}
						}
					}
				}
			}
		}
	}

	void Place::Main(int& resEvent, int& resDetail) {
		int res = -1;		// �Ԃ�l
		int res_d = -1;		// �ڍוԂ�l

		// �w�i�`��
		backImg.Main();

		// available�ȃI�u�W�F�N�g�̉摜��`��
		for (const auto& ev : events) {
			if (ev.available && ev.gh_obj != 0 && ev.gh_obj != -1) {
				DrawGraph(ev.x_obj, ev.y_obj, ev.gh_obj, TRUE);
			}
		}

		// �C�x���g���s���łȂ��Ƃ��́A�C�x���g�������Ď�����
		if (!onEvent) {
			// �C�x���g������(trigger�I����)�̏����A�����available�݂̂ŏ���
			for (int i = 0; i < nEvent; ++i) {
				if (/*events[i].trigger && */events[i].available) {
					index_factor = 0;
					onEvent = true;
					onNext = true;
					index_event = i;
					break;
				}
			}
		}

		// �C�x���g���I���ɂȂ������̏���
		if (onNext) {
			SetFactor();
		}

		// �G�t�F�N�g�̎��s
		onEffect = effect.Main();

		// �C�x���g���s���̏���(�G�t�F�N�g�ݒ�ȊO)
		if (onEvent) {
			res = 0;

			// �C�x���g�̒��g�������E���s
			onNext = true;
			if (useDlg) {					// ��b�E�A�C�e���擾�E�A�C�e���g�p
				if (dialog.Main() == 0) {
					useDlg = false;
				}
				else {
					onNext = false;
				}
			}
			if (onChoice) {
				if (dialog.Main(1) == 2) {
					onMenuAllow = true;
					res_d = choice.Main();
					if (res_d < 0) {
						onNext = false;
					}
					else {
						onChoice = false;
						onMenuAllow = false;
						if (js["event"][index_event]["content"][index_factor]["choice"]["option"].is_array()
							&& js["event"][index_event]["content"][index_factor]["choice"]["option"][res_d].is_array()) {
							if (js["event"][index_event]["content"][index_factor]["choice"]["option"][res_d][1] == "general") {
								if (js["event"][index_event]["content"][index_factor]["choice"]["option"][res_d][2].is_number_integer()) {
									int i = js["event"][index_event]["content"]["choice"]["option"][res_d][2];
									if (i >= 0 && i < FLAG_MAX) {
										if (js["event"][index_event]["content"][index_factor]["choice"]["option"][res_d][3].is_boolean()) {
											flag[i] = js["event"][index_event]["content"][index_factor]["choice"]["option"][res_d][3];
										}
									}
								}
							}
							else if (js["event"][index_event]["content"][index_factor]["choice"]["option"][res_d][1] == "event") {
								if (js["event"][index_event]["content"][index_factor]["choice"]["option"][res_d][2].is_number_integer()) {
									int i = js["event"][index_event]["content"][index_factor]["choice"]["option"][res_d][2];
									if (i >= 0 && i < nEvent) {
										if (js["event"][index_event]["content"][index_factor]["choice"]["option"][res_d][3].is_boolean()) {
											events[i].available = js["event"][index_event]["content"][index_factor]["choice"]["option"][res_d][3];
										}
									}
								}
							}
						}
					}
				}
				else {
					onNext = false;
				}
			}
			if (onEffect) {
				if (js["event"][index_event]["content"][index_factor]["effect"][4].is_boolean()) {
					if (js["event"][index_event]["content"][index_factor]["effect"][4] == false) {
						onNext = false;
					}
				}
				else {
					onNext = false;
				}
			}

			// ���̍��ڂ֐i�ޏ���
			if (onNext) {
				index_factor++;
			}

			// index���C�x���g�����ڐ��ɒB���Ă���΁A�I�����A�I���������s��
			if (index_factor >= events[index_event].nFactor) {
				onEvent = false;
				onNext = false;
				index_factor = 0;
				events[index_event].available = false;

				res = index_event;
			}
		}

		if (onPlaceChange) {
			ChangePlace(nTmpNextPlace);
			onPlaceChange = false;
		}

		resEvent = res;
		resDetail = res_d;
	}

	void Place::ChangePlace(int index) {
		if (index >= 0 && index < nPlace) {
			index_place = index;
			string str_file = STR_JSON_DIRECTORY;
			if (js_gen[index_place]["file"].is_string()) {
				str_file += js_gen[index_place]["file"];
				Set(str_file);
			}
		}
	}

	void Place::ChangeEventAvailable(int index, bool available) {
		if (index > nEvent) {
			return;
		}
		events[index].available = available;
	}

	void Place::SetFactor() {
		// �G�t�F�N�g
		if (js["event"][index_event]["content"][index_factor]["effect"].is_array()) {
			effectType eType = effectType::NO_EFFECT;
			int frame = 0;
			color_t color = 0U;
			int frame_after = 30;		// �G�t�F�N�g��̑ҋ@���Ԃ͊���30�t���[��
			if (js["event"][index_event]["content"][index_factor]["effect"][0].is_number_integer()) {
				eType = static_cast<effectType>(js["event"][index_event]["content"][index_factor]["effect"][0]);
			}
			if (js["event"][index_event]["content"][index_factor]["effect"][1].is_number()) {
				frame = js["event"][index_event]["content"][index_factor]["effect"][1];
			}
			if (js["event"][index_event]["content"][index_factor]["effect"][2].is_string()) {
				string str = js["event"][index_event]["content"][index_factor]["effect"][2];
				if (!str.empty()) {
					color = static_cast<unsigned int>(std::stoul(str, nullptr, 16));
				}
			}
			if (js["event"][index_event]["content"][index_factor]["effect"][3].is_number()) {
				frame_after = js["event"][index_event]["content"][index_factor]["effect"][3];
			}
			effect.Set(eType, frame, frame_after, color);
		}

		// �_�C�A���O
		if (js["event"][index_event]["content"][index_factor]["dialog"].is_array()) {
			string speaker = "";
			string content = "";
			if (js["event"][index_event]["content"][index_factor]["dialog"][0].is_string()) {
				speaker = js["event"][index_event]["content"][index_factor]["dialog"][0];
			}
			if (js["event"][index_event]["content"][index_factor]["dialog"][1].is_string()) {
				content = js["event"][index_event]["content"][index_factor]["dialog"][1];
			}
			dialog.Set(speaker, content);
			useDlg = true;
		}

		// �I����
		if (js["event"][index_event]["content"][index_factor]["choice"].is_object()) {
			if (js["event"][index_event]["content"][index_factor]["choice"]["text"].is_string()) {
				string str = js["event"][index_event]["content"][index_factor]["choice"]["text"];
				dialog.Set("", str);
			}
			if (js["event"][index_event]["content"][index_factor]["choice"]["option"].is_array()) {
				int n = static_cast<int>(js["event"][index_event]["content"][index_factor]["choice"]["option"].size());
				vector<string> vstr(n);
				for (int i = 0; i < n; ++i) {
					if (js["event"][index_event]["content"][index_factor]["choice"]["option"][i].is_array()
						&& js["event"][index_event]["content"][index_factor]["choice"]["option"][i][0].is_string()) {
						vstr[i] = js["event"][index_event]["content"][index_factor]["choice"]["option"][i][0];
					}
				}
				choice.Set(vstr);
			}
			onChoice = true;
		}

		// BGM
		// �Đ��E��~
		if (js["event"][index_event]["content"][index_factor]["bgm"].is_object()) {
			if (js["event"][index_event]["content"][index_factor]["bgm"]["play"].is_array()) {
				int tmp_zero = TRUE;
				if (js["event"][index_event]["content"][index_factor]["bgm"]["play"][0].is_boolean()) {
					if (js["event"][index_event]["content"][index_factor]["bgm"]["play"][0] == true) {		// �Đ�
						if (js["event"][index_event]["content"][index_factor]["bgm"]["play"][1].is_boolean()) {
							if (js["event"][index_event]["content"][index_factor]["bgm"]["play"][1] == false) {
								tmp_zero = FALSE;
							}
						}
						bgm.Play(sh_bgm, type_bgm, vol_bgm, tmp_zero);
					}
					else {		// ��~
						bgm.Pause();
					}
				}
			}
			// �G�t�F�N�g
			if (js["event"][index_event]["content"][index_factor]["bgm"]["effect"].is_array()) {
				BGM_effct tmp_type = BGM_effct::NO_EFFECT;
				double tmp_arg = 0.0;
				if (js["event"][index_event]["content"][index_factor]["bgm"]["effect"][0].is_number_integer()) {
					tmp_type = static_cast<BGM_effct>(js["event"][index_event]["content"][index_factor]["bgm"]["effect"][0]);
				}
				if (js["event"][index_event]["content"][index_factor]["bgm"]["effect"][1].is_number()) {
					tmp_arg = static_cast<double>(js["event"][index_event]["content"][index_factor]["bgm"]["effect"][1]);
				}
				bgm.SetEffect(tmp_type, tmp_arg);
			}
		}

		// �t���O����
		if (js["event"][index_event]["content"][index_factor]["flag"].is_array()) {
			if (js["event"][index_event]["content"][index_factor]["flag"][0].is_string()) {
				if (js["event"][index_event]["content"][index_factor]["flag"][0] == "general") {
					if (js["event"][index_event]["content"][index_factor]["flag"][1].is_number_integer()) {
						int i = js["event"][index_event]["content"][index_factor]["flag"][1];
						if (i >= 0 && i < FLAG_MAX) {
							if (js["event"][index_event]["content"][index_factor]["flag"][2].is_boolean()) {
								flag[i] = js["event"][index_event]["content"][index_factor]["flag"][2];
							}
						}
					}
				}
				else if (js["event"][index_event]["content"][index_factor]["flag"][0] == "event") {
					if (js["event"][index_event]["content"][index_factor]["flag"][1].is_number_integer()) {
						int i = js["event"][index_event]["content"][index_factor]["flag"][1];
						if (i >= 0 && i < nEvent) {
							if (js["event"][index_event]["content"][index_factor]["flag"][2].is_boolean()) {
								events[i].available = js["event"][index_event]["content"][index_factor]["flag"][2];
							}
						}
					}
				}
			}
		}

		// Place�ړ�
		if (js["event"][index_event]["content"][index_factor]["place"].is_array()) {
			if (js["event"][index_event]["content"][index_factor]["place"][0].is_number_integer()) {
				nTmpNextPlace = js["event"][index_event]["content"][index_factor]["place"][0];
				onPlaceChange = true;
			}
		}
	}
}

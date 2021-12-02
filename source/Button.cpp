#include "Button.h"

namespace Game {
	void Button::SetGroup(int span_ver, int span_hol, color_t color) {
		index = 0;
		num = 0;
		this->span_ver = span_ver;
		this->span_hol = span_hol;
		this->color = color;
		fcounter = 0;
		vvpos = vector<vector<int>>();
	}

	void Button::AddButton(int x, int y, int width, int height) {
		// �ʒu����o�^
		vector<int> vtmp = { x, y, width, height };
		vvpos.push_back(vtmp);

		// �{�^�����𑝂₷
		num++;
	}

	int Button::Main(bool freeze) {
		int res = -1;		// �Ԃ�l

		Draw();

		if (!freeze) {
			fcounter++;

			// �L�[���͂�����
			if (GetSingleRight()) {
				if (span_hol != 0) {
					index += span_hol;
					PlaySoundMem(sh_cursor, DX_PLAYTYPE_BACK, TRUE);
					if (index > num - 1) {
						index = 0;
					}
					fcounter = 0;
				}
			}
			if (GetSingleLeft()) {
				if (span_hol != 0) {
					index -= span_hol;
					PlaySoundMem(sh_cursor, DX_PLAYTYPE_BACK, TRUE);
					if (index < 0) {
						index = num - 1;
					}
					fcounter = 0;
				}
			}
			if (GetSingleUp()) {
				if (span_ver != 0) {
					index -= span_ver;
					PlaySoundMem(sh_cursor, DX_PLAYTYPE_BACK, TRUE);
					if (index < 0) {
						index = num - 1;
					}
					fcounter = 0;
				}
			}
			if (GetSingleDown()) {
				if (span_ver != 0) {
					index += span_ver;
					PlaySoundMem(sh_cursor, DX_PLAYTYPE_BACK, TRUE);
					if (index > num - 1) {
						index = 0;
					}
					fcounter = 0;
				}
			}
			if (GetSingleOk()) {
				res = index;
			}
			if (GetSingleCancel()) {
				res = -2;
			}
		}

		return res;
	}

	void Button::Draw() {
		// �A���t�@�l�̌v�Z
		if (fcounter % 60 < 30) {
			alpha = static_cast<int>(40.0 + 2.0 * (fcounter % 60));
		}
		else {
			alpha = static_cast<int>(160.0 - 2.0 * (fcounter % 60));
		}

		// �{�^���̕`��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawBox(vvpos[index][0], vvpos[index][1], vvpos[index][0] + vvpos[index][2],
			vvpos[index][1] + vvpos[index][3], color, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha + 30);
		DrawBoxAA(static_cast<float>(vvpos[index][0]), static_cast<float>(vvpos[index][1]), static_cast<float>(vvpos[index][0] + vvpos[index][2]),
			static_cast<float>(vvpos[index][1] + vvpos[index][3]), color, FALSE, 2.f);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	void Button::SetSelection(int index) {
		if (index >= 0 && index < num) {
			this->index = index;
			fcounter = 0;
		}
	}
}
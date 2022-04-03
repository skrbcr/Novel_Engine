#include "Global.h"

namespace Game {
	string strGameName = "";
	string strGameVersion = "";

	/* �L�[���� */

	static bool singleOk = false;			// OK�L�[�P����
	static bool singleCancel = false;		// �L�����Z���L�[�P����
	static bool singleUp = false;			// ��L�[�P����
	static bool singleDown = false;			// ���L�[�P����
	static bool singleRight = false;		// �E�L�[�P����
	static bool singleLeft = false;			// ���L�[�P����
	static bool autoSkip = false;			// �X�L�b�v�L�[����

	static bool okPress = false;			// �L�[���́iOK�j
	static bool cancelPress = false;		// �L�[���́i�L�����Z��)
	static bool singleOkFlag = false;		// ����P�����t���O
	static bool singleCancelFlag = false;	// �L�����Z���P�����t���O�j
	static bool upPress = false;			// ��L�[����
	static bool downPress = false;			// ���L�[����
	static bool rightPress;					// �E�N���b�N
	static bool leftPress;					// ���N���b�N
	static bool singleUpFlag = false;		// ��L�[�P�����t���O
	static bool singleDownFlag = false;		// ���L�[�P�����t���O
	static bool singleRightFlag;			// �E�L�[�P�����t���O
	static bool singleLeftFlag;				// ���L�[�P�����t���O
	static bool skipPress = false;			// �L�[����(�X�L�b�v)
	static int autoSkipCount = 0;			// �X�L�b�v�I�[�g�J�E���^


	/* SE */
	//int sh_cursor = 0;
	//int sh_decide = 0;
	//int sh_cancel = 0;
	//int sh_success = 0;
	//int sh_fail = 0;

	/* �t�H���g */
	int font1 = 0;
	int font2 = 0;
	int font3 = 0;
	int font4 = 0;
	int font5 = 0;
	int font6 = 0;

	bool onMenu = false;
	bool onEvent = false;
	bool onMenuAllow = false;

	class Effect effect = Effect();
	class BGM bgm = BGM();
	class SE se = SE();
	vector<Font> vfont = vector<Font>();

	int index_place = 0;

	void SetKey(const char* key) {
		okPress = cancelPress = singleOk = singleCancel = skipPress = false;
		upPress = downPress = rightPress = leftPress = singleUp = singleDown = singleRight = singleLeft = autoSkip = false;
		if (key[KEY_INPUT_RETURN] || key[KEY_INPUT_Z] || key[KEY_INPUT_SPACE]) okPress = true;
		if (key[KEY_INPUT_ESCAPE] || key[KEY_INPUT_X]) cancelPress = true;
		if (key[KEY_INPUT_UP]) upPress = true;
		if (key[KEY_INPUT_DOWN]) downPress = true;
		if (key[KEY_INPUT_RIGHT]) rightPress = true;
		if (key[KEY_INPUT_LEFT]) leftPress = true;
		if (key[KEY_INPUT_S]) skipPress = true;

		if (okPress && singleOkFlag) {
			singleOk = true;
			singleOkFlag = false;
		}
		else if (!okPress && !singleOkFlag) singleOkFlag = true;
		if (cancelPress && singleCancelFlag) {
			singleCancel = true;
			singleCancelFlag = false;
		}
		else if (!cancelPress && !singleCancelFlag) singleCancelFlag = true;
		if (upPress && singleUpFlag) {
			singleUp = true;
			singleUpFlag = false;
		}
		else if (!upPress && !singleUpFlag) singleUpFlag = true;
		if (downPress && singleDownFlag) {
			singleDown = true;
			singleDownFlag = false;
		}
		else if (!downPress && !singleDownFlag) singleDownFlag = true;
		if (rightPress && singleRightFlag) {
			singleRight = true;
			singleRightFlag = false;
		}
		else if (!rightPress && !singleRightFlag) singleRightFlag = true;
		if (leftPress && singleLeftFlag) {
			singleLeft = true;
			singleLeftFlag = false;
		}
		else if (!leftPress && !singleLeftFlag) singleLeftFlag = true;
		if (skipPress && autoSkipCount % 4 == 0) {
			autoSkip = true;
			autoSkipCount++;
		}
		else if (skipPress) autoSkipCount++;
		else autoSkipCount = 0;
	}

	bool GetSingleOk() {
		return singleOk;
	}

	bool GetSingleCancel() {
		return singleCancel;
	}

	bool GetSingleUp() {
		return singleUp;
	}

	bool GetSingleDown() {
		return singleDown;
	}

	bool GetSingleRight() {
		return singleRight;
	}

	bool GetSingleLeft() {
		return singleLeft;
	}

	bool GetAutoSkip() {
		return autoSkip;
	}

	void ErrorLog(int ER_TYPE, string_view state1, string_view state2) {
		ofstream ofs = ofstream("!Error log.txt", std::ios::app);
		if (ofs) {
			switch (ER_TYPE)
			{
			case ER_JSON_OPEN:
				ofs << (const char*)u8"Catastrophic: JSON�t�@�C�����J���܂���I\n" << "\t�t�@�C����: " << state1 << endl;
				break;
			case ER_JSON_SYNTAX:
				ofs << (const char*)u8"Catastrophic: JSON�t�@�C���̒��g���ُ�ł��I\n" << "\t�t�@�C����: " << state1 <<
					(const char*)u8"\n\t�ڍ�: JSON�t�@�C���ɋL�q�~�X������܂��B���邢�́A�G���R�[�h���Ԉ���Ă��܂��AUTF-8�ŃG���R�[�h���Ă��������B" << endl;
				break;
			case ER_JSON_RULE:
				ofs << (const char*)u8"Catastrophic: JSON�t�@�C�����Q�[������̎d�l���ɏ]���Ă��܂���I\n" << (const char*)u8"\t�t�@�C����: " << state1 <<
					(const char*)u8"\n\t�ڍ�: �Q�[������̎d�l�����������Ă��������B" << state2 << endl;
				break;
			case ER_PLC_SET:
				ofs << (const char*)u8"Catastrophic: Place�̐ݒ�ŃG���[���������܂����I\n" << (const char*)u8"\tPlace no: " << state1 <<
					(const char*)u8"\n\t�ڍ�: ���̃G���[�����������ꍇ�A�����͗l�X�l�����܂��B�Ⴆ�΁AJSON�̋L�q��v���O�����̃G���[�ȂǁB\n"
					<< state2 << endl;
				break;
			case ER_IMG_LOAD:
				ofs << (const char*)u8"Mild: �摜��ǂݍ��߂܂���ł����I\n" << (const char*)u8"�t�@�C����: " << state1 <<
					(const char*)u8"\n\t�ڍ�: ���Y�̉摜�t�@�C����ǂݍ��߂܂���ł����B�t�@�C�������݂��Ă��邩�A���邢�́AJSON�t�@�C���Ő������t�@�C�������w�肵�Ă��邩�m�F���Ă�������" << endl;
				break;
			case ER_SND_LOAD:
				ofs << (const char*)u8"Mild: ������ǂݍ��߂܂���ł����I\n" << (const char*)u8"�t�@�C����: " << state1 <<
					(const char*)u8"\n\t�ڍ�: ���Y�̉����t�@�C����ǂݍ��߂܂���ł����B�t�@�C�������݂��Ă��邩�A���邢�́AJSON�t�@�C���Ő������t�@�C�������w�肵�Ă��邩�m�F���Ă�������" << endl;
				break;
			default:
				ofs << (const char*)u8"Unknown: ���̕s���̃G���[���������܂����I\n" <<
					(const char*)u8"\t�ڍ�: �G���[�ԍ����������w�肳��Ă��Ȃ��ł��B�Ȃ��G���[���N�����̂��A���������{���ɃG���[�����������̂����s���ł��B" <<
					(const char*)u8"\n\t�G���[���e1: " << state1 << "\n\t�G���[���e2: " << state2 << endl;
				break;
			}
			ofs.close();
		}
	}
}
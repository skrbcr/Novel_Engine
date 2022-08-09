#include "Global.h"

namespace Game {
	bool onMenu = false;
	bool onEvent = false;
	bool onMenuAllow = false;

	class GameWindow gw = GameWindow();

	class Effect effect = Effect();
	class BGM bgm = BGM();
	class SE se = SE();

	int index_place = 0;

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
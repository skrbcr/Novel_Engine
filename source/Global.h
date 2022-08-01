#pragma once
#include <stdexcept>
#include <vector>
#include <string>
#include <string_view>
#include <fstream>
#include "nlohmann/json.hpp"
#include "DxLib.h"
#include "Effect.h"
#include "BGM.h"
#include "SE.h"

using std::vector;
using std::string;
using std::string_view;
using std::ofstream;
using std::endl;
using nlohmann::json;
//using color_t = unsigned int;		// �F

namespace Game {
	struct Font {
		int fh = 0;
		int height = 0;
		int lspace = 0;
	};

	constexpr char SOFT_NAME[] = "skrb_novel";
	constexpr char SOFT_VER[] = "version 0.2.0";

	extern string strGameName;
	extern string strGameVersion;

	constexpr int WIDTH = 1280;		// �E�B���h�E��
	constexpr int HEIGHT = 720;		// �E�B���h�E����
	constexpr int MAX_SAVE = 3;		// �Z�[�u�t�@�C���ő�
	constexpr int FLAG_MAX = 64;	// �t���O�̍ő�l�E������g�p��~

	constexpr char STR_BGM_DIRECTORY[] = "data/bgm/";
	constexpr char STR_BGS_DIRECTORY[] = "data/bgs/";
	constexpr char STR_ME_DIRECTORY[] = "data/me/";
	constexpr char STR_SE_DIRECTORY[] = "data/se/";
	constexpr char STR_JSON_DIRECTORY[] = "data/data/";	

	constexpr int ER_JSON_OPEN = 10;
	constexpr int ER_JSON_SYNTAX = 11;
	constexpr int ER_JSON_RULE = 12;
	constexpr int ER_PLC_SET = 13;
	constexpr int ER_IMG_LOAD = 21;
	constexpr int ER_SND_LOAD = 31;

	//extern int sh_cursor;			// �J�[�\��SE(���L�[�E�ڗ������Ȃ�OK�L�[)
	//extern int sh_decide;			// ����SE
	//extern int sh_cancel;			// �L�����Z��SE
	//extern int sh_success;			// ����SE(�Z�[�u��)
	//extern int sh_fail;				// ���sSE(�Z�[�u��)

	extern class Effect effect;
	extern class BGM bgm;
	extern class SE se;
	extern vector<Font> vfont;

	struct SaveData
	{
		time_t saveTime = 0;				// �Z�[�u����
		int saveCount = 0;					// �Z�[�u��
		int index_place = 0;				// Place��index
		bool flag[FLAG_MAX] = { false };	// �t���O�z��
	};

	__declspec(selectany) struct SaveData saveData[3] = {};
	__declspec(selectany) json js_saveFile[3] = {};

	extern int font1;		// 24px�t�H���g
	extern int font2;		// 18px�t�H���g
	extern int font3;		// 20px�t�H���g
	extern int font4;		// 48px�t�H���g
	extern int font5;		// 12px�t�H���g
	extern int font6;		// 30px�t�H���g

	extern bool onMenu;		// ���j���[�I�[�v�����t���O
	extern bool onMenuAllow;// ���j���[�I�[�v�����t���O
	extern bool onEvent;	// �C�x���g���t���O

	__declspec(selectany) bool flag[FLAG_MAX] = { false };		// �t���O�z��(�Q�[���{�җp)
	extern int index_place;	// Place��index

	/// <summary>
	/// �`����ʗ񋓌^
	/// </summary>
	enum class drawEffect
	{
		NO_EFFECT,		// ���ʂȂ��i�ʏ�j
		FADE_OUT,		// �t�F�[�h�A�E�g
		FADE_IN,		// �t�F�[�h�C��
		FLASH,			// �_��
		MOVE_UP,		// �w�i�摜�̏�ֈړ�
		MOVE_DOWN,		// �w�i�摜�̉��ֈړ�
		MOVE_RIGHT,		// �w�i�摜�̉E�ֈړ�
		MOVE_LEFT,		// �w�i�摜�̍��ֈړ�
		WAIT,			// �҂�����
	};

	/// <summary>
	/// �P�����L�[�擾
	/// </summary>
	/// <param name="key">�L�[�z��</param>
	void SetKey(const char* key);

	// OK�L�[�P�����擾
	bool GetSingleOk();

	// Cancel�L�[�P�����擾
	bool GetSingleCancel();

	// ��L�[�P�����擾
	bool GetSingleUp();

	// ���L�[�P�����擾
	bool GetSingleDown();

	// �E�L�[�P�����擾
	bool GetSingleRight();

	// ���L�[�P�����擾
	bool GetSingleLeft();

	// �X�L�b�v�L�[�擾
	bool GetAutoSkip();

	// �G���[���O�̏o��
	void ErrorLog(int ER_TYPE, string_view state1 = "", string_view state2 = "");
}
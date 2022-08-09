#pragma once
#include <stdexcept>
#include <vector>
#include <string>
#include <string_view>
#include <fstream>
#include "nlohmann/json.hpp"
#include "DxLib.h"
#include "GameWindow.h"
#include "Effect.h"
#include "BGM.h"
#include "SE.h"

using std::vector;
using std::string;
using std::string_view;
using std::ofstream;
using std::ifstream;
using std::endl;
using nlohmann::json;
using color_t = unsigned int;		// �F

namespace Game {
	constexpr int ER_JSON_OPEN = 10;
	constexpr int ER_JSON_SYNTAX = 11;
	constexpr int ER_JSON_RULE = 12;
	constexpr int ER_PLC_SET = 13;
	constexpr int ER_IMG_LOAD = 21;
	constexpr int ER_SND_LOAD = 31;

	extern class GameWindow gw;

	extern class Effect effect;
	extern class BGM bgm;
	extern class SE se;

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

	// �G���[���O�̏o��
	void ErrorLog(int ER_TYPE, string_view state1 = "", string_view state2 = "");
}
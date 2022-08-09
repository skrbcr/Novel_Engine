#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>
#include "DxLib.h"
#include "nlohmann/json.hpp"

using std::string;
using std::vector;
using std::runtime_error;
using std::ifstream;
using nlohmann::json;

namespace Game {
	constexpr char SOFT_NAME[] = "skrb_novel";
	constexpr char SOFT_VER[] = "version 0.2.0";

	constexpr int WIDTH = 1280;		// �E�B���h�E��
	constexpr int HEIGHT = 720;		// �E�B���h�E����
	constexpr int MAX_SAVE = 3;		// �Z�[�u�t�@�C���ő�
	constexpr int FLAG_MAX = 64;	// �t���O�̍ő�l�E������g�p��~

	constexpr char STR_BGM_DIRECTORY[] = "data/bgm/";
	constexpr char STR_BGS_DIRECTORY[] = "data/bgs/";
	constexpr char STR_ME_DIRECTORY[] = "data/me/";
	constexpr char STR_SE_DIRECTORY[] = "data/se/";
	constexpr char STR_JSON_DIRECTORY[] = "data/data/";

	struct Font {
		int fh = 0;
		int height = 0;
		int lspace = 0;
	};

	struct SaveData {
		time_t saveTime = 0;				// �Z�[�u����
		int saveCount = 0;					// �Z�[�u��
		int index_place = 0;				// Place��index
		bool flag[FLAG_MAX] = { false };	// �t���O�z��
	};

	class GameWindow {
	private:
		bool singleOk = false;			// OK�L�[�P����
		bool singleCancel = false;		// �L�����Z���L�[�P����
		bool singleUp = false;			// ��L�[�P����
		bool singleDown = false;		// ���L�[�P����
		bool singleRight = false;		// �E�L�[�P����
		bool singleLeft = false;		// ���L�[�P����
		bool autoSkip = false;			// �X�L�b�v�L�[����
		bool okPress = false;			// �L�[���́iOK�j
		bool cancelPress = false;		// �L�[���́i�L�����Z��)
		bool singleOkFlag = false;		// ����P�����t���O
		bool singleCancelFlag = false;	// �L�����Z���P�����t���O�j
		bool upPress = false;			// ��L�[����
		bool downPress = false;			// ���L�[����
		bool rightPress;				// �E�N���b�N
		bool leftPress;					// ���N���b�N
		bool singleUpFlag = false;		// ��L�[�P�����t���O
		bool singleDownFlag = false;	// ���L�[�P�����t���O
		bool singleRightFlag;			// �E�L�[�P�����t���O
		bool singleLeftFlag;			// ���L�[�P�����t���O
		bool skipPress = false;			// �L�[����(�X�L�b�v)
		int autoSkipCount = 0;			// �X�L�b�v�I�[�g�J�E���^

	public:
		string strGameName = "";
		string strGameVersion = "";

		json js_cfg = json();		// Config.json
		json js_saveFile[3] = {};	// �Z�[�u�f�[�^�t�@�C������
		SaveData saveData[3] = {};	// �Z�[�u�f�[�^���g����

		vector<Font> vfont = vector<Font>();

		// �����̃t�H���g�͌�ŏ��������i�ŏ�����t�H���g���ʂɎ���Ă����̂͗ǂ��Ȃ��̂Łj
		int font1;		// 24px�t�H���g
		int font2;		// 18px�t�H���g
		int font3;		// 20px�t�H���g
		int font4;		// 48px�t�H���g
		int font5;		// 12px�t�H���g
		int font6;		// 30px�t�H���g

	public:
		GameWindow();
		~GameWindow();
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

	private:
		void LoadConfig();
		void MakeHandles();			// �e��n���h���̍쐬
		void DeleteHandles();		// �e��n���h���̍폜
	};
}

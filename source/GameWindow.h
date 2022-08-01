#pragma once
#include "nlohmann/json.hpp"
#include "Global.h"
#include "Title.h"
#include "Menu.h"
#include "Place.h"
#include "Choice.h"
#include "Button.h"
#include "BGM.h"

using std::runtime_error;

namespace Game {
	class GameWindow {
	private:
		json js_cfg = json();	// Config.json
		Title title;			// �^�C�g�����
		Menu menu;				// ���j���[
		Place place;			// �ꏊ�C���X�^���X

		int status = 0;				// �X�e�[�^�X�ԍ�
		int counter = 0;			// �t���[���J�E���^
		int snum = 0;				// �V�[���Ǘ��ԍ�
		int resEvent = 0;			// �C�x���g�Ԃ�l
		int resEvDet = 0;			// �C�x���g�Ԃ�l�ڍ�
		bool playFinFlag = false;	// �Q�[���{�ҏI���t���O

	public:
		GameWindow();
		~GameWindow();
		void GameMain();			// �Q�[���̃��C�����[�v����
		int GamePlay();				// �Q�[���{��

	private:
		void GameInit();			// �Q�[���̏������B�{�҈ڍs�O�ɍs��
		void MakeHandles();			// �e��n���h���̍쐬
		void DeleteHandles();		// �e��n���h���̍폜
		void LoadConfig();			// Config.json�̓ǂݍ��݁E�E�B���h�E�̐ݒ�
		void SetConfig();			// Config.json �̓K�p
	};
}

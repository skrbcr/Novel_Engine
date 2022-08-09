#pragma once
#include "GameWindow.h"
#include "Title.h"
#include "Menu.h"
#include "Place.h"
#include "Choice.h"
#include "Button.h"
#include "BGM.h"

namespace Game {
	class GameControl {
	private:
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
		GameControl();
		void GameInit();			// �Q�[���̏������B�{�҈ڍs�O�ɍs��
		void GameMain();			// �Q�[���̃��C�����[�v����
		int GamePlay();				// �Q�[���{��
		void SetConfig();			// Config.json �̓K�p
	};
}

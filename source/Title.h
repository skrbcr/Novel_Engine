#pragma once
#include <fstream>
#include <map>
#include "DxLib.h"
#include "Global.h"
#include "Button.h"

namespace Game {
	class Title
	{
	private:
		int nPage = 0;			// �^�C�g���̃y�[�W�ԍ�
		int fcounter = 0;		// �t���[���J�E���^

		int gh_back = 0;		// �w�i�摜 �O���t�B�b�N�n���h��
		int width_hajime = 0;	// "�͂��߂���"�̕�
		int width_tuduki = 0;	// "�Â�����"�̕�
		bool showVerFlag = false;		// �o�[�W���������^�C�g����ʂɕ\�����邩

		int sh_bgm = 0;			// BGM �T�E���h�n���h��
		double bgmVol = 1.0;	// BGM ����
		std::map<const char*, int> mapSe;
		
		Button button_title = Button();		// �^�C�g����ʂ̃{�^��
		Button button_load = Button();		// ���[�h��ʂ̃{�^��
		int opt_title = 0;		// �^�C�g����ʂ̃{�^���̑I�𒆔ԍ�
		int opt_load = 0;		// ���[�h��ʂ̃{�^���̑I��ԍ�

	public:
		Title() {

		}

		~Title() {

		}

		/// <summary>
		/// �ݒ�̓K�p
		/// </summary>
		/// <param name="js">json["title"]</param>
		void ApplyConfig(json& js);

		/// <summary>
		/// 
		/// </summary>
		/// <returns>0: �ʏ� 1: �Q�[���{�҂� 10~: 10������index�̃Z�[�u��ǂݍ���Ŗ{�҂�</returns>
		int Main();

		void Init() {
			nPage = 0;
			fcounter = 0;
		}
	};
}

// �����EnPage
// 0: �N����
// 1: �^�C�g��
// 2: ���[�h�I��
// 3: �^�C�g�����Q�[���J�n
// 4: ���[�h���Q�[���J�n

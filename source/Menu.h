#pragma once
#include <string>
#include <ctime>
#include <direct.h>
#include <fstream>
#include "nlohmann/json.hpp"
#include "javacommons/strconv.h"
#include "Global.h"
#include "Button.h"

using std::string;
using nlohmann::json;

namespace Game {
	class Menu
	{
	private:
		int opt = 0;
		int opt_title = 0;
		bool onTitle = false;

		Button button1 = Button();
		Button button2 = Button();


	private:
		/// <summary>
		/// �Z�[�u�t�@�C���쐬�E�o��
		/// </summary>
		/// <param name="i">�t�@�C���ԍ�</param>
		/// <returns>0:���� -1:���s</returns>
		int MakeSaveData(int i);


	public:
		Menu();


		~Menu() {

		}

		/// <summary>
		/// �I��ԍ��E�t���[���J�E���^�E�t���O�����Z�b�g
		/// </summary>
		void Reset();

		/// <summary>
		/// ���j���[�{��
		/// </summary>
		/// <returns>-1:���j���[�Ȃ� 0:���j���[�E�ʏ� 1:�{�ҏI���̍��}</returns>
		int Main();
	};
}

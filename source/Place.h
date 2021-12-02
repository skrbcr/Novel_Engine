#pragma once
#include <string>
#include <string_view>
#include <fstream>
#include "nlohmann/json.hpp"
#include "javacommons/strconv.h"
#include "Global.h"
#include "BackImage.h"
#include "Dialog.h"
#include "Choice.h"
#include "Effect.h"

using std::string;
using std::string_view;
using std::ifstream;
using std::to_string;
using json = nlohmann::json;

namespace Game {
	/// <summary>
	/// �C�x���g�\����
	/// </summary>
	struct Event
	{
		bool available = true;		// �C�x���g�����p�\��

		int gh_obj = 0;				// �I�u�W�F�N�g�摜 �O���t�B�b�N�n���h��
		int x_obj = 0;				// �I�u�W�F�N�g�摜 x���W
		int y_obj = 0;				// �I�u�W�F�N�g�摜 y���W
		int width_obj = 0;			// �I�u�W�F�N�g�摜 ��
		int height_obj = 0;			// �I�u�W�F�N�g�摜 ����

		int gh_ev = 0;				// �C�x���g�ŕ\������摜
		int x_ev = 0;				// �C�x���g�ŕ\������摜
		int y_ev = 0;				// �C�x���g�ŕ\������摜
		int nFactor = 0;			// �C�x���g���̍��ڐ�
	};

	/// <summary>
	/// �ꏊ�N���X
	/// </summary>
	class Place
	{
	private:
		json js_gen = json();		// PlaceNote��JSON
		int nPlace = 0;				// Place�t�@�C���̐�

		int gh_back = 0;					// �w�i�摜
		double drawX = 0.0;					// �w�i�摜�̕`��x���W
		double drawY = 0.0;					// �w�i�摜�̕`��y���W
		BackImage backImg = BackImage();	// �w�i

		int sh_bgm = 0;						// BGM�̃T�E���h�n���h��
		int type_bgm = DX_PLAYTYPE_LOOP;	// BGM�̍Đ����@
		double vol_bgm = 1.0;				// BGM�̉���

		bool onEffect = false;			// �G�t�F�N�g���t���O
		bool onNext = false;			// ���̍��ڂɈڂ�t���O
		bool useDlg = false;			// �_�C�A���O���g���Ă��邩�t���O
		bool onChoice = false;			// �I�����C�x���g��
		bool onPlaceChange = false;		// Place�ύX�t���O
		int nTmpNextPlace = 0;			// ����Place�̃t�@�C��

		json js = json();			// JSON�t�@�C��
		int nEvent = 0;				// �C�x���g��
		Event* events = nullptr;	// �C�x���g���X�g
		int index_event = 0;		// ���ݎ��s���̃C�x���g�̃C���f�b�N�X
		int index_factor = 0;		// ���ݎ��s���̃C�x���g��content�̃C���f�b�N�X
		Dialog dialog = Dialog();	// �_�C�A���O�C���X�^���X
		Choice choice = Choice();	// �I�����C���X�^���X

	public:
		Place() {

		}

		~Place();

	public:
		void SetGeneral();

		/// <summary>
		/// Place�̓o�^
		/// </summary>
		/// <param name="strFilepath">Place�f�[�^�t�@�C���p�X</param>
		void Set(string_view strFilepath);
				
		/// <summary>
		/// ���C���֐�
		/// </summary>
		/// <param name="resEvent">�Ԃ�l�i�C�x���g�ԍ��j</param>
		/// <param name="resDetail">�Ԃ�l�i�ڍׁj</param>
		void Main(int& resEvent, int& resDetail);

		void ChangePlace(int index);

		/// <summary>
		/// �C�x���g��"available"��ύX
		/// </summary>
		/// <param name="index">�C�x���g�ԍ�</param>
		/// <param name="available">bool�l</param>
		void ChangeEventAvailable(int index, bool available);

		/// <summary>
		/// �C�x���g�v�f���Z�b�g
		/// </summary>
		void SetFactor();
	};
}

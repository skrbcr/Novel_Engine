// skrbcr/Novel_Engine�ihttps://github.com/skrbcr/Novel_Engine�j
// DX���C�u�����g�p�̃m�x���Q�[���G���W���H�̃A���t�@�� ver.0.2.0
// 
// �z�z�\�[�X�R�[�h�̈ꕔ�ɁA�ȉ��̃��C�u�������܂݂܂�
// ���쌠�\���̏ڍׂ́A"./nlohmann/json.hpp" �� "../README.md" ��������������
// �Enlohmann/json�ihttps://github.com/nlohmann/json�jversion 3.9.1
// 
// �܂��A�{�\�t�g�� DX���C�u�����iVer3.23 https://dxlib.xsrv.jp/�j���g�p���Ă��܂���
// �z�z�\�[�X�R�[�h�ɂ͊܂�ł���܂���
// �ł�����A�r���h�������́A�����g�ł̃_�E�����[�h��ݒ蓙�����肢�������܂�
// 

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include "DxLib.h"
#include "Global.h"
#include "GameWindow.h"
#include "GameControl.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	/* �f�o�b�O�p�i���������[�N���m�j */
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	//int* a = new int();		// ���������[�N�̃T���v���idelete���Ă΂Ȃ��j
	
	try {
		//Game::gw = Game::GameWindow();
		Game::GameControl gc = Game::GameControl();
		char key[256];		// �L�[���͔z��

		while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll(key) == 0) {
			Game::gw.SetKey(key);
			gc.GameMain();
		}
	}
	catch (const std::exception&) {
		return -1;		// ���ƂŃG���[�����������Ă���
	}

	return 0;
}

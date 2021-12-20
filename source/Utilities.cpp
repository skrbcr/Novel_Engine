#include "Utilities.h"

namespace Game {
	size_t strcount_utf8(const char* str) {
		size_t zStrCount = 0;
		size_t zStrLen = std::strlen(str);
		for (size_t i = 0; i < zStrLen; ++i) {
			// マルチバイト文字の2バイト目以降
			if (static_cast<unsigned char>(str[i]) >= 0x80 && static_cast<unsigned char>(str[i]) <= 0xBF) {
				continue;
			}
			// Xバイト文字の1文字目
			else {
				// 描画指定コマンドを除外
				if (str[i] == u8'\\' && i + 3 < zStrLen && str[i + 3] == u8'\\') {
					if (str[i + 1] == u8'c' || str[i + 1] == u8's') {
						if (str[i + 2] >= u8'0' && str[i + 2] <= u8'9') {
							i += 3;
							continue;
						}
					}
				}
				// 文字数を+1
				++zStrCount;
			}
		}
		return zStrCount;
	}

	string strextract_utf8(const char* str, size_t nCount) {
		size_t zStrCount = 0;
		size_t zStrLen = std::strlen(str);
		string strRes = "";
		unsigned char c;
		for (size_t i = 0; i < zStrLen; ++i) {
			c = static_cast<unsigned char>(str[i]);
			if (zStrCount >= nCount) {
				break;
			}
			// 1バイト文字の処理
			if (c >= 0x00 && c <= 0x7F) {
				// 描画指定コマンドは何もせずに、そのまま格納
				if (str[i] == u8'\\' && i + 3 < zStrLen && str[i + 3] == u8'\\') {
					if (str[i + 1] == u8'c' || str[i + 1] == u8's') {
						if (str[i + 2] >= u8'0' && str[i + 2] <= u8'9') {
							strRes += str[i];
							strRes += str[i + 1];
							strRes += str[i + 2];
							strRes += str[i + 3];
							i += 3;
						}
					}
				}
				else if (str[i] == u8'\n') {
					strRes += str[i];
				}
				else {
					strRes += str[i];
					zStrCount++;
				}
			}
			// 2バイト文字の処理
			else if (c >= 0xC0 && c <= 0xDF) {
				strRes += str[i];
				strRes += str[i + 1];
				zStrCount++;
				i++;
			}
			// 3バイト文字の処理
			else if (c >= 0xE0 && c <= 0xEF) {
				strRes += str[i];
				strRes += str[i + 1];
				strRes += str[i + 2];
				zStrCount++;
				i += 2;
			}
			// 4バイト文字の処理;
			else if (c >= 0xF0 && c <= 0xF7) {
				strRes += str[i];
				strRes += str[i + 1];
				strRes += str[i + 2];
				strRes += str[i + 3];
				zStrCount++;
				i += 3;
			}
		}
		return strRes;
	}
}
#pragma once
#include <string>

using std::string;
using std::string_view;

namespace Game {
	size_t strcount_utf8(const char* str);

	string strextract_utf8(const char* str, size_t nCount);
}
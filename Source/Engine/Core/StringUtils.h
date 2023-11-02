#pragma once
#include <string>
#include <ctype.h>

namespace nc {
	class StringUtils {
	public:
		static std::string toUpper(const std::string& s);
		static std::string toLower(const std::string& s);
		static bool isEqualIgnoreCase(const std::string& s1, const std::string& s2);
		static std::string CreateUnique(const std::string& s);
	};
}
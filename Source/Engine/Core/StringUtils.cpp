#include "StringUtils.h"
#include <string>

namespace nc {
	std::string StringUtils::toUpper(const std::string& s) {
		std::string end = s;
		for (char& c : end) {
			if (c >= 'a' && c <= 'z') {
				c += ('A' - 'a');
			}
		}

		return end;
	}

	std::string StringUtils::toLower(const std::string& s) {
		std::string end = s;
		for (char& c : end) {
			if (c >= 'A' && c <= 'Z') {
				c += ('a' - 'A');
			}
		}

		return end;
	}

	bool StringUtils::isEqualIgnoreCase(const std::string& s1, const std::string& s2) {
		if (StringUtils::toLower(s1) == StringUtils::toLower(s2)) {
			return true;
		}

		return false;
	}

	std::string StringUtils::CreateUnique(const std::string& s) {
		static uint32_t count = 0;
		return s + std::to_string(count++);
	}
}
#include "KMP.h"
#include <vector>

KMP::KMP()
{

}

KMP::KMP(std::string haystack)
	: StringSearch(haystack)
{

}

std::size_t KMP::FindString(std::string pattern, std::size_t startIndex)
{
	if (false == CheckString(pattern, startIndex))
		return std::string::npos;

	std::string haystack = this->haystack.substr(startIndex);

	std::vector<std::size_t> skipInfo(pattern.size(), 0);
	std::size_t index = 0;
	for (int i = 0; i < pattern.size(); ++i) // i : incorrect index when haystack and pattern are compared
	{
		for (int j = 0; j < i - 1; ++j) // j : index for finding the longest border in equivalent prefix of haystack and pattern
		{
			for (index = 0; index <= j; ++index)
				if (pattern[index] != pattern[(std::size_t)i - 1 - j + index])
					break;
			if (index > j)
				skipInfo[i] = (std::size_t)i - (j + 1);
		}
		if (0 == skipInfo[i])
			skipInfo[i] = 2 > i ? 1 : i;
	}

	std::size_t i = 0; // i : beginning index of comparison
	while (i <= haystack.size() - pattern.size())
	{
		for (index = 0; index < pattern.size(); ++index)
			if (haystack[i + index] != pattern[index])
				break;
		if (pattern.size() == index)
			return startIndex + i;
		i += skipInfo[index];
	}

	return std::string::npos;
}

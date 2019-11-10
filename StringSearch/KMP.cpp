#include "KMP.h"
#include <vector>

KMP::KMP(std::string haystack)
	: StringSearch(haystack)
{

}

std::size_t KMP::FindString(std::string pattern, std::size_t startIndex)
{
	if (false == CheckString(pattern, startIndex))
		return std::string::npos;

	std::string haystack = this->haystack.substr(startIndex);

	std::vector<std::size_t> skipInfo(pattern.size());
	skipInfo[0] = 1;
	std::size_t index = 0;
	for (std::size_t i = 1; i < pattern.size(); ++i)
	{
		skipInfo[i] = 0;
		for (std::size_t j = 0; j < i; ++j)
		{
			for (index = 0; index <= j; ++index)
				if (pattern[index] != pattern[i - (j - index)])
					break;
			if (index > j)
				skipInfo[i] = i - j;
		}
		if (0 == skipInfo[i])
			skipInfo[i] = i + 1;
	}

	std::size_t i = 0;
	while (i <= haystack.size() - pattern.size())
	{
		for (index = 0; index < pattern.size(); ++index)
			if (haystack[i + index] != pattern[index])
				break;
		if (pattern.size() == index)
			return startIndex + i;
		if (0 == index)
			i += 1;
		else
			i += skipInfo[index - 1];
	}

	return std::string::npos;
}

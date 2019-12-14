#include "Naive.h"

Naive::Naive()
{

}

Naive::Naive(std::string haystack)
	: StringSearch(haystack)
{

}

std::size_t Naive::FindString(std::string pattern, std::size_t startIndex)
{
	if (false == CheckString(pattern, startIndex))
		return std::string::npos;

	std::string haystack = this->haystack.substr(startIndex);

	std::size_t index = std::string::npos;
	for (std::size_t i = 0; i <= haystack.size() - pattern.size(); ++i)
	{
		for (index = 0; index < pattern.size(); ++index)
		{
			if (pattern[index] != haystack[i + index])
				break;
		}

		if (index == pattern.size())
			return startIndex + i;
	}

	return std::string::npos;
}
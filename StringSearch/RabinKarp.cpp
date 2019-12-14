#include "RabinKarp.h"

#include <cstddef>
#include <cmath>

RabinKarp::RabinKarp()
{

}

RabinKarp::RabinKarp(std::string haystack)
	: StringSearch(haystack)
{

}

std::size_t RabinKarp::MakeHash(std::size_t beforeHash, const char* beforeFirstChar, std::string haystack, std::size_t patterSize)
{
	std::size_t ret = 0;
	if (nullptr == beforeFirstChar)
	{
		for (std::size_t i = 0; i < patterSize; ++i)
		{
			ret += (std::size_t)(haystack[i] * pow(2.f, patterSize - i - 1));
		}
		return ret % std::numeric_limits<std::size_t>::max();
	}
	else
	{
		ret = (std::size_t)(2 * (beforeHash - *beforeFirstChar * pow(2.f, patterSize - 1)) + haystack[patterSize - 1]);
		return ret % std::numeric_limits<std::size_t>::max();
	}

	return std::string::npos;
}

std::size_t RabinKarp::FindString(std::string pattern, std::size_t startIndex)
{
	if (false == CheckString(pattern, startIndex))
		return std::string::npos;

	std::string haystack = this->haystack.substr(startIndex);

	std::size_t patternHash = MakeHash(0, nullptr, pattern, pattern.size());
	std::size_t haystackHash = MakeHash(0, nullptr, haystack, pattern.size());
	std::size_t index = 0;
	for (std::size_t i = 0; i <= haystack.size() - pattern.size(); ++i)
	{
		if (patternHash == haystackHash)
		{
			for (index = 0; index < pattern.size(); ++index)
				if (haystack[i + index] != pattern[index])
					break;
			if (pattern.size() == index)
				return startIndex + i;
		}

		if(i != haystack.size() - pattern.size())
			haystackHash = MakeHash(haystackHash, &haystack[i], haystack.substr(i + 1), pattern.size());
	}

	return std::string::npos;
}

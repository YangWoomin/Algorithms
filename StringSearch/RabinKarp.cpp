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

std::size_t RabinKarp::MakeHash(std::size_t index, std::size_t beforeHash, std::string& haystack, std::size_t patternSize)
{
	std::size_t ret = 0;
	if (0 == index) // first H
	{
		for (std::size_t i = 0; i < patternSize; ++i)
		{
			ret += (std::size_t)(haystack[i] * pow(2.f, patternSize - i - 1));
		}
		return ret % std::numeric_limits<std::size_t>::max();
	}
	else // H of i + 1
	{
		ret = (std::size_t)(2 * (beforeHash - haystack[index - 1] * pow(2.f, patternSize - 1)) + haystack[index + patternSize - 1]);
		return ret % std::numeric_limits<std::size_t>::max();
	}

	return std::string::npos;
}

std::size_t RabinKarp::FindString(std::string pattern, std::size_t startIndex)
{
	if (false == CheckString(pattern, startIndex))
		return std::string::npos;

	std::string haystack = this->haystack.substr(startIndex);

	std::size_t patternHash = MakeHash(0, 0, pattern, pattern.size());
	std::size_t haystackHash = MakeHash(0, 0, haystack, pattern.size());
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
			haystackHash = MakeHash(i + 1, haystackHash, haystack, pattern.size());
	}

	return std::string::npos;
}

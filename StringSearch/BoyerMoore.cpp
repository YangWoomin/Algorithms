#include "BoyerMoore.h"
#include <vector>
#include <climits>

BoyerMoore::BoyerMoore()
{

}

BoyerMoore::BoyerMoore(std::string haystack)
	: StringSearch(haystack)
{

}

std::size_t BoyerMoore::FindString(std::string pattern, std::size_t startIndex)
{
	if (false == CheckString(pattern, startIndex))
		return std::string::npos;

	std::string haystack = this->haystack.substr(startIndex);

	const std::size_t patternSize = pattern.size();
	std::vector<std::size_t> badCharTable(CHAR_MAX + 1, patternSize);
	for (std::size_t i = 0; i < patternSize; ++i)
		badCharTable[pattern[i]] = i;
	
	std::vector<std::size_t> goodSuffixTable1(patternSize, patternSize);
	std::size_t index = 0;
	for (std::size_t i = 1; i < patternSize; ++i)
	{
		for (std::size_t j = 0; j < i; ++j)
		{
			for (index = j; index < patternSize - i; ++index)
				if (pattern[index] != pattern[i + index])
					break;
			if (patternSize - i == index)
				goodSuffixTable1[i - 1] = j;
		}
	}

	std::vector<std::size_t> goodSuffixTable2(patternSize, patternSize);
	for (std::size_t i = 1; i < patternSize; ++i)
	{
		for (index = 0; index < i; ++index)
			if (pattern[index] != pattern[patternSize - i + index])
				break;
		if (i == index)
			goodSuffixTable2[patternSize - i - 1] = patternSize - i;
		else
			for (std::size_t j = patternSize - i; j < patternSize; ++j)
				if (patternSize != goodSuffixTable2[j])
					goodSuffixTable2[patternSize - i - 1] = goodSuffixTable2[j];
	}

	int idx = 0;
	std::size_t i = 0, badCharIdx, goodSfxIdx;
	while (i <= haystack.size() - patternSize)
	{
		for (idx = (int)(patternSize - 1); idx >= 0; --idx)
			if (haystack[i + idx] != pattern[idx])
				break;
		if (0 > idx)
			return startIndex + i;
		badCharIdx = badCharTable[haystack[i + idx]];
		if (patternSize == badCharIdx) // cannot find bad char in pattern
			i += ((std::size_t)idx + 1);
		else
		{
			goodSfxIdx = goodSuffixTable1[idx];
			if (badCharIdx < idx && badCharIdx < goodSfxIdx)
			{
				i += (idx - badCharIdx);
				continue;
			}
			else if (patternSize > goodSfxIdx)
			{
				if (0 < goodSfxIdx && haystack[i + index] != pattern[goodSfxIdx - 1])
				{
					i += goodSuffixTable2[idx];
					continue;
				}
				i += goodSuffixTable1[idx];
				continue;
			}

			i += goodSuffixTable2[idx];
		}
	}

	return std::string::npos;
}

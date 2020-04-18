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

	// preprocessing for bad char table
	std::vector<std::size_t> badCharTable(CHAR_MAX + 1, patternSize);
	for (std::size_t i = 0; i < patternSize; ++i)
		badCharTable[pattern[i]] = i;
	
	// preprocessing for good suffix table 1
	// good suffix table 1 index : incorrect index
	// good suffix table 1 value : left good suffix index
	std::vector<std::size_t> goodSuffixTable1(patternSize, patternSize);
	std::size_t index = 0;
	// i : beginning index of right good suffix
	for (std::size_t i = 1; i < patternSize; ++i)
	{
		// j : index for finding left good suffix
		for (std::size_t j = 0; j < i; ++j) 
		{
			// index : index for comparing those strings
			for (index = 0; index < patternSize - i; ++index)
				if (pattern[j + index] != pattern[i + index])
					break;
			if (patternSize - i == index)
				goodSuffixTable1[i - 1] = j;
		}
	}

	// preprocessing  for good suffix table 2
	// good suffix table 2 index : incorrect index
	// good suffix table 2 value : suffix index of the longest border
	std::vector<std::size_t> goodSuffixTable2(patternSize, patternSize);
	std::size_t longestBorderIdx = patternSize;
	// i : border length
	for (std::size_t i = 1; i < patternSize; ++i)
	{
		std::size_t beginningIdxOfPfx = 0;
		const std::size_t beginningIdxOfSfx = patternSize - i;
		for (; beginningIdxOfPfx < i; ++beginningIdxOfPfx)
			if (pattern[beginningIdxOfPfx] != pattern[beginningIdxOfSfx + beginningIdxOfPfx])
				break;
		if (i == beginningIdxOfPfx)
		{
			goodSuffixTable2[beginningIdxOfSfx - 1] = beginningIdxOfSfx;
			longestBorderIdx = beginningIdxOfSfx;
		}
		else
			goodSuffixTable2[beginningIdxOfSfx - 1] = longestBorderIdx;
	}

	int idx = 0;
	std::size_t i = 0, badCharIdx, leftGoodSfxIdx;
	while (i <= haystack.size() - patternSize)
	{
		for (idx = (int)(patternSize - 1); idx >= 0; --idx)
			if (haystack[i + idx] != pattern[idx])
				break;
		if (0 > idx)
			return startIndex + i;

		badCharIdx = badCharTable[haystack[i + idx]];
		leftGoodSfxIdx = goodSuffixTable1[idx];

		if (badCharIdx < idx)
		{
			if (badCharIdx <= leftGoodSfxIdx)
				i += (idx - badCharIdx);
			else
				i += ((std::size_t)idx + 1 - leftGoodSfxIdx);
		}
		else
			i += goodSuffixTable2[idx];
	}

	return std::string::npos;
}

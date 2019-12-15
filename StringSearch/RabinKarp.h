#pragma once

#include "StringSearch.h"

class RabinKarp : public StringSearch
{
private:
	std::size_t MakeHash(std::size_t index, std::size_t beforeHash, std::string& haystack, std::size_t patternSize);

public:
	RabinKarp();
	RabinKarp(std::string haystack);
	virtual std::size_t FindString(std::string pattern, std::size_t startIndex = 0) override;
};
#pragma once

#include "StringSearch.h"

class RabinKarp : public StringSearch
{
private:
	std::size_t MakeHash(std::size_t beforeHash, const char* beforeFirstChar, std::string haystack, std::size_t patterSize);

public:
	RabinKarp(std::string haystack);
	virtual std::size_t FindString(std::string pattern, std::size_t startIndex = 0) override;
};
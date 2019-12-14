#pragma once

#include "StringSearch.h"

class Naive : public StringSearch
{
public:
	Naive();
	Naive(std::string haystack);
	std::size_t FindString(std::string pattern, std::size_t startIndex = 0) override;
};
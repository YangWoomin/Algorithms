#pragma once

#include "StringSearch.h"

class BoyerMoore : public StringSearch
{
public:
	BoyerMoore(std::string haystack);
	virtual std::size_t FindString(std::string pattern, std::size_t startIndex = 0) override;
};
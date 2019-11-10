#pragma once

#include "StringSearch.h"

class KMP : public StringSearch
{
public:
	KMP(std::string haystack);
	virtual std::size_t FindString(std::string pattern, std::size_t startIndex = 0) override;
};


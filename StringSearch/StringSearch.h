#pragma once

#include <string>

class StringSearch
{
protected:
	std::string haystack;

public:
	StringSearch() { }
	StringSearch(std::string haystack) : haystack(haystack) { }
	bool CheckString(std::string pattern, std::size_t startIndex)
	{
		if (0 >= pattern.size())
			return false;

		std::string haystack = this->haystack.substr(startIndex);
		if (haystack.size() < pattern.size())
			return false;

		return true;
	}

	void SetHaystack(std::string haystack)
	{
		this->haystack = haystack;
	}

	virtual std::size_t FindString(std::string pattern, std::size_t startIndex = 0) = 0;
};

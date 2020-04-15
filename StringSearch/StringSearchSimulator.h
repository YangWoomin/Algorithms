#pragma once

#include "StringSearch.h"
#include <map>
#include <memory>

#include <cstdlib>
#include <ctime>

#include <iostream>

class StringSearchSimulator final
{
private:
	typedef StringSearch* StringSearchSPtr;
	typedef std::map<std::string, StringSearchSPtr> StringSearches;
	StringSearches stringSearches;

public:
	StringSearchSimulator() 
	{ 
		static bool init = false;
		if (false == init)
		{
			init = true;
			srand((unsigned int)time(NULL));
		}
	}

	bool AddStringSearch(std::string stringSearchName, StringSearchSPtr stringSearch)
	{
		if (nullptr != stringSearch)
		{
			auto ret = stringSearches.emplace(stringSearchName, stringSearch);
			return ret.second;
		}

		return false;
	}

	bool DoSimulate(std::string haystack, std::string pattern, std::size_t simulationCount, bool showLog)
	{
		if (0 >= stringSearches.size())
			return false;

		if (0 >= haystack.size())
			return false;

		auto itCursor = stringSearches.begin();
		auto itFinish = stringSearches.end();
		for (; itCursor != itFinish; ++itCursor)
			itCursor->second->SetHaystack(haystack);

		for (std::size_t i = 0; i < simulationCount; ++i)
		{
			std::string pat = pattern;
			while (true == pat.empty() || " " == pat)
			{
				std::size_t randIndex = (std::size_t)rand() % haystack.size();
				if (' ' == haystack[randIndex])
					continue;
				std::string temp = haystack.substr(randIndex);
				std::size_t rightSpaceIndex = temp.find(" ");
				if (std::string::npos == rightSpaceIndex)
					pat = temp;
				else
					pat = haystack.substr(randIndex, rightSpaceIndex);
			}
			
			if (showLog)
				std::cout << "[" << i + 1 << "] pattern : " << pat << std::endl;

			itCursor = stringSearches.begin();
			std::size_t index = std::string::npos;
			for (; itCursor != itFinish; ++itCursor)
			{
				std::size_t ret = itCursor->second->FindString(pat);
				if (std::string::npos == index)
					index = ret;
				else if (ret != index)
				{
					if(showLog)
						std::cout << " * " << ret << "  index of  " << itCursor->first << " mismatched with " << index << std::endl;
					return false;
				}
				if (showLog)
					std::cout << itCursor->first << " index : " << (std::string::npos ==  ret ? "npos" : std::to_string(ret)) << std::endl;
			}
		}

		return true;
	}
};

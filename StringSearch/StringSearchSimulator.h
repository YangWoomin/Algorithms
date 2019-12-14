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

	bool DoSimulate(std::string haystack, std::size_t simulationCount, bool showLog)
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
			std::string pattern;
			while (true)
			{
				std::size_t randIndex = (std::size_t)rand() % haystack.size();
				std::string temp = haystack.substr(randIndex);
				std::size_t endIndex1 = temp.find(" ") + randIndex;
				temp = haystack.substr(0, randIndex);
				std::size_t endIndex2 = temp.rfind(" ");
				if (std::string::npos == endIndex1 || std::string::npos == endIndex2)
					continue;
				pattern = haystack.substr(endIndex2, endIndex1 - endIndex2 + 1);
				if (false == pattern.empty() && " " != pattern)
					break;
			}
			
			if (showLog)
				std::cout << "[" << i + 1 << "] pattern : " << pattern << std::endl;

			itCursor = stringSearches.begin();
			std::size_t index = std::string::npos;
			for (; itCursor != itFinish; ++itCursor)
			{
				std::size_t ret = itCursor->second->FindString(pattern);
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

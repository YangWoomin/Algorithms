#include "Naive.h"
#include "RabinKarp.h"
#include "KMP.h"
#include "BoyerMoore.h"

#include <iostream>

using namespace std;

int main()
{
	std::string haystack = "aabbbababbbbbabbbaaabababbba";
	std::string pattern = "bbbb"; // babbb, baaa

	std::cout << "haystack : " << haystack << ", pattern : " << pattern << std::endl;
	
	Naive naive(haystack);
	std::size_t index = naive.FindString(pattern);
	std::cout << "[Naive] found in " << index << std::endl;

	RabinKarp rabin(haystack);
	index = rabin.FindString(pattern);
	std::cout << "[RabinKarp] found in " << index << std::endl;

	KMP kmp(haystack);
	index = kmp.FindString(pattern);
	std::cout << "[KMP] found in " << index << std::endl;

	BoyerMoore boyerMoore(haystack);
	index = boyerMoore.FindString(pattern);
	std::cout << "[BoyerMoore] found in " << index << std::endl;

	return 0;
}
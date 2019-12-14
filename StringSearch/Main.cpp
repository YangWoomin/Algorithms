#include "Naive.h"
#include "RabinKarp.h"
#include "KMP.h"
#include "BoyerMoore.h"

#include "StringSearchSimulator.h"

#include <fstream>

using namespace std;

int main(int argc, char** argv)
{
	if (3 != argc)
	{
		return -1;
	}

	std::size_t simulationCount = (std::size_t)atoi(argv[1]);
	std::string fileName = argv[2];
	ifstream file(fileName);
	if (false == file.is_open())
		return -2;

	std::string haystack, temp;
	while (getline(file, temp))
		haystack += temp;

	StringSearchSimulator simulator;
	simulator.AddStringSearch("Naive", new Naive());
	simulator.AddStringSearch("RabinKarp", new RabinKarp());
	simulator.AddStringSearch("KMP", new KMP());
	simulator.AddStringSearch("BoyerMoore", new BoyerMoore());

	if (true == simulator.DoSimulate(haystack, simulationCount, true)) 
		std::cout << "simulating succeeded" << std::endl;
	else
		std::cout << "simulating failed" << std::endl;

	return 0;
}

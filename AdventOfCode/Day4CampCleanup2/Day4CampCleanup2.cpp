// Day4CampCleanup2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#if defined(__GNUC__) ||defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wc++98-compat"
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <chrono>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string section;
	int fullyoverlapping = 0;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	while (std::getline(inputfile, section))
	{
		size_t commapos = section.find_first_of(',', 0);

		std::string pair1 = section.substr(0, commapos);
		std::string pair2 = section.substr(commapos + 1, section.length());

		int pair1start = stoi(pair1.substr(0, pair1.find_first_of('-', 0)));
		int pair1end = stoi(pair1.substr(pair1.find_first_of('-', 0) + 1, pair1.length()));

		int pair2start = stoi(pair2.substr(0, pair2.find_first_of('-', 0)));
		int pair2end = stoi(pair2.substr(pair2.find_first_of('-', 0) + 1, pair2.length()));

		if ((std::max(pair1start, pair2start) - std::min(pair1end, pair2end)) <= 0)
			fullyoverlapping++;
	}

	std::cout << "Fully overlapping: " << fullyoverlapping << "\n";

	inputfile.close();

	auto stop = std::chrono::high_resolution_clock::now();

	auto duration = duration_cast<std::chrono::microseconds>(stop - start);

	std::cout << "Time taken by function: "
		<< duration.count() << " microseconds\n";

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

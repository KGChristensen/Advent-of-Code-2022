// Day3RucksackReorganization2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

	std::string line1;
	std::string line2;
	std::string line3;
	int itemsum = 0;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	while (std::getline(inputfile, line1))
	{
		std::getline(inputfile, line2);
		std::getline(inputfile, line3);

		bool found = false;

		for (auto chr1 : line1) {
			for (auto chr2 : line2) {
				for (auto chr3 : line3) {

					if (chr1 == chr2 && chr1 == chr3) {
						int priority = (chr1 <= 'Z' ? chr1 - 38 : chr1 - 96);
						//std::cout << chr1 << " (" << priority << ")\n";
						itemsum += priority;
						found = true;
					}
					if (found) break;
				}
				if (found) break;
			}
			if (found) break;
		}

	}

	std::cout << itemsum;

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

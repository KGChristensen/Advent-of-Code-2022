// Day5SupplyStacks1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

	std::string line;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	std::getline(inputfile, line);

	size_t linesections = (line.length() + 1) / 4;

	std::vector<std::vector<std::string>> stacksofcrates(linesections, std::vector<std::string>(0,""));

	do
	{
		if (line.substr(0, 4).compare("move") == 0) {

			int move = stoi(line.substr(5, line.find_first_of(' ') - 5));

			std::istringstream issfrom(line.substr(line.find_first_of('f') + 4, line.find_first_of('t') - 1));
			size_t from;
			issfrom >> from;

			std::istringstream issto(line.substr(line.find_first_of('t') + 2, line.length()));
			size_t to;
			issto >> to;

			while (move--) {
				stacksofcrates[to - 1].push_back(stacksofcrates[from-1].back());
				stacksofcrates[from - 1].pop_back();
			}

		} else if (!line.empty() && line.substr(0, 3).compare(" 1 ") != 0){
			for (size_t shift = 0; shift < linesections; shift ++) {
				std::string crate = line.substr(shift * 4, 3);
				if (crate.find_first_of(' '))
					stacksofcrates[shift].insert(stacksofcrates[shift].begin(), crate);
			}
		}

	} while (std::getline(inputfile, line));

	for (auto stack : stacksofcrates) {
		std::cout << stack.back().substr(1,1);
	}

	std::cout << "\n";

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

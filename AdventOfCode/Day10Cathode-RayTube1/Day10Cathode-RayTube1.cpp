// Day10Cathode-RayTube1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#if defined(__GNUC__) ||defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wc++98-compat"
#pragma GCC diagnostic ignored "-Wc++98-compat-pedantic"
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
#include <ranges>
#include <chrono>
#include <stack>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	int cycles = 0;
	int registerX = 1;
	int sumofsignalstrengths = 0;
	std::set<int> signalstrengths = { 20, 60, 100, 140, 180, 220 };

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	while (std::getline(inputfile, line))
	{
		char instruction = line[0];

		cycles++;

		if (signalstrengths.contains(cycles)) {
			sumofsignalstrengths += (cycles * registerX);
		}

		if (instruction == 'a') {
			int value = stoi(line.substr(5, line.length() - 5));
			cycles++;
			
			if (signalstrengths.contains(cycles)) {
				sumofsignalstrengths += (cycles * registerX);
			}
			registerX += value;

		}

	}


	std::cout << "Sum of signal strengths: " << sumofsignalstrengths << "\n";

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

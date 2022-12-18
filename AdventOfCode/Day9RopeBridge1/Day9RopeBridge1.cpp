// Day9RopeBridge1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
	std::set<std::pair<int, int>> visitedpositions;	// coors of (x,y)
	//long long int visitedpositions = 0;
	int xaxis = 0;							// left to right
	int yaxis = 0;							// top to bottom
	int headcurrentposition[2] = { 0,0 };	// Initialize starting point (x,y)
	int tailcurrentposition[2] = { 0,0 };	// Initialize starting point (x,y)

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	while (std::getline(inputfile, line))
	{
		char direction = line[0];
		int steps = stoi(line.substr(2, line.length() - 2));
		//std::cout << direction << ": " << steps << "\n";

		if (direction == 'R') {				// Move head right

			while (steps--) {
				headcurrentposition[0]++;

				if (std::abs(headcurrentposition[0] - tailcurrentposition[0]) > 1) {
					tailcurrentposition[0] = headcurrentposition[0] - 1;
					tailcurrentposition[1] = headcurrentposition[1];
				}
				//else {
				//	tailcurrentposition[0] = headcurrentposition[0] - 1;
				//}
				visitedpositions.insert(std::make_pair(tailcurrentposition[0], tailcurrentposition[1]));
			}

		}
		else if (direction == 'L') {
			while (steps--) {
				headcurrentposition[0]--;

				if (std::abs(headcurrentposition[0] - tailcurrentposition[0]) > 1) {
					tailcurrentposition[0] = headcurrentposition[0] + 1;
					tailcurrentposition[1] = headcurrentposition[1];
				}
				//else {
				//	tailcurrentposition[0] = headcurrentposition[0] - 1;
				//}
				visitedpositions.insert(std::make_pair(tailcurrentposition[0], tailcurrentposition[1]));
			}

		} 
		else if (direction == 'U') {
			while (steps--) {
				headcurrentposition[1]++;

				if (std::abs(headcurrentposition[1] - tailcurrentposition[1]) > 1) {
					tailcurrentposition[1] = headcurrentposition[1] - 1;
					tailcurrentposition[0] = headcurrentposition[0];
				}
				//else {
				//	tailcurrentposition[1] = headcurrentposition[1] - 1;
				//}
				visitedpositions.insert(std::make_pair(tailcurrentposition[0], tailcurrentposition[1]));
			}
		}
		else if (direction == 'D') {
			while (steps--) {
				headcurrentposition[1]--;

				if (std::abs(headcurrentposition[1] - tailcurrentposition[1]) > 1) {
					tailcurrentposition[1] = headcurrentposition[1] + 1;
					tailcurrentposition[0] = headcurrentposition[0];
				}
				//else {
				//	tailcurrentposition[1] = headcurrentposition[1] - 1;
				//}
				visitedpositions.insert(std::make_pair(tailcurrentposition[0], tailcurrentposition[1]));
			}
		}

	}

	std::cout << "Visited positions: " << visitedpositions.size() << "\n";

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

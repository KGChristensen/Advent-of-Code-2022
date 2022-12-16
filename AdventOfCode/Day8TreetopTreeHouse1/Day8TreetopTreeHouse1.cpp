// Day8TreetopTreeHouse1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <ranges>
#include <chrono>
#include <stack>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	std::vector<std::vector<char>> forest;
	long long int visibletrees = 0;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	while (std::getline(inputfile, line))
	{
		std::vector<char> horizontalline;

		for (auto ch : line) {
			horizontalline.emplace_back(ch);
		}
		forest.push_back(horizontalline);
	}

	const size_t vercount = forest.size() - 1;								// Towards bottom
	const size_t hozcount = forest.front().size() - 1;						// To the right

	visibletrees += (vercount * 2) + (hozcount * 2);						// Calculate visible edges

	for (size_t vertical = 1; vertical < vercount; vertical++) {			// Loop top to bottom
		for (size_t horizontal = 1; horizontal < hozcount; horizontal++) {	// Loop left to right

			const char tree = forest[vertical][horizontal];					// get current tree

			bool ishighesttree[4] = { true, true, true, true };				// Top, Left, Right, Bottom

			for (size_t i = 0; i < (vercount + 1); i++) {					// Look up to down according to current tree

				const char treeinline = forest[i][horizontal];

				if (i < vertical) {											// Above
					ishighesttree[0] = tree > treeinline ? ishighesttree[0] : false;
				}
				else if (i > vertical) {									// Below
					ishighesttree[3] = tree > treeinline ? ishighesttree[3] : false;
				}

			}

			for (size_t j = 0; j < (hozcount + 1); j++) {					// Look left to right according to current tree

				const char treeinline = forest[vertical][j];

				if (j < horizontal) {										// Left
					ishighesttree[1] = tree > treeinline ? ishighesttree[1] : false;
				}
				else if (j > horizontal) {									// Right
					ishighesttree[2] = tree > treeinline ? ishighesttree[2] : false;
				}

			}

			bool highesttree = false;
			for (bool t : ishighesttree) {
				if (t) highesttree = true;
			}

			if (highesttree) { 
				visibletrees++; 
			}

		}

	}

	std::cout << "Visible trees: " << visibletrees << "\n";

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

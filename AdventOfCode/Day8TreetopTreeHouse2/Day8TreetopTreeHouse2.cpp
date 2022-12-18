// Day8TreetopTreeHouse2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
	unsigned long long highestscenicscore = 0;

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

	for (size_t vertical = 1; vertical < vercount; vertical++) {			// Loop top to bottom
		for (size_t horizontal = 1; horizontal < hozcount; horizontal++) {	// Loop left to right

			const char tree = forest[vertical][horizontal];					// get current tree

			unsigned long long distancesfromtree[4] = { 0,0,0,0 };			// Top, Left, Right, Bottom

			for (size_t i = 0; i < (vercount + 1); i++) {					// Look up to down according to current tree

				const char treeinline = forest[i >= vertical ? i : (vertical - i - 1)][horizontal];

				if (i < vertical) {											// Above
					distancesfromtree[0] = (i + 1);
					if (tree <= treeinline)
						i = vertical;
				}
				else if (i > vertical) {									// Below
					distancesfromtree[3] = (i - vertical);
					if (tree <= treeinline)
						i = (vercount + 1);
				}

			}

			for (size_t j = 0; j < (hozcount + 1); j++) {					// Look left to right according to current tree

				const char treeinline = forest[vertical][j >= horizontal ? j : (horizontal - j - 1)];

				if (j < horizontal) {										// Left
					distancesfromtree[1] = (j + 1);
					if (tree <= treeinline)
						j = horizontal;
				}
				else if (j > horizontal) {									// Right
					distancesfromtree[2] = (j - horizontal);
					if (tree <= treeinline) 
						j = (hozcount + 1);
				}

			}

			highestscenicscore = std::max(highestscenicscore, (distancesfromtree[0] * distancesfromtree[1] * distancesfromtree[2] * distancesfromtree[3]));

		}

	}

	std::cout << "Highest scenic score: " << highestscenicscore << "\n";

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

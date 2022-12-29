// Day14RegolithReservoir1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <array>
#include <set>
#include <queue>
#include <ranges>
#include <variant>
#include <tuple>
#include <chrono>
#include <stack>
#include <charconv>

[[maybe_unused]] static void printCave(std::vector<std::vector<int>>& cave) {

	for (size_t ydown = 0; ydown < cave.size(); ydown++) {

		std::cout << std::setw(3) << std::setfill('0') << ydown << " ";

		for (size_t xright = 0; xright < cave[0].size(); xright++) {

			auto i = cave[ydown][xright];

			if (i == 0)
				std::cout << ".";
			else if (i == 1)
				std::cout << "+";
			else if (i == 2)
				std::cout << "#";
			else if (i == 3)
				std::cout << "o";

		}

		std::cout << "\n";

	}

}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string rockpath;
	std::vector<std::vector<int>> cave;				// Air (0), Source of the sand (1), Rock (2), sand (3)
	std::vector<std::pair<int,int>> allrockpaths;	// All rock paths
	std::pair<int, int> Sourceofsand{ 0, 500 };		// Source of sand
	bool sandflowsintotheabyss = false;
	int sandcount = 0;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	while (std::getline(inputfile, rockpath))
	{
		auto it = rockpath.begin();
		auto end = rockpath.end();

		std::vector<int> rockpaths;

		while (it != end) {
			if (std::isdigit(*it)) {
				auto endofint = std::ranges::find_if(it, end, [](auto c) {
					return c == ',' || c == ' ';
					});
				int v = std::stoi(std::string{ it, end });
				rockpaths.emplace_back(v);

				it = endofint;
			}
			else {
				++it;
			}

		}

		for (size_t pathidx = 0; pathidx < rockpaths.size(); pathidx += 2) {
			int currentpointx = rockpaths[pathidx];
			int currentpointy = rockpaths[pathidx + 1];

			if (pathidx < (rockpaths.size() - 2)) {
				int nextpointx = rockpaths[pathidx + 2];
				int nextpointy = rockpaths[pathidx + 3];

				if (currentpointx == nextpointx) {				// Rock path to left or right
					int rangey = nextpointy - currentpointy;
					for (size_t yIdx = 0; yIdx <= static_cast<unsigned int>(std::abs(rangey)); yIdx++) {
						allrockpaths.push_back(std::make_pair((rangey > 0 ? currentpointy++ : currentpointy--), currentpointx));
					}
				}
				else {											// Rock path to top or bottom
					int rangex = nextpointx - currentpointx;
					for (size_t xIdx = 0; xIdx <= static_cast<unsigned int>(std::abs(rangex)); xIdx++) {
						allrockpaths.push_back(std::make_pair(currentpointy, (rangex > 0 ? currentpointx++ : currentpointx--)));

					}

				}
			}
		}

	}

	int maxy = std::max_element(allrockpaths.begin(), allrockpaths.end(), [](const auto& lhs, const auto& rhs) { return lhs.first < rhs.first; })->first;
	int maxx = std::max_element(allrockpaths.begin(), allrockpaths.end(), [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; })->second;

	for (int y = 0; y <= maxy; y++) {
		std::vector<int> tmpv;
		for (int x = 0; x <= maxx; x++) {


			if (std::find_if(allrockpaths.begin(), allrockpaths.end(), [x,y](const std::pair<int, int>& element) { return element.first == y && element.second == x; }) != allrockpaths.end())
				tmpv.push_back(2);
			else
				tmpv.push_back(0);
		}
		cave.push_back(tmpv);
	}

	cave[static_cast<unsigned int>(Sourceofsand.first)][static_cast<unsigned int>(Sourceofsand.second)] = 1;

	//printCave(cave);

	// Drop sand

	while (!sandflowsintotheabyss) {

		// Span new sand
		std::pair<int, int> sand = Sourceofsand;

		bool hitobsticle = false;

		for (size_t yIdx = 0; yIdx < (cave.size()); yIdx++) {
			if (cave[yIdx][static_cast<unsigned int>(sand.second)] > 1) {			// Hits obstacle

				if (sand.second <= 0 || sand.first > maxy) {
				//if (sand.second <= 0) {
					sandflowsintotheabyss = true;
					break;
				}

				if (cave[yIdx][static_cast<unsigned int>(sand.second - 1)] < 2) {
					sand.second -= 1;					// Continue
				}
				else if (cave[yIdx][static_cast<unsigned int>(sand.second + 1)] < 2) {
					sand.second += 1;
				}
				else {
					cave[yIdx - 1][static_cast<unsigned int>(sand.second)] = 3;			// Sand comes to rest
					hitobsticle = true;
					sandcount++;
					yIdx = cave.size();
					break;
				}
			}

		}

		if (!hitobsticle) {
			sandflowsintotheabyss = true;
		}

	}
	
	//printCave(cave);
	
	std::cout << "Units of sand: " << sandcount << "\n";

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

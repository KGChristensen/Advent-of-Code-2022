// Day14RegolithReservoir1-optimized.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string rockpath;
	std::set<std::pair<int, int>> allrockpaths;		// All rock paths
	std::pair<int, int> Sourceofsand{ 500, 0 };		// Source of sand
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
						allrockpaths.insert(std::make_pair(currentpointx, (rangey > 0 ? currentpointy++ : currentpointy--)));
					}
				}
				else {											// Rock path to top or bottom
					int rangex = nextpointx - currentpointx;
					for (size_t xIdx = 0; xIdx <= static_cast<unsigned int>(std::abs(rangex)); xIdx++) {
						allrockpaths.insert(std::make_pair((rangex > 0 ? currentpointx++ : currentpointx--), currentpointy));

					}

				}
			}
		}

	}

	int maxy = std::max_element(allrockpaths.begin(), allrockpaths.end(), [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; })->second;
	
	while (true) {
		auto does_sand_come_to_rest = [&allrockpaths, Sourceofsand, maxy]() {

			std::pair<int, int> sand = Sourceofsand;

			while (sand.second <= maxy) {

				auto itbelow = allrockpaths.find(std::pair<int, int>(sand.first, sand.second + 1));
				if (itbelow == std::end(allrockpaths)) {
					sand.second++;
					continue;
				}

				//if (std::find_if(
				//	allrockpaths.begin(),
				//	allrockpaths.end(),
				//	[sand](std::pair<int, int> const& rock) {
				//		if (rock.first == sand.first && rock.second == (sand.second + 1)) return true;
				//		else return false;
				//	}
				//) == std::end(allrockpaths)) {
				//	sand.second++;
				//	continue;
				//}

				auto itleft = allrockpaths.find(std::pair<int, int>(sand.first - 1, sand.second + 1));
				if (itleft == std::end(allrockpaths)) {
					sand.first--;
					sand.second++;
					continue;
				}

				//if (std::find_if(
				//	allrockpaths.begin(),
				//	allrockpaths.end(),
				//	[sand](std::pair<int, int> const& rock) {
				//		if (rock.first == (sand.first - 1) && rock.second == (sand.second + 1)) return true;
				//		else return false;
				//	}
				//) == std::end(allrockpaths)) {
				//	sand.first--;
				//	sand.second++;
				//	continue;
				//}

				auto itright = allrockpaths.find(std::pair<int, int>(sand.first + 1, sand.second + 1));
				if (itright == std::end(allrockpaths)) {
					sand.first++;
					sand.second++;
					continue;
				}

				//if (std::find_if(
				//	allrockpaths.begin(),
				//	allrockpaths.end(),
				//	[sand](std::pair<int, int> const& rock) {
				//		if (rock.first == (sand.first + 1) && rock.second == (sand.second + 1)) return true;
				//		else return false;
				//	}
				//) == std::end(allrockpaths)) {
				//	sand.first++;
				//	sand.second++;
				//	continue;
				//}

				allrockpaths.insert(sand);
				return true;
			}
			return false;

		}();

		if (!does_sand_come_to_rest)
			break;

		sandcount++;

	}

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

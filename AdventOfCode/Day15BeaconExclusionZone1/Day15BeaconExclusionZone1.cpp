// Day15BeaconExclusionZone1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

	std::string sensorreport;
	std::set<int> positionsdonotcontainbeacons;
	const int fixedrowy = 2000000;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	//int minx = INT_MAX;
	//int maxx = INT_MIN;

	//int miny = INT_MAX;
	//int maxy = INT_MIN;

	while (std::getline(inputfile, sensorreport))
	{
		int sensorx = stoi(sensorreport.substr(sensorreport.find_first_of('=') + 1, sensorreport.find_first_of(',') - sensorreport.find_first_of('=') - 1));
		int sensory = stoi(sensorreport.substr(sensorreport.find_first_of(',') + 4, sensorreport.find_first_of(':') - sensorreport.find_first_of(',') - 4));

		int beaconx = stoi(sensorreport.substr(sensorreport.find_first_of(':') + 25, sensorreport.find_last_of(',') - (sensorreport.find_first_of(':') + 25)));
		int beacony = stoi(sensorreport.substr(sensorreport.find_last_of('=') + 1, sensorreport.length()));

		int manhattandistance = (std::abs(sensorx - beaconx) + std::abs(sensory - beacony));

		//minx = std::min(minx, std::min(sensorx, beaconx));
		//maxx = std::max(maxx, std::max(sensorx, beaconx));

		//miny = std::min(miny, std::min(sensory, beacony));
		//maxy = std::max(maxy, std::max(sensory, beacony));



		if ((fixedrowy <= (sensory + manhattandistance)) && (fixedrowy >= sensory - manhattandistance)) {
			int startx = sensorx - (manhattandistance - std::abs(sensory - fixedrowy));
			int endx = sensorx + (manhattandistance - std::abs(sensory - fixedrowy));

			//positionsdonotcontainbeacons += (endx - startx);

			for (int count = startx; count < endx; count++) {
				positionsdonotcontainbeacons.insert(count);
			}

		}


	}

	//std::cout << "Min x: " << minx << "\n";
	//std::cout << "Max x: " << maxx << "\n";

	//std::cout << "Min y: " << miny << "\n";
	//std::cout << "Max y: " << maxy << "\n";

	//for (size_t y = 0; y < 27; y++) {
	//	for (size_t x = 0; x < 22; x++) {
	//		std::cout << ".";
	//	}
	//	std::cout << "\n";
	//}

	std::cout << "Number of positions that do not contain a beacon; " << positionsdonotcontainbeacons.size() << "\n";
	//std::cout << "Number of positions that do not contain a beacon; " << positionsdonotcontainbeacons << "\n";

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

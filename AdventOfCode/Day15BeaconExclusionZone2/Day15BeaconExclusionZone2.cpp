// Day15BeaconExclusionZone2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
	std::vector<std::pair<long long, long long>> sensors;
	std::vector<std::pair<long long, long long>> beacons;
	std::vector<long long> positivelines;
	std::vector<long long> negativelines;
	std::vector<long long> distances;

	long long positive = LLONG_MAX;
	long long negative = LLONG_MAX;

	long long x = 0;
	long long y = 0;

	long long tuningfrequency = 4000000;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	while (std::getline(inputfile, sensorreport))
	{
		int sensorx = stoi(sensorreport.substr(sensorreport.find_first_of('=') + 1, sensorreport.find_first_of(',') - sensorreport.find_first_of('=') - 1));
		int sensory = stoi(sensorreport.substr(sensorreport.find_first_of(',') + 4, sensorreport.find_first_of(':') - sensorreport.find_first_of(',') - 4));

		sensors.push_back(std::make_pair(sensorx, sensory));

		int beaconx = stoi(sensorreport.substr(sensorreport.find_first_of(':') + 25, sensorreport.find_last_of(',') - (sensorreport.find_first_of(':') + 25)));
		int beacony = stoi(sensorreport.substr(sensorreport.find_last_of('=') + 1, sensorreport.length()));

		beacons.push_back(std::make_pair(beaconx, beacony));

		distances.push_back(std::abs(sensorx - beaconx) + std::abs(sensory - beacony));

	}

	for (size_t distanceidx = 0; distanceidx < sensors.size(); distanceidx++) {
		long long distance = distances[distanceidx];
		negativelines.push_back(sensors[distanceidx].first + sensors[distanceidx].second - distance);
		negativelines.push_back(sensors[distanceidx].first + sensors[distanceidx].second + distance);
		positivelines.push_back(sensors[distanceidx].first - sensors[distanceidx].second - distance);
		positivelines.push_back(sensors[distanceidx].first - sensors[distanceidx].second + distance);
	}

	for (size_t i = 0; i < (2 * sensors.size()); i++) {
		for (size_t j = (i+1); j < (2 * sensors.size()); j++) {
			long long a = positivelines[i];
			long long b = positivelines[j];

			if (std::abs(a - b) == 2) {
				positive = std::min(a, b) + 1;
			}

			a = negativelines[i];
			b = negativelines[j];

			if (std::abs(a - b) == 2) {
				negative = std::min(a, b) + 1;
			}

		}

	}

	x = static_cast<long long>(std::floor((positive + negative) / 2));
	y = static_cast<long long>(std::floor((negative - positive) / 2));

	tuningfrequency = x * tuningfrequency + y;

	std::cout << "Number of positions that do not contain a beacon; " << tuningfrequency << "\n";

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

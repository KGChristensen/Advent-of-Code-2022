// Day16ProboscideaVolcanium1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <bitset>
#include <set>
#include <queue>
#include <ranges>
#include <variant>
#include <tuple>
#include <chrono>
#include <stack>
#include <charconv>
#include <cassert>

static unsigned long long f(auto& E, auto &R, auto& DP, unsigned long long p1, unsigned long long U, unsigned long long time, unsigned long long other_players) {
	if (time == 0) {
		return other_players > 0 ? f(E, R, DP, 0, U, 26, other_players - 1) : 0ll;
	}

	auto key = U * R.size() * 31 * 2 + p1 * 31 * 2 + time * 2 + other_players;
	if (DP[key] >= 0) {
		return std::make_unsigned_t<unsigned long long>(DP[key]);
	}

	unsigned long long ans = 0;
	bool no_p1 = ((U & (1ll << p1)) == 0);
	if (no_p1 && R[p1] > 0) {
		unsigned long long newU = U | (1ll << p1);
		assert(newU > U);
		ans = std::max(ans, (time - 1) * R[p1] + f(E, R, DP, p1, newU, time - 1ULL, other_players));
	}
	for (auto& y : E[p1]) {
		ans = std::max(ans, f(E, R, DP, y, U, time - 1, other_players));
	}
	DP[key] = static_cast<long long>(ans);

	return ans;
}



int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string valve_output;

	std::map<std::string, std::pair<unsigned long long, std::vector<std::string>>> valves;

	std::vector<std::vector<unsigned long long>> E;
	std::vector<unsigned long long> R;
	std::vector<long long> DP;

	std::map<std::string, long long> INDEX_OF;
	std::vector<std::string> ORDER;
	unsigned long long nonzero = 0;
	unsigned long long mostpressurepossible = 0;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	while (std::getline(inputfile, valve_output))
	{
		std::string label = valve_output.substr(6, 2);

		int flowrate = stoi(valve_output.substr(23, valve_output.find(';') - 23));

		std::vector<std::string> tunnelsleadingvalves;
		std::string valvesleading = valve_output.substr(valve_output.find(';') + 24, valve_output.length() - (valve_output.find(';') + 24));
		for (size_t vlidx = 0; vlidx < valvesleading.length(); vlidx++) {
			if (valvesleading[vlidx] != ' ') {
				tunnelsleadingvalves.push_back(valvesleading.substr(vlidx, 2));
				vlidx += 3;
			}
		}

		valves[label] = std::make_pair(flowrate, tunnelsleadingvalves);

	}

	size_t n = valves.size();



	// Convenient to have the start position have index 0
	for (auto& v : valves) {
		if (v.first == "AA") {
			INDEX_OF[v.first] = static_cast<long long>(ORDER.size());
			ORDER.push_back(v.first);
			nonzero++;
		}
	}

	// put valves with non-zero flow rate first
	for (auto& v : valves) {
		if (v.second.first > 0) {
			INDEX_OF[v.first] = static_cast<long long>(ORDER.size());
			ORDER.push_back(v.first);
			nonzero++;
		}
	}

	for (auto& v : valves) {
		if (INDEX_OF.count(v.first) == 0) {
			INDEX_OF[v.first] = static_cast<long long>(ORDER.size());
			ORDER.push_back(v.first);
		}
	}

	R = std::vector<unsigned long long>(n, 0);
	for (size_t i = 0; i < n; i++) {
		R[i] = valves[ORDER[i]].first;
	}
	E = std::vector<std::vector<unsigned long long>>(n, std::vector<unsigned long long>{});
	for (size_t i = 0; i < n; i++) {
		for (auto& y : valves[ORDER[i]].second) {
			E[i].push_back(std::make_unsigned_t<unsigned long long>(INDEX_OF[y]));
		}
	}

	DP = std::vector<long long>((1L << nonzero) * n * 31 * 2, -1);


	mostpressurepossible = f(E, R, DP, 0, 0, 30, false);


	//std::cout << releasedpressures[releasedpressures.size()-1] << "\n";

	std::cout << "Most pressure possible: " << mostpressurepossible << "\n";

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

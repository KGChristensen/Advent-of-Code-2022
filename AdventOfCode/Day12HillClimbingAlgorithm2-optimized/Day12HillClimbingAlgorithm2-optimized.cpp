// Day12HillClimbingAlgorithm2-optimized.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <chrono>
#include <stack>

struct coord {

	//coord() { puts("coord() - Default constructor"); }																		// Default constructor
	//coord(const coord &) { puts("coord(const coord &) - Copy construction"); }												// Copy construction
	//coord(coord&&) noexcept { puts("coord(coord&&) - Move construction"); }													// Move construction
	//~coord() { puts("~coord() - Destructor"); }																				// Destructor
	//coord &operator=(const coord&) { puts("coord &operator=(const coord &) - Copy assignment operator"); return *this; }	// Copy assignment operator
	//coord &operator=(coord&&) noexcept { puts("coord &operator=(coord&&) - Move assignment operator"); return *this; }		// Move assignment operator

	int x;
	int y;

	friend auto operator <=> (coord const&, coord const&) = default;
};

struct entry {
	coord c;
	int n_steps;
};

std::pair<std::vector<coord>, coord> get_start_end_pos(auto& lines) {
	std::vector<coord>startingpoints;
	coord endingpoint;
	for (int lineidx = 0; std::string line : lines) {
		for (int charidx = 0;  char c : line) {
			if (c == 'S' or c == 'a')
				startingpoints.push_back(coord{ charidx, lineidx });
			else if (c == 'E') 
				endingpoint = { charidx, lineidx };
			++charidx;
		}
		++lineidx;
	}
	return std::pair(startingpoints,endingpoint);
}

auto get_neighbors(coord c) {
	return std::array{
		coord{c.x + 1, c.y},
		coord{c.x - 1, c.y},
		coord{c.x, c.y + 1},
		coord{c.x, c.y - 1},
	};
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	std::vector<std::string> lines;
	std::vector<int> steps;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	while (std::getline(inputfile, line))
	{
		lines.push_back(line);
	}

	auto [startingpoints, endingpoint] = get_start_end_pos(lines);

	for (auto startingpoint : startingpoints) {

		std::queue<entry> q;
		std::set<coord> visited{ startingpoint };

		q.push(entry{ startingpoint,0 });

		auto valid = [&](coord from, coord to) {

			auto in_bounds = to.x >= 0 && to.x < lines[0].size()
				&& to.y >= 0 && to.y < lines.size();

			if (!in_bounds) return false;

			auto to_char = lines[to.y][to.x];
			to_char = to_char == 'E' ? 'z' : to_char;

			auto from_char = lines[from.y][from.x];
			from_char = from_char == 'S' ? 'a' : from_char;

			return (to_char - from_char <= 1)
				&& !visited.contains(to);
		};

		// Breadth first search
		while (!q.empty() && q.front().c != endingpoint) {
			auto [front_coord, front_steps] = q.front();
			q.pop();

			for (coord neighbor : get_neighbors(front_coord)) {
				if (valid(front_coord, neighbor)) {
					visited.insert(neighbor);
					q.push(entry{ neighbor, front_steps + 1 });
				}
			}
		}

		if (!q.empty())
			steps.push_back(q.front().n_steps);

	}

	std::sort(steps.begin(), steps.end(), std::greater<int>());

	for (auto s : steps) {
		std::cout << s << "\n";
	}

	std::cout << "Shortest steps: " << steps[steps.size() - 1] << "\n";

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

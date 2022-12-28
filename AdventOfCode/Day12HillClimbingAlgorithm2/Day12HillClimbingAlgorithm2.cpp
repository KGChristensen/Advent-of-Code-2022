// Day12HillClimbingAlgorithm2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

struct elevationnode {

	//elevationnode() { puts("elevationnode() - Default constructor"); }																						// Default constructor
	//elevationnode(const elevationnode &) { puts("elevationnode(const elevationnode &) - Copy construction"); }												// Copy construction
	//elevationnode(elevationnode&&) noexcept { puts("elevationnode(elevationnode&&) - Move construction"); }													// Move construction
	//~elevationnode() { puts("~elevationnode() - Destructor"); }																								// Destructor
	//elevationnode &operator=(const elevationnode&) { puts("elevationnode &operator=(const elevationnode &) - Copy assignment operator"); return *this; }	// Copy assignment operator
	//elevationnode &operator=(elevationnode&&) noexcept { puts("elevationnode &operator=(elevationnode&&) - Move assignment operator"); return *this; }		// Move assignment operator

	char c;
	int f;
	int g;
	int h;
	int x;
	int y;
	std::vector<std::pair<int, int>> neighbors;
	std::pair<int, int> previous{ INT_MIN,INT_MIN };
};

static void printHeightmap(std::vector<std::vector<elevationnode>>& map, std::vector<std::pair<int, int>>& todo, std::vector<std::pair<int, int>>& done, std::vector<std::pair<int, int>>& path) {

	for (int rowid = 0; auto m : map) {
		for (int colid = 0; auto n : m) {
			char o = n.c;

			for (auto t : todo) {
				if (t.first == colid && t.second == rowid) {
					o = ' ';
				}
			}

			for (auto d : done) {
				if (d.first == colid && d.second == rowid) {
					o = '@';
				}
			}

			for (auto p : path) {
				if (p.first == colid && p.second == rowid) {
					o = '%';
				}
			}

			std::cout << o;
			++colid;
		}
		++rowid;
		std::cout << "\n";
	}

}

static int heuristic(const std::pair<int, int> n, const std::pair<int, int> ep) {
	return std::abs(n.first - ep.first) + std::abs(n.second - ep.second);
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	std::vector<std::vector<elevationnode>> heightmap;			// y , x
	std::vector<std::pair<int, int>> openSet;					// x (>),y (V)
	std::vector<std::pair<int, int>> closedSet;
	std::vector<std::pair<int, int>> path;
	std::pair<int, int> startingpoint;
	std::pair<int, int> endingpoint;
	std::vector<int> steps;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	while (std::getline(inputfile, line))
	{
		std::vector<elevationnode> heightmaprow;
		for (char& c : line) {
			elevationnode e;
			e.c = c;
			e.f = 0;
			e.g = 0;
			e.h = 0;

			e.y = heightmap.size();					// VVVVVV
			e.x = heightmaprow.size();				// >>>>>>

			if (c == 'S') {				// Find starting point
				e.c = 'a';
				//startingpoint = std::make_pair(heightmaprow.size(), heightmap.size());
				//openSet.push_back(std::make_pair(heightmaprow.size(), heightmap.size()));
			}
			else if (c == 'E') {		// Find ending point
				e.c = 'z';
				endingpoint = std::make_pair(heightmaprow.size(), heightmap.size());
			}
			heightmaprow.push_back(e);

		}
		heightmap.push_back(heightmaprow);
	}

	//closedSet.push_back(std::make_pair(1,2));

	//printHeightmap(heightmap, openSet, closedSet, path);

	for (int rowid = 0; auto m : heightmap) {
		for (int colid = 0; auto n : m) {

			if (colid > 0) {													// Left
				if (heightmap[rowid][colid].c + 1 >= heightmap[rowid][colid - 1].c)
					heightmap[rowid][colid].neighbors.push_back(std::make_pair(colid - 1, rowid));
			}
			if (colid < heightmap[0].size() - 1) {								// right
				if (heightmap[rowid][colid].c + 1 >= heightmap[rowid][colid + 1].c)
					heightmap[rowid][colid].neighbors.push_back(std::make_pair(colid + 1, rowid));
			}
			if (rowid > 0) {													// Top
				if (heightmap[rowid][colid].c + 1 >= heightmap[rowid - 1][colid].c)
					heightmap[rowid][colid].neighbors.push_back(std::make_pair(colid, rowid - 1));
			}
			if (rowid < heightmap.size() - 1) {									// Bottom
				if (heightmap[rowid][colid].c + 1 >= heightmap[rowid + 1][colid].c)
					heightmap[rowid][colid].neighbors.push_back(std::make_pair(colid, rowid + 1));
			}


			++colid;
		}

		++rowid;
	}

	const char findch = 'a';

	for (auto const& heightmaprow : heightmap) {
		auto it = std::find_if(std::begin(heightmaprow), 
							std::end(heightmaprow), 
							[](elevationnode const& data) {
								if (data.c == findch) return true;
								else return false;
							});
		if (it != std::end(heightmaprow)) {
			//std::cout << it[0].x << "," << it[0].y << "\n";
			//std::vector<elevationnode> e = (std::vector<elevationnode>)it;
			startingpoint = std::make_pair(it[0].x, it[0].y);
			openSet.push_back(std::make_pair(it[0].x, it[0].y));
			{

				int pid = 0;

				while (!openSet.empty()) {

					std::pair<int, int> current = openSet[0];

					for (auto node : openSet) {
						if (heightmap[current.second][current.first].f > heightmap[node.second][node.first].f) {
							current = node;
						}
					}

					if (current.first == endingpoint.first && current.second == endingpoint.second) {
						//std::cout << "Done\n";

						std::pair<int, int> temp = current;
						path.push_back(temp);
						while (heightmap[temp.second][temp.first].previous.first != INT_MIN) {

							path.push_back(heightmap[temp.second][temp.first].previous);
							temp = heightmap[temp.second][temp.first].previous;
						}

						break;
						// More?
					}

					auto it = std::remove_if(
						openSet.begin(),
						openSet.end(),
						[current](std::pair<int, int> const& data) {
							if (data.first == current.first && data.second == current.second) return true;
							else return false;
						}
					);

					openSet.erase(it);
					closedSet.push_back(current);

					for (auto neighbor : heightmap[current.second][current.first].neighbors) {

						if (std::find_if(
							closedSet.begin(),
							closedSet.end(),
							[neighbor](std::pair<int, int> const& data) {
								if (data.first == neighbor.first && data.second == neighbor.second) return true;
								else return false;
							}
						) == std::end(closedSet)) {			// Not in closedSet
							int tmpg = heightmap[current.second][current.first].g + 1;


							if (std::find_if(
								openSet.begin(),
								openSet.end(),
								[neighbor](std::pair<int, int> const& data) {
									if (data.first == neighbor.first && data.second == neighbor.second) return true;
									else return false;
								}
							) != std::end(openSet)) {		// In openset
								if (tmpg < heightmap[neighbor.second][neighbor.first].g)
									heightmap[neighbor.second][neighbor.first].g = tmpg;
							}
							else {
								heightmap[neighbor.second][neighbor.first].g = tmpg;
								openSet.push_back(std::make_pair(neighbor.first, neighbor.second));
							}

							heightmap[neighbor.second][neighbor.first].h = heuristic(neighbor, endingpoint);
							heightmap[neighbor.second][neighbor.first].f = heightmap[neighbor.second][neighbor.first].g + heightmap[neighbor.second][neighbor.first].h;
							heightmap[neighbor.second][neighbor.first].previous = current;

						}

					}
					//if (pid == 1663) {
					//	printHeightmap(heightmap, openSet, closedSet, path);
					//	std::cout << "";
					//}
					////std::wcout << "\n(" << pid << ")\n";
					////printHeightmap(heightmap, openSet, closedSet,path);
					//pid++;
				}

				//std::cout << "steps: " << path.size() - 1 << "\n";

				steps.push_back(path.size() - 1);

				openSet.clear();
				closedSet.clear();
				path.clear();

				for (int rowid = 0; auto m : heightmap) {
					for (int colid = 0; auto n : m) {

						heightmap[rowid][colid].f = 0;
						heightmap[rowid][colid].g = 0;
						heightmap[rowid][colid].h = 0;
						heightmap[rowid][colid].previous = std::make_pair(INT_MIN,INT_MIN);
						

						++colid;
					}

					++rowid;
				}

			}
			
		}
	}


	//printHeightmap(heightmap, openSet, closedSet, path);

	std::sort(steps.begin(), steps.end(), std::greater<int>());

	for (auto s : steps) {
		std::cout << s << "\n";
	}

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

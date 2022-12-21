// Day9RopeBridge2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

static void printState(int robepositions[10][2]) {
	const int width = 26;
	const int height = 21;
	const int offsetwidth = 11;
	const int offsetheight = 6;
	const char space = '.';

	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			
			char print = ' ';
			
			//Go throught robes
			for (int r = 10; r >= 0; --r) {
				int rx = robepositions[r][0];
				int ry = robepositions[r][1];

				if (h == (height - (ry+offsetheight))  && w == (rx + offsetwidth)) {
					if (r == 0) {
						print = 'H';
					}
					else  {
						print = char(r)+'0';
					}
				}

			}

			if (print == ' ')
				std::cout << space;
			else
				std::cout << print;
		}
		std::cout << "\n";
	}
	std::cout << "#\n";

}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	std::set<std::pair<int, int>> visitedpositions;													// coors of (x,y)

	int robepositions[10][2] = { {0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0} };		// Initialize starting point (x,y)

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	while (std::getline(inputfile, line))
	{
		char direction = line[0];
		int steps = stoi(line.substr(2, line.length() - 2));

		if (direction == 'R') {																		// Move head right

			while (steps--) {
				robepositions[0][0]++;																// First knot (head)
				
				for (int idx = 1; idx < 10; idx++) {

					int diffx = robepositions[idx - 1][0] - robepositions[idx][0];
					int diffx_abs = std::abs(diffx);
					int diffy = robepositions[idx - 1][1] - robepositions[idx][1];
					int diffy_abs = std::abs(diffy);

					if (diffx_abs == 2 && diffy_abs == 0) {
						robepositions[idx][0] = robepositions[idx - 1][0] - 1;
					}
					else if (diffx_abs == 0 && diffy_abs == 2) {
						robepositions[idx][1] += diffy > 0 ? 1 : -1;
					}
					else if (diffy_abs == 2 && diffx_abs == 1) {
						robepositions[idx][1] += diffy > 0 ? 1 : -1;
						robepositions[idx][0] += diffx > 0 ? 1 : -1;
					}
					else if (diffy_abs == 1 && diffx_abs == 2) {
						robepositions[idx][1] += diffy > 0 ? 1 : -1;
						robepositions[idx][0] += diffx > 0 ? 1 : -1;
					}
					else if (diffy_abs == 2 && diffx_abs == 2) {
						robepositions[idx][1] += diffy > 0 ? 1 : -1;
						robepositions[idx][0] += diffx > 0 ? 1 : -1;
					}
					
					visitedpositions.insert(std::make_pair(robepositions[9][0], robepositions[9][1]));
					
				}

			}
		}
		else if (direction == 'L') {
			while (steps--) {
				robepositions[0][0]--;

				for (int idx = 1; idx < 10; idx++) {

					int diffx = robepositions[idx - 1][0] - robepositions[idx][0];
					int diffx_abs = std::abs(diffx);
					int diffy = robepositions[idx - 1][1] - robepositions[idx][1];
					int diffy_abs = std::abs(diffy);

					if (diffx_abs == 2 && diffy_abs == 0) {
						robepositions[idx][0] = robepositions[idx - 1][0] + 1;
					} else if (diffx_abs == 0 && diffy_abs == 2) {
						robepositions[idx][1] += diffy > 0 ? 1 : -1;
					}
					else if (diffy_abs == 2 && diffx_abs == 1) {
						robepositions[idx][1] += diffy > 0 ? 1 : -1;
						robepositions[idx][0] += diffx > 0 ? 1 : -1;
					}
					else if (diffy_abs == 1 && diffx_abs == 2) {
						robepositions[idx][1] += diffy > 0 ? 1 : -1;
						robepositions[idx][0] += diffx > 0 ? 1 : -1;
					}
					else if (diffy_abs == 2 && diffx_abs == 2) {
						robepositions[idx][1] += diffy > 0 ? 1 : -1;
						robepositions[idx][0] += diffx > 0 ? 1 : -1;
					}

					visitedpositions.insert(std::make_pair(robepositions[9][0], robepositions[9][1]));
				}

			}

		}
		else if (direction == 'U') {

			while (steps--) {
				robepositions[0][1]++;

				for (int idx = 1; idx < 10; idx++) {

					int diffx = robepositions[idx - 1][0] - robepositions[idx][0];
					int diffx_abs = std::abs(diffx);
					int diffy = robepositions[idx - 1][1] - robepositions[idx][1];
					int diffy_abs = std::abs(diffy);

					if (diffy_abs == 2 && diffx_abs == 0) {
						robepositions[idx][1] = robepositions[idx-1][1] - 1;
					} else if (diffy_abs == 0 && diffx_abs == 2) {
						robepositions[idx][0] += diffx > 0 ? 1 : -1;
					}
					else if (diffy_abs == 2 && diffx_abs == 1) {
						robepositions[idx][1] += diffy > 0 ? 1 : -1;
						robepositions[idx][0] += diffx > 0 ? 1 : -1;
					} else if (diffy_abs == 1 && diffx_abs == 2) {
						robepositions[idx][1] += diffy > 0 ? 1 : -1;
						robepositions[idx][0] += diffx > 0 ? 1 : -1;
					}
					else if (diffy_abs == 2 && diffx_abs == 2) {
						robepositions[idx][1] += diffy > 0 ? 1 : -1;
						robepositions[idx][0] += diffx > 0 ? 1 : -1;
					}
					
					visitedpositions.insert(std::make_pair(robepositions[9][0], robepositions[9][1]));
				}

			}
			
		}
		else if (direction == 'D') {
			while (steps--) {
				robepositions[0][1]--;

				for (int idx = 1; idx < 10; idx++) {

					int diffx = robepositions[idx - 1][0] - robepositions[idx][0];
					int diffx_abs = std::abs(diffx);
					int diffy = robepositions[idx - 1][1] - robepositions[idx][1];
					int diffy_abs = std::abs(diffy);

					if (diffy_abs == 2 && diffx_abs == 0) {
						robepositions[idx][1] = robepositions[idx - 1][1] + 1;
					}
					else if (diffy_abs == 0 && diffx_abs == 2) {
						robepositions[idx][0] += diffx > 0 ? 1 : -1;
					}
					else if (diffy_abs == 2 && diffx_abs == 1) {
						robepositions[idx][1] += diffy > 0 ? 1 : -1;
						robepositions[idx][0] += diffx > 0 ? 1 : -1;
					}
					else if (diffy_abs == 1 && diffx_abs == 2) {
						robepositions[idx][1] += diffy > 0 ? 1 : -1;
						robepositions[idx][0] += diffx > 0 ? 1 : -1;
					}
					else if (diffy_abs == 2 && diffx_abs == 2) {
						robepositions[idx][1] += diffy > 0 ? 1 : -1;
						robepositions[idx][0] += diffx > 0 ? 1 : -1;
					}

					visitedpositions.insert(std::make_pair(robepositions[9][0], robepositions[9][1]));
				}

			}

		}

	}

	printState(robepositions);

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

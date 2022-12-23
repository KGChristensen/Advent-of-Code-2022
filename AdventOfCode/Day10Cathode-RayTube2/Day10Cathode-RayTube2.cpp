// Day10Cathode-RayTube2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

static void printCRT(char CRT[6][40], int spritemiddle, int crtdrawingoperations, int cpucycles) {
	const int crtwidetmp = 40;
	const int crthightmp = 6;

	for (int crtpixelh = 0; crtpixelh < crthightmp; crtpixelh++) {
		for (int crtpixelw = 0; crtpixelw < crtwidetmp; crtpixelw++) {

			if (crtpixelw >= (spritemiddle - 1) && crtpixelw <= (spritemiddle + 1) && crtpixelh == crtdrawingoperations)
				std::cout << "S";				// Sprite position
			else if (crtpixelw == (cpucycles % crtwidetmp))
				std::cout << "P";				// Current CRT drawing position
			else
				std::cout << CRT[crtpixelh][crtpixelw];

		}
		std::cout << "\n";
	}
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	const int crtwide = 40;
	const int crthigh = 6;
	int cpucycles = 0;
	int crtdrawingoperations = 0;
	int registerX = 1;
	char CRT[crthigh][crtwide];
	int spritemiddle = 1;

	// Initialize CRT screen
	for (int crtpixelh = 0; crtpixelh < crthigh; crtpixelh++) {
		for (int crtpixelw = 0; crtpixelw < crtwide; crtpixelw++) {
			CRT[crtpixelh][crtpixelw] = '.';
		}
	}

	std::cout << "Starting position:\n";

	printCRT(CRT, spritemiddle, crtdrawingoperations, cpucycles);

	std::cout << "\nDrawing CRT\n";

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	while (std::getline(inputfile, line))
	{
		char instruction = line[0];

		int rowcounter = cpucycles % crtwide;

		if (rowcounter >= (spritemiddle - 1) && rowcounter <= (spritemiddle + 1)) {
			CRT[(cpucycles - rowcounter) / crtwide][rowcounter] = '#';
		}

		crtdrawingoperations = crtdrawingoperations < (crthigh - 1) ? crtdrawingoperations + 1 : 0;
		cpucycles++;

		if (instruction == 'a') {
			int value = stoi(line.substr(5, line.length() - 5));

			rowcounter = cpucycles % crtwide;

			if (rowcounter >= (spritemiddle - 1) && rowcounter <= (spritemiddle + 1)) {
				CRT[(cpucycles - rowcounter) / crtwide][rowcounter] = '#';
			}

			crtdrawingoperations = crtdrawingoperations < (crthigh - 1) ? crtdrawingoperations + 1 : 0;

			registerX += value;
			spritemiddle = registerX;

			cpucycles++;

		}

	}

	std::cout << "\nFinale result:\n";

	printCRT(CRT, INT_MIN, INT_MIN, INT_MIN);

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

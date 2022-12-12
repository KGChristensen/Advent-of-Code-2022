// Day6TuningTrouble2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#if defined(__GNUC__) ||defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wc++98-compat"
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <chrono>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	const int sequencelength = 14;
	const char normalizecharindex = 'a';
	char sequence[sequencelength] = { '\0' };
	char ch = 0;
	int marker = 0;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	while (inputfile.get(ch))
	{

		int curpos = marker % sequencelength;

		sequence[curpos] = ch;

		marker++;

		if (marker >= sequencelength) {

			int checker = 0;

			bool isunique = true;

			for (int pos = 0; pos < sequencelength; pos++) {

				int bitAtIndex = sequence[pos] - normalizecharindex;

				// if that bit is already set in
				// checker, return false
				if ((checker & (1 << bitAtIndex)) > 0) {
					isunique = false;
				}

				// otherwise update and continue by
				// setting that bit in the checker
				checker = checker | (1 << bitAtIndex);
			}

			if (isunique) { std::cout << "Characters processed before the first start-of-packet: " << marker << "\n"; break; }

		}


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

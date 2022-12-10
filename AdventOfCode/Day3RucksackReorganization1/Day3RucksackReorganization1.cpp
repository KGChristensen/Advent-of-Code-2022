// Day3RucksackReorganization1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

	std::string line;
	int itemsum = 0;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	while (std::getline(inputfile, line))
	{
		size_t strlen = line.length();
		size_t offset = strlen / 2;
		
		bool found = false;

		for (size_t chrno1 = 0; chrno1 < offset; chrno1++) {
			char& compartment1 = line[chrno1];

			for (size_t chrno2 = offset; chrno2 < strlen; chrno2++) {
				char& compartment2 = line[chrno2];

				if (compartment1 == compartment2) {
					int priority = (compartment1 <= 'Z' ? compartment1 - 38 : compartment1 - 96);
					//std::cout << compartment1 << " (" << priority << ")\n";
					found = true;
					itemsum += priority;
				}

				if (found) break;

			}
			if (found) break;

		}

		std::cout << itemsum;

		//int charArr[50] = { 0 };
		//for (char &chr : line) {
		//	if (chr >= 'A' && chr <= 'Z')
		//		charArr[chr-'A']++;
		//	else if (chr >= 'a' && chr <= 'z')
		//		charArr[chr - 'a' + 25]++;
		//}

		//std::cout << "finished";
		//std::cout << "\n";

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

// Day7NoSpaceLeftOnDevice1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <ranges>
#include <chrono>
#include <stack>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	const long long int maxsize = 100000;
	long long int totalsize = 0;

	std::map<std::string, long long int> directories;
	std::vector<std::string> navigate;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	//filesystem.emplace_back("- / (dir)");

	while (std::getline(inputfile, line))
	{
		char cmd = line[0];

		if (cmd == '$') {

			if (line.substr(2, 4).compare("cd /") == 0) {
				navigate.clear();
				navigate.emplace_back("/");
			}
			else if (line.substr(2, 5).compare("cd ..") == 0) {
				navigate.pop_back();
			}
			else if (line.substr(2, 3).compare("cd ") == 0) {
				navigate.emplace_back(line.substr(5, line.length() - 5) + "/");
			}

		}
		else {
			if (line.substr(0, 4).compare("dir ") != 0) {

				long long int filesize = stoi(line.substr(0, line.find_first_of(' ')));

				std::string str = std::accumulate(navigate.begin(), navigate.end(), std::string{});

				if (!directories.contains(str)) {
					directories.emplace(str, filesize);
				}
				else {
					directories[str] += filesize;
				}
				auto it = navigate.end();
				while (it != navigate.begin()) {
					str = std::accumulate(navigate.begin(), --it, std::string{});
					directories[str] += filesize;
				}
			}

		}

	}

	for (auto d : directories) {
		//std::cout << d.first << ": " << d.second << "\n";
		if (d.second <= maxsize)
			totalsize += d.second;
	}

	std::cout << "Total size: " << totalsize << "\n";

	//auto sum = std::accumulate(directories.begin(), directories.end(), 0, [](auto prev_sum, auto& directory) {return directory.second >= maxsize ? directory.second : 0; });

	//std::cout << sum;

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

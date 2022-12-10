// Day2RockPaperScissors1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <chrono>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	int opponent_sum = 0;
	int you_sum = 0;
	int loose = 0;
	int draw = 3;
	int win = 6;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	while (std::getline(inputfile, line))
	{
		std::string opponent = line.substr(0, 1);
		std::string you = line.substr(2, 1);

		int opponentchoice = opponent.compare("A") == 0 ? 1 : 0;	// Rock
		opponentchoice += opponent.compare("B") == 0 ? 2 : 0;		// Paper
		opponentchoice += opponent.compare("C") == 0 ? 3 : 0;		// Scissors

		int youchoice = you.compare("X") == 0 ? 1 : 0;				// Rock
		youchoice += you.compare("Y") == 0 ? 2 : 0;					// Paper
		youchoice += you.compare("Z") == 0 ? 3 : 0;					// Scissors

		if ((opponentchoice == 1 && youchoice == 3) || (opponentchoice == 3 && youchoice == 2) || (opponentchoice == 2 && youchoice == 1)) {
			opponent_sum += (win + opponentchoice);
			you_sum += (loose + youchoice);
		}
		else if ((youchoice == 1 && opponentchoice == 3) || (youchoice == 3 && opponentchoice == 2) || (youchoice == 2 && opponentchoice == 1)) {
			you_sum += (win + youchoice);
			opponent_sum += (loose + opponentchoice);
		}
		else {
			opponent_sum += (draw + opponentchoice);
			you_sum += (draw + youchoice);
		}
	}

	std::cout << "Opponent: " << opponent_sum << "\n";
	std::cout << "You: " << you_sum << "\n";

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

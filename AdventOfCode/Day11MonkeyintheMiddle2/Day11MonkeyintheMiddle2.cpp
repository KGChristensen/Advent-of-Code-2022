// Day11MonkeyintheMiddle2.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

enum class Operation {
	Multiply,
	Add,
	Square
};

struct monkey {
	int number;
	std::vector<long long int> startingitems;
	Operation operation;
	long long int operationamout;
	int divisibletest;
	unsigned int throwtrue;
	unsigned int throwfalse;
	int inspectitems = 0;
};

static void printMonkey(monkey& m) {

	std::cout << "Monkey " << m.number << ":\n";

	std::cout << "  Starting items: ";

	if (!m.startingitems.empty()) {
		auto first = m.startingitems.cbegin();
		std::cout << *first;

		while (m.startingitems.cend() != ++first) {
			std::cout << ", " << *first;
		}
	}

	char o = '^';

	if (m.operation != Operation::Square) {
		o = (m.operation == Operation::Add ? '+' : '*');
		std::cout << "\n  Operation: new = old " << o << " ";
		std::cout << m.operationamout << "\n";
	}
	else {
		std::cout << "\n  Operation: new = old " << o << " ";

		std::cout << "2\n";
	}

	std::cout << "  Test: divisible by " << m.divisibletest << "\n";
	std::cout << "    If true: throw to monkey " << m.throwtrue << "\n";
	std::cout << "    If false: throw to monkey " << m.throwfalse << "\n";
	std::cout << "  inspected items " << m.inspectitems << "\n";
	std::cout << "\n";
}

static bool monkeyComparer(const monkey& m1, const monkey& m2)
{
	return m1.inspectitems > m2.inspectitems;				// Highest to lowest
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	std::vector<monkey> monkeys;
	const size_t rounds = 10000;
	long long int modulusproductofall = 1;
	size_t mostactive = 2;
	long long int sumofmostactivemonkeys = 1;
	int monkeynumber = 0;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	while (std::getline(inputfile, line))
	{
		if (line[0] == 'M') {
			monkey m;

			m.number = (monkeynumber++);

			// Starting items
			std::getline(inputfile, line);

			std::stringstream ss(line.substr(line.find_first_of(':') + 1, line.length()));
			std::string word;
			while (!ss.eof()) {
				std::getline(ss, word, ',');
				m.startingitems.push_back(stoi(word));
			}

			// Operation
			std::getline(inputfile, line);

			const size_t chk = line.find("old");

			const std::string o = line.substr(chk + 4, 1);
			const std::string am = line.substr(chk + 6, (chk + 6 - line.length()));
			const size_t c = am.find("old");
			if (c == 0) {
				m.operation = Operation::Square;
				m.operationamout = 0;
			}
			else {
				if (o == "+") {
					m.operation = Operation::Add;
				}
				else if (o == "*") {
					m.operation = Operation::Multiply;
				}
				m.operationamout = stoi(am);
			}

			// Tests
			std::getline(inputfile, line);
			m.divisibletest = stoi(line.substr(line.find_last_of(' '), line.length()));

			// Test (true)
			std::getline(inputfile, line);
			m.throwtrue = std::make_unsigned_t<int>(stoi(line.substr(line.find_last_of(' '), line.length())));

			// Test (false)
			std::getline(inputfile, line);
			m.throwfalse = std::make_unsigned_t<int>(stoi(line.substr(line.find_last_of(' '), line.length())));

			monkeys.push_back(m);
		}
	}

	for (auto& m : monkeys) {
		modulusproductofall *= m.divisibletest;
	}

	for (size_t r = 0; r < rounds; r++) {
		for (auto& currentmonkey : monkeys) {
			std::vector<long long int> tmpstartingitems = currentmonkey.startingitems;
			currentmonkey.inspectitems += currentmonkey.startingitems.size();
			currentmonkey.startingitems.clear();
			for (auto itm : tmpstartingitems) {

				long long int worrylevel;

				switch (currentmonkey.operation)
				{
				case Operation::Multiply:
					worrylevel = itm * currentmonkey.operationamout;
					break;
				case Operation::Add:
					worrylevel = itm + currentmonkey.operationamout;
					break;
				case Operation::Square:
					worrylevel = itm * itm;
					break;
				}

				worrylevel %= modulusproductofall;

				if (worrylevel % currentmonkey.divisibletest == 0)
					monkeys[currentmonkey.throwtrue].startingitems.push_back(worrylevel);
				else
					monkeys[currentmonkey.throwfalse].startingitems.push_back(worrylevel);
			}
		}
	}

	std::cout << "Finished after " << rounds << ":\n\n";

	for (auto m : monkeys) {
		printMonkey(m);
	}

	std::sort(monkeys.begin(), monkeys.end(), monkeyComparer);

	for (auto &m : monkeys) {
		std::cout << "Monkey " << m.number << " inspected items " << m.inspectitems << " times.\n";
	}

	std::cout << "\n" << mostactive << " most active monkeys: ";

	while (mostactive--) {
		sumofmostactivemonkeys *= monkeys[mostactive].inspectitems;
	}

	std::cout << sumofmostactivemonkeys << "\n";

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

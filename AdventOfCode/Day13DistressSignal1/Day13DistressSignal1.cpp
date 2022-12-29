// Day13DistressSignal1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <variant>
#include <tuple>
#include <chrono>
#include <stack>
#include <charconv>

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };

template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

struct packet {

	std::variant<int, std::vector<packet>> data;

	explicit packet(int value) : data(value) {}
	explicit packet(std::vector<packet> value) : data(std::move(value)) {}

	// Overload lambdas for comparision for every case
	friend bool operator<(packet const& left, packet const& right) {
		return std::visit(overloaded{
			[](int l, int r) { return l < r; },
			[](std::vector<packet> const& l, std::vector<packet> const& r) { return l < r; },
			[](int l, std::vector<packet> const& r) { return std::vector<packet>{packet{ l }} < r; },
			[](std::vector<packet> const& l, int r) { return l < std::vector<packet>{packet{ r }}; }
			}, left.data, right.data);
	}
};

int parseInt(auto& it, auto end) {
	auto endofint = std::ranges::find_if(it, end, [](auto c) {		// Find last int
		return c == ',' || c == ']';
		});
	
	int retvalue = std::stoi(std::string{it, end});

	it = endofint;

	return retvalue;
}

std::vector<packet> parseList(auto& it, auto end) {
	
	++it;															// Move past first bracket

	std::vector<packet> packets;

	while (it != end && *it != ']') {
		if (std::isdigit(*it)) {									// Check if value is int (digit)
			packets.emplace_back(packet{ parseInt(it, end) });
		}
		else if(*it == '[') {										// Check if begining of list 
			packets.emplace_back(packet{ parseList(it, end) });
		}

		if (*it == ',') {
			++it;													// Move past comma
		}

	}

	++it;															// Move past last bracket
	return packets;
}

static packet parsePacket(std::string_view line) {
	auto it = line.begin();
	auto end = line.end();

	return packet{ parseList(it, end) };
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto start = std::chrono::high_resolution_clock::now();

	std::string line;
	int index = 0;
	int sumofindices = 0;

	std::ifstream inputfile("input.txt");

	if (!inputfile.is_open()) { std::cerr << "Cannot open file!\n"; return 0; }

	while (std::getline(inputfile, line))
	{
		std::string left = line; std::getline(inputfile, line);
		std::string right = line; std::getline(inputfile, line);
		
		auto ppleft = parsePacket(left);
		auto ppright = parsePacket(right);

		if (ppleft < ppright)
			sumofindices += (index + 1);			// One (1) based index

		index++;
	}

	std::cout << "Sum of the indices: " << sumofindices << "\n";

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

#include <iostream>
#include <fstream>
#include <string>
#include <set>

int main()
{
	std::ifstream file("input.txt");
	std::string line;
	int firstMarker = -1;

	getline(file, line);

	constexpr int cConsequtiveLength = 14;

	for (int i = 0; i < line.size() - cConsequtiveLength; i++)
	{
		std::set<char> uniqueLetters;
		std::string substr = line.substr(i, cConsequtiveLength);

		for(const auto chr : substr)
			uniqueLetters.emplace(chr);

		if (uniqueLetters.size() == cConsequtiveLength)
		{
			firstMarker = i + cConsequtiveLength;
			break;
		}
	}
	
	std::cout << "First marker = " << firstMarker << std::endl;

	std::cin.get();
	return 0;
}
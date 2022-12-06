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

	for (int i = 0; i < line.size() - 4; i++)
	{
		std::set<char> uniqueLetters;
		std::string substr = line.substr(i, 4);

		for(const auto chr : substr)
			uniqueLetters.emplace(chr);

		if (uniqueLetters.size() == 4)
		{
			firstMarker = i + 4;
			break;
		}
	}
	
	std::cout << "First marker = " << firstMarker << std::endl;

	std::cin.get();
	return 0;
}
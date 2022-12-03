#include <iostream>
#include <fstream>
#include <string>
#include <set>

int main()
{
	std::ifstream file("input.txt");
	std::string line;
	int prioritySum = 0;

	while (getline(file, line))
	{
		std::set<char> uniqueLetters1;
		std::set<char> uniqueLetters2;
		std::string compartment1 = line.substr(0, line.size() / 2);
		std::string compartment2 = line.substr(line.size() / 2, line.size() / 2);

		for (int i = 0; i < compartment1.size(); i++)
			uniqueLetters1.insert(compartment1[i]);

		for (int i = 0; i < compartment2.size(); i++)
			uniqueLetters2.insert(compartment2[i]);

		for (auto iter = uniqueLetters1.begin(); iter != uniqueLetters1.end(); iter++)
		{
			if (uniqueLetters2.find(*iter) != uniqueLetters2.end())
			{
				if (*iter >= 'a' && *iter <= 'z')
					prioritySum += *iter - 'a' + 1;
				else
					prioritySum += *iter - 'A' + 26 + 1;
			}
		}
	}

	std::cout << "Priority sum = " << prioritySum << std::endl;

	std::cin.get();
	return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main()
{
	std::ifstream file("input.txt");
	std::vector<int> elves;
	int currentElf = 0;

	std::string line;
	while (getline(file, line))
	{
		if (line != "")
			currentElf += std::stoi(line);
		else
		{
			elves.push_back(currentElf);
			currentElf = 0;
		}
	}

	if (currentElf != 0)
		elves.push_back(currentElf);

	int maxValue = INT_MIN;
	int maxIndex = -1;

	for (int i = 0; i < elves.size(); i++)
	{
		if (elves[i] > maxValue)
		{
			maxValue = elves[i];
			maxIndex = i;
		}
	}
	
	std::cout << "The elf with the most calories is elf index " << maxIndex << ", carrying " << maxValue;

	std::cin.get();
	return 0;
}
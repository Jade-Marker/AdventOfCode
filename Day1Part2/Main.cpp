#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

std::pair<int,int> GetMaxValue(std::vector<int>& elves)
{
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

	return std::pair<int, int>(maxValue, maxIndex);
}

void RemoveIndex(std::vector<int>& elves, int index)
{
	auto iter = elves.begin();
	for (int i = 0; i < index; i++)
	{
		iter++;
	}

	elves.erase(iter);
}

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

	int sumMax = 0;
	std::pair<int, int> elf;
	for (int i = 0; i < 3; i++)
	{
		elf = GetMaxValue(elves);
		std::cout << "The elf with the most calories is elf index " << elf.second << ", carrying " << elf.first << std::endl;
		RemoveIndex(elves, elf.second);
		sumMax += elf.first;
	}
	std::cout << "Max sum = " << sumMax;

	std::cin.get();
	return 0;
}
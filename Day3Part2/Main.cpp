#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>

void UpdateUniqueCharCount(std::map<char, int>& uniqueCharCount, std::string& line)
{
	std::set<char> uniqueChar;

	for (int i = 0; i < line.size(); i++)
		uniqueChar.insert(line[i]);

	for (auto iter = uniqueChar.begin(); iter != uniqueChar.end(); iter++)
	{
		if (uniqueCharCount.find(*iter) == uniqueCharCount.end())
			uniqueCharCount.emplace(*iter, 1);
		else
			uniqueCharCount[*iter]++;
	}
}

int main()
{
	std::ifstream file("input.txt");
	std::string line1, line2, line3;
	int prioritySum = 0;

	while (getline(file, line1))
	{
		std::map<char, int> uniqueCharCount;

		getline(file, line2);
		getline(file, line3);

		UpdateUniqueCharCount(uniqueCharCount, line1);
		UpdateUniqueCharCount(uniqueCharCount, line2);
		UpdateUniqueCharCount(uniqueCharCount, line3);

		for (auto iter = uniqueCharCount.begin(); iter != uniqueCharCount.end(); iter++)
		{
			if (iter->second == 3)
			{
				if (iter->first >= 'a' && iter->first <= 'z')
					prioritySum += iter->first - 'a' + 1;
				else
					prioritySum += iter->first - 'A' + 26 + 1;

				break;
			}
		}
	}

	std::cout << "Priority sum = " << prioritySum << std::endl;

	std::cin.get();
	return 0;
}
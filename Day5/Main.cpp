#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>

int main()
{
	std::ifstream file("input.txt");
	std::string line = "";
	std::vector<std::vector<char>> crateStacks;
	int numStacks;
	std::string topOfEachStack = "";

	//skip ahead to the line specifying how many stacks
	while (line.find("1") == line.npos)
		getline(file, line);

	line = line.substr(line.find_last_not_of(' '));
	numStacks = std::stoi(line);
	crateStacks.resize(numStacks);

	file.close();
	file.open("input.txt");

	while (line.find("1") == line.npos)
	{
		getline(file, line);

		if (line.find("1") == line.npos)
		{
			for (int i = 0; i < numStacks; i++)
			{
				std::string subStr = line.substr(i * 4, 4);	//4 since there is 3 chars for [C] and 1 for space

				//if first char is [, the subStr[1] is the crate char

				if (subStr[1] != ' ')	//If there's a space then there's no crate, so ignore
					crateStacks[i].push_back(subStr[1]);
			}
		}
	}

	//each stack is actually in reverse, so reverse them
	for (int i = 0; i < numStacks; i++)
	{
		std::vector<char> reverse;
		reverse.clear();

		for (int j = crateStacks[i].size(); j > 0; j--)
		{
			reverse.push_back(crateStacks[i][j - 1]);
		}

		crateStacks[i] = reverse;
	}

	//skip blank line
	getline(file, line);

	//Now that the crates are setup, we can just iterate over the rest of the file
	while (getline(file, line))
	{
		int numToMove;
		int moveSrc;
		int moveDst;

		//line is always move {num} from {src} to {dst}
		int spaceIndex = line.find_last_of(' ');
		moveDst = std::stoi(line.substr(spaceIndex + 1));
		line = line.substr(0, spaceIndex - 3); //-3 to skip over " to"

		spaceIndex = line.find_last_of(' ');
		moveSrc = std::stoi(line.substr(spaceIndex + 1));
		line = line.substr(0, spaceIndex - 5); //-5 to skip over " from"

		numToMove = std::stoi(line.substr(line.find(' ')));

		for (int i = 0; i < numToMove; i++)
		{
			std::vector<char>& src = crateStacks[moveSrc - 1];
			std::vector<char>& dst = crateStacks[moveDst - 1];
			
			char crate = src.back();
			src.pop_back();

			dst.push_back(crate);
		}
	}

	for (int i = 0; i < numStacks; i++)
	{
		topOfEachStack += crateStacks[i].back();
	}

	std::cout << topOfEachStack;

	std::cin.get();
	return 0;
}
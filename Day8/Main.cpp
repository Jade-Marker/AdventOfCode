#include <iostream>
#include <fstream>
#include <string>
#include <vector>

enum Direction
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

int FindNumVisibleTrees(const std::vector<std::string>& trees, std::vector<std::vector<bool>>& hasTreeBeenChecked, Direction dir)
{
	int innerDeltaX, innerDeltaY;
	int outerDeltaX, outerDeltaY;
	int x, y;
	int currentTreeHeight;
	int numVisibleTrees = 0;

	switch (dir)
	{
		case LEFT:
			x = trees[0].size() - 2; y = 1;
			innerDeltaX = -1; innerDeltaY = 0;
			outerDeltaX = 0; outerDeltaY = 1;
			break;

		case RIGHT:
			x = 1; y = 1;
			innerDeltaX = 1; innerDeltaY = 0;
			outerDeltaX = 0; outerDeltaY = 1;
			break;

		case UP:
			x = 1; y = trees[0].size() - 2;
			innerDeltaX = 0; innerDeltaY = -1;
			outerDeltaX = 1; outerDeltaY = 0;
			break;

		case DOWN:
			x = 1; y = 1;
			innerDeltaX = 0; innerDeltaY = 1;
			outerDeltaX = 1; outerDeltaY = 0;
			break;
	}

	for(int i = 0; i < trees.size() - 2; i++)
	{
		int intialXValue = x;
		int initalYValue = y;
		currentTreeHeight = trees[y - innerDeltaY][x - innerDeltaX];

		for(int j = 0; j < trees.size() - 2; j++)
		{
			if (trees[y][x] > currentTreeHeight)
			{
				currentTreeHeight = trees[y][x];
				if (hasTreeBeenChecked[y][x] == false)
				{
					numVisibleTrees++;
					hasTreeBeenChecked[y][x] = true;
				}
			}
			

			x += innerDeltaX;
			y += innerDeltaY;
		}

		x = intialXValue + outerDeltaX;
		y = initalYValue + outerDeltaY;
	}

	return numVisibleTrees;
}

int main()
{
	std::ifstream file("input.txt");
	std::string line;
	std::vector<std::string> trees;
	std::vector<std::vector<bool>> hasTreeBeenChecked;
	int numVisible;


	while (getline(file, line))
	{
		if(line != "")
			trees.push_back(line);

		std::vector<bool> currentLine;
		for (int i = 0; i < line.size(); i++)
			currentLine.push_back(false);

		hasTreeBeenChecked.push_back(currentLine);
	}

	numVisible = FindNumVisibleTrees(trees, hasTreeBeenChecked, Direction::LEFT);
	numVisible += FindNumVisibleTrees(trees, hasTreeBeenChecked, Direction::RIGHT);
	numVisible += FindNumVisibleTrees(trees, hasTreeBeenChecked, Direction::UP);
	numVisible += FindNumVisibleTrees(trees, hasTreeBeenChecked, Direction::DOWN);

	//Lastly, we need to add the trees from the outerlayer
	numVisible += trees.size() * 2 + (trees.size() - 2) * 2;

	std::cout << "Num visible trees = " << numVisible << std::endl;

	std::cin.get();
	return 0;
}
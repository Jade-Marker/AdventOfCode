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

int GetViewingDistance(const std::vector<std::string>& trees, int initialX, int initialY, Direction dir)
{
	int deltaX, deltaY;
	int x, y;
	int numTreesToCheck;
	int viewingDistance = 0;

	switch (dir)
	{
		case LEFT:
			deltaX = -1; deltaY = 0;
			numTreesToCheck = initialX;
			break;

		case RIGHT:
			deltaX = 1; deltaY = 0;
			numTreesToCheck = trees.size() - initialX - 1;
			break;

		case UP:
			deltaX = 0; deltaY = -1;
			numTreesToCheck = initialY;
			break;

		case DOWN:
			deltaX = 0; deltaY = 1;
			numTreesToCheck = trees.size() - initialY - 1;
			break;
	}

	if (numTreesToCheck == 0)
		return 0;

	x = initialX + deltaX;
	y = initialY + deltaY;
	viewingDistance++;

	for (int i = 0; i < numTreesToCheck; i++)
	{
		if (x == 0 || x == trees.size() - 1 || y == 0 || y == trees.size() - 1)
			break;

		if (trees[y][x] < trees[initialY][initialX])
			viewingDistance++;
		else
			break;

		x += deltaX;
		y += deltaY;

		if (x == 0 || x == trees.size() - 1 || y == 0 || y == trees.size())
			break;
	}

	return viewingDistance;
}

int GetHighestScenicScore(const std::vector<std::string>& trees)
{
	int highestScenicScore = INT_MIN;

	for (int y = 0; y < trees.size(); y++)
	{
		for (int x = 0; x < trees.size(); x++)
		{
			int scenicScore = 
				GetViewingDistance(trees, x, y, Direction::LEFT) * 
				GetViewingDistance(trees, x, y, Direction::RIGHT) * 
				GetViewingDistance(trees, x, y, Direction::UP) *
				GetViewingDistance(trees, x, y, Direction::DOWN);

			if (scenicScore > highestScenicScore)
				highestScenicScore = scenicScore;
		}
	}

	return highestScenicScore;
}

int main()
{
	std::ifstream file("input.txt");
	std::string line;
	std::vector<std::string> trees;

	while (getline(file, line))
	{
		if(line != "")
			trees.push_back(line);
	}

	std::cout << "Highest score = " << GetHighestScenicScore(trees) << std::endl;

	std::cin.get();
	return 0;
}
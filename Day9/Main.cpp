#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <tuple>

struct Vec2
{
	int x;
	int y;

	Vec2() : x(0), y(0)
	{
	}

	Vec2(int x, int y) : x(x), y(y)
	{
	}

	int DistX(const Vec2& other)
	{
		return (x - other.x);
	}

	int DistY(const Vec2& other)
	{
		return (y - other.y);
	}

	friend bool operator<(const Vec2& a, const Vec2& b)
	{
		return std::tie(a.x, a.y) < std::tie(b.x, b.y);
	}
};

Vec2 UpdateTailPosition(Vec2 headPosition, Vec2 tailPosition)
{
	int distX = headPosition.DistX(tailPosition);
	int distY = headPosition.DistY(tailPosition);

	if (distX * distX + distY * distY <= 1 || (distX * distX == 1 && distY * distY == 1))
		return tailPosition;

	int xOffset = distX;
	int yOffset = distY;
	
	if (abs(xOffset) > 1)
		xOffset -= distX < 0 ? -1 : 1;
	if (abs(yOffset) > 1)
		yOffset -= distY < 0 ? -1 : 1;

	//if in the same row or column
	if (distX == 0)
	{
		tailPosition.y += yOffset;
	}
	else if (distY == 0)
	{
		tailPosition.x += xOffset;
	}
	else
	{
		tailPosition.x += xOffset;
		tailPosition.y += yOffset;
	}

	return tailPosition;
}

int main()
{
	std::ifstream file("input.txt");
	std::string line;
	std::set<Vec2> visitedPositions;
	Vec2 headPosition;
	Vec2 tailPosition;

	while (getline(file, line))
	{
		if (line != "")
		{
			char direction = line[0];
			int numTimes = std::stoi(line.substr(2));

			for (int i = 0; i < numTimes; i++)
			{
				switch (direction)
				{
					case 'R':
						headPosition.x += 1;
						break;

					case 'L':
						headPosition.x -= 1;
						break;

					case 'U':
						headPosition.y += 1;
						break;

					case 'D':
						headPosition.y -= 1;
						break;
				}

				tailPosition = UpdateTailPosition(headPosition, tailPosition);
				visitedPositions.emplace(tailPosition);
			}
		}
	}

	std::cout << "Num unique positions = " << visitedPositions.size() << std::endl;

	std::cin.get();
	return 0;
}


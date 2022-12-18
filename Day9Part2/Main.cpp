#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <tuple>
#include <vector>

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
	std::vector<Vec2> ropeKnots;

	ropeKnots.resize(10);

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
					ropeKnots[0].x += 1;
					break;

				case 'L':
					ropeKnots[0].x -= 1;
					break;

				case 'U':
					ropeKnots[0].y += 1;
					break;

				case 'D':
					ropeKnots[0].y -= 1;
					break;
				}

				for (int i = 1; i < ropeKnots.size(); i++)
					ropeKnots[i] = UpdateTailPosition(ropeKnots[i - 1], ropeKnots[i]);

				visitedPositions.emplace(ropeKnots[9]);
			}
		}
	}

	std::cout << "Num unique positions = " << visitedPositions.size() << std::endl;

	std::cin.get();
	return 0;
}

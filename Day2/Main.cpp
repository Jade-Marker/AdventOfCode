#include <iostream>
#include <fstream>
#include <string>

enum CHOICE
{
	ROCK = 1,
	PAPER = 2,
	SCISSORS = 3
};

enum GAMESTATE
{
	LOSS = 0,
	DRAW = 3,
	WIN = 6,
};

class RockPaperState
{
private:
	CHOICE _choice;

public:
	RockPaperState(char input);
	GAMESTATE HasWon(const RockPaperState& other);
	int GetScore(const RockPaperState& other);

};

RockPaperState::RockPaperState(char input)
{
	switch (input)
	{
		case 'A':
		case 'X':
			_choice = CHOICE::ROCK;
			break;
		
		case 'B':
		case 'Y':
			_choice = CHOICE::PAPER;
			break;

		case 'C':
		case 'Z':
			_choice = CHOICE::SCISSORS;
			break;
	}
}

GAMESTATE RockPaperState::HasWon(const RockPaperState& other)
{
	if(_choice == other._choice)
		return GAMESTATE::DRAW;

	switch (_choice)
	{
		case CHOICE::ROCK:
			if (other._choice == CHOICE::PAPER)
				return GAMESTATE::LOSS;
			else
				return GAMESTATE::WIN;
			break;

		case CHOICE::PAPER:
			if (other._choice == CHOICE::ROCK)
				return GAMESTATE::WIN;
			else
				return GAMESTATE::LOSS;
			break;

		case CHOICE::SCISSORS:
			if (other._choice == CHOICE::ROCK)
				return GAMESTATE::LOSS;
			else
				return GAMESTATE::WIN;
			break;
	}
}

int RockPaperState::GetScore(const RockPaperState& other)
{
	return (int)_choice + (int)HasWon(other);
}

int main()
{
	std::ifstream file("input.txt");
	
	int totalScore = 0;

	std::string line;
	while (getline(file, line))
	{
		RockPaperState opponent = RockPaperState(line[0]);
		RockPaperState player = RockPaperState(line[2]);

		totalScore += player.GetScore(opponent);
	}


	std::cout << "Total score = " << totalScore << std::endl;

	std::cin.get();
	return 0;
}


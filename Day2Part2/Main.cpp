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
public:
	CHOICE _choice;

public:
	RockPaperState(char input);

	CHOICE GetWinningHand() const;
	CHOICE GetLosingHand() const;
};

RockPaperState::RockPaperState(char input)
{
	switch (input)
	{
		case 'A':
			_choice = CHOICE::ROCK;
			break;
		
		case 'B':
			_choice = CHOICE::PAPER;
			break;

		case 'C':
			_choice = CHOICE::SCISSORS;
			break;
	}
}

CHOICE RockPaperState::GetWinningHand() const
{
	switch (_choice)
	{
		case CHOICE::ROCK:
			return CHOICE::PAPER;
			break;

		case CHOICE::PAPER:
			return CHOICE::SCISSORS;
			break;

		case CHOICE::SCISSORS:
			return CHOICE::ROCK;
			break;
	}
}

CHOICE RockPaperState::GetLosingHand() const
{
	switch (_choice)
	{
	case CHOICE::ROCK:
		return CHOICE::SCISSORS;
		break;

	case CHOICE::PAPER:
		return CHOICE::ROCK;
		break;

	case CHOICE::SCISSORS:
		return CHOICE::PAPER;
		break;
	}
}

class Cheater
{
private:
	GAMESTATE _desiredGamestate;

public:
	Cheater(char input);
	int GetScore(const RockPaperState& other);
};

Cheater::Cheater(char input)
{
	switch (input)
	{
	case 'X':
		_desiredGamestate = GAMESTATE::LOSS;
		break;

	case 'Y':
		_desiredGamestate = GAMESTATE::DRAW;
		break;

	case 'Z':
		_desiredGamestate = GAMESTATE::WIN;
		break;
	}
}

int Cheater::GetScore(const RockPaperState& other)
{
	CHOICE choice;

	switch (_desiredGamestate)
	{
		case GAMESTATE::WIN:
			choice = other.GetWinningHand();
			break;

		case GAMESTATE::LOSS:
			choice = other.GetLosingHand();
			break;

		case GAMESTATE::DRAW:
			choice = other._choice;
			break;
	}
	

	return (int)_desiredGamestate + (int)choice;
}

int main()
{
	std::ifstream file("input.txt");
	
	int totalScore = 0;

	std::string line;
	while (getline(file, line))
	{
		RockPaperState opponent = RockPaperState(line[0]);
		Cheater player = Cheater(line[2]);

		totalScore += player.GetScore(opponent);
	}


	std::cout << "Total score = " << totalScore << std::endl;

	std::cin.get();
	return 0;
}
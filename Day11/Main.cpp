#include <iostream>
#include <fstream>
#include <string>
#include <vector>

enum Operation
{
	ADD,
	MULT
};

enum OperationTarget
{
	NUM,
	SELF
};

class Monkey
{
private:
	std::vector<int> _items;

	Operation _operation;
	OperationTarget _operationTarget;
	int _operationNum;
	
	int _testDivisor;

	int _monkeyToThrowIfTrue;
	int _monkeyToThrowIfFalse;

	int _numItemsInspected;

public:
	Monkey();

	void AddItem(int item);

	void SetInitialItems(std::string line);
	void SetOperation(std::string line);
	void SetTestDivisor(std::string line);
	void SetMonkeyTargets(std::string line, std::string line2);

	void InspectItem(int index);

	std::vector<int>& GetItems();
	int GetNextMonkeyIndex(int index);
	int GetNumItemsInspected();

};

Monkey::Monkey():
	_numItemsInspected(0)
{
}

void Monkey::AddItem(int item)
{
	_items.push_back(item);
}

void Monkey::SetInitialItems(std::string line)
{
	line = line.substr(line.find(": ") + 1);
	while (line.size() > 0)
	{
		int commaIndex = line.find_first_of(',');

		if (commaIndex == line.npos)
		{
			AddItem(std::stoi(line));
			line = "";
		}
		else
		{
			AddItem(std::stoi(line.substr(0, commaIndex + std::string(", ").size())));
			line = line.substr(commaIndex + std::string(", ").size());
		}
	}
}

void Monkey::SetOperation(std::string line)
{
	int operationIndex = line.find("old ") + std::string("old ").size();
	if (line[operationIndex] == '+')
		_operation = Operation::ADD;
	else
		_operation = Operation::MULT;

	line = line.substr(operationIndex + std::string("* ").size());
	if (line == "old")
		_operationTarget = OperationTarget::SELF;
	else
	{
		_operationTarget = OperationTarget::NUM;
		_operationNum = std::stoi(line);
	}

}

void Monkey::SetTestDivisor(std::string line)
{
	_testDivisor = std::stoi(line.substr(line.find("by ") + std::string("by ").size()));
}

void Monkey::SetMonkeyTargets(std::string line, std::string line2)
{
	_monkeyToThrowIfTrue = std::stoi(line.substr(line.find("monkey ") + std::string("monkey ").size()));
	_monkeyToThrowIfFalse = std::stoi(line2.substr(line2.find("monkey ") + std::string("monkey ").size()));
}

void Monkey::InspectItem(int index)
{
	int* target;

	if (_operationTarget == OperationTarget::SELF)
		target = &_items[index];
	else
		target = &_operationNum;

	if (_operation == Operation::ADD)
		_items[index] += *target;
	else
		_items[index] *= *target;

	_items[index] /= 3;

	_numItemsInspected++;
}

std::vector<int>& Monkey::GetItems()
{
	return _items;
}

int Monkey::GetNextMonkeyIndex(int index)
{
	if (_items[index] % _testDivisor == 0)
		return _monkeyToThrowIfTrue;
	else
		return _monkeyToThrowIfFalse;
}

int Monkey::GetNumItemsInspected()
{
	return _numItemsInspected;
}

void MonkeyRound(std::vector<Monkey>& monkeys)
{
	for (int i = 0; i < monkeys.size(); i++)
	{
		auto& items = monkeys[i].GetItems();

		for (int j = 0; j < items.size(); j++)
		{
			monkeys[i].InspectItem(j);
			
			monkeys[monkeys[i].GetNextMonkeyIndex(j)].AddItem(items[j]);
		}
	
		items.clear();
	}
}

int main()
{
	std::ifstream file("input.txt");
	std::string line;
	std::string line2;
	std::vector<Monkey> monkeys;

	while (getline(file, line))
	{
		if (line != "")
		{
			Monkey monkey;

			getline(file, line);
			monkey.SetInitialItems(line);

			getline(file, line);
			monkey.SetOperation(line);

			getline(file, line);
			monkey.SetTestDivisor(line);

			getline(file, line);
			getline(file, line2);
			monkey.SetMonkeyTargets(line, line2);

			monkeys.push_back(monkey);
		}
	}

	for (int i = 0; i < 20; i++)
		MonkeyRound(monkeys);

	int higestNumItems = INT_MIN;
	int secondHighest = INT_MIN;
	for (auto& monkey : monkeys)
	{
		int numItems = monkey.GetNumItemsInspected();
		if (numItems > higestNumItems)
		{
			secondHighest = higestNumItems;
			higestNumItems = numItems;
		}
		else if (numItems > secondHighest)
			secondHighest = numItems;
	}

	std::cout << "Monkey business = " << higestNumItems * secondHighest << std::endl;
	std::cin.get();
	return 0;
}

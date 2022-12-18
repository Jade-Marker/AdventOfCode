#include <iostream>
#include <fstream>
#include <string>
#include <array>

class CPU
{
private:
	enum Instruction
	{
		NOOP,
		ADDX
	};

	int xRegister;
	Instruction currentInstruction;
	int vRegister;
	int cycleCount;

public:
	CPU();
	
	bool IsReadyForNextInstruction();
	void TakeNextInstruction(std::string instruction);
	void Tick();

	int GetXRegister();
};

CPU::CPU():
	xRegister(1), currentInstruction(Instruction::NOOP), vRegister(0), cycleCount(0)
{
}

bool CPU::IsReadyForNextInstruction()
{
	return cycleCount == 0;
}

void CPU::TakeNextInstruction(std::string instruction)
{
	if (instruction == "noop")
	{
		currentInstruction = Instruction::NOOP;
		cycleCount = 1;
	}
	else
	{
		currentInstruction = Instruction::ADDX;
		vRegister = std::stoi(instruction.substr(instruction.find(' ') + 1));
		cycleCount = 2;
	}
}

void CPU::Tick()
{
	cycleCount--;

	if (currentInstruction == Instruction::ADDX && cycleCount == 0)
	{
		xRegister += vRegister;
	}
}

int CPU::GetXRegister()
{
	return xRegister;
}

int main()
{
	std::ifstream file("input.txt");
	std::string line;
	CPU cpu;
	int cycleCount = 0;
	std::array<int, 6> cyclesToCheckSignal = { 20, 60, 100, 140, 180, 220 };
	int signalSum = 0;
	int currentIndexToCheck = 0;


	while (getline(file, line))
	{
		cpu.TakeNextInstruction(line);

		while (!cpu.IsReadyForNextInstruction())
		{
			cycleCount++;

			if (cyclesToCheckSignal[currentIndexToCheck] == cycleCount)
			{
				signalSum += cpu.GetXRegister() * cycleCount;
				currentIndexToCheck++;
			}

			if (currentIndexToCheck == cyclesToCheckSignal.size())
				break;

			cpu.Tick();
		}

		if (currentIndexToCheck == cyclesToCheckSignal.size())
			break;
	}

	std::cout << "Signal sum = " << signalSum << std::endl;

	std::cin.get();
	return 0;
}

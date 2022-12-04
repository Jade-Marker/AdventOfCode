#include <iostream>
#include <fstream>
#include <string>

class Elf
{
private:
	int lowerSection, higherSection;

public:
	Elf(std::string str);

	bool Overlaps(const Elf& other);
};

Elf::Elf(std::string str)
{
	int dashIndex = str.find_first_of('-');

	lowerSection = std::stoi(str.substr(0, dashIndex));
	higherSection = std::stoi(str.substr(dashIndex + 1, str.size() - dashIndex));
}

bool Elf::Overlaps(const Elf& other)
{
	return (lowerSection >= other.lowerSection && lowerSection <= other.higherSection);
}

int main()
{
	std::ifstream file("input.txt");
	std::string line;
	int numOverlaps = 0;


	while (getline(file, line))
	{
		int commaIndex = line.find_first_of(',');

		Elf elf1 = Elf(line.substr(0, commaIndex));
		Elf elf2 = Elf(line.substr(commaIndex + 1, line.size() - commaIndex));

		if (elf1.Overlaps(elf2) || elf2.Overlaps(elf1))
			numOverlaps++;
	}

	std::cout << "Num overlaps = " << numOverlaps << std::endl;
	std::cin.get();
	return 0;
}

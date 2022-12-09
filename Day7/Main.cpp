#include <iostream>
#include <fstream>
#include "Node.h"

void ReopenFileOnLine(std::ifstream& file, int lineNo)
{
	std::string line;

	file.close();

	file.open("input.txt");
	for (int i = 0; i < lineNo; i++)
		getline(file, line);
}

int main()
{
	std::ifstream file("input.txt");
	std::string line;
	int lineNo = 0;

	Node root = Node("/", 0, false, nullptr);
	Node* currentNode = &root;

	while (getline(file, line))
	{
		lineNo++;

		//commands can either be cd or ls
		if (line.find("cd") != line.npos)
		{
			line = line.substr(line.find("cd") + std::string("cd ").length());

			//Line now equals directory

			if (line == "/")
				currentNode = &root;
			else if (line == "..")
				currentNode = currentNode->GetParent();
			else
				currentNode = currentNode->FindDir(line);
		}
		else
		{
			//ls, so we want to keep going until we reach a command
			getline(file, line);
			lineNo++;

			while (line[0] != '$' && line != "")
			{
				//either get dir DIRNAME
				//or FILESIZE FILENAME

				if (line.find("dir") != line.npos)
				{
					line = line.substr(line.find("dir") + std::string("dir ").length());
					currentNode->AddChild(Node(line, 0, 0, currentNode));
				}
				else
				{
					int fileSize = std::stoi(line.substr(0, line.find(' ')));
					std::string fileName = line.substr(line.find(' ') + 1);

					currentNode->AddChild(Node(fileName, fileSize, true, currentNode));
				}

				getline(file, line);
				lineNo++;
			}

			//Make sure that we don't skip over the command detected
			lineNo--;
			ReopenFileOnLine(file, lineNo);
		}
	}

	//File system thing is created (maybe)
	//Now to actually solve the problem
	
	Node::UpdateDirectorySize(&root);

	std::cout << Node::FindTotalSize(&root, 100000) << std::endl;

	std::cin.get();
	return 0;
}
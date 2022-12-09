#pragma once
#include <string>
#include <vector>

class Node
{
private:
	std::string _name;
	int _size;
	bool _isFile;
	std::vector<Node> _children;
	Node* _pParent;

public:
	Node(const std::string& name, int size, bool isFile, Node* pParent);

	void AddChild(Node node);
	Node* FindDir(const std::string& name);

	static int UpdateDirectorySize(Node* node);
	static int FindTotalSize(Node* node, int max);

	Node* GetParent();
	const std::vector<Node>& GetChildren();

	friend bool operator<(const Node& a, const Node& b);
};
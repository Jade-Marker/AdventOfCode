#include "Node.h"
#include <tuple>

Node::Node(const std::string& name, int size, bool isFile, Node* pParent):
	_name(name), _size(size), _isFile(isFile), _pParent(pParent)
{
}

void Node::AddChild(Node node)
{
	_children.push_back(node);
}

Node* Node::FindDir(const std::string& name)
{
	for (auto iter = _children.begin(); iter != _children.end(); iter++)
	{
		if (iter->_name == name && !iter->_isFile)
			return (Node*)(&*iter);
	}

	return nullptr;
}

int Node::UpdateDirectorySize(Node* node)
{
	int dirSize = 0;
	for (auto iter = node->_children.begin(); iter != node->_children.end(); iter++)
	{
		if (iter->_isFile)
			dirSize += iter->_size;
		else
			dirSize += Node::UpdateDirectorySize((Node*)(&*iter));
	}

	node->_size = dirSize;

	return dirSize;
}

int Node::FindTotalSize(Node* node, int max)
{
	int size = 0;

	for (auto iter = node->_children.begin(); iter != node->_children.end(); iter++)
	{
		if (!iter->_isFile)
		{
			if (iter->_size <= max)
				size += iter->_size;


			size += Node::FindTotalSize((Node*)(&*iter), max);
		}
	}

	return size;
}

Node* Node::GetParent()
{
	return _pParent;
}

const std::vector<Node>& Node::GetChildren()
{
	return _children;
}

bool operator<(const Node& a, const Node& b)
{
	return std::tie(a._name) < std::tie(b._name);
}

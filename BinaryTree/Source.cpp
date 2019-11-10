#include <iostream>

using namespace std;

class BinaryTree
{
private:
	// return value : equal to 0(found), less than 0(left), larger than 0(right)
	typedef int (*fnCompare)(void* /*value in node*/, void* /*searching value*/);
	typedef void (*fnShow)(void*);

	struct Node
	{
		void* _value;
		Node* _left;
		Node* _right;

		Node() : _value(nullptr), _left(nullptr), _right(nullptr)
		{

		}

		Node(void* value) : _value(value), _left(nullptr), _right(nullptr)
		{

		}
	};

	Node* _root;
	fnCompare _comparer;
	fnShow _shower;

	Node* search(void* value, Node*& parent, int& comp)
	{
		Node* found = _root;
		int ret = 0;
		while (nullptr != found)
		{
			ret = _comparer(found->_value, value);
			if (0 == ret)
				break;

			comp = ret;
			parent = found;
			if (0 < ret)
				found = found->_right;
			else
				found = found->_left;
		}

		return found;
	}

	void clear(Node* node)
	{
		if (nullptr == node)
			return;
		if (nullptr != node->_left)
			clear(node->_left);
		if (nullptr != node->_right)
			clear(node->_right);
		delete node;
	}

	void show(Node* node)
	{
		if (nullptr != node)
		{
			if (nullptr != node->_left)
				show(node->_left);
			_shower(node->_value);
			if (nullptr != node->_right)
				show(node->_right);
		}
	}

public:
	BinaryTree(fnCompare comparer, fnShow shower)
		: _root(nullptr), _comparer(comparer), _shower(shower)
	{

	}

	~BinaryTree()
	{
		clear(_root);
	}

	bool Search(void* value)
	{
		Node* parent = nullptr;
		int comp = 0;
		if (nullptr == search(value, parent, comp))
			return false;
		else
			return true;
	}

	bool Insert(void* value)
	{
		if (nullptr == _root)
		{
			_root = new Node(value);
			return true;
		}
		else
		{
			Node* parent = nullptr;
			int comp = 0;
			Node* found = search(value, parent, comp);
			if (nullptr == found)
			{
				found = new Node(value);
				if (0 < comp)
					parent->_right = found;
				else
					parent->_left = found;
				return true;
			}
			else
				return false;
		}

		return false;
	}

	bool Delete(void* value)
	{
		if (nullptr == _root)
			return false;

		Node* parent = nullptr;
		int comp = 0;
		Node* found = search(value, parent, comp);
		if (nullptr == found)
			return false;

		if (nullptr == found->_left && nullptr == found->_right)
		{
			if (found == parent->_left)
				parent->_left = nullptr;
			else if (found == parent->_right)
				parent->_right = nullptr;
		}
		else if (nullptr == found->_left)
		{
			if (found == parent->_left)
				parent->_left = found->_right;
			else if (found == parent->_right)
				parent->_right = found->_right;
		}
		else if (nullptr == found->_right)
		{
			if (found == parent->_left)
				parent->_left = found->_left;
			else if (found == parent->_left)
				parent->_right = found->_left;
		}
		else
		{
			Node* child = found->_left;
			Node* childParent = found;
			while (nullptr != child->_right)
			{
				childParent = child;
				child = child->_right;
			}

			if (childParent == found)
			{
				if (found == parent->_left)
					parent->_left = child;
				else
					parent->_right = child;
				child->_right = found->_right;
			}
			else
			{
				if (nullptr != child->_left)
					childParent->_right = child->_left;
				else
					childParent->_right = nullptr;
				if (found == parent->_left)
					parent->_left = child;
				else
					parent->_right = child;
				child->_left = found->_left;
				child->_right = found->_right;
			}
		}

		delete found;
		return true;
	}

	void Clear()
	{
		clear(_root);
	}

	void Show()
	{
		show(_root);
	}
};

int comparer(void* value1, void* value2)
{
	return (int)value2 - (int)value1;
}

void shower(void* value)
{
	std::cout << (int)value << " ";
}

int main()
{
	BinaryTree bt(comparer, shower);
	bt.Insert((void*)5);
	bt.Insert((void*)6);
	bt.Insert((void*)12);
	bt.Insert((void*)4);
	bt.Insert((void*)1);
	bt.Insert((void*)55);
	bt.Insert((void*)80);
	bt.Insert((void*)9);
	bt.Insert((void*)11);
	bt.Insert((void*)10);
	bt.Insert((void*)8);

	bt.Delete((void*)12);

	bt.Show();
}
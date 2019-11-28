#include "RedBlackTree.h"

using namespace YangAlgorithms;

#define TEXT(X) #X
const RedBlackTree::TreeValue RedBlackTree::None = nullptr;
const std::string RedBlackTree::NODE_COLOR_NAME[] = { TEXT(RED), TEXT(BLACK), };

RedBlackTree::Node* RedBlackTree::search(TreeValue value, Node*& parent, int& comp)
{
	Node* found = _root;
	int ret = 0;
	while (_nil != found)
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

void RedBlackTree::clear(Node* node)
{
	if (_nil == node)
		return;
	clear(node->_left);
	clear(node->_right);
	delete node;
}

void RedBlackTree::show(Node* node, int deepCount)
{
	if (_nil != node)
	{
		_shower(node->_value, node->_color, deepCount++);
		show(node->_left, deepCount);
		show(node->_right, deepCount);
	}
}

void RedBlackTree::reconstructionAfterInsertion(Node* node, bool left)
{
	Node* parent = node->_parent;
	while (nullptr != parent && RED == parent->_color)
	{
		// in loop grand parent must exist
		Node* grandParent = parent->_parent;
		bool leftParent = grandParent->_left == parent;
		Node* uncle = leftParent ? grandParent->_right : grandParent->_left;
		if (RED == uncle->_color)
		{
			parent->_color = BLACK;
			uncle->_color = BLACK;
			grandParent->_color = RED;
			node = grandParent;
			parent = grandParent->_parent;
			if (nullptr != parent)
				left = parent->_left == node;
		}
		else
		{
			if ((leftParent && false == left) || (false == leftParent && left))
			{
				leftParent ? leftRotate(parent) : rightRotate(parent);
				parent = node;
				left = !left;
			}

			parent->_color = BLACK;
			grandParent->_color = RED;
			left ? rightRotate(grandParent) : leftRotate(grandParent);
			break;
		}
	}
	_root->_color = BLACK;
}

void RedBlackTree::reconstructionAfterDeletion(Node* child, Node* parent)
{
	while (nullptr != parent)
	{
		bool left = parent->_left == child;
		Node* sibling = left ? parent->_right : parent->_left;
		if (RED == parent->_color)
		{
			if (BLACK == sibling->_left->_color && BLACK == sibling->_right->_color)
			{
				// case 1
				// parent : red, sibling : black, sibling left : black, sibling right : black
				sibling->_color = RED;
				parent->_color = BLACK;
				break; 
			}
		}
		else if(BLACK == sibling->_left->_color && BLACK == sibling->_right->_color)
		{
			if (BLACK == sibling->_color)
			{
				// case 4
				// parent : black, sibling : black, sibling left : black, sibling right : black
				sibling->_color = RED;
				child = parent;
				parent = parent->_parent;
				continue; 
			}
			else // RED == sibling->_color
			{
				// case 5
				// parent : black, sibling : red, sibling left : black, sibling right : black
				parent->_color = RED;
				sibling->_color = BLACK;
				if (left)
				{
					leftRotate(parent);
					sibling = parent->_right;
				}
				else
				{
					rightRotate(parent);
					sibling = parent->_left;
				}
				continue;
			}
		}

		if (BLACK == sibling->_color &&
			((left && RED == sibling->_left->_color && BLACK == sibling->_right->_color)
				|| (!left && BLACK == sibling->_left->_color && RED == sibling->_right->_color)))
		{
			// case 3
			// parent : all, sibling : black, sibling left : red, sibling right : black
			if (left)
			{
				rightRotate(sibling);
				parent->_right->_color = BLACK;
				parent->_right->_right->_color = RED;
				sibling = parent->_right;
			}
			else
			{
				leftRotate(sibling);
				parent->_left->_color = BLACK;
				parent->_left->_left->_color = RED;
				sibling->_parent->_left;
			}
		}
		
		if (BLACK == sibling->_color && ((left && RED == sibling->_right->_color) || (!left && RED == sibling->_left->_color)))
		{
			// case 2
			// parent : all, sibling : black, sibling left : all, sibling right : red
			left ? leftRotate(parent) : rightRotate(parent);
			NODE_COLOR temp = parent->_color;
			parent->_color = sibling->_color;
			sibling->_color = temp;
			left ? sibling->_right->_color = BLACK : sibling->_left->_color = BLACK;
			break; 
		}
	}
}

void RedBlackTree::leftRotate(Node* node)
{
	if (_nil == node || _nil == node->_right)
		return;

	Node* temp = node->_right;
	node->_right = node->_right->_left;
	if(_nil != node->_right)
		node->_right->_parent = node;
	temp->_left = node;
	temp->_parent = node->_parent;
	if (nullptr != node->_parent)
	{
		if (node->_parent->_left == node)
			node->_parent->_left = temp;
		else
			node->_parent->_right = temp;
	}
	node->_parent = temp;
	if (_root == node)
		_root = temp;
}

void RedBlackTree::rightRotate(Node* node)
{
	if (_nil == node || _nil == node->_left)
		return;

	Node* temp = node->_left;
	node->_left = node->_left->_right;
	if(_nil != node->_left)
		node->_left->_parent = node;
	temp->_right = node;
	temp->_parent = node->_parent;
	if (nullptr != node->_parent)
	{
		if (node->_parent->_left == node)
			node->_parent->_left = temp;
		else
			node->_parent->_right = temp;
	}
	node->_parent = temp;
	if (_root == node)
		_root = temp;
}

bool RedBlackTree::checkNil(Node* node)
{
	if (_nil != node)
	{
		return checkNil(node->_left) && checkNil(node->_right);
	}
	else
	{
		if (_nil != node)
			return false;
		if (nullptr != node->_left || nullptr != node->_right)
			return false;
		if (None != node->_value)
			return false;
		if (BLACK != node->_color)
			return false;
		if (nullptr != node->_parent)
			return false;
	}

	return true;
}

bool RedBlackTree::checkRedNode(Node* node)
{
	if (RED == node->_color)
		if (BLACK != node->_left->_color || BLACK != node->_right->_color)
			return false;

	bool ret = true;

	if (nullptr != node->_left)
		ret = checkRedNode(node->_left);
	if (nullptr != node->_right)
		ret = (ret && checkRedNode(node->_right));

	return ret;
}

bool RedBlackTree::checkBlackNodeCount(Node* node, int count, int& result)
{
	if (_nil == node)
	{
		if (-1 == result)
		{
			result = count;
			return true;
		}
		
		if (count != result)
			return false;
		else
			return true;
	}
	else
	{
		if (BLACK == node->_color)
			count++;

		return checkBlackNodeCount(node->_left, count, result) && checkBlackNodeCount(node->_right, count, result);
	}
}

RedBlackTree::RedBlackTree(fnCompare comparer, fnShow shower)
	: _root(nullptr), _comparer(comparer), _shower(shower)
{
	_nil = new Node(None, nullptr, BLACK, true);
	_root = _nil;
}

RedBlackTree::~RedBlackTree()
{
	clear(_root);

	if (nullptr != _nil)
	{
		delete _nil;
		_nil = nullptr;
	}
}

bool RedBlackTree::Search(TreeValue value)
{
	Node* parent = nullptr;
	int comp = 0;
	if (nullptr == search(value, parent, comp))
		return false;
	else
		return true;
}

bool RedBlackTree::Insert(TreeValue value)
{
	if (nullptr == _nil)
		return false;

	if (_nil == _root)
	{
		_root = new Node(value, nullptr, BLACK);
		if (nullptr == _root)
			return false;
		_root->_left = _nil;
		_root->_right = _nil;
		return true;
	}
	else
	{
		Node* parent = nullptr;
		int comp = 0;
		Node* found = search(value, parent, comp);
		if (_nil == found)
		{
			found = new Node(value, parent);
			if (nullptr == found)
				return false;
			found->_left = _nil;
			found->_right = _nil;
			if (nullptr != parent)
			{
				if (0 < comp)
					parent->_right = found;
				else
					parent->_left = found;
			}
			reconstructionAfterInsertion(found, 0 > comp);
			return true;
		}
		else
			return false;
	}

	return false;
}

bool RedBlackTree::Delete(TreeValue value)
{
	if (_nil == _root)
		return false;

	Node* parent = nullptr;
	int comp = 0;
	Node* found = search(value, parent, comp);
	if (_nil == found)
		return false;

	Node** parentChild = nullptr == parent ? &_root : found == parent->_left ? &(parent->_left) : &(parent->_right);
	Node* child = found->_left != _nil ? found->_left : found->_right;
	NODE_COLOR deleteNodeColor = BLACK;
	if (_nil == found->_left || _nil == found->_right)
	{
		if(_nil != child)
			child->_parent = parent;
		*parentChild = child;
		
		deleteNodeColor = found->_color;
	}
	else
	{
		while (_nil != child->_right)
			child = child->_right;
		Node* childParent = child->_parent;

		*parentChild = child;
		child->_parent = parent;
		child->_right = found->_right;
		child->_right->_parent = child;

		deleteNodeColor = child->_color;
		child->_color = found->_color;

		if (childParent != found)
		{
			childParent->_right = child->_left;
			if (_nil != child->_left)
				child->_left->_parent = childParent;

			child->_left = found->_left;
			child->_left->_parent = child;

			// restore for reconstructionAfterDeletion
			child = childParent->_right;
			parent = childParent;
		}
		else
		{
			// restore for reconstructionAfterDeletion
			parent = child;
			child = child->_left;
		}
	}

	if (BLACK == deleteNodeColor)
	{
		if (RED == child->_color)
			child->_color = BLACK;
		else
			reconstructionAfterDeletion(child, parent);
	}

	delete found;
	_root->_parent = nullptr;
	_root->_color = BLACK;
	return true;
}

void RedBlackTree::Clear()
{
	clear(_root);
}

void RedBlackTree::Show()
{
	show(_root, 0);
}

bool RedBlackTree::CheckIntegrity()
{
	if (_nil == _root)
		return true;

	if (RED == _root->_color)
		return false;

	if (true != checkNil(_root))
		return false;

	if (true != checkRedNode(_root))
		return false;

	int result = -1;
	return checkBlackNodeCount(_root, 0, result);
}
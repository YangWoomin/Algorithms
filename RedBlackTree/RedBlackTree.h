#pragma once

#include <string>

namespace YangAlgorithms
{
	class RedBlackTree
	{
	public:
		typedef void* TreeValue;
		static const TreeValue None;
		enum NODE_COLOR
		{
			RED = 0,
			BLACK = 1,
		};
		static const std::string NODE_COLOR_NAME[];

	private:
		// return value : equal to 0(found), less than 0(left), larger than 0(right)
		typedef int (*fnCompare)(TreeValue /*value in node*/, TreeValue /*searching value*/);
		typedef void (*fnShow)(TreeValue, NODE_COLOR color, int deepCount);

		struct Node
		{
			TreeValue _value;
			Node* _left;
			Node* _right;
			Node* _parent;
			NODE_COLOR _color;

			Node(TreeValue value, Node* parent, NODE_COLOR color = RED, bool nil = false) : 
				_value(value), 
				_left(nullptr), 
				_right(nullptr), 
				_parent(parent), 
				_color(color)
			{

			}
		};

		Node* _root;
		Node* _nil;
		fnCompare _comparer;
		fnShow _shower;

		Node* search(TreeValue value, Node*& parent, int& comp);
		void clear(Node* node);
		void show(Node* node, int deepCount);

		// red black tree rules
		// 1. all nodes are red or black
		// 2. root node is black
		// 3. all leaf nodes are black
		// 4. red nodes must have child node(s) of black
		// 5. the count of black nodes is same from any leaf node to root node
		void reconstructionAfterInsertion(Node* node, bool left);
		void reconstructionAfterDeletion(Node* child, Node* parent);
		void leftRotate(Node* node);
		void rightRotate(Node* node);
		bool checkNil(Node* node);
		bool checkRedNode(Node* node);
		bool checkBlackNodeCount(Node* node, int count, int& result);

	public:
		RedBlackTree(fnCompare comparer, fnShow shower);
		~RedBlackTree();
		bool Search(TreeValue value);
		bool Insert(TreeValue value);
		bool Delete(TreeValue value);
		void Clear();
		void Show();
		bool CheckIntegrity();
	};
}
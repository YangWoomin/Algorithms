#include "RedBlackTree.h"

#include <Windows.h>
#include <iostream>

using namespace std;
using namespace YangAlgorithms;

#define TEXT(X) #X

int comparer(RedBlackTree::TreeValue value1, RedBlackTree::TreeValue value2)
{
	return (int)value2 - (int)value1;
}

void shower(RedBlackTree::TreeValue value, RedBlackTree::NODE_COLOR color, int deepCount)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	for (int i = 0; i < deepCount; ++i)
		std::cout << "*";

	if (RedBlackTree::RED == color)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		
	std::cout << (int)value << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

int main()
{
	RedBlackTree rbt(comparer, shower);
	rbt.Insert((RedBlackTree::TreeValue)5);
	rbt.Insert((RedBlackTree::TreeValue)6);
	rbt.Insert((RedBlackTree::TreeValue)12);
	rbt.Insert((RedBlackTree::TreeValue)4);
	rbt.Insert((RedBlackTree::TreeValue)1);
	rbt.Insert((RedBlackTree::TreeValue)55);
	rbt.Insert((RedBlackTree::TreeValue)80);
	rbt.Insert((RedBlackTree::TreeValue)9);
	rbt.Insert((RedBlackTree::TreeValue)8);
	rbt.Insert((RedBlackTree::TreeValue)11);
	rbt.Insert((RedBlackTree::TreeValue)17);
	rbt.Insert((RedBlackTree::TreeValue)19);
	rbt.Insert((RedBlackTree::TreeValue)21);
	rbt.Insert((RedBlackTree::TreeValue)77);
	rbt.Insert((RedBlackTree::TreeValue)35);
	rbt.Insert((RedBlackTree::TreeValue)44);
	rbt.Insert((RedBlackTree::TreeValue)18);
	rbt.Insert((RedBlackTree::TreeValue)7);
	rbt.Insert((RedBlackTree::TreeValue)66);
	rbt.Insert((RedBlackTree::TreeValue)99);
	rbt.Insert((RedBlackTree::TreeValue)87);
	rbt.Insert((RedBlackTree::TreeValue)29);
	rbt.Insert((RedBlackTree::TreeValue)30);
	rbt.Insert((RedBlackTree::TreeValue)70);
	rbt.Insert((RedBlackTree::TreeValue)65);
	rbt.Insert((RedBlackTree::TreeValue)47);
	rbt.Insert((RedBlackTree::TreeValue)48);
	rbt.Insert((RedBlackTree::TreeValue)49);
	rbt.Insert((RedBlackTree::TreeValue)50);
	rbt.Insert((RedBlackTree::TreeValue)51);
	rbt.Insert((RedBlackTree::TreeValue)52);
	rbt.Insert((RedBlackTree::TreeValue)53);
	rbt.Insert((RedBlackTree::TreeValue)54);
	rbt.Insert((RedBlackTree::TreeValue)56);

	rbt.Delete((RedBlackTree::TreeValue)49);

	rbt.Show();

	std::cout << std::endl;

	if (true == rbt.CheckIntegrity())
		std::cout << "checking rbt integrity succeeded" << std::endl;
	else
		std::cout << "checking rbt integrity failed" << std::endl;
}
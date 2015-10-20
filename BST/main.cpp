#include "BST.h"
#include <iostream>
using namespace std;



int main()
{
	BST<int> tree;
	tree.add(44);
	tree.add(77);
	tree.add(55);
	tree.add(22);
	tree.add(99);
	tree.add(33);
	tree.add(88);

	cout << "Tree inorder:\n";
	tree.inorder(cout,tree.getRoot());

	cout<<"\n-----------------------------------------\n";
	BST<int> tree2;
	tree2.add(48);
	tree2.add(69);
	tree2.add(60);
	tree2.add(22);
	tree2.add(99);
	tree2.add(30);
	tree2.add(88);

	cout << "Tree2 inorder:\n";
	tree2.inorder(cout,tree2.getRoot());


	cout << "\n\nTree and Tree2 are ";
	if(tree==tree2)
		cout <<"same";
	else
		cout <<"Not same";


	int key = 77;
	cout << "\n\nsearching "<<key<<": ";
	BSTNode<int> * t = tree.search(key,tree.getRoot());
	if(t == NULL)
		cout << "Not found";
	else
	{
		cout << "found\nvalue:"<<t->getValue()<<"\nParent : ";
		t->getParent()?cout << t->getParent()->getValue():cout <<"No parent";//age root bashe va parentesh null bashe value nadare
	}
	cout<<"\n-----------------------------------------\n";

	try
	{
		key = 44;
		cout << "\nRemoving "<<key<<" :\n";
		tree.remove(key);
		cout << "New Tree inorder:\n";
		tree.inorder(cout,tree.getRoot());
	}
	catch(exception ex)
	{
		cout << ex.what();
	}

	try
	{
		key = 73;
		cout << "\nRemoving "<<key<<" :\n";
		tree.remove(key);
		cout << "New Tree inorder:\n";
		tree.inorder(cout,tree.getRoot());
	}
	catch(exception ex)
	{
		cout << ex.what();
	}


	cout << "\n\nTree and Tree2 are ";
	if(tree==tree2)
		cout <<"same";
	else
		cout <<"Not same";


	BST<int> tree3;
	tree3.add(44);
	tree3.add(77);
	tree3.add(55);
	tree3.add(22);
	tree3.add(99);
	tree3.add(33);
	tree3.add(88);

	cout << "\n-------------------------\nTree3 inorder:\n";
	tree3.inorder(cout,tree3.getRoot());
	cout << "\nTree2 inorder:\n";
	tree3.inorder(cout,tree2.getRoot());
	cout << "\n\nTree3 and Tree2 are ";
	if(tree3==tree2)
	{
		cout <<"same\nLet's Copy 2 to 3:";
		try
		{
			tree2.copy(tree3);
			cout << "\nTree3 inorder:\n";
			tree3.inorder(cout,tree3.getRoot());
			cout << "\nTree2 inorder:\n";
			tree3.inorder(cout,tree2.getRoot());
		}
		catch(exception ex)
		{
			cout << ex.what();
		}
	}
	else
		cout <<"Not same/ncen not copy";


	cin.ignore();
	cin.get();
	return 0;
}
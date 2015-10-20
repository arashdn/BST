#pragma once
#include <stdlib.h> // for NULL
#include <iostream>
#include <stdexcept>

//Coments are written in Persian

template <class T>
class BSTNode
{
public:
	BSTNode()
	{
		parent = NULL;
		leftChild = NULL;
		rightChild = NULL;
	}
	BSTNode(T val)
	{
		value = val;
		parent = NULL;
		leftChild = NULL;
		rightChild = NULL;
	}
	BSTNode(T val , BSTNode * prnt)
	{
		value = val;
		parent = prnt;
		leftChild = NULL;
		rightChild = NULL;
	}

	template <class T>
	friend class BST;

	T getValue()
	{
		return value;
	}
	//void setValue(T v)
	//{
	//	value = v;
	//}

	//BSTNode<T> * getLeftChild()
	//{
	//	return leftChild;
	//}

	//BSTNode<T> * getRightChild()
	//{
	//	return rightChild;
	//}

	BSTNode<T> * getParent()
	{
		return parent;
	}
private:
	T value;
	BSTNode<T> * parent;
	BSTNode<T> * leftChild;
	BSTNode<T> * rightChild;
};


template <class T>
class BST
{
public:
	BST()
	{
		root = NULL;
	}
	bool isEmpty()
	{
		return !root;
	}

	void add(T val)
	{
		if(isEmpty())
		{
			root = new BSTNode<T>(val);
			return;
		}

		BSTNode<T> * temp = root;
		BSTNode<T> * parent = temp;
		while (temp)//while temp != NULL //while temp != 0
		{
			parent = temp;
			if(val<= temp->value)
				temp = temp->leftChild;
			else
				temp = temp->rightChild;
		}

		if(val<= parent->value)
			parent->leftChild = new BSTNode<T>(val,parent);
		else
			parent->rightChild = new BSTNode<T>(val,parent);
	}

	BSTNode<T> * search(T key,BSTNode<T> * s)
	{
		if(!s) // if s==NULL
			return NULL;//not found
		
		if(s->value == key)
			return s;

		if(key<s->value)
			return search(key,s->leftChild);
		else
			return search(key,s->rightChild);
	}

	void remove(T val)
	{
		BSTNode<T> * x = search(val,this->getRoot());//x --> nodi ke gharare hazf beshe
		if(!x) //if x == NULL
		{
			throw std::exception("Item not found.");
			return;
		}

		/*3 halat
		1. x barg bashe (rahat hazf mishe , hich farzandi nadare)
		2. x ye farzand dashte bashe ( farzand ro mizarim jash)
		3. x 2 ta farzand dashe bashe (yeki be rast mirim baad inghadr too chap mirim ta null beshe) va meghdaresho midim be x
		   hazf nodi ke peyda kardim chon farzand chap  nadare be soorate halat 1 ya 2 anjam mishe
		*/


		//aval check mikonim ke 2 farzand dare ya na , age dasht peymayesh ro anjam midim ta...
		BSTNode<T> * temp = x;
		if(x->leftChild != NULL && x->rightChild != NULL)
		{
			//aval yeki be rast:
			temp = x->rightChild;
			//baad inghadr too chap pish mirim ta NULL beshe
			while (temp->leftChild != NULL)
				temp = temp->leftChild;
			
			//hala meghdar temp ro mizarim too x
			x->value = temp->value;

			//hala mikhaym temp hazf beshe , bedoone shak temp farzand chap nadare , pass ya ye farzand dare ya farzand nadare
			//temp ro mizarim too x va ejaze midim tabe khodesh dar marhale baad hazfesh kone :)
			x = temp;
		}

		//halate ke 1 farzand bashe ya aslan farzand nabashe
		if(x->leftChild == NULL) // faghat farzand rast darim:
			temp = x->rightChild;
		else if(x->rightChild == NULL) // faghat farzand chap darim:
			temp = x->leftChild;
		else
			throw std::exception("Fatal error");//barname hich vaght nabayad vared inja beshe.

		//age mikhaym root ro hazf konim bayad link root ro update konim:
		if ( x->parent == NULL)//agar root bood
			root = temp;
		else if( x == x->parent->leftChild) //agar x farzand chap bashe
			x->parent->leftChild = temp;
		else if( x == x->parent->rightChild) //agar x farzand rast bashe
			x->parent->rightChild = temp;
		else
			throw std::exception("Fatal error");//barname hich vaght nabayad vared inja beshe.


		delete [] x;
	}

	std::ostream& inorder(std::ostream& os , BSTNode<T> * node)
	{
	
		if(node->leftChild)
			inorder(os,node->leftChild);
		os << node->value<<"  ";
		if(node->rightChild)
			inorder(os,node->rightChild);
		return os;

	}

	BSTNode<T> * getRoot()
	{
		return root;
	}

	bool operator==(BST<T> b)
	{
		if(isEmpty() && b.isEmpty())
			return true;
		if(isEmpty())
			return false;
		if(b.isEmpty())
			return false;
		return areSame(getRoot(),b.getRoot());
	}

	void copy(BST <T> dest)
	{
		if (!(*this==dest))
		{
			throw std::exception("To copy Trees must be same");
			return;
		}

		copyNode(getRoot(),dest.getRoot());
	}

private:

	static bool areSame(BSTNode<T> * a,BSTNode<T> *b)
	{

		/* 3a=halat darim
		1.age har 2 ta null bashan baraban
		2.age yeki null va yeki gheire null bashe barabar nistan
		3.age har 2 ta null nabashan bayad 2 mored baresi beshe:
			a.barabar boodan farzande rast
			b.barabar boodan farzande chap
		*/

		if(a == NULL && b == NULL)
			return true;
		else if((a == NULL && b!=NULL) || (a!=NULL && b == NULL))
			return false;
		else
			return(areSame(a->leftChild,b->leftChild)&&areSame(a->rightChild,b->rightChild));

	}
	static void copyNode(BSTNode<T> * src,BSTNode<T> *dst)
	{
		/*moshabehe algorithm areSame ...
		aval value copy mishe
		baad age farzande chap dashte bashe oon
		va age farzande rast dashte bashe oonam copy mishe
		*/
		dst->value = src->value;
		if(src->leftChild != NULL)
			copyNode(src->leftChild,dst->leftChild);
		if(src->rightChild != NULL)
			copyNode(src->rightChild,dst->rightChild);
	}
	BSTNode<T> * root;
};

#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

int SetNode::getSize()
{
	return length;
}

void SetNode::resizeSecond()
{
	TValue* aux = new TValue[capacity];
	for (int i = 0; i < length; i++)
		aux[i] = element.second[i];

	capacity *= 2;
	element.second = new TValue[capacity];
	for (int i = 0; i < length; i++)
		element.second[i] = aux[i];
	delete[] aux;
}

void SortedMultiMap::deleteTree(node current)
{
	if (current != nullptr)
	{
		deleteTree(current->left);
		deleteTree(current->right);
		//delete[] &current->element;
		delete current;
	}
}

void SortedMultiMap::rearange(node current, node change)
{
	while (current->left != nullptr)
		current = current->left;
	current->left = change;
}

void SortedMultiMap::addRec(node current, TKey c, TValue v)
{
	if (c == current->element.first)
	{
		current->element.second[current->length] = v;
		current->length++;
		if (current->length == current->capacity)
			current->resizeSecond();
		nrElem++;
	}
	else if (rel(c, current->element.first))
	{
		if (current->left == nullptr)
		{
			TElem a;
			a.first = c;
			a.second = new TValue[2];
			a.second[0] = v;
			node aux = new SetNode(a, current, nullptr, nullptr, 1, 2);
			current->left = aux;
			nrElem++;
			nrOfKeys++;
		}
		else
			addRec(current->left,c,v);
	}
	else
	{
		if (current->right == nullptr)
		{
			TElem a;
			a.first = c;
			a.second = new TValue[2];
			a.second[0] = v;
			node aux = new SetNode(a, current, nullptr, nullptr, 1, 2);
			current->right = aux;
			nrElem++;
			nrOfKeys++;
		}
		else
			addRec(current->right,c,v);
	}
}

bool SortedMultiMap::remRec(node current, TKey c, TValue v)
{
	if (current == nullptr)
		return false;
	if (current->element.first == c)
	{
		bool arg = current->removeValue(v);
		if (arg == false)
			return false;
		if (current->length == 0)
		{
			bool rig = false;
			node aux = current, parent = current->parent;
			if (parent->right != nullptr)
			{
				if (parent->right->element.first == c)
				{
					if (current->right != nullptr)
					{
						if (current->left != nullptr)
						{
							rearange(current->right, current->left);
						}
						parent->right = current->right;
						parent->right->parent = parent;
					}
					else if (current->left != nullptr)
					{
						parent->right = current->left;
						parent->right->parent = parent;
					}
					else
						parent->right = nullptr;
					rig = true;
				}
			}
			if(rig == false)
			{
				if (current->right != nullptr)
				{
					if (current->left != nullptr)
					{
						rearange(current->right, current->left);
					}
					parent->left = current->right;
					parent->left->parent = parent;
				}
				else if (current->left != nullptr)
				{
					parent->left = current->left;
					parent->left->parent = parent;
				}
				else
					parent->left = nullptr;
			}
			
			delete aux;
			nrOfKeys--;
		}
		if (arg)
		{
			nrElem--;
			return true;
		}
	}
	else if (rel(c, current->element.first))
		return remRec(current->left,c,v);
	else
		return remRec(current->right,c,v);
}

SortedMultiMap::SortedMultiMap(Relation r) {
	nrElem = 0;
	nrOfKeys = 0;
	rel = r;
	root = nullptr;
}

void SortedMultiMap::add(TKey c, TValue v) {
	if (root != nullptr)
	{
		addRec(root, c, v);
	}
	else
	{
		TElem a;
		a.first = c;
		a.second = new TValue[2];
		a.second[0] = v;
		node aux = new SetNode(a, nullptr, nullptr, nullptr, 1, 2);
		root = aux;
		nrOfKeys++;
		nrElem++;
	}
}

vector<TValue> SortedMultiMap::search(TKey c) const {

	if (root != nullptr)
	{
		node current = root;
		while (current != nullptr)
		{
			if (c == current->element.first)
			{
				vector<TValue> aux;
				for (int i = 0; i < current->length; i++)
					aux.push_back(current->element.second[i]);
				return aux;
			}
			else if (rel(c, current->element.first))
				current = current->left;
			else
				current = current->right;
		}
	}
	return vector<TValue>();
}

bool SortedMultiMap::remove(TKey c, TValue v) {
	if (root != nullptr)
	{
		if (root->element.first == c)
		{
			bool arg = root->removeValue(v);
			if (arg == false)
				return false;
			if (root->length == 0)
			{
				node p = root;
				if (root->right != nullptr)
				{
					rearange(root->right, root->left);
					root = root->right;
					root->parent = nullptr;
				}
				else if (root->left != nullptr)
				{
					root = root->left;
					root->parent = nullptr;
				}
				else
					root = nullptr;
				delete p;
				nrOfKeys--;

			}
			if (arg)
			{
				nrElem--;
				return true;
			}
		}
		return remRec(root, c, v);
	}

	return false;
}


int SortedMultiMap::size() const {
	return nrElem;
}

bool SortedMultiMap::isEmpty() const {
	return root == nullptr;
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
	deleteTree(root);
}

SetNode::SetNode(TElem e,node p, node r, node l, int le, int cap)
{
	element = e;
	right = r;
	left = l;
	parent = p;
	length = le;
	capacity = cap;
}

bool SetNode::removeValue(TValue v)
{
	int pos = 0;
	while (v != element.second[pos] && pos<length)
		pos++;
	if (pos == length)
		return false;
	for (int i = pos; i < length - 1; i++)
		element.second[i] = element.second[i + 1];
	length--;
	return true;
}

TElem SetNode::getElement()
{
	return element;
}

node SetNode::goRight()
{
	return right;
}

node SetNode::goLeft()
{
	return left;
}

node SetNode::goUp()
{
	return parent;
}

#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	first();
}

void SMMIterator::first() {
	index = 0;
	direction = 1;
	if (!map.isEmpty())
	{
		current = map.root;
		while (!past.empty())
			past.pop();
		while (current->goLeft() != nullptr)
		{
			past.push(current);
			current = current->goLeft();
		}
	}
	else
	{
		current = nullptr;
		while (!past.empty())
			past.pop();
	}
}

void SMMIterator::next(){
	if (!valid())
		throw exception();
	if (index == current->getSize() - 1)
	{
		if (direction == 1)
		{
			if (current->goRight() != nullptr)
			{
				current = current->goRight();
				direction = 0;
			}
			else
				direction = 2;
		}
		if (direction == 0)
		{
			if (current->goLeft() != nullptr)
			{
				while (current->goLeft() != nullptr)
				{
					past.push(current);
					current = current->goLeft();
				}
			}
			else
				direction = 1;
		}
		if (direction == 2)
		{
			if (!past.empty())
			{
				direction = 1;
				current = past.top();
				past.pop();
			}
			else
				current = nullptr;
		}
		index = 0;
	}
	else
		index++;
}

bool SMMIterator::valid() const{
	return current != nullptr;
}

TElem SMMIterator::getCurrent() const{
	if(valid())
		return current->getElement();
	throw exception();
}



#pragma once

#include "SortedMultiMap.h"
#include <stack>


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);

	int index, direction; // 0 - left, 1 - right, 2 - middle
	node current;
	stack<node> past;

public:
	void first();
	void next();
	bool valid() const;
	std::pair<TKey, TValue> getCurrent() const;
};


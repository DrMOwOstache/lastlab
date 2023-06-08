#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue*> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue*>(-111111, nullptr);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);

class SetNode;

typedef SetNode* node;

class SetNode
{
private:
    TElem element;
    int capacity;
    int length;
    node right;
    node left;
    node parent;
public:
    friend class SortedMultiMap;
    SetNode(TElem e,node p, node r, node l, int le, int cap);
    bool removeValue(TValue v);
    TElem getElement();
    node goRight();
    node goLeft();
    node goUp();

    int getSize();
    void resizeSecond();
};



class SortedMultiMap {
    friend class SMMIterator;
private:
    
    node root;
    int nrElem;
    int nrOfKeys;
    Relation rel;

   
    void deleteTree(node current);
    void rearange(node current, node change);

    void addRec(node current, TKey c, TValue v);
    bool remRec(node current, TKey c, TValue v);
public:

    // constructor
    SortedMultiMap(Relation r);

    //adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

    //returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

    //removes a key value pair from the sorted multimap
    //returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    // destructor
    ~SortedMultiMap();
};
